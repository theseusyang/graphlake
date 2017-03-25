#pragma once

#include "graph.h"

<class T>
class  edgeT_t {
    vid_t src_id;
    T     dst_id;
};

//generic label class.
<class T>
class lkv_t {
    T* kv;
    sid_t super_id;
};

<class T>
class enumkv_t : public pinfo_t 
{
  protected:
    lkv_t<T>* lkv_out; 
    sgraph_t* sgraph_in;
    
    //mapping between enum and string
    map<string, T> str2enum;
    char**      enum2str;
    T           ecount;
    T           max_count;

  public:
    void batch_update(const string& src, const string& dst);
    void make_graph_baseline();
    void store_graph_baseline(string dir);
};

template<class T>
void enumkv_t<T>::batch_update(const string& src, const string& dst)
{
    vid_t src_id;
    T     dst_id;
    index_t index = 0;
    edgeT_t<T>* edges = (edgeT_t*) buf;

    map<string, vid_t>::iterator str2vid_iter = str2vid.find(src);
    if (str2vid.end() == str2vid_iter) {
        assert(0);
    } else {
        src_id = str2vid_iter->second;
    }

    map<string, T>::iterator str2enum_iter = str2enum.find(dst);
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

    vid_t src;
    T dst;
    edgeT_t<T>* edges = (edgeT_t<T>*) buf;
    
    beg_pos_in = (index_t*)calloc(sizeof(index_t), vert_count);
    adj_list_in = (vid_t*) calloc (sizeof(vid_t), count);
    kv_out = (uint8_t*) calloc(sizeof(uint8_t), vert_count);

    //estimate 
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        beg_pos_in[dst]++;
    }

    //prefix sum
    index_t prev_in;
    index_t prefix_in = 0;
    for (vid_t j = 0; j < vert_count; ++j) {
        prev_in = beg_pos_in[j];
        beg_pos_in[j] = prefix_in;
        prefix_in += prev_in;
    }
    beg_pos_in[vert_count] = prefix_in;
    
    //populate
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        adj_list_in[beg_pos_in[dst]++] = src;
        kv_out[src] = dst;
    }
    
    //correcting beg pos
    for (vid_t j = vert_count; j > 0; j--) {
        beg_pos_in[j] = beg_pos_in[j - 1];
    }
}

template<class T>
void enumkv_t<T>::store_graph_baseline(const string& src, const string& dst)
{
    if (count == 0) return;

    string file = dir + p_name + ".beg_pos_in";
    FILE* f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(beg_pos_in, sizeof(index_t), vert_count + 1, f);
    fclose(f);
    
    file = dir + p_name + ".adj_list_in";
    f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(adj_list_in, sizeof(vid_t), beg_pos_in[vert_count], f);
    fclose(f);
    
    file = dir + p_name + ".kv_out";
    f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(kv_out, sizeof(vid_t), vert_count, f);
    fclose(f);

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
