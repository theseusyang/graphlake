#pragma once
#include "graph.h"
#include "prop_encoder.h"
#include "sgraph.h"

class p_pgraph_t : public pgraph_t {
    size_t MAXX_ECOUNT;
    //edge properties are part of adj-list
    string edge_propname;
    prop_encoder_t* encoder;

 
 public:
    p_pgraph_t();

    //For heavy weight edges.
    status_t batch_update(const string& src, const string& dst, propid_t pid, 
                          propid_t count, prop_pair_t* prop_pair, int del = 0);
    //status_t batch_update(const string& src, const string& dst, propid_t pid = 0);
    
    void add_edge_property(const char* longname, prop_encoder_t* prop_encoder);
 
 public:
    
    void fill_adj_list(lite_sgraph_t** sgraph_out, lite_sgraph_t** sgraph_in);
    void fill_adj_list_in(lite_skv_t** skv_out, lite_sgraph_t** sgraph_in); 
    void fill_adj_list_out(lite_sgraph_t** sgraph_out, lite_skv_t** skv_in); 
    void fill_skv(lite_skv_t** skv_out, lite_skv_t** skv_in);

    /*status_t query_adjlist_td(lite_sgraph_t** sgraph, srset_t* iset, srset_t* oset);
    status_t query_kv_td(lite_skv_t** skv, srset_t* iset, srset_t* oset);
    status_t query_adjlist_bu(lite_sgraph_t** sgraph, srset_t* iset, srset_t* oset);
    status_t query_kv_bu(lite_skv_t** skv, srset_t* iset, srset_t* oset);
  
    status_t extend_adjlist_td(lite_sgraph_t** skv, srset_t* iset, srset_t* oset);
    status_t extend_kv_td(lite_skv_t** skv, srset_t* iset, srset_t* oset);
    */
};

class p_ugraph_t: public p_pgraph_t {
 public:
    lite_sgraph_t** sgraph;

 public:
    static cfinfo_t* create_instance();
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    //status_t calc_deletededge_count(pedge_t* edge);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class p_dgraph_t: public p_pgraph_t {
 public:
    //count is hidden in type count
    lite_sgraph_t** sgraph_out;
    lite_sgraph_t** sgraph_in; 
 public:
    static cfinfo_t* create_instance();
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class p_many2one_t: public p_pgraph_t {
 public:
    lite_skv_t**     skv_out;
    lite_sgraph_t**  sgraph_in;

 public:
    static cfinfo_t* create_instance();
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class p_one2one_t: public p_pgraph_t {
 public:
    lite_skv_t**   skv_in;
    lite_skv_t**   skv_out;

 public:
    static cfinfo_t* create_instance();
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class p_one2many_t: public p_pgraph_t {
 public:
    lite_sgraph_t**   sgraph_out;
    lite_skv_t**      skv_in;

 public:
    static cfinfo_t* create_instance();
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

