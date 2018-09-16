#pragma once

#include <string>
#include <dirent.h>
#include <assert.h>
#include <string>
#include <unistd.h>

#include "type.h"
#include "graph.h"
#include "typekv.h"
#include "sgraph.h"
#include "util.h"

using namespace std;

extern index_t residue;

template <class T>
class plaingraph_manager_t {
  public:
    //Class member, pgraph_t<T> only
    cfinfo_t* pgraph; 
    
  public:
    plaingraph_manager_t() {
        pgraph = 0;
    }

    inline pgraph_t<T>* get_plaingraph() {
        return static_cast<pgraph_t<T>*> (pgraph);
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
     void prep_graph_and_compute(const string& idirname, 
                                 const string& odirname, 
                                 stream_t<T>* streamh);
     void reg_stream_engine(typename callback<T>::func func, stream_t<T>** streamh);
     void unreg_stream_engine(stream_t<T>* streamh);

     void reg_wsstream_engine(typename callback<T>::wsfunc func,
                    wsstream_t<T>** wsstreamw, bool simple, bool priv, bool stale);
     void reg_sstream_engine(typename callback<T>::sfunc func, sstream_t<T>** sstreamh,
                             bool simple, bool priv, bool stale);
     void reg_wstream_engine(typename callback<T>::wfunc func, wstream_t<T>** wstreamh);
     
     void unreg_wsstream_engine(wsstream_t<T>* wsstreamh);
     void unreg_sstream_engine(sstream_t<T>* sstreamh);
     void unreg_wstream_engine(wstream_t<T>* wstreamh);

     void create_static_view(bool simple, bool priv, bool stale, snap_t<T>** a_snaph);
     void delete_static_view(snap_t<T>* snaph);
    
     void run_pr();
     void run_prd();
     void run_bfs();
     void run_bfsd();
     void run_1hop();
     void run_1hopd();
     void run_2hop();
};

template <class T>
void plaingraph_manager_t<T>::schema_plaingraph()
{
    g->cf_info = new cfinfo_t*[2];
    g->p_info = new pinfo_t[2];
    
    pinfo_t*    p_info    = g->p_info;
    cfinfo_t*   info      = 0;
    const char* longname  = 0;
    const char* shortname = 0;
    
    longname = "gtype";
    shortname = "gtype";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new typekv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "friend";
    shortname = "friend";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new ugraph<T>;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    set_pgraph(info);

}

template <class T>
void plaingraph_manager_t<T>::schema_plaingraphd()
{
    g->cf_info = new cfinfo_t*[2];
    g->p_info = new pinfo_t[2];
    
    pinfo_t*    p_info    = g->p_info;
    cfinfo_t*   info      = 0;
    const char* longname  = 0;
    const char* shortname = 0;
    
    longname = "gtype";
    shortname = "gtype";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new typekv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "friend";
    shortname = "friend";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new dgraph<T>;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    set_pgraph(info);
}

template <class T>
void plaingraph_manager_t<T>::schema_weightedgraphu()
{
    g->cf_info = new cfinfo_t*[2];
    g->p_info = new pinfo_t[2];
    
    pinfo_t*    p_info    = g->p_info;
    cfinfo_t*   info      = 0;
    const char* longname  = 0;
    const char* shortname = 0;
    
    longname = "gtype";
    shortname = "gtype";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new typekv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "friend";
    shortname = "friend";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new ugraph<T>;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    set_pgraph(info);
}

template <class T>
void plaingraph_manager_t<T>::schema_weightedgraphd()
{
    g->cf_info = new cfinfo_t*[2];
    g->p_info = new pinfo_t[2];
    
    pinfo_t*    p_info    = g->p_info;
    cfinfo_t*   info      = 0;
    const char* longname  = 0;
    const char* shortname = 0;
    
    longname = "gtype";
    shortname = "gtype";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new typekv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "friend";
    shortname = "friend";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new dgraph<T>;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    set_pgraph(info);
}

template <class T>
void plaingraph_manager_t<T>::setup_graph(vid_t v_count)
{
    //do some setup for plain graphs
    pgraph_t<T>* graph = (pgraph_t<T>*)get_plaingraph();
    graph->flag1 = 1;
    graph->flag2 = 1;
    typekv_t* typekv = g->get_typekv();
    typekv->manual_setup(v_count);
    g->prep_graph_baseline();
    g->file_open(true);
    g->make_graph_baseline();
    g->store_graph_baseline(); 
}

template <class T>
void plaingraph_manager_t<T>::setup_weightedgraph(vid_t v_count)
{
    //do some setup for plain graphs
    pgraph_t<T>* graph = (pgraph_t<T>*)get_plaingraph();
    graph->flag1 = 1;
    graph->flag2 = 1;
    typekv_t* typekv = g->get_typekv();
    typekv->manual_setup(v_count);
    g->prep_graph_baseline();
    g->file_open(true);
    g->make_graph_baseline();
    g->store_graph_baseline(); 
}

template <class T>
void plaingraph_manager_t<T>::setup_weightedgraph_memory(vid_t v_count)
{
    //do some setup for plain graphs
    pgraph_t<T>* graph = (pgraph_t<T>*)get_plaingraph();
    graph->flag1 = 1;
    graph->flag2 = 1;
    typekv_t* typekv = g->get_typekv();
    typekv->manual_setup(v_count);
    //g->prep_graph_baseline();
    //g->file_open(true);
    //g->make_graph_baseline();
    //g->store_graph_baseline(); 
}

extern vid_t v_count;

void* recovery_func(void* arg); 

template <class T>
void plaingraph_manager_t<T>::recover_graph_adj(const string& idirname, const string& odirname)
{
    string idir = idirname;
    index_t batch_size = (1L << residue);
    cout << "batch_size = " << batch_size << endl;

    pthread_t recovery_thread;
    if (0 != pthread_create(&recovery_thread, 0, recovery_func , &idir)) {
        assert(0);
    }
    
    pgraph_t<T>* ugraph = (pgraph_t<T>*)get_plaingraph();
    blog_t<T>*     blog = ugraph->blog;
    index_t marker = 0;
    index_t snap_marker = 0;
    index_t size = fsize(idirname);
    index_t edge_count = size/sizeof(edge_t);
    
    double start = mywtime();
    
    //Make Graph
    while (0 == blog->blog_head) {
        usleep(20);
    }
    while (marker < edge_count) {
        usleep(20);
        while (marker < blog->blog_head) {
            marker = min(blog->blog_head, marker+batch_size);
            ugraph->create_marker(marker);
            if (eOK != ugraph->move_marker(snap_marker)) {
                assert(0);
            }
            ugraph->make_graph_baseline();
            //ugraph->store_graph_baseline();
            g->incr_snapid(snap_marker, snap_marker);
            //blog->marker = marker;
            ugraph->update_marker();
            //cout << marker << endl;
        }
    }
    
    double end = mywtime ();
    cout << "Make graph time = " << end - start << endl;
}

template <class T>
void plaingraph_manager_t<T>::prep_graph_adj(const string& idirname, const string& odirname)
{
    pgraph_t<T>* ugraph = (pgraph_t<T>*)get_plaingraph();
    blog_t<T>*     blog = ugraph->blog;
    
    blog->blog_head  += read_idir(idirname, &blog->blog_beg, false);
    
    //Upper align this, and create a mask for it
    index_t new_count = upper_power_of_two(blog->blog_head);
    BLOG_MASK = new_count -1;
    
    double start = mywtime();
    
    //Make Graph
    index_t marker = 0;
    index_t snap_marker = 0;
    //index_t total_edge_count = blog->blog_head;
    //index_t batch_size = (total_edge_count >> residue);
    index_t batch_size = (1L << residue);
    cout << "batch_size = " << batch_size << endl;

    while (marker < blog->blog_head) {
        marker = min(blog->blog_head, marker+batch_size);
        ugraph->create_marker(marker);
        if (eOK != ugraph->move_marker(snap_marker)) {
            assert(0);
        }
        ugraph->make_graph_baseline();
        //ugraph->store_graph_baseline();
        g->incr_snapid(snap_marker, snap_marker);
        //blog->marker = marker;
        ugraph->update_marker();
        //cout << marker << endl;
    }
    double end = mywtime ();
    cout << "Make graph time = " << end - start << endl;
}

template <class T>
void plaingraph_manager_t<T>::prep_graph(const string& idirname, const string& odirname)
{
    //-----
    g->create_snapthread();
    usleep(1000);
    //-----
    
    edge_t* edges = 0;
    index_t total_edge_count = read_idir(idirname, &edges, true); 
    
    pgraph_t<T>* ugraph = (pgraph_t<T>*)get_plaingraph();
    
    //Batch and Make Graph
    double start = mywtime();
    for (index_t i = 0; i < total_edge_count; ++i) {
        ugraph->batch_edge(edges[i]);
    }
    
    blog_t<T>* blog = ugraph->blog;
    index_t marker = blog->blog_head;
    double end = mywtime ();
    cout << "Batch Update Time = " << end - start << endl;

    //----------
    if (marker != blog->blog_marker) {
        ugraph->create_marker(marker);
    }

    //Wait for make graph
    while (blog->blog_tail != blog->blog_head) {
        usleep(1);
    }
    end = mywtime();
    cout << "Make graph time = " << end - start << endl;
    //---------
}

template <class T>
void plaingraph_manager_t<T>::prep_graph_durable(const string& idirname, const string& odirname)
{
    //-----
    g->create_wthread();
    g->create_snapthread();
    usleep(1000);
    //-----
    
    edge_t* edges = 0;
    index_t total_edge_count = read_idir(idirname, &edges, true); 
    
    pgraph_t<T>* ugraph = (pgraph_t<T>*)get_plaingraph();
    
    //Batch and Make Graph
    double start = mywtime();
    for (index_t i = 0; i < total_edge_count; ++i) {
        ugraph->batch_edge(edges[i]);
    }
    
    blog_t<T>* blog = ugraph->blog;
    index_t marker = blog->blog_head;

    //----------
    double end = mywtime ();
    cout << "Batch Update Time = " << end - start << endl;
    
    if (marker != blog->blog_marker) {
        ugraph->create_marker(marker);
    }

    //Wait for make graph
    bool done_making = false;
    bool done_persisting = false;
    while (!done_making || !done_persisting) {
        if (blog->blog_tail == blog->blog_head && !done_making) {
            end = mywtime();
            cout << "Make Graph Time = " << end - start << endl;
            done_making = true;
        }
        if (blog->blog_wtail == blog->blog_head && !done_persisting) {
            end = mywtime();
            cout << "Durable Graph Time = " << end - start << endl;
            done_persisting = true;
        }
        usleep(1);
    }
    //while (blog->blog_tail != blog->blog_head) {
    //    usleep(10);
    //}
    //end = mywtime();
    //cout << "Make graph time = " << end - start << endl;
    //---------
}

#include "iterative_analytics.h"
#include "mem_iterative_analytics.h"

template <class T>
void plaingraph_manager_t<T>::run_pr() 
{
    ugraph<T>* ugraph1 = (ugraph<T>*)get_plaingraph();
    blog_t<T>* blog = ugraph1->blog;
    onegraph_t<T>*   sgraph = ugraph1->sgraph[0];
    vert_table_t<T>* graph = sgraph->get_begpos();
    
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array = 0;
        
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));

    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;
    
    mem_pagerank<T>(graph, degree_array, degree_array, 
               snapshot, marker, blog->blog_beg,
               v_count, 5);
    free(degree_array);
}

