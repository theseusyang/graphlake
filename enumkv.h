#pragma once

#include "graph.h"

//generic enum class
template <class T>
class enumkv_t : public pkv_t<T> {
  protected:
    
    //mapping between enum and string
    map<string, T> str2enum;
    char**      enum2str;
    T           ecount;
    T           max_count;
  
  private:
    using pkv_t<T>::batch_info1;
    using pkv_t<T>::batch_count1;
    using pkv_t<T>::batch_info;
    using pkv_t<T>::batch_count;
    using pkv_t<T>::flag1;
    using pkv_t<T>::flag1_count;
    using pkv_t<T>::lkv_out;
    using pkv_t<T>::prep_lkv;
    using pkv_t<T>::lgraph_in;
    using pkv_t<T>::nebr_count;

  public:
    enumkv_t();
    void init_enum(int enumcount);
    void populate_enum(const char* e);
    void batch_update(const string& src, const string& dst);
    void make_graph_baseline();
    void store_graph_baseline(string dir);

  public:
    void store_lkv(lkv_t<T>* lkv_out, string dir, string postfix);
    
    status_t filter(sid_t sid, void* value, filter_fn_t fn);
    
};

template<class T>
void enumkv_t<T>::batch_update(const string& src, const string& dst)
{
    vid_t src_id;
    T     dst_id;
    index_t index = 0;
    edgeT_t<T>* edges;

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
    
    if (batch_info1[batch_count1].count == MAX_ECOUNT) {
        ++batch_count1;
    }

    index = batch_info1[batch_count1].count++;
    edges = (edgeT_t<T>*) batch_info1[batch_count1].buf;
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
}

template<class T>
void enumkv_t<T>::make_graph_baseline()
{
    if (batch_info[0].count == 0) return;
   
    flag1_count = __builtin_popcountll(flag1);
    
    //super bins memory allocation
    lkv_out  = prep_lkv();
    lgraph_in = prep_lgraph(ecount);    

    //estimate edge count
    calc_edge_count(lgraph_in);
    
    //prefix sum then reset the count
    prep_lgraph_internal(lgraph_in, ecount);
    
    fill_Adj_list_kv(lkv_out, lgraph_in, flag1);
}



template<class T>
void enumkv_t<T>::store_lkv(lkv_t<T>* lkv_out, string dir, string postfix)
{
}

template<class T>
void enumkv_t<T>::store_graph_baseline(string dir)
{
    /*
    if (count == 0) return;
    store_lgraph(lgraph_in, dir, "in");
    
    store_lkv(lkv_out, dir, "out");
    
    //XXX writing enum mapping is pending
   */ 
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
status_t enumkv_t<T>::filter(sid_t src, void* a_value, filter_fn_t fn)
{
    //value is already encoded, so typecast it
    T     dst = (T) a_value;
    vid_t vert1_id;
    tid_t src_index;
  
    assert(fn == fn_out); 
    
    vert1_id = TO_VID(src);
	src_index = TO_TID(src);
    if (lkv_out[src_index]->kv[vert1_id] == dst) {
        return eOK;
    }
    return eQueryFail;
}
