#pragma once
#include "type.h"
//#include "graph.h"


//generic classes for label.
template <class T>
class  edgeT_t {
 public:
    vid_t src_id;
    T     dst_id;
};

template <class T>
class lkv_t {
 public:
    T* kv;
    sid_t super_id;
};

//lgraph doesn't need super id stuff
//as this graphs' src id may be an enum (e.g.)
typedef beg_pos_t lgraph_t;


//base class for label graphs.
template <class T>
class pkv_t: public pinfo_t {
 public:
    uint64_t    flag1;
    uint8_t     flag1_count;

 public:
    lgraph_t* prep_lgraph(index_t ecount);
    void prep_lgraph_internal(lgraph_t* lgraph_in, index_t ecount, index_t edge_count);
    void store_lgraph(lgraph_t* lgraph_in, string dir, string postfix);
    void calc_edge_count(lgraph_t* lgraph_in, edge_t* edges, index_t count);
};

class stringkv_t : public pkv_t<char*> {
 protected:
    lkv_t<char*>* kv_out;
 public:
    void batch_update(const string& src, const string& dst);
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    lkv_t<char*>* prep_lkv(sflag_t ori_flag, tid_t flag_count);
    void fill_adj_list_kv(lkv_t<char*>* lkv_out, sflag_t flag1,
                              edgeT_t<char*>* edges, index_t count);
    
    //status_t filter(sid_t sid_set, void* value, filter_fn_t fn);
};

/*---------------vinfo--------------------*/
class vgraph_t: public pkv_t<char*>
{
public:
    lkv_t<char*>* kv_out;

 public:    
    void id2name(vid_t src_id, const string& src); 
    //void batch_update(const string& src, const string& dst);
    void type_done();
    void store_graph_baseline(string dir);
    
    lkv_t<char*>* prep_lkv(sflag_t ori_flag, tid_t flag_count);
    void fill_adj_list_kv(lkv_t<char*>* lkv_out, sflag_t flag1,
                          edgeT_t<char*>* edges, index_t count);

 public:
    const char* get_value(tid_t tid, vid_t vid);

 public:
    vgraph_t();
    ~vgraph_t();
};

/**************/
template <class T>
lgraph_t* pkv_t<T>::prep_lgraph(index_t ecount)
{
    lgraph_t* lgraph  = (beg_pos_t*) calloc (sizeof(beg_pos_t), ecount);
    return lgraph;
}

template <class T>
void pkv_t<T>::prep_lgraph_internal(lgraph_t* lgraph_in, index_t ecount, index_t edge_count)
{
    vid_t* adj_list = (vid_t*) calloc (sizeof(vid_t), edge_count);
    
    index_t     prefix = 0;
    beg_pos_t*  beg_pos = lgraph_in;
    
    for (vid_t j = 0; j < ecount; ++j) {
        beg_pos[j].adj_list = adj_list + prefix;
        prefix += beg_pos[j].count;
        beg_pos[j].count = 0;
    }
}

template <class T>
void pkv_t<T>::calc_edge_count(lgraph_t* lgraph_in, edge_t* edges, index_t count)
{
    sid_t dst;
    
    for (index_t i = 0; i < count; ++i) {
        dst = edges[i].dst_id;
        lgraph_in[dst].count  += 1;
    }
}

template <class T>
void pkv_t<T>::store_lgraph(lgraph_t* lgraph_in, string dir, string postfix)
{
    //base name using relationship type
    /*
    string basefile = dir + p_name;
    string file = basefile + "beg_pos";
    FILE* f;
    */
    
}


#include "typekv.h"
#include "numkv.h"
#include "enumkv.h"


typedef enumkv_t<uint8_t> enum8kv_t;
typedef numkv_t<uint8_t>  uint8kv_t;
typedef numkv_t<uint64_t> uint64kv_t;


