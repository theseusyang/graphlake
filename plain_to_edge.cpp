#include <algorithm>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <assert.h>
#include <vector>
#include <string>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "csv_to_edge.h"
#include "type.h"
#include "graph.h"
#include "typekv.h"
#include "sgraph.h"

#include "iterative_analytics.h"
#include "mem_iterative_analytics.h"
using namespace std;


index_t residue = 0;

index_t read_idir(const string& idirname, edge_t** pedges, bool alloc)
{
    struct dirent *ptr;
    DIR *dir;
    int file_count = 0;
    string filename;
        
    FILE* file = 0;
    index_t size =  0;
    index_t edge_count = 0;
    index_t total_edge_count = 0;
    
    //Read graph files
    double start = mywtime();
    dir = opendir(idirname.c_str());
    edge_t* edges = 0;
    if (alloc) {
        edges =  (edge_t*)calloc(sizeof(edge_t),(1L<<32));
        *pedges = edges;
    } else {
        edges = *pedges;
    }
    edge_t* edge = edges;
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        filename = idirname + "/" + string(ptr->d_name);
        file_count++;
        
        file = fopen((idirname + "/" + string(ptr->d_name)).c_str(), "rb");
        assert(file != 0);
        size = fsize(filename);
        edge_count = size/sizeof(edge_t);
        edge = edges + total_edge_count;
        if (edge_count != fread(edge, sizeof(edge_t), edge_count, file)) {
            assert(0);
        }
        total_edge_count += edge_count;
    }
    closedir(dir);
    double end = mywtime();
    cout << "Reading "  << file_count  << " file time = " << end - start << endl;
    cout << "End marker = " << total_edge_count << endl;
    return total_edge_count;
}

void plaingraph_manager::schema_plaingraph()
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
    info = new ugraph_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;

}

void plaingraph_manager::schema_plaingraphd()
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
    info = new dgraph_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
}

void plaingraph_manager::schema_weightedgraphu()
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
    info = new p_ugraph_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
}

void plaingraph_manager::schema_weightedgraphd()
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
    info = new p_dgraph_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
}


void plaingraph_manager::setup_graph(vid_t v_count)
{
    //do some setup for plain graphs
    propid_t cf_id = g->get_cfid("friend");
    pgraph_t<sid_t>* graph = (pgraph_t<sid_t>*)g->cf_info[cf_id];
    graph->flag1 = 1;
    graph->flag2 = 1;
    typekv_t* typekv = g->get_typekv();
    typekv->manual_setup(v_count);
    g->prep_graph_baseline();
    g->file_open(true);
    g->make_graph_baseline();
    g->store_graph_baseline(); 
}

void plaingraph_manager::setup_weightedgraph(vid_t v_count)
{
    //do some setup for plain graphs
    propid_t cf_id = g->get_cfid("friend");
    pgraph_t<lite_edge_t>* graph = (pgraph_t<lite_edge_t>*)g->cf_info[cf_id];
    graph->flag1 = 1;
    graph->flag2 = 1;
    typekv_t* typekv = g->get_typekv();
    typekv->manual_setup(v_count);
    g->prep_graph_baseline();
    g->file_open(true);
    g->make_graph_baseline();
    g->store_graph_baseline(); 
}

