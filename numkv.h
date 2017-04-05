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
    void batch_update(const string& src, const string& dst);
    void store_graph_baseline(string dir);

    status_t filter(sid_t sid, void* value);

  private:
    using pkv_t<T>::buf;
    using pkv_t<T>::count;
    using pkv_t<T>::flag1;
    using pkv_t<T>::flag1_count;
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

    
template<class T>
status_t numkv_t<T>::filter(sid_t sid, void* value)
{
    return eOK;
}
