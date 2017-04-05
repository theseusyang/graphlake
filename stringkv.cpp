#include "graph.h"

void stringkv_t::batch_update(const string& src, const string& dst)
{
    vid_t src_id;
    char* dst_id;
    index_t index = 0;
    edgeT_t<char*>* edges = (edgeT_t<char*>*) buf;

    map<string, vid_t>::iterator str2vid_iter = g->str2vid.find(src);
    if (g->str2vid.end() == str2vid_iter) {
        assert(0);
    } else {
        src_id = str2vid_iter->second;
    }
    
    tid_t type_id = TO_TID(src_id);
    flag1 |= (1L << type_id);
    
    dst_id = gstrdup(dst.c_str());
    index = count++;
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
}

void stringkv_t::store_graph_baseline(string dir)
{
    if (count == 0) return;
}
