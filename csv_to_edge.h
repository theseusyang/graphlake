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

class plaingraph_manager {
    public:
    static void schema_plaingraph();
    static void schema_plaingraphd();
    static void schema_weightedgraphu();
    static void schema_weightedgraphd();
    
    static void setup_graph(vid_t v_count);
    static void setup_weightedgraph(vid_t v_count);
    static void setup_weightedgraph_memory(vid_t v_count);

    static void prep_graph_adj(const string& idirname, const string& odirname);
    static void prep_graph(const string& idirname, const string& odirname);
    static void prep_graph_durable(const string& idirname, const string& odirname);
    static void prep_graph_paper_chain(const string& idirname, const string& odirname);
    static void prep_weighted_rmat(const string& graph_file, const string& action_file);
    
		static void recover_graph_adj(const string& idirname, const string& odirname);

    static void run_pr();
    static void run_prd();
    static void run_bfs();
    static void run_bfsd();
    static void run_1hop();
    static void run_1hopd();
    static void run_2hop();
};
