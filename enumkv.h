#pragma once

#include "graph.h"

//generic enum class
template <class T>
class enumkv_t : public pkv_t {
  protected:
    lkv_t<T>* lkv_out; 
    lgraph_t* lgraph_in;
    
    //mapping between enum and string
    map<string, T> str2enum;
    char**      enum2str;
    T           ecount;
    T           max_count;

  public:
    enumkv_t();
    void init_enum(int enumcount);
    void populate_enum(const char* e);
    void batch_update(const string& src, const string& dst);
    void make_graph_baseline();
    void store_graph_baseline(string dir);

  public:

    lkv_t<T>* prep_lkv(sflag_t ori_flag, tid_t flag_count);

    void fill_adj_list_kv(lkv_t<T>* lkv_out, lgraph_t* lgraph_in, 
                 sflag_t flag1, edgeT_t<T>* edges, index_t count);

    void store_lkv(lkv_t<T>* lkv_out, string dir, string postfix);
    
    status_t filter(sid_set_t* sid_set, void* value, filter_fn_t fn);
    
};

template<class T>
void enumkv_t<T>::batch_update(const string& src, const string& dst)
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

    typename map<string, T>::iterator str2enum_iter = str2enum.find(dst);
    if (str2enum.end() == str2enum_iter) {
        dst_id = ecount++;
        str2enum[dst] = dst_id;
        enum2str[dst_id] = gstrdup(dst.c_str());
    } else {
        dst_id = str2enum_iter->second;
    }

    index = count++;
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
}

template<class T>
void enumkv_t<T>::make_graph_baseline()
{
    if (count == 0) return;
   
    flag1_count = __builtin_popcountll(flag1);
    
    //super bins memory allocation
    lkv_out  = prep_lkv(flag1, flag1_count);
    lgraph_in = prep_lgraph(ecount);    

    //estimate edge count
    edge_t* edges1 = (edge_t*) buf;
    calc_edge_count(lgraph_in, edges1, count);
    
    //prefix sum then reset the count
    prep_lgraph_internal(lgraph_in, ecount, count);
    
    //populate and get the original count back
    //handle kv_out as well.
    edgeT_t<T>* edges = (edgeT_t<T>*) buf;
    fill_adj_list_kv(lkv_out, lgraph_in, flag1, edges, count);
}

//super bins memory allocation
template<class T>
lkv_t<T>* enumkv_t<T>::prep_lkv(sflag_t ori_flag, tid_t flag_count)
{
    sflag_t flag = ori_flag;
    lkv_t<T>*  lkv  = (lkv_t<T>*) calloc (sizeof(lkv_t<T>), flag_count);
    tid_t      pos  = 0;
    sid_t super_id;
    vid_t v_count;

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

template<class T>
void enumkv_t<T>::fill_adj_list_kv(lkv_t<T>* lkv_out, lgraph_t* lgraph_in, 
                             sflag_t flag1, edgeT_t<T>* edges, index_t count)
{
    sid_t src;
    T         dst;
    vid_t     vert1_id;
    tid_t     type1_id;
    sflag_t   flag1_mask;
    tid_t     src_index;
    beg_pos_t* beg_pos_in = lgraph_in;
    
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        
        vert1_id = TO_VID(src);
        type1_id = TO_TID(src) + 1;
        flag1_mask = flag1 & ( (1L << type1_id) - 1);
        src_index = __builtin_popcountll(flag1_mask);
        
        lkv_out[src_index].kv[vert1_id] = dst;
        
        beg_pos_in[dst].adj_list[beg_pos_in->count++] = src;
    }
}


template<class T>
void enumkv_t<T>::store_lkv(lkv_t<T>* lkv_out, string dir, string postfix)
{
}

template<class T>
void enumkv_t<T>::store_graph_baseline(string dir)
{
    if (count == 0) return;
    store_lgraph(lgraph_in, dir, "in");
    
    store_lkv(lkv_out, dir, "out");
    
    //XXX writing enum mapping is pending
}

template <class T>
void enumkv_t<T>::init_enum(int enumcount)
{
    max_count = enumcount;
    ecount = 0;
    enum2str = new char*[enumcount];
}

template<class T>
void enumkv_t<T>::populate_enum(const char* e)
{
    vid_t id = ecount++;
    str2enum[e] = id;
    enum2str[id] = gstrdup(e);
}

template<class T>
enumkv_t<T>::enumkv_t()
{
    init_enum(256);
}
    
template<class T>
status_t enumkv_t<T>::filter(sid_set_t* sid_set, void* a_value, filter_fn_t fn)
{
    //value is already encoded, so typecast it
    T     dst = (T) a_value;
    sid_t src;
    vid_t vert1_id;
    tid_t type1_id, src_index;
    sflag_t flag1_mask;
  
    assert(fn == fn_out); 
    
    for (int i = 0; i < sid_set->count; ++i ) {
        src = sid_set->sids[i];
        vert1_id = TO_VID(src);
        type1_id = TO_TID(src) + 1;
        flag1_mask = flag1 & ( (1L << type1_id) - 1);
        src_index = __builtin_popcountll(flag1_mask);
        if (lkv_out[src_index].kv[vert1_id] == dst) {
            //XXX 
        }
    }
    
    return eOK;
}
