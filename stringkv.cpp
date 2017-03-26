#include "graph.h"


typedef struct __label_string_t {
    vid_t src_id;
    char* dst_id;
} label_string_t;

void stringkv_t::batch_update(const string& src, const string& dst)
{
    vid_t src_id;
    char* dst_id;
    index_t index = 0;
    label_string_t* edges = (label_string_t*) buf;
    map<string, vid_t>::iterator str2vid_iter = str2vid.find(src);
    if (str2vid.end() == str2vid_iter) {
        src_id = vert_count++;
        str2vid[src] = src_id;
    } else {
        src_id = str2vid_iter->second;
    }
    
    dst_id = gstrdup(dst.c_str());
    index = count++;
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
}
    
void stringkv_t::make_graph_baseline()
{
    if (count == 0) return;
    
    flag1_count = __builtin_popcountll(flag1);
    kv_out = prep_lkv(flag1, flag1_count);
    
    edgeT_t<char*>* edges = (edgeT_t<char*>*) buf;
    fill_adj_list_kv(kv_out, flag1,  edges, count);
    
}
//super bins memory allocation
lkv_t<char*>* stringkv_t::prep_lkv(sflag_t ori_flag, tid_t flag_count)
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

void stringkv_t::fill_adj_list_kv(lkv_t<char*>* lkv_out, sflag_t flag1,
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
        src_index = __builtin_popcountll(flag1_mask);
        
        lkv_out[src_index].kv[vert1_id] = dst;
    }
}

    
void stringkv_t::store_graph_baseline(string dir)
{
    if (count == 0) return;

    //XXX it is wrong, we are writing the char*, not the string
    string file = dir + p_name + ".kv_out";
    FILE* f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(kv_out, sizeof(int64_t), vert_count, f);
    fclose(f);
}
