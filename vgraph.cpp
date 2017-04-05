#include "graph.h"


vgraph_t::vgraph_t()
{
    buf = calloc(sizeof(vid_t), 1000000);
    count = 0; 
}

vgraph_t::~vgraph_t()
{
}

void vgraph_t::id2name(vid_t src_id, const string& src)
{
    index_t index = 0;
    char* dst_id = gstrdup(src.c_str());
    edgeT_t<char*>* edges = (edgeT_t<char*>*) buf;

    tid_t type_id = TO_TID(src_id);
    flag1 |= (1L << type_id);
    
    index = count++;
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
}

void vgraph_t::store_graph_baseline(string dir)
{
    if (count == 0) return;
}

const char* vgraph_t::get_value(tid_t tid, vid_t vid)
{
    return lkv_out[tid].kv[vid];
}