template <class T>
void plaingraph_manager_t<T>::run_prd()
{
    dgraph<T>* ugraph = (dgraph<T>*)get_plaingraph();
    blog_t<T>* blog = ugraph->blog;
    
    onegraph_t<T>*   sgraph_out = ugraph->sgraph_out[0];
    vert_table_t<sid_t>* graph_out = sgraph_out->get_begpos();
    onegraph_t<T>*   sgraph_in = ugraph->sgraph_in[0];
    vert_table_t<T>* graph_in =  sgraph_in->get_begpos();
    
    //Run PageRank
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array_out = (degree_t*) calloc(v_count, sizeof(degree_t));
    degree_t* degree_array_in = (degree_t*) calloc(v_count, sizeof(degree_t));
        
    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnapd(graph_out, graph_in, snapshot, marker, blog->blog_beg,
                           degree_array_out, degree_array_in, v_count);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;
    /*
    mem_pagerank_push<sid_t>(graph_out, degree_array_out, 
               snapshot, marker, blog->blog_beg,
               v_count, 5);
   */ 
   
    
    mem_pagerank<T>(graph_in, degree_array_in, degree_array_out, 
               snapshot, marker, blog->blog_beg,
               v_count, 5);
    
    free(degree_array_out);
    free(degree_array_in);
}

