#include <getopt.h>
#include <iostream>

#include "all.h"
#include "csv_to_edge.h"
#include "iterative_analytics.h"
#include "ext_iterative_analytics.h"
#include "snap_iterative_analytics.h"


#define no_argument 0
#define required_argument 1 
#define optional_argument 2

using namespace std;

void schema_plaingraph()
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


void plain_test0(const string& idir, const string& odir)
{
    schema_plaingraph();
    //do some setup for plain graphs
    vid_t v_count = (1<<21);
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    bfs<sid_t>(ugraph->sgraph, ugraph->sgraph, 1); 
    
    return ;
}

void plain_test1(const string& idir, const string& odir)
{
    schema_plaingraph();
    //do some setup for plain graphs
    vid_t v_count = (1<<21);
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    bfs<sid_t>(ugraph->sgraph, ugraph->sgraph, 1); 
    
    string idir1 = "/mnt/disk_huge_1/pradeepk/pradeep_graph/kron_21_16_incr/"; 
    plaingraph_manager::prep_graph(idir1, odir);
    
    bfs<sid_t>(ugraph->sgraph, ugraph->sgraph, 1); 
    
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    index_t edge_count = (v_count << 5);
    uint8_t* level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    
    snap_bfs<sid_t>(graph, graph, v_count, edge_count, level_array, 1, 1);
    
    memset(level_array, 0, v_count*sizeof(uint8_t));
    ext_bfs<sid_t>(graph, graph, v_count, edge_count, level_array, 1);
    cout << "multi-snap BFS" << endl; 
    multisnap_bfs<sid_t>(graph, graph, v_count, edge_count, 1, 2, 1);
    return ;
}

void plain_test2(const string& odir)
{
    schema_plaingraph();
    //do some setup for plain graphs
    vid_t v_count = (1<<21);
    plaingraph_manager::setup_graph(v_count);    
    
    g->read_graph_baseline(odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    bfs<sid_t>(ugraph->sgraph, ugraph->sgraph, 1); 
    return ;
}

void plain_test3(const string& idir, const string& odir)
{
    schema_plaingraph();
    //do some setup for plain graphs
    vid_t v_count = (1<<21);
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    verification<sid_t>(ugraph->sgraph, ugraph->sgraph, 1); 
    return ;
}

void plain_test4(const string& idir, const string& odir)
{
    schema_plaingraph();
    //do some setup for plain graphs
    vid_t v_count = (1<<21);
    plaingraph_manager::setup_graph(v_count);    
    
    plaingraph_manager::prep_graph(idir, odir);
    
    string idir1 = "/mnt/disk_huge_1/pradeepk/pradeep_graph/kron_21_16_incr/"; 
    plaingraph_manager::prep_graph(idir1, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    verification<sid_t>(ugraph->sgraph, ugraph->sgraph, 1); 
    return ;
}

void plain_test5(const string& odir)
{
    schema_plaingraph();
    //do some setup for plain graphs
    vid_t v_count = (1<<21);
    plaingraph_manager::setup_graph(v_count);    
    
    g->read_graph_baseline(odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    verification<sid_t>(ugraph->sgraph, ugraph->sgraph, 1); 
    return ;
}

void plain_test6(const string& odir)
{
    schema_plaingraph();

    //do some setup for plain graphs
    vid_t v_count = (1<<21);
    plaingraph_manager::setup_graph(v_count);    
    
    g->read_graph_baseline(odir);
    
    //call ext_bfs
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    index_t edge_count = (v_count << 5);
    uint8_t* level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    
    snap_bfs<sid_t>(graph, graph, v_count, edge_count, level_array, 1, 1);
    return ;
}
