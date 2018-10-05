#include "graph.h"
#include "stringkv.h"


cfinfo_t* stringkv_t::create_instance()
{
    return new stringkv_t;
}

status_t stringkv_t::batch_edge(edgeT_t<char*>& edge)
{
    vid_t vid = TO_VID(edge.src_id);
    tid_t tid = TO_TID(edge.src_id);
    strkv_out[tid]->set_value(vid, edge.dst_id);
    return eOK;
}

status_t stringkv_t::batch_update(const string& src, const string& dst, propid_t pid /* = 0*/)
{
    /*
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

    src_id = g->get_sid(src.c_str());
    
    tid_t type_id = TO_TID(src_id);
    flag1 |= (1L << type_id);
    
    dst_id = gstrdup(dst.c_str());
    //dst_id = log_beg + log_head;
    //log_head += sizeof(dst.c_str());

    index = batch_info1[batch_count1].count++;
    edges = (edgeT_t<char*>*) batch_info1[batch_count1].buf;
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
    */
    return eOK;
}

void stringkv_t::make_graph_baseline()
{
    /*
    if (batch_info[batch_count].count == 0) return;

    flag1_count = __builtin_popcountll(flag1);
    
    //super bins memory allocation
    prep_strkv();

    //populate and get the original count back
    //handle kv_out as well.
    fill_kv_out();

    cleanup();
    */
}

void stringkv_t::prep_graph_baseline()
{
    sflag_t    flag = flag1;
    tid_t      pos  = 0;
    tid_t   t_count = g->get_total_types();
    
    if (0 == strkv_out) {
        strkv_out = (strkv_t**) calloc (sizeof(strkv_t*), t_count);
    }
    flag1_count = __builtin_popcountll(flag);
    for(tid_t i = 0; i < flag1_count; i++) {
        pos = __builtin_ctzll(flag);
        flag ^= (1L << pos);//reset that position
        if (0 == strkv_out[pos]) {
            strkv_out[pos] = new strkv_t;
            strkv_out[pos]->setup(pos);
        }
    }
    //return strkv_out;
}

void stringkv_t::fill_kv_out()
{
    /*
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
    }*/
}

void stringkv_t::file_open(const string& dir, bool trunc)
{
    if (strkv_out == 0) return;
    
    tid_t       t_count = g->get_total_types();
    
    //base name using relationship type
    string basefile;
    if (col_count) {
        basefile = dir + col_info[0]->p_name;
    } else {
        basefile = dir;
    }

    // For each file.
    for (tid_t i = 0; i < t_count; ++i) {
        if (strkv_out[i] == 0) continue;
        strkv_out[i]->file_open(basefile, trunc);
    }
}

void stringkv_t::store_graph_baseline(bool clean /*=false*/)
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
        if (strkv_out[i] == 0) continue;
        strkv_out[i]->read_vtable();
        //strkv_out[i]->read_etable();
    }
}

////////////////////////////////////////////////////////////////

strkv_t::strkv_t()
{
    kv = 0;
    tid = 0;
    //super_id = 0;
    log_head = 0;
    log_tail = 0;
    log_wpos = 0;
    vtf = -1;
    etf = -1;
}

void strkv_t::set_value(vid_t vid, const char* value)
{
    //Check if values are same;
    if (0 != strncmp(log_beg + kv[vid], value, strlen(value))) {
        kv[vid] = log_head;
        char* ptr = log_beg + log_head;
        log_head += strlen(value) + 1;
        assert(log_head < log_count);
        memcpy(ptr, value, strlen(value) + 1);
    }

    /*
    kv[vid] = ptr;
    dvt[dvt_count].vid = vid;
    dvt[dvt_count].offset = ptr - log_beg; 
    ++dvt_count;
    */
}

const char* strkv_t::get_value(vid_t vid)
{
    return log_beg + kv[vid];
}