template <class T>
void plaingraph_manager_t<T>::run_bfs()
{
    snap_t<T>* snaph;
    create_static_view(true, true, true, &snaph);
    //cout << "old marker = " << old_marker << " New marker = " << marker << endl;
    
    uint8_t* level_array = 0;
    level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    mem_bfs<T>(snaph, level_array, 1);
    free(level_array);
    delete_static_view(snaph);
}

//template <class T>
//void plaingraph_manager_t<T>::run_bfs()
//{
//    ugraph<T>* ugraph1 = (ugraph<T>*)get_plaingraph();
//    blog_t<T>* blog = ugraph1->blog;
//    vert_table_t<T>* graph = ugraph1->sgraph[0]->get_begpos();
//    uint8_t* level_array = 0;
//    
//    /*
//    level_array = (uint8_t*)mmap(NULL, sizeof(uint8_t)*v_count, 
//                            PROT_READ|PROT_WRITE,
//                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0 );
//    
//    if (MAP_FAILED == level_array) {
//        cout << "Huge page alloc failed for level array" << endl;
//        level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
//    }*/
//    
//    level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
//    
//    
//    snapshot_t* snapshot = g->get_snapshot();
//    index_t  marker = blog->blog_head;
//    index_t old_marker = 0;
//    degree_t* degree_array = 0;
//        
//    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));
//
//    if (snapshot) {
//        old_marker = snapshot->marker;
//        create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);
//    }
//
//    cout << "old marker = " << old_marker << " New marker = " << marker << endl;
//    /*
//    ext_bfs<sid_t>(sgraph, degree_array, sgraph, degree_array, 
//                   snapshot, marker, blog->blog_beg,
//                   v_count, level_array, 1);
//    */
//    mem_bfs<T>(graph, degree_array, graph, degree_array, 
//                   snapshot, marker, blog->blog_beg,
//                   v_count, level_array, 1);
//    free(level_array);
//    free(degree_array);
//}

