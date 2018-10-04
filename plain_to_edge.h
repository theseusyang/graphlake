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
     void schema_plaingraphuni();
    
     void setup_graph(vid_t v_count);
     void setup_graph_memory(vid_t v_count);
     void restore_graph();

     void prep_graph_fromtext(const string& idirname, const string& odirname, typename callback<T>::parse_fn_t);
     void prep_graph_edgelog(const string& idirname, const string& odirname);
     void prep_graph_adj(const string& idirname, const string& odirname);
     void prep_graph(const string& idirname, const string& odirname);
     void prep_graph_durable(const string& idirname, const string& odirname);
    
     void recover_graph_adj(const string& idirname, const string& odirname);
     void prep_graph_serial_scompute(const string& idirname, const string& odirname, sstream_t<T>* sstreamh);
     void prep_graph_and_scompute(const string& idirname, const string& odirname,
                                  sstream_t<T>* sstreamh);
     void prep_graph_and_compute(const string& idirname, 
                                 const string& odirname, 
                                 stream_t<T>* streamh);
     void reg_stream_view(typename callback<T>::func func, stream_t<T>** streamh);
     void unreg_stream_view(stream_t<T>* streamh);
     
     void reg_sstream_view(typename callback<T>::sfunc func, sstream_t<T>** sstreamh,
                             bool simple, bool priv, bool stale);
     void unreg_sstream_view(sstream_t<T>* sstreamh);

     void reg_wsstream_view(typename callback<T>::wsfunc func,
                    wsstream_t<T>** wsstreamw, bool simple, bool priv, bool stale);
     void unreg_wsstream_view(wsstream_t<T>* wsstreamh);
     
     void reg_wstream_view(typename callback<T>::wfunc func, wstream_t<T>** wstreamh);
     void unreg_wstream_view(wstream_t<T>* wstreamh);

     void create_static_view(bool simple, bool priv, bool stale, snap_t<T>** a_snaph);
     void delete_static_view(snap_t<T>* snaph);
     void create_prior_static_view(prior_snap_t<T>** a_prior_snaph, index_t start_offset, index_t end_offset);
     void delete_prior_static_view(prior_snap_t<T>** a_prior_snaph);
    
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
void plaingraph_manager_t<T>::schema_plaingraphuni()
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
    info = new unigraph<T>;
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
    g->type_done();
    g->prep_graph_baseline();
    g->file_open(true);
    //g->make_graph_baseline();
    //g->store_graph_baseline(); 
}

template <class T>
void plaingraph_manager_t<T>::restore_graph()
{
    //do some setup for plain graphs
    pgraph_t<T>* graph = (pgraph_t<T>*)get_plaingraph();
    graph->flag1 = 1;
    graph->flag2 = 1;
    g->read_graph_baseline();
}

template <class T>
void plaingraph_manager_t<T>::setup_graph_memory(vid_t v_count)
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

struct arg_t {
    string file;
    void* manager;
};

//void* recovery_func(void* arg); 

template <class T>
void* recovery_func(void* a_arg) 
{
    arg_t* arg = (arg_t*) a_arg; 
    string filename = arg->file;
    plaingraph_manager_t<T>* manager = (plaingraph_manager_t<T>*)arg->manager;

    pgraph_t<T>* ugraph = (pgraph_t<T>*)manager->get_plaingraph();
    blog_t<T>*     blog = ugraph->blog;
    
    index_t to_read = 0;
    index_t total_read = 0;
    index_t batch_size = (1L << residue);
    cout << "batch_size = " << batch_size << endl;
        
    FILE* file = fopen(filename.c_str(), "rb");
    assert(file != 0);
    index_t size = fsize(filename);
    index_t edge_count = size/sizeof(edgeT_t<T>);
    
    //Lets set the edge log higher
    index_t new_count = upper_power_of_two(edge_count);
    ugraph->alloc_edgelog(new_count);
    edgeT_t<T>*    edge = blog->blog_beg;
    cout << "edge_count = " << edge_count << endl;
    cout << "new_count  = " << new_count << endl;
    
    //XXX some changes require to be made if edge log size is finite.   
    while (total_read < edge_count) {
        to_read = min(edge_count - total_read,batch_size);
        if (to_read != fread(edge + total_read, sizeof(edgeT_t<T>), to_read, file)) {
            assert(0);
        }
        blog->blog_head += to_read;
        total_read += to_read;
    }
    return 0;
}

