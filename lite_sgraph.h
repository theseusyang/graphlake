#pragma once
#include "sgraph.h"

class lite_pgraph_t : public pgraph_t {
    //edge properties.
    map <string, propid_t> str2pid;
    cfinfo_t** cf_info;
    pinfo_t *  p_info;
    
    propid_t   cf_count;
    propid_t   p_count;
    sid_t      edge_count;
 
 public:
    lite_pgraph_t();
    status_t batch_update(const string& src, const string& dst, propid_t pid = 0);
    
    //For heavy weight edges.
    status_t batch_update(const string& src, const string& dst, propid_t pid, 
                          propid_t count, prop_pair_t* prop_pair);
    
    lite_sgraph_t** prep_sgraph(sflag_t ori_flag, lite_sgraph_t** a_sgraph);
    lite_skv_t** prep_skv(sflag_t ori_flag, lite_skv_t** a_skv);
    
    void prep_sgraph_internal(lite_sgraph_t** sgraph);
    
    void calc_edge_count(lite_sgraph_t** sgraph_out, lite_sgraph_t** sgraph_in); 
    void calc_edge_count_out(lite_sgraph_t** lite_sgraph_out);
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
};
