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
    lkv_t<T>* lkv_out;
    uint64_t    flag1;
    uint8_t     flag1_count;

 public:
    lgraph_t* prep_lgraph(index_t ecount);
    lkv_t<T>* prep_lkv();
    void fill_kv_out();
    
    void prep_lgraph_internal(lgraph_t* lgraph_in, index_t ecount, index_t edge_count);
    void store_lgraph(lgraph_t* lgraph_in, string dir, string postfix);
    void calc_edge_count(lgraph_t* lgraph_in, edge_t* edges, index_t count);
    void make_graph_baseline();

    void print_raw_dst(tid_t tid, vid_t vid);
};

class stringkv_t : public pkv_t<char*> {
 protected:
 public:
    void batch_update(const string& src, const string& dst);
    void store_graph_baseline(string dir);

    void get_raw_dst(tid_t tid, vid_t vid);
};

/*---------------vinfo--------------------*/
class vgraph_t: public pkv_t<char*>
{

 public:    
    void id2name(vid_t src_id, const string& src); 
    void store_graph_baseline(string dir);
    

 public:
    const char* get_value(tid_t tid, vid_t vid);

 public:
    vgraph_t();
    ~vgraph_t();
};

/**************/
//super bins memory allocation
template<class T>
lkv_t<T>* pkv_t<T>::prep_lkv()
{
    sflag_t flag = flag1;
    lkv_t<T>*  lkv  = (lkv_t<T>*) calloc (sizeof(lkv_t<T>), flag1_count);
    tid_t      pos  = 0;
    sid_t super_id;
    vid_t v_count;

    for(tid_t i = 0; i < flag1_count; i++) {
        pos = __builtin_ctz(flag);
        flag ^= (1L << pos);//reset that position
        super_id = g->get_type_scount(pos);
        v_count = TO_VID(super_id);
        lkv[i].kv = (T*)calloc(sizeof(T), v_count);
        lkv[i].super_id = super_id;
    }
    return lkv;
}

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

template<class T>
void pkv_t<T>::fill_kv_out()
{
    sid_t src;
    T dst;
    vid_t     vert1_id;
    tid_t     src_index;
    edgeT_t<T>* edges = (edgeT_t<T>*) buf;
    
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        
        vert1_id = TO_VID(src);
        src_index = get_sindex(src, flag1);
        lkv_out[src_index].kv[vert1_id] = dst;
    }
}

template<class T>
void pkv_t<T>::make_graph_baseline()
{
    if (count == 0) return;

    flag1_count = __builtin_popcountll(flag1);
    
    //super bins memory allocation
    lkv_out  = prep_lkv();

    //populate and get the original count back
    //handle kv_out as well.
    fill_kv_out();
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
template <class T>
void pkv_t<T>::print_raw_dst(tid_t tid, vid_t vid)
{
    tid_t sindex = get_sindex(tid, flag1);
    
    cout << lkv_out[sindex].kv[vid];
}

#include "typekv.h"
#include "numkv.h"
#include "enumkv.h"


typedef enumkv_t<uint8_t> enum8kv_t;
typedef numkv_t<uint8_t>  uint8kv_t;
typedef numkv_t<uint64_t> uint64kv_t;


