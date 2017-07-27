#pragma once
#include "sgraph.h"

class p_pgraph_t : public cfinfo_t {
    //edge properties are part of adj-list
    string edge_propname;
 
 public:
    p_pgraph_t();
    status_t add_property(const char* longname);
    void add_columnfamily(cfinfo_t* cf);
    
    //status_t batch_update(const string& src, const string& dst, propid_t pid = 0);
    
    //For heavy weight edges.
    status_t batch_update(const string& src, const string& dst, propid_t pid, 
                          propid_t count, prop_pair_t* prop_pair);
    
    lite_sgraph_t** prep_sgraph(sflag_t ori_flag, lite_sgraph_t** a_sgraph);
    lite_skv_t** prep_skv(sflag_t ori_flag, lite_skv_t** a_skv);
    
    void prep_sgraph_internal(lite_sgraph_t** sgraph);
    
    void calc_edge_count(lite_sgraph_t** sgraph_out, lite_sgraph_t** sgraph_in); 
    void calc_edge_count_out(lite_sgraph_t** p_sgraph_out);
    void calc_edge_count_in(lite_sgraph_t** sgraph_in);
    void update_count(lite_sgraph_t** sgraph);
    
    void fill_adj_list(lite_sgraph_t** sgraph_out, lite_sgraph_t** sgraph_in);
    void fill_adj_list_in(lite_skv_t** skv_out, lite_sgraph_t** sgraph_in); 
    void fill_adj_list_out(lite_sgraph_t** sgraph_out, lite_skv_t** skv_in); 
    void fill_skv(lite_skv_t** skv_out, lite_skv_t** skv_in);
    
    void store_sgraph(lite_sgraph_t** sgraph, string dir, string postfix);
    void store_skv(lite_skv_t** skv, string dir, string postfix);
    
    void read_sgraph(lite_sgraph_t** sgraph, string dir, string postfix);
    void read_skv(lite_skv_t** skv, string dir, string postfix);

    void make_edge_properties();
    void store_edge_properties(const string& odir);
    void read_edge_properties(const string& odir);
    
    status_t query_adjlist_td(lite_sgraph_t** sgraph, srset_t* iset, srset_t* oset);
    status_t query_kv_td(lite_skv_t** skv, srset_t* iset, srset_t* oset);
    status_t query_adjlist_bu(lite_sgraph_t** sgraph, srset_t* iset, srset_t* oset);
    status_t query_kv_bu(lite_skv_t** skv, srset_t* iset, srset_t* oset);
  
    status_t extend_adjlist_td(lite_sgraph_t** skv, srset_t* iset, srset_t* oset);
    status_t extend_kv_td(lite_skv_t** skv, srset_t* iset, srset_t* oset);
};

class p_ugraph_t: public p_pgraph_t {
 protected:
    lite_sgraph_t** sgraph;

 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    //status_t calc_deletededge_count(pedge_t* edge);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class p_dgraph_t: public p_pgraph_t {
 protected:
    //count is hidden in type count
    lite_sgraph_t** sgraph_out;
    lite_sgraph_t** sgraph_in; 
 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class p_many2one_t: public p_pgraph_t {
 protected:
    lite_skv_t**     skv_out;
    lite_sgraph_t**  sgraph_in;

 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class p_one2one_t: public p_pgraph_t {
 protected:
    lite_skv_t**   skv_in;
    lite_skv_t**   skv_out;

 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class p_one2many_t: public p_pgraph_t {
 protected:
    lite_sgraph_t**   sgraph_out;
    lite_skv_t**      skv_in;

 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};