template <class T>
void plaingraph_manager_t<T>::run_bfsd() 
{
    dgraph<T>* ugraph = (dgraph<T>*)get_plaingraph();
    blog_t<T>* blog = ugraph->blog;
    
    onegraph_t<T>*   sgraph_out = ugraph->sgraph_out[0];
    vert_table_t<T>* graph_out = sgraph_out->get_begpos();
    onegraph_t<T>*   sgraph_in = ugraph->sgraph_in[0];
    vert_table_t<T>* graph_in =  sgraph_in->get_begpos();
    
    uint8_t* level_array = 0;
    level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    
    /*
    level_array = (uint8_t*)mmap(NULL, sizeof(uint8_t)*v_count, 
                            PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0 );
    
    if (MAP_FAILED == level_array) {
        cout << "Huge page alloc failed for level array" << endl;
        level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    }*/
    
    
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
        
    degree_t* degree_array_out = (degree_t*) calloc(v_count, sizeof(degree_t));
    degree_t* degree_array_in = (degree_t*) calloc(v_count, sizeof(degree_t));

    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnapd(graph_out, graph_in, snapshot, marker, blog->blog_beg,
                           degree_array_out, degree_array_in, v_count);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;
    /*
    ext_bfs<sid_t>(sgraph, degree_array, sgraph, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    */
    mem_bfs<T>(graph_out, degree_array_out, graph_in, degree_array_in, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    free(level_array);
    free(degree_array_out);
    free(degree_array_in);
}

template <class T>
void plaingraph_manager_t<T>::run_1hop()
{
    ugraph<T>* ugraph1 = (ugraph<T>*)get_plaingraph();
    blog_t<T>* blog = ugraph1->blog;
    vert_table_t<T>* graph = ugraph1->sgraph[0]->get_begpos();
   
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array = 0;
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));
    if (snapshot) {
        old_marker = snapshot->marker;
    }
    create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    mem_hop1<T>(graph, degree_array, snapshot, marker, blog->blog_beg, v_count);

}

