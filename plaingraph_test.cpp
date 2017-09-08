#include <getopt.h>
#include <iostream>

#include "all.h"
#include "csv_to_edge.h"
#include "iterative_analytics.h"
#include "ext_iterative_analytics.h"
#include "mem_iterative_analytics.h"
#include "snap_iterative_analytics.h"

using namespace std;
    
vid_t v_count = 0;

void plain_test0(const string& idir, const string& odir)
{
    /*
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    bfs<sid_t>(ugraph->sgraph, ugraph->sgraph, 1); 
    */
    
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph_sync(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    blog_t<sid_t>* blog = ugraph->blog;
   
    uint8_t* level_array = (uint8_t*)mmap(NULL, sizeof(uint8_t)*v_count, PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0 );
    if (MAP_FAILED == level_array) {
        cout << "Huge page alloc failed for level array" << endl;
        level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    }
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array = 0;

    if (snapshot) {
        old_marker = snapshot->marker;
        degree_array = create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg);
    } else {
        degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    ext_bfs<sid_t>(graph, degree_array, graph, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, ugraph->sgraph[0]->etf, 1);
    
    return ;
}

void plain_test1(const string& idir, const string& odir)
{
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    blog_t<sid_t>* blog = ugraph->blog;
    cout << "snapshot id = " << g->get_snapid() << endl;
    snapshot_t* snapshot = g->get_snapshot();
    //bfs<sid_t>(ugraph->sgraph, ugraph->sgraph, 1); 
    
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    
    string idir1 = "/mnt/disk_huge_1/pradeepk/pradeep_graph/kron_21_16_incr/"; 
    //string idir1 = "../data/kron_21_16_incr/"; 
    plaingraph_manager::prep_graph(idir1, odir);
    
    snapid_t snap_id = g->get_snapid(); 
    uint8_t* level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    /*
    cout << "BFS on whole graph" << endl; 
    bfs<sid_t>(ugraph->sgraph, ugraph->sgraph, 1); 
    
    
    //memset(level_array, 0, v_count*sizeof(uint8_t));
    cout << "BFS on snap id = " << snap_id << endl; 
    snap_bfs<sid_t>(graph, graph, v_count, edge_count, level_array, snap_id - 1, 1);
    

    cout << "multi-snap BFS" << endl;
    multisnap_bfs<sid_t>(graph, graph, v_count, edge_count, snap_id - 1, snap_id , 1);
    */
    memset(level_array, 0, v_count*sizeof(uint8_t));
    snapshot_t* old_snapshot = snapshot;
    snapshot = g->get_snapshot();
    index_t marker = snapshot->marker;
    
    snap_id = old_snapshot->snap_id;
    degree_t* degree_array = create_degreesnap(graph, v_count, old_snapshot, old_snapshot->marker, blog->blog_beg);
    
    cout << "BFS on snap id = " << snap_id << endl; 
    cout << "old marker = " << old_snapshot->marker << " New marker = " << marker << endl;
    mem_bfs<sid_t>(graph, degree_array, graph, degree_array, 
                   old_snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    
    /*
    memset(level_array, 0, v_count*sizeof(uint8_t));
    
    old_snapshot = snapshot;
    snapshot = g->get_snapshot();
    marker = snapshot->marker;
    snap_id = old_snapshot->snap_id;
    degree_array = create_degreesnap(graph, v_count, snap_id);
    cout << "BFS on snap id = " << snap_id << endl; 
    cout << "old marker = " << old_snapshot->marker << " New marker = " << marker << endl;
    mem_bfs<sid_t>(graph, degree_array, graph, degree_array, 
                   old_snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    
    memset(level_array, 0, v_count*sizeof(uint8_t));
    old_snapshot = snapshot;
    marker = snapshot->marker;
    snap_id = old_snapshot->snap_id;
    degree_array = create_degreesnap(graph, v_count, snap_id);
    cout << "BFS on snap id = " << snap_id << endl; 
    cout << "old marker = " << old_snapshot->marker << " New marker = " << marker << endl;
    mem_bfs<sid_t>(graph, degree_array, graph, degree_array, 
                   old_snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    
    */
    /*
    memset(level_array, 0, v_count*sizeof(uint8_t));
    cout << "BFS on first snapshot" << endl; 
    snap_bfs<sid_t>(graph, graph, v_count, edge_count, level_array, snap_id, 1);
    */
    return ;
}

void plain_test2(const string& odir)
{
    //do some setup for plain graphs
    //plaingraph_manager::setup_graph(v_count);    
    
    g->read_graph_baseline(odir);
   

    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    blog_t<sid_t>* blog = ugraph->blog;
   
    uint8_t* level_array = (uint8_t*)mmap(NULL, sizeof(uint8_t)*v_count, 
                            PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0 );
    if (MAP_FAILED == level_array) {
        cout << "Huge page alloc failed for level array" << endl;
        level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    }

    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array = 0;

    if (snapshot) {
        old_marker = snapshot->marker;
        degree_array = create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg);
    } else {
        degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    ext_bfs<sid_t>(graph, degree_array, graph, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, ugraph->sgraph[0]->etf, 1);
    
/*
    index_t edge_count = (v_count << 5);
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    bfs<sid_t>(ugraph->sgraph, ugraph->sgraph, 1); 
    
    snapid_t snap_id = g->get_snapid();
    cout << "multi-snap BFS" << endl;
    cout << "snap id = " << snap_id << endl;
    cout << "durable marker = " <<g->get_snapshot()->durable_marker << endl;
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    multisnap_bfs<sid_t>(graph, graph, v_count, edge_count, snap_id - 1, snap_id , 1);
    
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = snapshot->marker;
    snapshot = snapshot->next;
    snap_id = snapshot->snap_id;
    uint8_t* level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    cout << "BFS on snap id = " << snap_id << endl; 
    cout << "old marker = " << snapshot->marker << " New marker = " << marker << endl;
    degree_t* degree_array = create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg);
    mem_bfs<sid_t>(graph, degree_array, graph, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
*/
    return ;
}

void plain_test3(const string& idir, const string& odir)
{
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    verification<sid_t>(ugraph->sgraph, ugraph->sgraph, 1); 
    return ;
}

void plain_test4(const string& idir, const string& odir)
{
    //do some setup for plain graphs
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
    //do some setup for plain graphs
    //plaingraph_manager::setup_graph(v_count);    
    
    g->read_graph_baseline(odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    verification<sid_t>(ugraph->sgraph, ugraph->sgraph, 1); 
    return ;
}

void plain_test6(const string& odir)
{
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    
    g->read_graph_baseline(odir);
    
    //call mem_bfs
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    index_t edge_count = (v_count << 5);
    uint8_t* level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    
    snap_bfs<sid_t>(graph, graph, v_count, edge_count, level_array, 1, 1);
    return ;
}

void paper_test0(vid_t v_count, const string& idir, const string& odir)
{
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph_paper_num(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    blog_t<sid_t>* blog = ugraph->blog;
   
    uint8_t* level_array = (uint8_t*)mmap(NULL, sizeof(uint8_t)*v_count, PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0 );
    if (MAP_FAILED == level_array) {
        cout << "Huge page alloc failed for level array" << endl;
        level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    }
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array = 0;

    if (snapshot) {
        old_marker = snapshot->marker;
        degree_array = create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg);
    } else {
        degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    mem_bfs<sid_t>(graph, degree_array, graph, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);

}

void paper_test_pr(const string& idir, const string& odir)
{
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph_paper_num(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    blog_t<sid_t>* blog = ugraph->blog;
   
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array = 0;
    if (snapshot) {
        old_marker = snapshot->marker;
        degree_array = create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg);
    } else {
        degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    mem_pagerank<sid_t>(graph, degree_array, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, 5);

}

void paper_test_hop1(const string& idir, const string& odir)
{
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph_paper_num(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    blog_t<sid_t>* blog = ugraph->blog;
   
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array = 0;
    if (snapshot) {
        old_marker = snapshot->marker;
    }
    degree_array = create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg);
    //else { degree_array = (degree_t*) calloc(v_count, sizeof(degree_t)); }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    mem_hop1<sid_t>(graph, degree_array, snapshot, marker, blog->blog_beg, v_count);

}

void paper_test_hop2(const string& idir, const string& odir)
{
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph_paper_num(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    blog_t<sid_t>* blog = ugraph->blog;
   
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array = 0;
    if (snapshot) {
        old_marker = snapshot->marker;
    }
    degree_array = create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg);
    //} else { degree_array = (degree_t*) calloc(v_count, sizeof(degree_t)); }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    mem_hop2<sid_t>(graph, degree_array, snapshot, marker, blog->blog_beg, v_count);

}

void plain_test(vid_t v_count1, const string& idir, const string& odir, int job)
{
    plaingraph_manager::schema_plaingraph();
    v_count = v_count1; 
    switch (job) {
        case 0:
            plain_test0(idir, odir);
            break;
        case 1:
            plain_test1(idir, odir);
            break;
        case 2:
            plain_test2(odir);
            break;
        case 3:
            plain_test3(idir, odir);
            break;
        case 4:
            plain_test4(idir, odir);
            break;
        case 5:
            plain_test5(odir);
            break;
        case 6:
            plain_test6(odir);
            break;
        case 10:
            paper_test0(v_count1, idir, odir);
            break;
        case 11:
            paper_test_pr(idir, odir);
            break;
        case 12:
            paper_test_hop1(idir, odir);
            break;
        case 13:
            paper_test_hop2(idir, odir);
            break;
        default:
            break;
    }
}
