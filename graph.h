#pragma once

#include <map>
#include <string>
#include <string.h>
#include <stdint.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>

#include "type.h"
#include "query_clause.h"

using std::map;
using std::cout;
using std::endl;
using std::string;

inline char* gstrdup(const char* str) 
{
    return strdup(str);
}

#define bu_factor 0.07
#define MAX_BCOUNT 256
#define MAX_ECOUNT 1000000

//class pkv_t;
class graph;
extern graph* g;

class batchinfo_t {
 public:
    void*    buf;
    uint32_t count;
};

/////////////////////////////////
//One relationship or label
class pinfo_t {
 public:
    char*        p_name;
    char*        p_longname;
    batchinfo_t* batch_info;
    uint8_t      batch_count;

    batchinfo_t* batch_info1;
    uint8_t      batch_count1;
   
 public: 
    pinfo_t();   

 public:
    void populate_property(const char* longname, const char* property_name);
    virtual void batch_update(const string& src, const string& dst);
    void swap_log_buffer(); 
    void reset_buffer0();
    void reset_buffer1();
    virtual void make_graph_baseline();
    virtual void store_graph_baseline(string dir);
    
    virtual void make_graph_update();
    virtual void store_graph_update(string dir);

    //Graph specific
    virtual status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    //virtual status_t transform_withfilter(srset_t* iset, srset_t* oset, direction_t direction, filter_info_t* filter_info);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
    
    //label specific
    virtual status_t filter(sid_t sid, univ_t value, filter_fn_t fn);
    virtual void print_raw_dst(tid_t tid, vid_t vid);
    virtual status_t get_encoded_value(const char* value, univ_t* univ);
};

class vgraph_t;
////////////main class/////////////////////
class graph {
 public:
    //graphs and labels store.
    pinfo_t** p_info;
    int       p_count;
    map <string, propid_t> str2pid;

    //vertex information
    vgraph_t* v_graph;

    //Other information
    map <string, sid_t> str2vid;
    vid_t     vert_count;

 public:
    graph();
    sid_t get_type_scount(tid_t type);
    tid_t get_total_types();
    void type_update(const string& src, const string& dst);
    void type_done();

    propid_t get_pid(const char* property);
    sid_t get_sid(const char* src);
    
    void prep_graph(string idirname, string odirname);
    void update_graph(string idirname, string odirname);

    //queries
    void run_query(query_clause* q);
};



/******** graphs **************/
class pgraph_t: public pinfo_t {
  public:    
    sflag_t     flag1;
    tid_t       flag2;
    uint8_t     flag1_count;
    uint8_t     flag2_count;
 
    //graph specific functions 
    void batch_update(const string& src, const string& dst);
 
 public:
    pgraph_t();
 public:
    sgraph_t** prep_sgraph(sflag_t ori_flag, tid_t flag_count);
    skv_t** prep_skv(sflag_t ori_flag, tid_t flag_count);
    
    void calc_edge_count(sgraph_t** sgraph_out, sgraph_t** sgraph_in); 
    void calc_edge_count_out(sgraph_t** sgraph_out);
    void calc_edge_count_in(sgraph_t** sgraph_in); 
    
    void prep_sgraph_internal(sgraph_t** sgraph);
    
    void fill_adj_list(sgraph_t** sgraph_out, sgraph_t** sgraph_in);
    void fill_adj_list_in(skv_t** skv_out, sgraph_t** sgraph_in); 
    void fill_adj_list_out(sgraph_t** sgraph_out, skv_t** skv_in); 
    void fill_skv(skv_t** skv_out, skv_t** skv_in);
    
    void store_sgraph(sgraph_t** sgraph, string dir, string postfix);
    void store_skv(skv_t** skv, string dir, string postfix);

    status_t query_adjlist_td(sgraph_t** sgraph, sflag_t oflag, srset_t* iset, srset_t* oset);
    status_t query_kv_td(skv_t** skv, sflag_t oflag, srset_t* iset, srset_t* oset);
    status_t query_adjlist_bu(sgraph_t** sgraph, sflag_t flag, srset_t* iset, srset_t* oset);
    status_t query_kv_bu(skv_t** skv, sflag_t flag, srset_t* iset, srset_t* oset);
  
    
    status_t extend_adjlist_td(sgraph_t** skv, srset_t* iset, srset_t* oset);
    status_t extend_kv_td(skv_t** skv, srset_t* iset, srset_t* oset);
};


class ugraph_t: public pgraph_t {
 protected:
    sgraph_t** sgraph;

 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class dgraph_t: public pgraph_t {
 protected:
    //count is hidden in type count
    sgraph_t** sgraph_out;
    sgraph_t** sgraph_in; 
 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class many2one_t: public pgraph_t {
 protected:
    skv_t**     skv_out;
    sgraph_t**  sgraph_in;

 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class one2one_t: public pgraph_t {
 protected:
    skv_t**   skv_in;
    skv_t**   skv_out;

 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class one2many_t: public pgraph_t {
 protected:
    sgraph_t**   sgraph_out;
    skv_t**      skv_in;

 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

/*----------- labels ------------------ */
#include "labelkv.h"