template <class T>
void plaingraph_manager_t<T>::run_1hopd()
{
    pgraph_t<T>* ugraph = (pgraph_t<sid_t>*)get_plaingraph();
    blog_t<T>*     blog = ugraph->blog;
    
    onegraph_t<T>*   sgraph_out = ugraph->sgraph_out[0];
    vert_table_t<T>* graph_out = sgraph_out->get_begpos();
    onegraph_t<T>*   sgraph_in = ugraph->sgraph_in[0];
    vert_table_t<sid_t>* graph_in =  sgraph_in->get_begpos();
    degree_t* degree_array_out = 0;
    degree_t* degree_array_in = 0;
    
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_array_out = (degree_t*) calloc(v_count, sizeof(degree_t));
    degree_array_in = (degree_t*) calloc(v_count, sizeof(degree_t));
        
    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnapd(graph_out, graph_in, snapshot, marker, blog->blog_beg,
                           degree_array_out, degree_array_in, v_count);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;
    mem_hop1<T>(graph_out, degree_array_out, 
               snapshot, marker, blog->blog_beg,
               v_count);
    free(degree_array_out);
    free(degree_array_in);
}

template <class T>
void plaingraph_manager_t<T>::run_2hop()
{
    pgraph_t<T>* ugraph = (pgraph_t<T>*)get_plaingraph();
    vert_table_t<T>* graph = ugraph->sgraph[0]->get_begpos();
    blog_t<T>* blog = ugraph->blog;
   
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array = 0;
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t)); 
    if (snapshot) {
        old_marker = snapshot->marker;
    }
    degree_array = create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    mem_hop2<T>(graph, degree_array, snapshot, marker, blog->blog_beg, v_count);
    free(degree_array);
}

#include "stream_analytics.h"

template <class T>
void plaingraph_manager_t<T>::reg_sstream_engine(typename callback<T>::sfunc func, sstream_t<T>** a_sstreamh, bool simple, bool priv, bool stale)
{
    sstream_t<T>* sstreamh = new sstream_t<T>;
    sstreamh->stream_func = func;
    sstreamh->algo_meta = 0;
    sstreamh->v_count = v_count;
    
    pgraph_t<T>*       ugraph  = (pgraph_t<T>*)get_plaingraph();
    onegraph_t<T>*  sgraph_out = ugraph->sgraph_out[0];
    sstreamh->graph_out  = sgraph_out->get_begpos();
    sstreamh->degree_out = (degree_t*) calloc(v_count, sizeof(degree_t));
    
    if (ugraph->sgraph_in == 0) {
        sstreamh->graph_in   = sstreamh->graph_out;
        sstreamh->degree_in  = sstreamh->degree_out;
    } else {
        sstreamh->graph_in  = ugraph->sgraph_in[0]->get_begpos();
        sstreamh->degree_in = (degree_t*) calloc(v_count, sizeof(degree_t));
    }
    
    *a_sstreamh = sstreamh;
}

