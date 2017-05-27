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
class numkv_t : public pkv_t<T> 
{
  protected:
    //lkv_t<T>* lkv_out; 
    
  public:
    status_t batch_update(const string& src, const string& dst, propid_t pid = 0);
    void store_graph_baseline(string dir);

    status_t filter(sid_t sid, void* value);

  private:
    using pkv_t<T>::batch_info1;
    using pkv_t<T>::batch_count1;
    using pkv_t<T>::batch_info;
    using pkv_t<T>::batch_count;
    using pkv_t<T>::flag1;
    using pkv_t<T>::flag1_count;
};

template<class T>
status_t numkv_t<T>::batch_update(const string& src, const string& dst, propid_t pid /*= 0*/)
{
    vid_t src_id;
    T     dst_id;
    index_t index = 0;
    edgeT_t<T>* edges;
    
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

    atoT<T>(dst, &dst_id);

    index = batch_info1[batch_count1].count++;
    edges = (edgeT_t<T>*) batch_info1[batch_count1].buf;
    
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
    return eOK;
}


template <class T>
void numkv_t<T>::store_graph_baseline(string dir)
{
    //if (count == 0) return;

    /*
    string file = dir + p_name + ".kv_out";
    FILE* f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(kv_out, sizeof(int64_t), vert_count, f);
    fclose(f);
    */
}

    
template<class T>
status_t numkv_t<T>::filter(sid_t sid, void* value)
{
    return eOK;
}
