#include "graph.h"


template <class T>
T atoT(string value)
{
    assert(0);
    return (T)0;
}

template <>
uint32_t atoT(string value)
{
    uint32_t num = 0;
    sscanf(value.c_str(), "%d", &num);
    return num;
}

template <>
uint64_t atoT(string value)
{
    uint64_t num = 0;
    sscanf(value.c_str(), "%ld", &num);
    return num;
}

//generic number class
//
template <class T>
class numkv_t : public pinfo_t 
{
  protected:
    lkv_t<T>* lkv_out; 
    
  public:
    void batch_update(const string& src, const string& dst);
    void make_graph_baseline();
    void store_graph_baseline(string dir);
};

template<class T>
void numkv_t<T>::batch_update(const string& src, const string& dst)
{
    vid_t src_id;
    T     dst_id;
    index_t index = 0;
    edgeT_t<T>* edges = (edgeT_t<T>*) buf;

    map<string, vid_t>::iterator str2vid_iter = str2vid.find(src);
    if (str2vid.end() == str2vid_iter) {
        assert(0);
    } else {
        src_id = str2vid_iter->second;
    }
    
    tid_t type_id = TO_TYPE(src_id);
    flag1 |= (1L << type_id);

    dst_id = atoT<T>(dst);

    index = count++;
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
}

template<class T>
void numkv_t<T>::make_graph_baseline()
{
    if (count == 0) return;

    vid_t src;
    T dst;
    edgeT_t<T>* edges = (edgeT_t<T>*) buf;
   
    flag1_count = __builtin_popcountll(flag1);
    
    //super bins memory allocation
    lkv_out  = prep_lkv(flag1, flag1_count);

    //populate and get the original count back
    //handle kv_out as well.
    fill_adj_list_kv(skv_out, flag1  buf, count);
}

template<class T>
void numkv_t<T>::fill_adj_list_kv(lkv_t* lkv_out, sflag_t flag1,
                              edgeT_t<T>* edges, index_t count)
{
    superid_t src;
    T dst;
    vid_t     vert1_id;
    tid_t     type1_id;
    sflag_t   flag1_mask;
    tid_t     src_index;
    
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        
        vert1_id = TO_VID(src);
        type1_id = TO_TYPE(src) + 1;
        flag1_mask = flag1 & ( (1L << type1_id) - 1)
        src_index = __builtin_popcountll(flag1_mask);
        
        skv_out[src_index]->kv[vert1_id] = dst;
        
    }
}

template <class T>
void numkv_t::store_graph_baseline(string dir)
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
