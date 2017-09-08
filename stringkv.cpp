#include "graph.h"
#include "stringkv.h"


cfinfo_t* stringkv_t::create_instance()
{
    return new stringkv_t;
}

status_t stringkv_t::batch_update(const string& src, const string& dst, propid_t pid /* = 0*/)
{
    vid_t src_id;
    char* dst_id;
    index_t index = 0;
    edgeT_t<char*>* edges;
    
    if (batch_info1[batch_count1].count == MAX_ECOUNT) {
        void* mem = alloc_buf();
        if (mem == 0) return eEndBatch;
        ++batch_count1;
        batch_info1[batch_count1].count = 0;
        batch_info1[batch_count1].buf = mem; 
    }

    map<string, vid_t>::iterator str2vid_iter = g->str2vid.find(src);
    if (g->str2vid.end() == str2vid_iter) {
        assert(0);
    } else {
        src_id = str2vid_iter->second;
    }
    
    tid_t type_id = TO_TID(src_id);
    flag1 |= (1L << type_id);
    
    dst_id = gstrdup(dst.c_str());
    //dst_id = log_beg + log_head;
    //log_head += sizeof(dst.c_str());

    index = batch_info1[batch_count1].count++;
    edges = (edgeT_t<char*>*) batch_info1[batch_count1].buf;
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
    return eOK;
}

void stringkv_t::make_graph_baseline()
{
    if (batch_info[batch_count].count == 0) return;

    flag1_count = __builtin_popcountll(flag1);
    
    //super bins memory allocation
    prep_strkv();

    //populate and get the original count back
    //handle kv_out as well.
    fill_kv_out();

    cleanup();
}

strkv_t** stringkv_t::prep_strkv()
{
    sflag_t    flag = flag1;
    tid_t      pos  = 0;
    tid_t   t_count = g->get_total_types();
    
    if (0 == strkv_out) {
        strkv_out = (strkv_t**) calloc (sizeof(strkv_t*), t_count);
    }

    for(tid_t i = 0; i < flag1_count; i++) {
        pos = __builtin_ctz(flag);
        flag ^= (1L << pos);//reset that position
        if (0 == strkv_out[pos]) {
            strkv_out[pos] = new strkv_t;
            strkv_out[pos]->setup(pos);
        }
    }
    return strkv_out;
}

void stringkv_t::fill_kv_out()
{
    sid_t src;
    char* dst;
    vid_t     vert1_id;
    tid_t     src_index;
    edgeT_t<char*>*   edges;
    index_t   count;

    for (int j = 0; j <= batch_count; ++j) { 
        edges = (edgeT_t<char*>*)batch_info[j].buf;
        count = batch_info[j].count;
    
        for (index_t i = 0; i < count; ++i) {
            src = edges[i].src_id;
            dst = edges[i].dst_id;
            
            vert1_id = TO_VID(src);
            src_index = TO_TID(src);
            strkv_out[src_index]->set_value(vert1_id, dst);
        }
    }
}

void stringkv_t::file_open(const string& dir, bool trunc)
{
    if (strkv_out == 0) return;
    
    char name[8];
    string postfix = "out";
    tid_t       t_count = g->get_total_types();
    
    //base name using relationship type
    string basefile, filename;
    if (col_count) {
        basefile = dir + col_info[0]->p_name;
    } else {
        basefile = dir;
    }

    // For each file.
    for (tid_t i = 0; i < t_count; ++i) {
        if (strkv_out[i] == 0) continue;
        //name = typekv->get_type_name(i);
        sprintf(name, "%d", i);
        filename = basefile + name + postfix;

        strkv_out[i]->file_open(filename, trunc);
    }
}

void stringkv_t::store_graph_baseline()
{
    if (strkv_out == 0) return;
    
    tid_t       t_count = g->get_total_types();
    
    // For each file.
    for (tid_t i = 0; i < t_count; ++i) {
        if (strkv_out[i] == 0) continue;

        strkv_out[i]->persist_vlog();
        strkv_out[i]->persist_elog();
    }
}