template <class T>
void sstream_t<T>::update_sstream_engine()
{
    blog_t<T>* blog = pgraph->blog;
    index_t  marker = blog->blog_head;
    
    snapshot_t* snapshot = g->get_snapshot();
    index_t old_marker = 0;
    if (snapshot) {
        old_marker = snapshot->marker;
    }

    //for stale
    edges = blog->blog_beg;
    edge_count = 0;//marker - old_marker;
    
        
    if (pgraph->sgraph_in == 0) {
        create_degreesnap(graph_out, v_count, snapshot, 
                          old_marker, edges, degree_out);
    } else {
        create_degreesnapd(graph_out, graph_in, snapshot,
                           old_marker, edges, degree_out,
                           degree_in, v_count);
    }
}

template <class T>
void plaingraph_manager_t<T>::reg_stream_engine(typename callback<T>::func func1, stream_t<T>** a_streamh)
{
    stream_t<T>* streamh = new stream_t<T>;
    pgraph_t<T>* ugraph  = (pgraph_t<T>*)get_plaingraph();
    blog_t<T>* blog = ugraph->blog;
    index_t  marker = blog->blog_head;

    streamh->edge_offset = marker;
    streamh->edges      = 0;
    streamh->edge_count = 0;
    
    streamh->pgraph = ugraph;
    streamh->stream_func = func1;
    streamh->algo_meta = 0;

    *a_streamh = streamh;
}

template <class T>
void stream_t<T>::update_stream_engine()
{
    blog_t<T>* blog = pgraph->blog;
    index_t  marker = blog->blog_head;
    
    index_t a_edge_count = edge_count;
    
    //XXX need to copy it
    edges = blog->blog_beg + edge_offset + a_edge_count;
    edge_count = marker - edge_offset;
    edge_offset += a_edge_count;
}

template <class T>
void plaingraph_manager_t<T>::unreg_sstream_engine(sstream_t<T>* sstreamh)
{
    if (sstreamh->degree_in ==  sstreamh->degree_out) {
        delete sstreamh->degree_out;
    } else {
        delete sstreamh->degree_out;
        delete sstreamh->degree_in;
    }
    delete sstreamh;
}

template <class T>
void plaingraph_manager_t<T>::unreg_stream_engine(stream_t<T>* a_streamh)
{
    //XXX may need to delete the edge log
    delete a_streamh;
}

template <class T>
void plaingraph_manager_t<T>::create_static_view(bool simple, bool priv, bool stale, snap_t<T>** a_snaph)
{
    ugraph<T>* ugraph1 = (ugraph<T>*)get_plaingraph();
    vert_table_t<T>* graph = ugraph1->sgraph[0]->get_begpos();
    
    snapshot_t* snapshot = g->get_snapshot();
    
    blog_t<T>*    blog = ugraph1->blog;
    index_t     marker = blog->blog_head;
    
    index_t old_marker = 0;
    if (snapshot) {
        old_marker = snapshot->marker;
    }

    snap_t<T>* snaph = new snap_t<T>;
    snaph->snapshot  = snapshot;
    
    //need to copy it
    snaph->edges     = blog->blog_beg;
    snaph->edge_count = marker - old_marker;
    
    snaph->v_count    = v_count;
    snaph->graph_out  = graph;
    snaph->degree_out = (degree_t*) calloc(v_count, sizeof(degree_t));
    
    if (ugraph1->sgraph_in == 0) {
        snaph->graph_in   = snaph->graph_out;
        snaph->degree_in  = snaph->degree_out;
        create_degreesnap(snaph->graph_out, v_count, snapshot, marker, 
                          snaph->edges, snaph->degree_out);
    } else {
        snaph->graph_in  = ugraph1->sgraph_in[0]->get_begpos();
        snaph->degree_in = (degree_t*) calloc(v_count, sizeof(degree_t));
        create_degreesnapd(snaph->graph_out, snaph->graph_in, snapshot, marker, 
                           snaph->edges, snaph->degree_out, snaph->degree_in, v_count);
    }
    *a_snaph = snaph;
}

template <class T>
void plaingraph_manager_t<T>::delete_static_view(snap_t<T>* snaph) 
{
    if (snaph->degree_in ==  snaph->degree_out) {
        delete snaph->degree_out;
    } else {
        delete snaph->degree_out;
        delete snaph->degree_in;
    }
    //if edge log allocated, delete it
    delete snaph;
}