void plaingraph_manager::setup_weightedgraph_memory(vid_t v_count)
{
    //do some setup for plain graphs
    propid_t cf_id = g->get_cfid("friend");
    pgraph_t<lite_edge_t>* graph = (pgraph_t<lite_edge_t>*)g->cf_info[cf_id];
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

void* recovery_func(void* arg) 
{
    string filename = *(string*)arg;
    propid_t          cf_id = g->get_cfid("friend");
    pgraph_t<sid_t>* ugraph = (pgraph_t<sid_t>*)g->cf_info[cf_id];
    blog_t<sid_t>*     blog = ugraph->blog;
    edgeT_t<sid_t>*    edge = blog->blog_beg;
    
    index_t to_read = 0;
    index_t total_read = 0;
    index_t batch_size = (1L << residue);
    cout << "batch_size = " << batch_size << endl;
        
    FILE* file = fopen(filename.c_str(), "rb");
    assert(file != 0);
    index_t size = fsize(filename);
    index_t edge_count = size/sizeof(edge_t);
    
    
    while (total_read < edge_count) {
        to_read = min(edge_count - total_read,batch_size);
        if (to_read != fread(edge + total_read, sizeof(edge_t), to_read, file)) {
            assert(0);
        }
        blog->blog_head += to_read;
        total_read += to_read;
    }
    return 0;
}

void plaingraph_manager::recover_graph_adj(const string& idirname, const string& odirname)
{
    string idir = idirname;
    index_t batch_size = (1L << residue);
    cout << "batch_size = " << batch_size << endl;

    pthread_t recovery_thread;
    if (0 != pthread_create(&recovery_thread, 0, recovery_func , &idir)) {
        assert(0);
    }
    
    propid_t          cf_id = g->get_cfid("friend");
    pgraph_t<sid_t>* ugraph = (pgraph_t<sid_t>*)g->cf_info[cf_id];
    blog_t<sid_t>*     blog = ugraph->blog;
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

void plaingraph_manager::prep_graph_adj(const string& idirname, const string& odirname)
{
    propid_t          cf_id = g->get_cfid("friend");
    pgraph_t<sid_t>* ugraph = (pgraph_t<sid_t>*)g->cf_info[cf_id];
    blog_t<sid_t>*     blog = ugraph->blog;
    
    blog->blog_head  += read_idir(idirname, &blog->blog_beg, false);
    
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

void plaingraph_manager::prep_graph(const string& idirname, const string& odirname)
{
    //-----
    g->create_snapthread();
    usleep(1000);
    //-----
    
    edge_t* edges = 0;
    index_t total_edge_count = read_idir(idirname, &edges, true); 
    
    propid_t cf_id = g->get_cfid("friend");
    pgraph_t<sid_t>* ugraph = (pgraph_t<sid_t>*)g->cf_info[cf_id];
    
    //Batch and Make Graph
    double start = mywtime();
    for (index_t i = 0; i < total_edge_count; ++i) {
        ugraph->batch_edge(edges[i]);
    }
    
    blog_t<sid_t>* blog = ugraph->blog;
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

void plaingraph_manager::prep_graph_durable(const string& idirname, const string& odirname)
{
    //-----
    g->create_wthread();
    g->create_snapthread();
    usleep(1000);
    //-----
    
    edge_t* edges = 0;
    index_t total_edge_count = read_idir(idirname, &edges, true); 
    
    propid_t cf_id = g->get_cfid("friend");
    pgraph_t<sid_t>* ugraph = (pgraph_t<sid_t>*)g->cf_info[cf_id];
    
    //Batch and Make Graph
    double start = mywtime();
    for (index_t i = 0; i < total_edge_count; ++i) {
        ugraph->batch_edge(edges[i]);
    }
    
    blog_t<sid_t>* blog = ugraph->blog;
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

void plaingraph_manager::prep_graph_paper_chain(const string& idirname, const string& odirname)
{
    propid_t          cf_id = g->get_cfid("friend");
    pgraph_t<sid_t>* ugraph = (pgraph_t<sid_t>*)g->cf_info[cf_id];
    blog_t<sid_t>*     blog = ugraph->blog;
    
    blog->blog_head  += read_idir(idirname, &blog->blog_beg, false);
    
    cout << "Creating graph in " << residue << " installment" << endl;

    double start = mywtime();

    index_t marker = blog->blog_head/residue;
    index_t new_marker = 0;
    //bool clean = false;
    for (index_t i = 1; i <= residue; ++i) {

        new_marker = marker*i;
        cout << "make graph marker = " << new_marker << endl;
        index_t snap_marker = 0;
        if (marker == 0) return;

        ugraph->create_marker(new_marker);
        if (eOK == ugraph->move_marker(snap_marker)) {
            ugraph->make_graph_baseline();
			//clean = (i == residue);
            //ugraph->store_graph_baseline(clean);
            g->incr_snapid(snap_marker, snap_marker);
            ugraph->update_marker();
        }
    }

    double end = mywtime ();
    cout << "Make graph time = " << end - start << endl;
}

void plaingraph_manager::run_pr() 
{
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    blog_t<sid_t>* blog = ugraph->blog;
    onegraph_t<sid_t>*   sgraph = ugraph->sgraph[0];
    vert_table_t<sid_t>* graph = sgraph->get_begpos();
    
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
    
    mem_pagerank<sid_t>(graph, degree_array, degree_array, 
               snapshot, marker, blog->blog_beg,
               v_count, 5);
    free(degree_array);
}

void plaingraph_manager::run_prd()
{
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    blog_t<sid_t>* blog = ugraph->blog;
    
    onegraph_t<sid_t>*   sgraph_out = ugraph->sgraph_out[0];
    //vert_table_t<sid_t>* graph_out = sgraph_out->get_begpos();
    onegraph_t<sid_t>*   sgraph_in = ugraph->sgraph_in[0];
    vert_table_t<sid_t>* graph_in =  sgraph_in->get_begpos();
    
    //Run PageRank
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array_out = (degree_t*) calloc(v_count, sizeof(degree_t));
    degree_t* degree_array_in = (degree_t*) calloc(v_count, sizeof(degree_t));
        
    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnapd(sgraph_out, sgraph_in, snapshot, marker, blog->blog_beg,
                           degree_array_out, degree_array_in);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;
    /*
    mem_pagerank_push<sid_t>(graph_out, degree_array_out, 
               snapshot, marker, blog->blog_beg,
               v_count, 5);
   */ 
   
    
    mem_pagerank<sid_t>(graph_in, degree_array_in, degree_array_out, 
               snapshot, marker, blog->blog_beg,
               v_count, 5);
    
    free(degree_array_out);
    free(degree_array_in);
}

void plaingraph_manager::run_bfs()
{
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    blog_t<sid_t>* blog = ugraph->blog;
    //onegraph_t<sid_t>*   sgraph = ugraph->sgraph[0];
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    uint8_t* level_array = 0;
    
    /*
    level_array = (uint8_t*)mmap(NULL, sizeof(uint8_t)*v_count, 
                            PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0 );
    
    if (MAP_FAILED == level_array) {
        cout << "Huge page alloc failed for level array" << endl;
        level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    }*/
    
    level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    
    
    snapshot_t* snapshot = g->get_snapshot();
    index_t  marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array = 0;
        
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));

    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;
    /*
    ext_bfs<sid_t>(sgraph, degree_array, sgraph, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    */
    mem_bfs<sid_t>(graph, degree_array, graph, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    free(level_array);
    free(degree_array);
}

void plaingraph_manager::run_bfsd() 
{
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    blog_t<sid_t>* blog = ugraph->blog;
    
    onegraph_t<sid_t>*   sgraph_out = ugraph->sgraph_out[0];
    vert_table_t<sid_t>* graph_out = sgraph_out->get_begpos();
    onegraph_t<sid_t>*   sgraph_in = ugraph->sgraph_in[0];
    vert_table_t<sid_t>* graph_in =  sgraph_in->get_begpos();
    
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
        create_degreesnapd(sgraph_out, sgraph_in, snapshot, marker, blog->blog_beg,
                           degree_array_out, degree_array_in);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;
    /*
    ext_bfs<sid_t>(sgraph, degree_array, sgraph, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    */
    mem_bfs<sid_t>(graph_out, degree_array_out, graph_in, degree_array_in, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    free(level_array);
    free(degree_array_out);
    free(degree_array_in);
}

void plaingraph_manager::run_1hop()
{
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    blog_t<sid_t>* blog = ugraph->blog;
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
   
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

    mem_hop1<sid_t>(graph, degree_array, snapshot, marker, blog->blog_beg, v_count);

}

void plaingraph_manager::run_1hopd()
{
    propid_t          cf_id = g->get_cfid("friend");
    pgraph_t<sid_t>* ugraph = (pgraph_t<sid_t>*)g->cf_info[cf_id];
    blog_t<sid_t>*     blog = ugraph->blog;
    
    onegraph_t<sid_t>*   sgraph_out = ugraph->sgraph_out[0];
    vert_table_t<sid_t>* graph_out = sgraph_out->get_begpos();
    onegraph_t<sid_t>*   sgraph_in = ugraph->sgraph_in[0];
    //vert_table_t<sid_t>* graph_in =  sgraph_in->get_begpos();
    degree_t* degree_array_out = 0;
    degree_t* degree_array_in = 0;
    
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_array_out = (degree_t*) calloc(v_count, sizeof(degree_t));
    degree_array_in = (degree_t*) calloc(v_count, sizeof(degree_t));
        
    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnapd(sgraph_out, sgraph_in, snapshot, marker, blog->blog_beg,
                           degree_array_out, degree_array_in);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;
    mem_hop1<sid_t>(graph_out, degree_array_out, 
               snapshot, marker, blog->blog_beg,
               v_count);
    free(degree_array_out);
    free(degree_array_in);
}

void plaingraph_manager::run_2hop()
{
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    blog_t<sid_t>* blog = ugraph->blog;
   
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

    mem_hop2<sid_t>(graph, degree_array, snapshot, marker, blog->blog_beg, v_count);
    free(degree_array);
}
