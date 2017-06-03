#include "graph.h"
#include "stringkv.h"

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

void stringkv_t::store_graph_baseline(string dir)
{
    if (strkv_out == 0) return;
    
    string postfix = "out";

    //const char* name = 0;
    //typekv_t*   typekv = g->get_typekv();
    char name[8];
    tid_t       t_count = g->get_total_types();
    
    //base name using relationship type
    string basefile = dir + col_info[0]->p_name;
    string vtfile, etfile;

    // For each file.
    for (tid_t i = 0; i < t_count; ++i) {
        if (strkv_out[i] == 0) continue;
        //name = typekv->get_type_name(i);
        sprintf(name, "%d.", i);
        vtfile = basefile + name + "vtable" + postfix;
        etfile = basefile + name + "etable" + postfix;

        strkv_out[i]->persist_vlog(vtfile);
        strkv_out[i]->persist_elog(etfile);
    }
}


void strkv_t::persist_elog(const string& etfile)
{
    //Make a copy
    sid_t wpos = log_wpos;
    
    //Update the mark
    log_wpos = log_head;
        
    //Write the file.
    if (etf == 0) {
        etf = fopen(etfile.c_str(), "a+b");//append/write + binary
        assert(etf != 0);
    }
    fwrite(log_beg+wpos, sizeof(char), log_head-wpos, etf);
}

void strkv_t::persist_vlog(const string& vtfile)
{
    //Make a copy
    sid_t count =  dvt_count;

    //update the mark
    dvt_count = 0;

    //Write the file
    if(vtf == 0) {
        vtf = fopen(vtfile.c_str(), "a+b");
        assert(vtf != 0);
    }
    fwrite(dvt, sizeof(disk_strkv_t), count, vtf);
}

void strkv_t::read_etable(const string& etfile)
{
    if (etf == 0) {
        etf = fopen(etfile.c_str(), "r+b");//append/write + binary
        assert(etf != 0);
    }

    off_t size = fsize(etfile.c_str());
    if (size == -1L) {
        assert(0);
    }
    sid_t edge_count = size/sizeof(char);
    fread(log_beg, sizeof(char), edge_count, etf);

    log_head = edge_count;
    log_wpos = log_head;
}

void strkv_t::read_vtable(const string& vtfile)
{
    //Write the file
    if(vtf == 0) {
        vtf = fopen(vtfile.c_str(), "r+b");
        assert(vtf != 0);
    }

    off_t size = fsize(vtfile.c_str());
    if (size == -1L) {
        assert(0);
    }
    vid_t count = (size/sizeof(disk_vtable_t));

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
