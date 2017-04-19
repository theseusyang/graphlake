#include "graph.h"


vgraph_t::vgraph_t()
{
}

vgraph_t::~vgraph_t()
{
}

void vgraph_t::id2name(vid_t src_id, const string& src)
{
    index_t index = 0;
    char* dst_id = gstrdup(src.c_str());
    edgeT_t<char*>* edges;

    tid_t type_id = TO_TID(src_id);
    flag1 |= (1L << type_id);
    
    if (batch_info[batch_count].count == MAX_ECOUNT) {
        ++batch_count;
    }
    
    edges = (edgeT_t<char*>*) batch_info[batch_count].buf;
    index = batch_info[batch_count].count++;
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
}

const char* vgraph_t::get_value(tid_t tid, vid_t vid)
{
    return lkv_out[tid]->kv[vid];
}
