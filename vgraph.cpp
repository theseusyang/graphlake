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

void vgraph_t::type_done()
{
    if (count == 0) return;
    
    flag1_count = __builtin_popcountll(flag1);
    kv_out = prep_lkv(flag1, flag1_count);
    
    edgeT_t<char*>* edges = (edgeT_t<char*>*) buf;
    fill_adj_list_kv(kv_out, flag1,  edges, count);
}

//super bins memory allocation
lkv_t<char*>* vgraph_t::prep_lkv(sflag_t ori_flag, tid_t flag_count)
{
    sflag_t flag = ori_flag;
    lkv_t<char*>*  lkv  = (lkv_t<char*>*) calloc (sizeof(lkv_t<char*>), flag_count);
    tid_t      pos  = 0;
    sid_t super_id;
    vid_t v_count;

    for(tid_t i = 0; i < flag_count; i++) {
        pos = __builtin_ctz(flag);
        flag ^= (1L << pos);//reset that position
        super_id = g->get_type_scount(pos);
        v_count = TO_VID(super_id);
        lkv[i].kv = (char**)calloc(sizeof(char*), v_count);
        lkv[i].super_id = super_id;
    }
    return lkv;
}

void vgraph_t::fill_adj_list_kv(lkv_t<char*>* lkv_out, sflag_t flag1,
                              edgeT_t<char*>* edges, index_t count)
{
    sid_t src;
    char*  dst;
    vid_t     vert1_id;
    tid_t     type1_id;
    sflag_t   flag1_mask;
    tid_t     src_index;
    
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        
        vert1_id = TO_VID(src);
        type1_id = TO_TID(src) + 1;
        flag1_mask = flag1 & ( (1L << type1_id) - 1);
        src_index = __builtin_popcountll(flag1_mask) - 1;
        
        lkv_out[src_index].kv[vert1_id] = dst;
    }
}

const char* vgraph_t::get_value(tid_t tid, vid_t vid)
{
    return kv_out[tid].kv[vid];
}
