#pragma once

#include <string>
#include "type.h"

using std::string;

template<class T>
class sstream_t;

template<class T>
struct callback {
      typedef void(*func)(sstream_t<T>*);
};

template <class T>
class sstream_t {
 public:
    vert_table_t<T>* graph_out;
    vert_table_t<T>* graph_in;
    degree_t*        degree_out;
    degree_t*        degree_in;

    snapshot_t*      snapshot;
    edgeT_t<T>*      edges; //mew edges
    index_t          edge_count;//their count
    
    void*            algo_meta;//algorithm specific data
    typename callback<T>::func   stream_func; 

 public:
    sstream_t(){
        graph_out = 0;
        graph_in = 0;
        degree_out = 0;
        degree_in = 0;
        snapshot = 0;
        edges = 0;
        edge_count = 0;
        algo_meta = 0;
    }
 public:
    inline void    set_algometa(void* a_meta) {algo_meta = a_meta;};
    inline void*   get_algometa() {return algo_meta;}

    inline edgeT_t<T>* get_edges() { return edges;}
    inline void        set_edges(edgeT_t<T>*a_edges) {edges = a_edges;}
    
    inline index_t     get_edgecount() { return edge_count;}
    inline void        set_edgecount(index_t a_edgecount){edge_count = a_edgecount;}
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

     sstream_t<sid_t>* reg_sstream_engine(callback<sid_t>::func func);
    
     void setup_graph(vid_t v_count);
     void setup_weightedgraph(vid_t v_count);
     void setup_weightedgraph_memory(vid_t v_count);

     void prep_graph_adj(const string& idirname, const string& odirname);
     void prep_graph(const string& idirname, const string& odirname);
     void prep_graph_durable(const string& idirname, const string& odirname);
     void prep_graph_paper_chain(const string& idirname, const string& odirname);
     void prep_weighted_rmat(const string& graph_file, const string& action_file);
    
     void recover_graph_adj(const string& idirname, const string& odirname);
     void prep_graph_and_compute(const string& idirname, 
                                 const string& odirname, 
                                 sstream_t<sid_t>* sstreamh);

     void run_pr();
     void run_prd();
     void run_bfs();
     void run_bfsd();
     void run_1hop();
     void run_1hopd();
     void run_2hop();
};

extern plaingraph_manager_t plaingraph_manager; 