void stringkv_t::read_graph_baseline()
{
    tid_t   t_count = g->get_total_types();
    if (0 == strkv_out) {
        strkv_out  = (strkv_t**) calloc (sizeof(strkv_t*), t_count);
    }
    
    // For each file.
    for (tid_t i = 0; i < t_count; ++i) {

        strkv_out[i] = new strkv_t;
        strkv_out[i]->setup(i);
        strkv_out[i]->read_vtable();
        strkv_out[i]->read_etable();
    }
}

////////////////////////////////////////////////////////////////

strkv_t::strkv_t()
{
    kv = 0;
    super_id = 0;
    max_vcount = 0;
    
    //XXX everything is in memory
    log_count = (1L << 28);//256*8 MB
    if (posix_memalign((void**)&log_beg, 2097152, log_count*sizeof(char))) {
        //log_beg = (sid_t*)calloc(sizeof(sid_t), log_count);
        perror("posix memalign edge log");
    }
    log_head = 0;
    log_tail = 0;
    log_wpos = 0;
    
    dvt_count = 0;
    dvt_max_count = (1L << 28);
    if (posix_memalign((void**) &dvt, 2097152, 
                       dvt_max_count*sizeof(disk_strkv_t*))) {
        perror("posix memalign vertex log");    
    }
    vtf = 0;
    etf = 0;
}

void strkv_t::set_value(vid_t vid, char* value)
{
    char* ptr = log_beg + log_head;
    log_head += strlen(value) + 1;
    memcpy(ptr, value, strlen(value) + 1);
    free(value);

    kv[vid] = ptr;
    dvt[dvt_count].vid = vid;
    dvt[dvt_count].offset = ptr - log_beg; 
    ++dvt_count;
}

void strkv_t::setup(tid_t tid) 
{
    if ( 0 == super_id ) {
        super_id = g->get_type_scount(tid);
        vid_t v_count = TO_VID(super_id);
        max_vcount = (v_count << 1);
        kv = (char**)calloc(sizeof(char*), max_vcount);
    } else {
        super_id = g->get_type_scount(tid);
        vid_t v_count = TO_VID(super_id);
        if (max_vcount < v_count) {
            assert(0);
        }
    }
}

void strkv_t::persist_elog()
{
    //Make a copy
    sid_t wpos = log_wpos;
    
    //Update the mark
    log_wpos = log_head;
        
    fwrite(log_beg+wpos, sizeof(char), log_head-wpos, etf);
}

void strkv_t::persist_vlog()
{
    //Make a copy
    sid_t count =  dvt_count;

    //update the mark
    dvt_count = 0;

    fwrite(dvt, sizeof(disk_strkv_t), count, vtf);
}

void strkv_t::file_open(const string& filename, bool trunc)
{
    string vtfile = filename + ".vtable";
    string etfile = filename + ".etable";
    if (trunc) {
        etf = fopen(etfile.c_str(), "wb");//append/write + binary
        assert(etf != 0);
        vtf = fopen(vtfile.c_str(), "wb");
        assert(vtf != 0);

    } else {
        etf = fopen(etfile.c_str(), "r+b");//append/write + binary
        assert(etf != 0);
        vtf = fopen(vtfile.c_str(), "r+b");
        assert(vtf != 0);
    }
}

void strkv_t::read_etable()
{
    off_t size = 0; //XXX fsize(etfile.c_str());
    if (size == -1L) {
        assert(0);
    }
    sid_t edge_count = size/sizeof(char);
    fread(log_beg, sizeof(char), edge_count, etf);

    log_head = edge_count;
    log_wpos = log_head;
}

void strkv_t::read_vtable()
{
    off_t size = 0; //XXX fsize(vtfile.c_str());
    if (size == -1L) {
        assert(0);
    }
    vid_t count = (size/sizeof(disk_strkv_t));

    //read in batches
    while (count !=0) {
        vid_t read_count = fread(dvt, sizeof(disk_strkv_t), dvt_max_count, vtf);
        for (vid_t v = 0; v < read_count; ++v) {
            kv[dvt[v].vid] = log_beg + dvt[v].offset;
        }
        count -= read_count;
    }
    dvt_count = 0;
}

void strkv_t::prep_str2sid(map<string, sid_t>& str2sid)
{
    string dst;
    sid_t sid = TO_THIGH(super_id);
    for(sid_t v = sid; v < super_id; ++v) {
        dst = kv[v - sid];
        str2sid[dst] = v;
    } 
}