template <class T>
void plaingraph_manager_t<T>::recover_graph_adj(const string& idirname, const string& odirname)
{
    string idir = idirname;
    index_t batch_size = (1L << residue);
    cout << "batch_size = " << batch_size << endl;

    arg_t* arg = new arg_t;
    arg->file = idir;
    arg->manager = this;
    pthread_t recovery_thread;
    if (0 != pthread_create(&recovery_thread, 0, &recovery_func<T> , arg)) {
        assert(0);
    }
    
    pgraph_t<T>* ugraph = (pgraph_t<T>*)get_plaingraph();
    blog_t<T>*     blog = ugraph->blog;
    index_t marker = 0;
    index_t snap_marker = 0;
    index_t size = fsize(idirname);
    index_t edge_count = size/sizeof(edgeT_t<T>);
    
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
    delete arg; 
    double end = mywtime ();
    cout << "Make graph time = " << end - start << endl;
}

template <class T>
void plaingraph_manager_t<T>::prep_graph_adj(const string& idirname, const string& odirname)
{
    pgraph_t<T>* ugraph = (pgraph_t<T>*)get_plaingraph();
    blog_t<T>*     blog = ugraph->blog;
    
    free(blog->blog_beg);
    blog->blog_beg = 0;
    blog->blog_head  += read_idir(idirname, &blog->blog_beg, false);
    
    //Upper align this, and create a mask for it
    index_t new_count = upper_power_of_two(blog->blog_head);
    blog->blog_mask = new_count -1;
    
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

template<class T>
void* sstream_func(void* arg) 
{
    sstream_t<T>* sstreamh = (sstream_t<T>*)arg;
    sstreamh->sstream_func(sstreamh);
    return 0;
}


//template <class T>
//void plaingraph_manager_t<T>::prep_graph_and_scompute(const string& idirname, const string& odirname, sstream_t<T>* sstreamh)
//{
//    pgraph_t<T>* ugraph = (pgraph_t<T>*)get_plaingraph();
//    blog_t<T>*     blog = ugraph->blog;
//    
//    free(blog->blog_beg);
//    blog->blog_beg = 0;
//    blog->blog_head  += read_idir(idirname, &blog->blog_beg, false);
//    
//    //Upper align this, and create a mask for it
//    index_t new_count = upper_power_of_two(blog->blog_head);
//    blog->blog_mask = new_count -1;
//    
//    double start = mywtime();
//    
//    //Make Graph
//    index_t marker = 0;
//    index_t snap_marker = 0;
//    index_t batch_size = (1L << residue);
//    cout << "batch_size = " << batch_size << endl;
//
//    //Create a thread for stream pagerank
//    pthread_t sstream_thread;
//    if (0 != pthread_create(&sstream_thread, 0, &sstream_func<T>, sstreamh)) {
//        assert(0);
//    }
//
//    while (marker < blog->blog_head) {
//        marker = min(blog->blog_head, marker+batch_size);
//        ugraph->create_marker(marker);
//        if (eOK != ugraph->move_marker(snap_marker)) {
//            assert(0);
//        }
//        ugraph->make_graph_baseline();
//        g->incr_snapid(snap_marker, snap_marker);
//        ugraph->update_marker();
//
//    }
//    double end = mywtime ();
//    cout << "Make graph time = " << end - start << endl;
//
//    void* ret;
//    pthread_join(sstream_thread, &ret);
//}
//
template <class T>
void plaingraph_manager_t<T>::prep_graph_edgelog(const string& idirname, const string& odirname)
{
    edgeT_t<T>* edges = 0;
    index_t total_edge_count = read_idir(idirname, &edges, true); 
    
    pgraph_t<T>* ugraph = (pgraph_t<T>*)get_plaingraph();
    
    //We need to increase the size of edge log to test logging functionalities
    ugraph->alloc_edgelog(total_edge_count);
    blog_t<T>*     blog = ugraph->blog;
    index_t new_count = upper_power_of_two(total_edge_count);
    blog->blog_mask = new_count -1;

    //Batch and Make Graph
    double start = mywtime();
    for (index_t i = 0; i < total_edge_count; ++i) {
        ugraph->batch_edge(edges[i]);
    }
    double end = mywtime ();
    cout << "Batch Update Time = " << end - start << endl;
}

template <class T>
void plaingraph_manager_t<T>::prep_graph_fromtext(const string& idirname, const string& odirname, 
                                                  typename callback<T>::parse_fn_t parsefile_fn)
{
    //-----
    g->create_wthread();
    g->create_snapthread();
    usleep(1000);
    //-----
    
    pgraph_t<T>* ugraph = (pgraph_t<T>*)get_plaingraph();
    
    //Batch and Make Graph
    double start = mywtime();
    read_idir_text(idirname, odirname, ugraph, parsefile_fn);    
    double end = mywtime ();
    cout << "Batch Update Time = " << end - start << endl;
    
    blog_t<T>* blog = ugraph->blog;
    index_t marker = blog->blog_head;

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
void plaingraph_manager_t<T>::prep_graph(const string& idirname, const string& odirname)
{
    //-----
    g->create_snapthread();
    usleep(1000);
    //-----
    
    edgeT_t<T>* edges = 0;
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
void plaingraph_manager_t<T>::prep_graph_and_scompute(const string& idirname, const string& odirname, sstream_t<T>* sstreamh)
{
    //-----
    g->create_snapthread();
    usleep(1000);
    
    edgeT_t<T>* edges = 0;
    index_t total_edge_count = read_idir(idirname, &edges, true); 
    
    pgraph_t<T>* ugraph = (pgraph_t<T>*)get_plaingraph();
    
    //Create a thread for stream pagerank
    pthread_t sstream_thread;
    if (0 != pthread_create(&sstream_thread, 0, &sstream_func<T>, sstreamh)) {
        assert(0);
    }
    
    //Batch and Make Graph
    double start = mywtime();
    for (index_t i = 0; i < total_edge_count; ++i) {
        ugraph->batch_edge(edges[i]);
    }
    
    blog_t<T>* blog = ugraph->blog;
    index_t marker = blog->blog_head;
    double end = mywtime ();
    cout << "Batch Update Time = " << end - start << endl;

    if (marker != blog->blog_marker) {
        ugraph->create_marker(marker);
    }

    //Wait for make graph
    while (blog->blog_tail != blog->blog_head) {
        usleep(1);
    }
    end = mywtime();
    cout << blog->blog_head;
    cout << " Make graph time = " << end - start << endl;
    //---------
    
    void* ret;
    pthread_join(sstream_thread, &ret);
}

//template<class T>
//void* serial_sstream_func(void* arg) 
//{
//    cout << "entering stream thread" << endl;
//    assert(arg);
//    sstream_t<T>* sstreamh = (sstream_t<T>*)arg;
//    pgraph_t<T>* ugraph  = sstreamh->pgraph;
//    assert(ugraph);
//    
//    blog_t<T>* blog = ugraph->blog;
//    index_t marker = 0; 
//    index_t snap_marker = 0;
//    double start = mywtime ();
//    
//    double epsilon =  1e-8;
//    double  delta = 1.0;
//    double  inv_count = 1.0/v_count;
//    double inv_v_count = 0.15/v_count;
//    
//    double* rank_array = (double*)calloc(v_count, sizeof(double));
//    double* prior_rank_array = (double*)calloc(v_count, sizeof(double));
//
//    #pragma omp parallel for
//    for (vid_t v = 0; v < v_count; ++v) {
//        prior_rank_array[v] = inv_count;
//    }
//
//    vert_table_t<T>* graph_in = sstreamh->graph_in;
//    degree_t* degree_in = sstreamh->degree_in;
//    degree_t* degree_out = sstreamh->degree_out;
//    
//    int iter = 0;
//
//    while (blog->blog_head < 65536) {
//        usleep(1);
//    }
//
//    cout << "starting pr" << endl;
//
//    while (blog->blog_tail < blog->blog_head || delta > epsilon) {
//        if (blog->blog_tail < blog->blog_head) {
//            marker = blog->blog_head;
//            cout << "marker = " << marker << endl;
//            ugraph->create_marker(marker);
//            if (eOK != ugraph->move_marker(snap_marker)) {
//                assert(0);
//            }
//            ugraph->make_graph_baseline();
//            g->incr_snapid(snap_marker, snap_marker);
//            ugraph->update_marker();
//        }
//
//        //update the sstream view
//        sstreamh->update_sstream_view();
//        graph_in = sstreamh->graph_in;
//        degree_in  = sstreamh->degree_in;
//        degree_out = sstreamh->degree_out;
//        //double start1 = mywtime();
//        #pragma omp parallel 
//        {
//            sid_t sid;
//            degree_t      delta_degree = 0;
//            degree_t    durable_degree = 0;
//            degree_t        nebr_count = 0;
//            degree_t      local_degree = 0;
//
//            vert_table_t<T>* graph  = graph_in;
//            vunit_t<T>*      v_unit = 0;
//            
//            delta_adjlist_t<T>* delta_adjlist;
//            T* local_adjlist = 0;
//
//            double rank = 0.0; 
//            
//            #pragma omp for 
//            for (vid_t v = 0; v < v_count; v++) {
//                v_unit = graph[v].get_vunit();
//                if (0 == v_unit) continue;
//
//                durable_degree = v_unit->count;
//                delta_adjlist = v_unit->delta_adjlist;
//                
//                nebr_count = degree_in[v];
//                rank = 0.0;
//                
//                //traverse the delta adj list
//                delta_degree = nebr_count - durable_degree;
//                while (delta_adjlist != 0 && delta_degree > 0) {
//                    local_adjlist = delta_adjlist->get_adjlist();
//                    local_degree = delta_adjlist->get_nebrcount();
//                    degree_t i_count = min(local_degree, delta_degree);
//                    for (degree_t i = 0; i < i_count; ++i) {
//                        sid = get_nebr(local_adjlist, i);
//                        rank += prior_rank_array[sid];
//                    }
//                    delta_adjlist = delta_adjlist->get_next();
//                    delta_degree -= local_degree;
//                }
//                rank_array[v] = rank;
//            }
//        
//            
//            double mydelta = 0;
//            double new_rank = 0;
//            delta = 0;
//            
//            #pragma omp for reduction(+:delta)
//            for (vid_t v = 0; v < v_count; v++ ) {
//                if (degree_out[v] == 0) continue;
//                new_rank = inv_v_count + 0.85*rank_array[v];
//                mydelta = new_rank - prior_rank_array[v]*degree_out[v];
//                if (mydelta < 0) mydelta = -mydelta;
//                delta += mydelta;
//
//                rank_array[v] = new_rank/degree_out[v];
//                prior_rank_array[v] = 0;
//            } 
//        }
//        swap(prior_rank_array, rank_array);
//        ++iter;
//    }
//    
//    #pragma omp for
//    for (vid_t v = 0; v < v_count; v++ ) {
//        rank_array[v] = rank_array[v]*degree_out[v];
//    }
//
//    double end = mywtime();
//    assert (blog->blog_tail == blog->blog_head);
//
//	  cout << "Iteration count" << iter << endl;
//    cout << "PR Time = " << end - start << endl;
//
//    free(rank_array);
//    free(prior_rank_array);
//	  cout << endl;
//
//
//    return 0;
//}
//
template<class T>
void* serial_sstream_func(void* arg) 
{
    cout << "entering stream thread" << endl;
    assert(arg);
    sstream_t<T>* sstreamh = (sstream_t<T>*)arg;
    pgraph_t<T>* ugraph  = sstreamh->pgraph;
    assert(ugraph);
    
    blog_t<T>* blog = ugraph->blog;
    index_t marker = 0; 
    index_t snap_marker = 0;
    double start = mywtime ();
    
    double epsilon =  1e-8;
    double  delta = 1.0;
    double  inv_count = 1.0/v_count;
    double inv_v_count = 0.15/v_count;
    
    double* rank_array = (double*)calloc(v_count, sizeof(double));
    double* prior_rank_array = (double*)calloc(v_count, sizeof(double));

    #pragma omp parallel for
    for (vid_t v = 0; v < v_count; ++v) {
        prior_rank_array[v] = inv_count;
    }

    vert_table_t<T>* graph_in = sstreamh->graph_in;
    degree_t* degree_in = sstreamh->degree_in;
    degree_t* degree_out = sstreamh->degree_out;
    
    int iter = 0;

    while (blog->blog_head < 65536) {
        usleep(1);
    }

    double end = 0;
    cout << "starting pr" << endl;

    while (blog->blog_tail < blog->blog_head || delta > epsilon) {
        if (blog->blog_tail < blog->blog_head) {
            marker = blog->blog_head;
            //cout << "marker = " << marker << endl;
            ugraph->create_marker(marker);
            if (eOK != ugraph->move_marker(snap_marker)) {
                assert(0);
            }
            ugraph->make_graph_baseline();
            g->incr_snapid(snap_marker, snap_marker);
            ugraph->update_marker();
        } else {
            end = mywtime();
            cout << blog->blog_tail << " " << blog->blog_head ;
            cout << " Make graph time = " << end - start << endl;
        }

        //update the sstream view
        sstreamh->update_sstream_view();
        graph_in = sstreamh->graph_in;
        degree_in  = sstreamh->degree_in;
        degree_out = sstreamh->degree_out;
        //double start1 = mywtime();
        #pragma omp parallel 
        {
            sid_t sid;
            degree_t      delta_degree = 0;
            degree_t    durable_degree = 0;
            degree_t        nebr_count = 0;
            degree_t      local_degree = 0;

            vert_table_t<T>* graph  = graph_in;
            vunit_t<T>*      v_unit = 0;
            
            delta_adjlist_t<T>* delta_adjlist;
            T* local_adjlist = 0;

            double rank = 0.0; 
            
            #pragma omp for 
            for (vid_t v = 0; v < v_count; v++) {
                v_unit = graph[v].get_vunit();
                if (0 == v_unit) continue;

                durable_degree = v_unit->count;
                delta_adjlist = v_unit->delta_adjlist;
                
                nebr_count = degree_in[v];
                rank = 0.0;
                
                //traverse the delta adj list
                delta_degree = nebr_count - durable_degree;
                while (delta_adjlist != 0 && delta_degree > 0) {
                    local_adjlist = delta_adjlist->get_adjlist();
                    local_degree = delta_adjlist->get_nebrcount();
                    degree_t i_count = min(local_degree, delta_degree);
                    for (degree_t i = 0; i < i_count; ++i) {
                        sid = get_nebr(local_adjlist, i);
                        rank += prior_rank_array[sid];
                    }
                    delta_adjlist = delta_adjlist->get_next();
                    delta_degree -= local_degree;
                }
                rank_array[v] = rank;
            }
            
            double mydelta = 0;
            double new_rank = 0;
            delta = 0;
            
            #pragma omp for reduction(+:delta)
            for (vid_t v = 0; v < v_count; v++ ) {
                if (degree_out[v] == 0) continue;
                new_rank = inv_v_count + 0.85*rank_array[v];
                mydelta = new_rank - prior_rank_array[v]*degree_out[v];
                if (mydelta < 0) mydelta = -mydelta;
                delta += mydelta;

                rank_array[v] = new_rank/degree_out[v];
                prior_rank_array[v] = 0;
            } 
        }
        swap(prior_rank_array, rank_array);
        ++iter;
    }
    
    assert (blog->blog_tail == blog->blog_head); 
    
    #pragma omp for
    for (vid_t v = 0; v < v_count; v++ ) {
        rank_array[v] = rank_array[v]*degree_out[v];
    }

    end = mywtime();

	cout << "Iteration count = " << iter << endl;
    cout << "PR Time = " << end - start << endl;

    free(rank_array);
    free(prior_rank_array);
    return 0;
}

template <class T>
void plaingraph_manager_t<T>::prep_graph_serial_scompute(const string& idirname, const string& odirname, sstream_t<T>* sstreamh)
{
    edgeT_t<T>* edges = 0;
    index_t total_edge_count = read_idir(idirname, &edges, true); 
    
    pgraph_t<T>* ugraph = (pgraph_t<T>*)get_plaingraph();
    
    //Create a thread for make graph and stream pagerank
    pthread_t sstream_thread;
    if (0 != pthread_create(&sstream_thread, 0, &serial_sstream_func<T>, sstreamh)) {
        assert(0);
    }
    cout << "created stream thread" << endl;
    
    //Batch and Make Graph
    double start = mywtime();
    for (index_t i = 0; i < total_edge_count; ++i) {
        ugraph->batch_edge(edges[i]);
    }
    double end = mywtime ();
    cout << "Batch Update Time = " << end - start << endl;
    
    void* ret;
    pthread_join(sstream_thread, &ret);
    //while (true) usleep(10);
}

template <class T>
void plaingraph_manager_t<T>::prep_graph_durable(const string& idirname, const string& odirname)
{
    //-----
    g->create_wthread();
    g->create_snapthread();
    usleep(1000);
    //-----
    
    edgeT_t<T>* edges = 0;
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
    level_array = (uint8_t*) calloc(snaph->v_count, sizeof(uint8_t));
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
void plaingraph_manager_t<T>::reg_sstream_view(typename callback<T>::sfunc func, sstream_t<T>** a_sstreamh, bool simple, bool priv, bool stale)
{
    sstream_t<T>* sstreamh = new sstream_t<T>;
    sstreamh->sstream_func = func;
    sstreamh->algo_meta = 0;
    sstreamh->v_count = v_count;
    
    pgraph_t<T>* ugraph  = (pgraph_t<T>*)get_plaingraph();
    sstreamh->pgraph     = ugraph;
    
    onegraph_t<T>* sgraph_out = ugraph->sgraph_out[0];
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
void sstream_t<T>::update_sstream_view()
{
    snapshot_t* new_snapshot = g->get_snapshot();
    if (new_snapshot == 0|| (new_snapshot == snapshot)) return;
    
    blog_t<T>* blog = pgraph->blog;
    
    //index_t  marker = blog->blog_head;
    index_t new_marker   = new_snapshot->marker;
    
    //for stale
    edges = blog->blog_beg;
    edge_count = 0;//marker - new_marker;
    
        
    if (pgraph->sgraph_in == 0) {
        create_degreesnap(graph_out, v_count, new_snapshot, 
                          new_marker, edges, degree_out);
    } else {
        create_degreesnapd(graph_out, graph_in, new_snapshot,
                           new_marker, edges, degree_out,
                           degree_in, v_count);
    }

    snapshot = new_snapshot;
}

template <class T>
void plaingraph_manager_t<T>::reg_stream_view(typename callback<T>::func func1, stream_t<T>** a_streamh)
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
void stream_t<T>::update_stream_view()
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
void plaingraph_manager_t<T>::unreg_sstream_view(sstream_t<T>* sstreamh)
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
void plaingraph_manager_t<T>::unreg_stream_view(stream_t<T>* a_streamh)
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
    if (stale) {
        snaph->edge_count = 0;
    } else {
        snaph->edge_count = marker - old_marker;
    }
    
    snaph->v_count    = g->get_type_scount();
    snaph->graph_out  = graph;
    snaph->degree_out = (degree_t*) calloc(snaph->v_count, sizeof(degree_t));
    
    if (ugraph1->sgraph_in == 0) {
        snaph->graph_in   = snaph->graph_out;
        snaph->degree_in  = snaph->degree_out;
        create_degreesnap(snaph->graph_out, snaph->v_count, snapshot, marker, 
                          snaph->edges, snaph->degree_out);
    } else {
        snaph->graph_in  = ugraph1->sgraph_in[0]->get_begpos();
        snaph->degree_in = (degree_t*) calloc(snaph->v_count, sizeof(degree_t));
        create_degreesnapd(snaph->graph_out, snaph->graph_in, snapshot, marker, 
                           snaph->edges, snaph->degree_out, snaph->degree_in, snaph->v_count);
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
degree_t snap_t<T>::get_degree_out(vid_t v)
{
    return degree_out[v];
}

template <class T>
degree_t snap_t<T>::get_degree_in(vid_t v)
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
    degree_t nebr_count     = get_degree_out[v];
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
    degree_t nebr_count     = get_degree_in[v];
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
     
template <class T>
void plaingraph_manager_t<T>::create_prior_static_view(prior_snap_t<T>** a_prior_snaph, index_t start_offset, index_t end_offset)
{
    pgraph_t<T>* pgraph = (pgraph_t<T>*)get_plaingraph();
    
    prior_snap_t<T>* snaph = new prior_snap_t<T>;
    
    snaph->v_count  = g->get_type_scount();
    //v_count = g->get_type_scount;
    snaph->pgraph    = pgraph;
    snaph->degree_out = (degree_t*) calloc(snaph->v_count, sizeof(degree_t));
    snaph->degree_out1= (degree_t*) calloc(snaph->v_count, sizeof(degree_t));
    
    if (pgraph->sgraph_in == 0) {
        snaph->degree_in  = snaph->degree_out;
        snaph->degree_in1 = snaph->degree_out1;
    } else {
        snaph->degree_in  = (degree_t*) calloc(snaph->v_count, sizeof(degree_t));
        snaph->degree_in1 = (degree_t*) calloc(snaph->v_count, sizeof(degree_t));
    }

    if (0 != start_offset) {
        pgraph->create_degree(snaph->degree_out1, snaph->degree_in1, 0, start_offset);
        memcpy(snaph->degree_out, snaph->degree_out1, sizeof(degree_t)*snaph->v_count);
        if (pgraph->sgraph_in !=0) {
            memcpy(snaph->degree_in, snaph->degree_in1, sizeof(degree_t)*snaph->v_count);
        }
    }
        
    pgraph->create_degree(snaph->degree_out, snaph->degree_in, start_offset, end_offset);
    
    *a_prior_snaph = snaph;

    return;
}

template <class T>
degree_t prior_snap_t<T>::get_degree_out(vid_t vid)
{
    return degree_out[vid] - degree_out1[vid];
}

template <class T>
degree_t prior_snap_t<T>::get_degree_in(vid_t vid)
{
    return degree_in[vid] - degree_in1[vid];
}

template <class T>
degree_t prior_snap_t<T>::get_nebrs_out(vid_t vid, T* ptr)
{
    return pgraph->get_wnebrs_out(vid, ptr, degree_out1[vid], get_degree_out(vid));
}

template <class T>
degree_t prior_snap_t<T>::get_nebrs_in(vid_t vid, T* ptr)
{
    if (degree_out == degree_in) {
        return pgraph->get_wnebrs_out(vid, ptr, degree_in1[vid], get_degree_in(vid));
    } else {
        return pgraph->get_wnebrs_in(vid, ptr, degree_in1[vid], get_degree_in(vid));
    }
}

extern plaingraph_manager_t<sid_t> plaingraph_manager; 
