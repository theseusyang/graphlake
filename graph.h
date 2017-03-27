#pragma once

#include <map>
#include <string>
#include <string.h>
#include <stdint.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>


using std::map;
using std::cout;
using std::endl;
using std::string;

inline char* gstrdup(const char* str) 
{
    return strdup(str);
}

typedef uint32_t propid_t;
typedef uint64_t vid_t;
typedef uint64_t sid_t;
typedef uint64_t index_t;
typedef uint32_t tid_t;
typedef uint64_t sflag_t;

#define TO_TID(sid) (sid >> 40)
#define TO_VID(sid)  (sid & 0xffffffffff)
#define TO_SUPER(tid) (((sid_t)(tid)) << 40)


class edge_t {
public:
    vid_t src_id;
    vid_t dst_id;
};

typedef struct __beg_pos_t {
public:
    index_t  count;
    vid_t*   adj_list;
} beg_pos_t;


class skv_t {
 public:
    sid_t super_id;
    vid_t* kv;
};

class sgraph_t {
public:
    sid_t      super_id;
    beg_pos_t* beg_pos;
};

/////////////////////////////////
class pinfo_t {
 public:
    char*       p_name;
    char*       p_longname;
    void*       buf;
    uint32_t    count;
    

 public:
    void populate_property(const char* longname, const char* property_name);
    virtual void batch_update(const string& src, const string& dst);
    virtual void make_graph_baseline();
    virtual void store_graph_baseline(string dir);
};

class tinfo_t {
 public:
    char*   type_name;
    sid_t vert_id;
};

class vinfo_t {
 public:
    char*       v_name;
    sflag_t     flag1;
    uint8_t     flag1_count;

};

////////////main class/////////////////////
class vgraph_t;

class graph {
 public:
    //Type information
    map<string, tid_t> str2enum;
    tinfo_t*       t_info;
    tid_t          t_count;
    tid_t          max_count;

    //graphs and labels store.
    pinfo_t** p_info;
    int       p_count;
    map <string, propid_t> str2pid;

    //vertex information
    vgraph_t* v_graph;

    //Other information
    map <string, vid_t> str2vid;
    vid_t     vert_count;


 public:
    graph();
    void init_type(tid_t enumcount);
    sid_t get_type_scount(int type);    
    void type_update(const string& src, const string& dst);
    void type_done();
    
    void prep_graph(string idirname, string odirname);
};

extern graph* g;


/******** graphs **************/
class pgraph_t: public pinfo_t {
  public:    
    uint64_t    flag1;
    uint64_t    flag2;
    uint8_t     flag1_count;
    uint8_t     flag2_count;
 
    //graph specific functions 
    void batch_update(const string& src, const string& dst);
 
 public:
    pgraph_t();
 public:
    sgraph_t* prep_sgraph(sflag_t ori_flag, tid_t flag_count);
    skv_t* prep_skv(sflag_t ori_flag, tid_t flag_count);
    
    void calc_edge_count(sgraph_t* sgraph_out, sgraph_t* sgraph_in); 
    void calc_edge_count_out(sgraph_t* sgraph_out);
    void calc_edge_count_in(sgraph_t* sgraph_in); 
    
    void prep_sgraph_internal(sgraph_t* sgraph, index_t edge_count, tid_t sgraph_count);
    
    void fill_adj_list(sgraph_t* sgraph_out, sgraph_t* sgraph_in);
    void fill_adj_list_in(skv_t* skv_out, sgraph_t* sgraph_in); 
    void fill_adj_list_out(sgraph_t* sgraph_out, skv_t* skv_in); 
    void fill_skv(skv_t* skv_out, skv_t* skv_in);
    
    void store_sgraph(sgraph_t* sgraph, sflag_t flag, string dir, string postfix);
    void store_skv(skv_t* skv, sflag_t flag, string dir, string postfix);
};


class ugraph_t: public pgraph_t {
 protected:
    sgraph_t* sgraph;

 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
};

class dgraph_t: public pgraph_t {
 protected:
    //count is hidden in flag1 and flag2
    sgraph_t* sgraph_out;
    sgraph_t* sgraph_in; 
 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
};

class many2one_t: public pgraph_t {
 protected:
    skv_t*     skv_out;
    sgraph_t*  sgraph_in;

 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
};

class one2one_t: public pgraph_t {
 protected:
    skv_t*   skv_in;
    skv_t*   skv_out;

 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
};

class one2many_t: public pgraph_t {
 protected:
    sgraph_t*   sgraph_out;
    skv_t*      skv_in;

 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
};


/*----------- labels ------------------ */
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

typedef beg_pos_t lgraph_t;

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

class stringkv_t : public pkv_t {
 protected:
    lkv_t<char*>* kv_out;
 public:
    void batch_update(const string& src, const string& dst);
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    lkv_t<char*>* prep_lkv(sflag_t ori_flag, tid_t flag_count);
    void fill_adj_list_kv(lkv_t<char*>* lkv_out, sflag_t flag1,
                              edgeT_t<char*>* edges, index_t count);
};


#include "numkv.h"
#include "enumkv.h"


typedef enumkv_t<uint8_t> enum8kv_t;
typedef numkv_t<uint8_t>  uint8kv_t;
typedef numkv_t<uint64_t> uint64kv_t;

/*---------------vinfo--------------------*/
class vgraph_t: public pkv_t
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
    vgraph_t();
    ~vgraph_t();
};
