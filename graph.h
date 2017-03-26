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

enum p_type {
    edgraph, //directed graph, many to many.
    emany2one, // directed graph many to one such as "advisor"
    eone2one,
    eone2many,
    eugraph, // undirected graph
    // All the label properties now
    eenum8,   // value is an enum, such as "type" property
    estring, // value is a string, such as "name"
    efloat,  // 
    edouble,
    euint8,
    eint32,
    euint32,
    eint64,
    euint64,
    edate,
    elast
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

////////////main class/////////////////////
typedef struct __type_info_t {
    char*   type_name;
    sid_t vert_id;
} type_info_t;

class graph {
 public:
    //mapping between enum and string
    map<string, tid_t> str2enum;
    type_info_t*       type_info;
    tid_t              ecount;
    tid_t              max_count;

    pinfo_t** p_info;
    int       p_count;
    map <string, propid_t> str2pid;

 public:
    graph();
    void init_type(tid_t enumcount);
    void batch_update(const string& src, const string& dst);
    sid_t get_type_scount(int type);    
    
    void prep_graph(string idirname, string odirname);
};

extern map <string, vid_t> str2vid;
extern vid_t vert_count;
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
    
    void calc_edge_count(sgraph_t* sgraph_out, sgraph_t* sgraph_in, 
                        sflag_t flag1, sflag_t flag2, 
                        edge_t* edges, index_t count);
    void calc_edge_count_out(sgraph_t* sgraph_out, sflag_t flag1, 
                               edge_t* edges, index_t count);
    void calc_edge_count_in(sgraph_t* sgraph_in, sflag_t flag2, 
                               edge_t* edges, index_t count);
    
    void prep_sgraph_internal(sgraph_t* sgraph, index_t edge_count, tid_t sgraph_count);
    
    void fill_adj_list(sgraph_t* sgraph_out, sgraph_t* sgraph_in,
                           sflag_t flag1, sflag_t flag2,
                           edge_t* edges, index_t count);
    void fill_adj_list_in(skv_t* skv_out, sgraph_t* sgraph_in, 
                              sflag_t flag1, sflag_t flag2,
                           edge_t* edges, index_t count);
    void fill_adj_list_out(sgraph_t* sgraph_out, skv_t* skv_in, 
                               sflag_t flag1, sflag_t flag2,
                               edge_t* edges, index_t count);
    void fill_skv(skv_t* skv_out, skv_t* skv_in,
                        sflag_t flag1, sflag_t flag2,
                        edge_t* edges, index_t count);
    
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
    char** kv_out;
 public:
    void batch_update(const string& src, const string& dst);
    void make_graph_baseline();
    void store_graph_baseline(string dir);
};


#include "numkv.h"
#include "enumkv.h"


typedef enumkv_t<uint8_t> enum8kv_t;
typedef numkv_t<uint8_t>  uint8kv_t;
typedef numkv_t<uint64_t> uint64kv_t;