template <class T>
void plaingraph_manager_t<T>::prep_graph_and_compute(const string& idirname, const string& odirname, stream_t<T>* streamh)
{
    pgraph_t<T>* ugraph = (pgraph_t<T>*)get_plaingraph();
    blog_t<T>*     blog = ugraph->blog;
    
    blog->blog_head  += read_idir(idirname, &blog->blog_beg, false);
    
    double start = mywtime();
    
    index_t marker = 0, prior_marker = 0;
    index_t batch_size = (1L << residue);
    cout << "batch_size = " << batch_size << endl;

    while (marker < blog->blog_head) {
        marker = min(blog->blog_head, marker+batch_size);
        
        //This is like a controlled update_stream_view() call
        streamh->set_edgecount(marker - prior_marker);
        streamh->set_edges(blog->blog_beg + prior_marker);
        streamh->edge_offset = prior_marker;
        streamh->stream_func(streamh);
        prior_marker = marker;
    }
    double end = mywtime ();
    cout << "Make graph time = " << end - start << endl;
}

template <class T>
degree_t snap_t<T>::get_nebrs_length_out(vid_t v)
{
    return degree_out[v];
}

template <class T>
degree_t snap_t<T>::get_nebrs_length_in(vid_t v)
{
    return degree_in[v];
}

template <class T>
degree_t snap_t<T>::get_nebrs_out(vid_t v, T*& adj_list)
{
    vert_table_t<T>* graph  = graph_out;
    vunit_t<T>*      v_unit = graph[v].get_vunit();
    if (0 == v_unit) return 0;
    
    degree_t local_degree = 0;
    degree_t total_degree = 0;
    T* local_adjlist = 0;

    delta_adjlist_t<T>* delta_adjlist;
    delta_adjlist           = v_unit->delta_adjlist;
    degree_t nebr_count     = get_nebrs_length_out[v];
    degree_t delta_degree   = nebr_count;

    //cout << "delta adjlist " << delta_degree << endl;	
    //cout << "Nebr list of " << v <<" degree = " << nebr_count << endl;	
    
    //traverse the delta adj list
    while (delta_adjlist != 0 && delta_degree > 0) {
        local_adjlist    = delta_adjlist->get_adjlist();
        local_degree     = delta_adjlist->get_nebrcount();
        degree_t i_count = min(local_degree, delta_degree);
        
        memcpy(adj_list + total_degree, local_adjlist, sizeof(T)*i_count);
        delta_adjlist = delta_adjlist->get_next();
        delta_degree -= i_count;
        total_degree += i_count;
    }
    return nebr_count;
}
template<class T>
degree_t snap_t<T>::get_nebrs_in(vid_t v, T*& adj_list)
{
    vert_table_t<T>* graph  = graph_in;
    vunit_t<T>*      v_unit = graph[v].get_vunit();
    if (0 == v_unit) return 0;
    
    degree_t local_degree = 0;
    degree_t total_degree = 0;
    T* local_adjlist = 0;

    delta_adjlist_t<T>* delta_adjlist;
    delta_adjlist           = v_unit->delta_adjlist;
    degree_t nebr_count     = get_nebrs_length_in[v];
    degree_t delta_degree   = nebr_count;

    //cout << "delta adjlist " << delta_degree << endl;	
    //cout << "Nebr list of " << v <<" degree = " << nebr_count << endl;	
    
    //traverse the delta adj list
    while (delta_adjlist != 0 && delta_degree > 0) {
        local_adjlist    = delta_adjlist->get_adjlist();
        local_degree     = delta_adjlist->get_nebrcount();
        degree_t i_count = min(local_degree, delta_degree);
        
        memcpy(adj_list + total_degree, local_adjlist, sizeof(T)*i_count);
        delta_adjlist = delta_adjlist->get_next();
        delta_degree -= i_count;
        total_degree += i_count;
    }
    return nebr_count;
}

extern plaingraph_manager_t<sid_t> plaingraph_manager; 
extern plaingraph_manager_t<lite_edge_t> weightedgraph_manager; 
