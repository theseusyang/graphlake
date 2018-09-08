#pragma once

#include <string>
#include "type.h"

using std::string;
class csv_manager {
 public:
    static void prep_graph(const string& conf_file, 
                           const string& idir, const string& odir);
    static void prep_vtable(const string& filename, string predicate, const string& odir);
    static void prep_etable(const string& filename, const econf_t& e_conf, const string& odir);
};

class plaingraph_manager_t {
  public:
    //Class member, pgraph_t<T> only
    cfinfo_t* pgraph; 
    
  public:
    plaingraph_manager_t() {
        pgraph = 0;
    }

    inline pgraph_t<sid_t>* get_plaingraph() {
        return static_cast<pgraph_t<sid_t>*> (pgraph);
    }
    
    inline pgraph_t<lite_edge_t>*
    get_weightedgraph(){
        return static_cast<pgraph_t<lite_edge_t>*>(pgraph);
    }

    inline void
    set_pgraph(cfinfo_t* a_pgraph) {
        pgraph = a_pgraph;
    }

    public:
     void schema_plaingraph();
     void schema_plaingraphd();
     void schema_weightedgraphu();
     void schema_weightedgraphd();
    
     void setup_graph(vid_t v_count);
     void setup_weightedgraph(vid_t v_count);
     void setup_weightedgraph_memory(vid_t v_count);

     void prep_graph_adj(const string& idirname, const string& odirname);
     void prep_graph(const string& idirname, const string& odirname);
     void prep_graph_durable(const string& idirname, const string& odirname);
     void prep_graph_paper_chain(const string& idirname, const string& odirname);
     void prep_weighted_rmat(const string& graph_file, const string& action_file);
    
     void recover_graph_adj(const string& idirname, const string& odirname);
     void prep_graph_and_compute(const string& idirname, const string& odirname);

     void run_pr();
     void run_prd();
     void run_bfs();
     void run_bfsd();
     void run_1hop();
     void run_1hopd();
     void run_2hop();
};

extern plaingraph_manager_t plaingraph_manager; 