void strkv_t::setup(tid_t t) 
{
    tid = t;
    vid_t v_count = g->get_type_scount(tid);
    
    kv = (sid_t*)calloc(sizeof(sid_t), v_count);
    
    //everything is in memory
    log_count = (1L << 28);//256*8 MB
    if (posix_memalign((void**)&log_beg, 2097152, log_count*sizeof(char))) {
        //log_beg = (sid_t*)calloc(sizeof(sid_t), log_count);
        perror("posix memalign edge log");
    }
    log_head = 0;
    log_tail = 0;
    log_wpos = 0;
    
    /*
    if (posix_memalign((void**) &dvt, 2097152, dvt_max_count*sizeof(disk_strkv_t*))) {
        perror("posix memalign vertex log");
    }*/
}

void strkv_t::persist_elog()
{
    //Make a copy
    sid_t wpos = log_wpos;
    //Update the mark
    log_wpos = log_head;
    write(etf, log_beg + wpos, log_head-wpos);
    //fwrite(log_beg+wpos, sizeof(char), log_head-wpos, etf);
}

void strkv_t::persist_vlog()
{
    /*
    //Make a copy
    sid_t count =  dvt_count;

    //update the mark
    dvt_count = 0;

    fwrite(dvt, sizeof(disk_strkv_t), count, vtf);*/
    vid_t v_count = g->get_type_vcount(tid);
    if (v_count != 0) {
        pwrite(vtf, kv, v_count*sizeof(sid_t), 0);
    }
}

void strkv_t::file_open(const string& filename, bool trunc)
{
    char  file_ext[16];
    sprintf(file_ext,"%u",tid);
    
    string vtfile = filename + file_ext + ".vtable";
    string etfile = filename + file_ext + ".etable";
    if (trunc) {
		etf = open(etfile.c_str(), O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
        //etf = fopen(etfile.c_str(), "wb");//append/write + binary
        //vtf = fopen(vtfile.c_str(), "wb");
		vtf = open(vtfile.c_str(), O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);

    } else {
	    etf = open(etfile.c_str(), O_RDWR|O_CREAT, S_IRWXU);
        //etf = fopen(etfile.c_str(), "r+b");//append/write + binary
	    vtf = open(vtfile.c_str(), O_RDWR|O_CREAT, S_IRWXU);
        //vtf = fopen(vtfile.c_str(), "r+b");
    }
        
    assert(etf != -1);
    assert(vtf != -1);
}

void strkv_t::read_etable()
{
    /*
    off_t size = 0; //XXX fsize(etfile.c_str());
    if (size == -1L) {
        assert(0);
    }
    sid_t edge_count = size/sizeof(char);
    fread(log_beg, sizeof(char), edge_count, etf);

    log_head = edge_count;
    log_wpos = log_head;
    */
}

void strkv_t::read_vtable()
{
    //read etf
    off_t size = fsize(etf);
    if (size == -1L) { assert(0); }
    
    if (size != 0) {
        sid_t edge_count = size/sizeof(char);
        read(etf, log_beg, sizeof(char)*edge_count);

        log_head = edge_count;
        log_wpos = log_head;
    }
    
    //read vtf 
    size = fsize(vtf);
    if (size == -1L) { assert(0); }
    
    if (size != 0) {
        vid_t vcount = size/sizeof(sid_t);
        assert(vcount == g->get_type_vcount(tid));
        vid_t max_vcount = g->get_type_scount(tid);
        kv = (sid_t*)calloc(sizeof(sid_t), max_vcount);
        read(vtf, kv, sizeof(sid_t)*vcount);
    }

    /*
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
    */
}

void strkv_t::prep_str2sid(map<string, sid_t>& str2sid)
{
    
    char* type_name = 0;
    sid_t super_id = TO_SUPER(tid);
    vid_t v_count = g->get_type_vcount(tid);
    
    //create the str2vid now
    for (vid_t vid = 0; vid < v_count; ++vid) {
        type_name = log_beg + kv[vid];
        str2sid[type_name] = super_id + vid;
    }

    /*
    if (log_head == 0) return;
    string dst;
    sid_t sid = TO_THIGH(super_id);
    for(sid_t v = sid; v < super_id; ++v) {
        dst = kv[v - sid];
        str2sid[dst] = v;
    } */
}
