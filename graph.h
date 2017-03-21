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
typedef uint32_t vid_t;
typedef uint64_t index_t;

enum p_type {
    edgraph, //directed graph
    emany2one, // directed graph many to one such as "advisor"
    eugraph, // undirected graph
    // All the label properties now
    eenum,   // value is an enum, such as "type" property
    estring, // value is a string, such as "name"
    efloat,  // 
    edouble,
    eint32,
    euint32,
    eint64,
    euint64,
    edate,
    elast
};

class edge_t {
public:
    vid_t src_id;
    vid_t dst_id;
};

class p_info_t {
 public:
    char*       p_name;
    void*       buf;
    uint32_t    count;
    uint32_t    flag;

 public:
    void populate_property(const char* property);
    virtual void batch_update(const string& src, const string& dst);
    virtual void make_graph_baseline();
    virtual void store_graph_baseline(string dir);
};

class graph {
public:
    graph();
    void prep_graph(string idirname);

public:
    p_info_t** p_info;
    int       p_count;
    map <string, propid_t> str2pid;

};

extern map <string, vid_t> str2vid;
extern vid_t vert_count;
extern graph* g;

class ugraph_t: public p_info_t {
 protected:
    index_t* beg_pos;
    vid_t*   adj_list;

 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
};

class dgraph_t: public p_info_t {
 protected:
    index_t* beg_pos_in;
    vid_t*   adj_list_in;
    index_t* beg_pos_out;
    vid_t*   adj_list_out;

 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
};

class many2one_t: public p_info_t {
 protected:
    index_t* beg_pos_in;
    vid_t*   adj_list_in;
    vid_t*   kv_out;

 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
};

class one2one_t: public p_info_t {
 protected:
    vid_t*   kv_in;
    vid_t*   kv_out;

 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
};

class one2many_t: public p_info_t {
 protected:
    index_t* beg_pos_out;
    vid_t*   adj_list_out;
    vid_t*   kv_in;

 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
};

/*------- labels */
class enum8kv_t: public p_info_t {
protected:
    int8_t*  kv_out;
    
    index_t*   beg_pos_in;
    vid_t*     adj_list_in;

    //mapping between enum and string
    map<string, int8_t> str2enum;
    char**      enum2str;
    int16_t     ecount;
    int16_t     max_count;

 public:
    void init_enum(int enumcount);
    void populate_enum(const char* e); 
    void batch_update(const string& src, const string& dst);
    void make_graph_baseline();
    void store_graph_baseline(string dir);

};

class int64kv_t: public p_info_t {
 protected:
    int64_t* kv_out;
 public:
    void batch_update(const string& src, const string& dst);
    void make_graph_baseline();
    void store_graph_baseline(string dir);
};

class int8kv_t: public p_info_t {
 protected:
    uint8_t* kv_out;
 public:
    void batch_update(const string& src, const string& dst);
    void make_graph_baseline();
    void store_graph_baseline(string dir);
};

class stringkv_t: public p_info_t {
 protected:
    char** kv_out;
 public:
    void batch_update(const string& src, const string& dst);
    void make_graph_baseline();
    void store_graph_baseline(string dir);
};
