#pragma once

#include "graph.h"


template <class T>
void atoT(string value, T* num)
{
    assert(0);
}


template <>
inline void atoT(string value, uint32_t* num)
{
    sscanf(value.c_str(), "%d", num);
}

template <>
inline void atoT(string value, uint64_t* num)
{
    sscanf(value.c_str(), "%ld", num);
}

//generic number class
//
template <class T>
class numkv_t : public pkv_t 
{
  protected:
    lkv_t<T>* lkv_out; 
    
  public:
    void batch_update(const string& src, const string& dst);
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    lkv_t<T>* prep_lkv(sflag_t ori_flag, tid_t flag_count);
    void fill_adj_list_kv(lkv_t<T>* lkv_out, sflag_t flag1,
                              edgeT_t<T>* edges, index_t count);
};

template<class T>
void numkv_t<T>::batch_update(const string& src, const string& dst)
{
    vid_t src_id;
    T     dst_id;
    index_t index = 0;
    edgeT_t<T>* edges = (edgeT_t<T>*) buf;

    map<string, vid_t>::iterator str2vid_iter = g->str2vid.find(src);
    if (g->str2vid.end() == str2vid_iter) {
        assert(0);
    } else {
        src_id = str2vid_iter->second;
    }
    
    tid_t type_id = TO_TID(src_id);
    flag1 |= (1L << type_id);

    atoT<T>(dst, &dst_id);


    index = count++;
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
}

template<class T>
void numkv_t<T>::make_graph_baseline()
{
    if (count == 0) return;

    edgeT_t<T>* edges = (edgeT_t<T>*) buf;
   
    flag1_count = __builtin_popcountll(flag1);
    
    //super bins memory allocation
    lkv_out  = prep_lkv(flag1, flag1_count);

    //populate and get the original count back
    //handle kv_out as well.
    fill_adj_list_kv(lkv_out, flag1,  edges, count);
}

template<class T>
void numkv_t<T>::fill_adj_list_kv(lkv_t<T>* lkv_out, sflag_t flag1,
                              edgeT_t<T>* edges, index_t count)
{
    sid_t src;
    T dst;
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

template <class T>
void numkv_t<T>::store_graph_baseline(string dir)
{
    if (count == 0) return;

    /*
    string file = dir + p_name + ".kv_out";
    FILE* f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(kv_out, sizeof(int64_t), vert_count, f);
    fclose(f);
    */
}

//super bins memory allocation
template<class T>
lkv_t<T>* numkv_t<T>::prep_lkv(sflag_t ori_flag, tid_t flag_count)
{
    sflag_t flag = ori_flag;
    lkv_t<T>*  lkv  = (lkv_t<T>*) calloc (sizeof(lkv_t<T>), flag_count);
    tid_t      pos  = 0;
    sid_t      super_id;
    vid_t      v_count;

    for(tid_t i = 0; i < flag_count; i++) {
        pos = __builtin_ctz(flag);
        flag ^= (1L << pos);//reset that position
        super_id = g->get_type_scount(pos);
        v_count = TO_VID(super_id);
        lkv[i].kv = (T*)calloc(sizeof(T), v_count);
        lkv[i].super_id = super_id;
    }
    return lkv;
}
