#include <getopt.h>
#include <iostream>
#include <dirent.h>

#include "all.h"
#include "csv_to_edge.h"
#include "iterative_analytics.h"
#include "ext_iterative_analytics.h"
#include "mem_iterative_analytics.h"
#include "snap_iterative_analytics.h"

using namespace std;

void prep_graph_sync(const string& idirname, const string& odirname);
    
extern index_t residue;
vid_t v_count = 0;

template <class T>
void split_graph(const string& idirname, const string& odirname)
{
    
    struct dirent *ptr;
    DIR *dir;
    int file_count = 0;
    string filename;
        
    FILE* file = 0;
    index_t size =  0;
    index_t edge_count = 0;

    blog_t<T> my_blog; 
    blog_t<T>* blog = &my_blog;
    memset(blog, sizeof(my_blog), 0);
    blog->blog_beg = (edgeT_t<T>*) calloc((1L<<33), sizeof(edgeT_t<T>)); 
    
    //Read graph files
    double start = mywtime();
    dir = opendir(idirname.c_str());
    edgeT_t<T>* edge = blog->blog_beg;
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        filename = idirname + "/" + string(ptr->d_name);
        file_count++;
        
        file = fopen((idirname + "/" + string(ptr->d_name)).c_str(), "rb");
        assert(file != 0);
        size = fsize(filename);
        edge_count = size/sizeof(edgeT_t<T>);
        edge = blog->blog_beg + blog->blog_head;
        if (edge_count != fread(edge, sizeof(edgeT_t<T>), edge_count, file)) {
            assert(0);
        }
        blog->blog_head += edge_count;
        fclose(file);
    }
    closedir(dir);
    double end = mywtime();
    cout << "Reading "  << file_count  << " file time = " << end - start << endl;
    cout << "Creating " << residue << " graphs of equal size" << endl;

    start = mywtime();

    index_t marker = blog->blog_head/residue;
    index_t old_marker = 0;
    index_t new_marker = 0;
    char  suffix[8];
    for (index_t i = 1; i <= residue; ++i) {
        sprintf(suffix, "%ld",i);
          
        new_marker = marker*i;
        cout << "graph marker = " << new_marker << endl;
        filename = odirname + "part" + suffix + ".dat";
        cout << "Filename = " << filename << endl;
        file = fopen(filename.c_str(), "wb");
        assert(file  != 0);
        edge_count = new_marker - old_marker;
        if (edge_count != fwrite(blog->blog_beg + old_marker, 
                                 sizeof(edgeT_t<T>), edge_count, file)) {
            assert(0);
        }
        fclose(file);
        old_marker = new_marker;
    }

    end = mywtime ();
    cout << "Make graph time = " << end - start << endl;
}

void plain_test0(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    prep_graph_sync(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    onegraph_t<sid_t>*   sgraph = ugraph->sgraph[0];
    vert_table_t<sid_t>* graph = sgraph->get_begpos();
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
        
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));

    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    ext_bfs<sid_t>(sgraph, degree_array, sgraph, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    
    return;
}

void plaind_test0(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraphd();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    prep_graph_sync(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    pgraph_t<sid_t>* pgraph = (pgraph_t<sid_t>*)g->cf_info[cf_id];
    onegraph_t<sid_t>* sgraph_out = pgraph->sgraph_out[0];
    onegraph_t<sid_t>* sgraph_in  = pgraph->sgraph_in[0];
    blog_t<sid_t>* blog = pgraph->blog;
   
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
    degree_t* degree_out = 0;
    degree_t* degree_in = 0;

    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnapd (sgraph_out, sgraph_in, snapshot, marker, blog->blog_beg,
                            degree_out, degree_in);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;


    ext_bfs<sid_t>(sgraph_out, degree_out, sgraph_in, degree_in, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    return ;
}
            
void weight_dtest0(const string& idir, const string& odir)
{
    plaingraph_manager::schema_weightedgraphd();
    plaingraph_manager::setup_weightedgraph(v_count);    
}

void weight_dtest1(const string& odir)
{
    plaingraph_manager::schema_weightedgraphu();
    plaingraph_manager::setup_weightedgraph(v_count);    
}

//template <class T>
void weighted_dtest0(const string& idir, const string& odir)
{
    
    plaingraph_manager::schema_weightedgraphu();
    
    //Is called from below function
    //plaingraph_manager::setup_weightedgraph(v_count);    
    
    string graph_file = idir + "g.bin";
    string action_file = idir + "a.bin"; 
    //plaingraph_manager::prep_weighted_rmat(graph_file, action_file);
    
    int fd = open(graph_file.c_str(), O_RDONLY);
    assert(fd != -1);
    index_t size = fsize(fd);
    int64_t* buf = (int64_t*)malloc(size);
    pread(fd, buf, size, 0);
    int64_t little_endian = buf[0];
    assert(little_endian == 0x1234ABCD);

    int64_t nv = buf[1]; 
    int64_t ne = buf[2];
    int64_t* v_offset = buf + 3;
    int64_t* index = v_offset + nv + 1; //+1 for offset in CSR 
    int64_t* weight = index + ne;
    lite_edge_t* nebrs = (lite_edge_t*)malloc(ne*sizeof(lite_edge_t));

    for (int64_t i = 0; i < ne; i++) {
        nebrs[i].first = index[i];
        nebrs[i].second.value = weight[i];  
    }

    //Create number of vertex
    v_count = nv;
    plaingraph_manager::setup_weightedgraph(v_count);
    
    //Do ingestion
    /*
     * We are doing something to be compliant with stinger test
     * 1. the graph file is CSR file, we don't expect that
     * 2. The graph already stores the reverse edge, we don't expect that
     * 3. Stinger does something directly with the memory that is allocated 
     *      for graph read, for initial graph building.
     */
    propid_t cf_id = g->get_cfid("friend");
    pgraph_t<lite_edge_t>*    graph = (pgraph_t<lite_edge_t>*)g->cf_info[cf_id];
    blog_t<lite_edge_t>*       blog = graph->blog;
    onegraph_t<lite_edge_t>* sgraph = graph->sgraph[0];
    nebrcount_t<lite_edge_t>* degree_array = sgraph->nebr_count;
    
    double start = mywtime();
    
    #pragma omp parallel
    {
        index_t   nebr_count = 0;
        
        #pragma omp for
        for (int64_t v = 0; v < nv; ++v) {
            nebr_count = v_offset[v+1] - v_offset[v];
            degree_array[v].add_count = nebr_count;
        }
        sgraph->setup_adjlist();
        
        #pragma omp for
        for (int64_t v = 0; v < nv; ++v) {
            nebr_count = v_offset[v+1] - v_offset[v];
            sgraph->add_nebr_bulk(v, nebrs + v_offset[v], nebr_count);
        }
    }
    
    double end = mywtime();
    
    blog->blog_head += ne;
    index_t marker = blog->blog_head;
    index_t snap_marker = 0;
    if (marker == 0) return;

    graph->create_marker(marker);
    if (eOK == graph->move_marker(snap_marker)) {
        blog->blog_tail = marker;
        //graph->make_graph_baseline();
        //graph->store_graph_baseline();
        g->incr_snapid(snap_marker, snap_marker);
    }
    cout << "Batch time = " << end - start << endl;
    end = mywtime();
    cout << "make graph marker = " << marker << endl;
    cout << "Make graph time = " << end - start << endl;

    free(buf);
    free(nebrs);

    //-------Run bfs and PR------
    uint8_t* level_array = (uint8_t*)mmap(NULL, sizeof(uint8_t)*v_count, 
                            PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0 );
    
    if (MAP_FAILED == level_array) {
        cout << "Huge page alloc failed for level array" << endl;
        level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    }
    
    
    vert_table_t<lite_edge_t>* beg_pos = sgraph->get_begpos();
    degree_t* degree_snap = 0;
    degree_snap = (degree_t*) calloc(v_count, sizeof(degree_t));

    index_t old_marker = 0;
    snapshot_t* snapshot = g->get_snapshot();
    marker = blog->blog_head;
    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnap(beg_pos, v_count, snapshot, marker, blog->blog_beg, degree_snap);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;
    
    mem_bfs<lite_edge_t>(beg_pos, degree_snap, beg_pos, degree_snap, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 0);
    
    mem_pagerank_epsilon<lite_edge_t>(beg_pos, degree_snap, degree_snap, 
                   snapshot, marker, blog->blog_beg,
                   v_count, 1e-8);

    free(degree_snap);
    free(level_array);
    


    //-------Graph Updates-------
    g->create_snapthread();
    int fd1 = open(action_file.c_str(), O_RDONLY);
    assert(fd1 != -1);
    index_t size1 = fsize(fd1);
    int64_t* buf1 = (int64_t*)malloc(size1);
    pread(fd1, buf1, size1, 0);
    int64_t little_endian1 = buf1[0];
    assert(little_endian1 == 0x1234ABCD);

    int64_t na = buf1[1];
    edge_t* edges = (edge_t*)(buf1 + 2);

    //Do ingestion
    start = mywtime();
    int64_t del_count = 0;
    
    //#pragma omp parallel 
    { 
    int64_t src, dst;
    edgeT_t<lite_edge_t> edge;

    //#pragma omp for reduction(+:del_count)
    for (int64_t i = 0; i < na; i++) {
        src = edges[i].src_id;
        edge.dst_id.second.value = 1;
        dst = edges[i].dst_id;
        if (src >= 0) {
            edge.src_id = src;
            edge.dst_id.first = dst;
            graph->batch_edge(edge);
        } else {
            edge.src_id = DEL_SID(-src);
            edge.dst_id.first = DEL_SID(-dst);
            graph->batch_edge(edge);
            ++del_count;
        }
    }
    }
    
    end = mywtime();
    
    marker = blog->blog_head;
    if (marker != blog->blog_marker) {
        graph->create_marker(marker);
    }
    
    //if (eOK == graph->move_marker(snap_marker)) {
        //graph->make_graph_baseline();
        //graph->store_graph_baseline();
        //g->incr_snapid(snap_marker, snap_marker);
    //}
    cout << "batch Edge time = " << end - start << endl;
    cout << "no of actions " << na << endl;
    cout << "del_count "<<del_count << endl;
    while (blog->blog_tail != blog->blog_head) {
        usleep(10);
    }
    end = mywtime();
    cout << "Make graph time = " << end - start << endl;
    

    //-------Run bfs and PR------
    level_array = (uint8_t*)mmap(NULL, sizeof(uint8_t)*v_count, 
                            PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0 );
    
    if (MAP_FAILED == level_array) {
        cout << "Huge page alloc failed for level array" << endl;
        level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    }
    
    degree_snap = (degree_t*) calloc(v_count, sizeof(degree_t));

    snapshot = g->get_snapshot();
    marker = blog->blog_head;
    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnap(beg_pos, v_count, snapshot, marker, blog->blog_beg, degree_snap);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;
    
    mem_bfs<lite_edge_t>(beg_pos, degree_snap, beg_pos, degree_snap, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 0);
    
    mem_pagerank_epsilon<lite_edge_t>(beg_pos, degree_snap, degree_snap, 
                   snapshot, marker, blog->blog_beg,
                   v_count, 1e-8);

    free(degree_snap);


    return ;
}

void plain_test1(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraph();
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
    degree_t* degree_array = 0; 
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));
    create_degreesnap(graph, v_count, old_snapshot, old_snapshot->marker, blog->blog_beg, degree_array);
    
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

void plaind_test1(const string& odir)
{
    plaingraph_manager::schema_plaingraphd();
    //do some setup for plain graphs
    //plaingraph_manager::setup_graph(v_count);    
    propid_t cf_id = g->get_cfid("friend");
    pgraph_t<sid_t>* pgraph = (pgraph_t<sid_t>*)g->cf_info[cf_id];
    pgraph->flag1 = 1;
    pgraph->flag2 = 1;
    
    g->read_graph_baseline();
   
    onegraph_t<sid_t>* sgraph_out = pgraph->sgraph_out[0];
    onegraph_t<sid_t>* sgraph_in  = pgraph->sgraph_in[0];
    blog_t<sid_t>* blog = pgraph->blog;
   
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
    degree_t* degree_out = 0;
    degree_t* degree_in  = 0;

    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnapd(sgraph_out, sgraph_in, snapshot, marker, blog->blog_beg,
                           degree_out, degree_in);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    ext_bfs<sid_t>(sgraph_out, degree_out, sgraph_in, degree_in, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    
    return ;
}

void plain_test2(const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    //plaingraph_manager::setup_graph(v_count);    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    ugraph->flag1 = 1;
    ugraph->flag2 = 1;
    
    g->read_graph_baseline();
   
/*
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];*/
    onegraph_t<sid_t>* sgraph = ugraph->sgraph[0];
    vert_table_t<sid_t>* graph = sgraph->get_begpos();
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
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));

    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    ext_bfs<sid_t>(sgraph, degree_array, sgraph, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    
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
    plaingraph_manager::schema_plaingraph();
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
    plaingraph_manager::schema_plaingraph();
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
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    //plaingraph_manager::setup_graph(v_count);    
    
    g->read_graph_baseline();
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    verification<sid_t>(ugraph->sgraph, ugraph->sgraph, 1); 
    return ;
}

void plain_test6(const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    
    g->read_graph_baseline();
    
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
    plaingraph_manager::schema_plaingraph();
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
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));

    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    mem_bfs<sid_t>(graph, degree_array, graph, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);

}

void paper_test_chain_bfs(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph_paper_chain(idir, odir);
    
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
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));

    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;
    
	
	ext_bfs<sid_t>(ugraph->sgraph[0], degree_array, ugraph->sgraph[0], degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
	
	/*
    mem_bfs<sid_t>(graph, degree_array, graph, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    */
}
void paper_test_pr_chain(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph_paper_chain(idir, odir);
    
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
        create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    mem_pagerank<sid_t>(graph, degree_array, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, 5);

}

void paper_test_pr(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraph();
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
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));
    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    mem_pagerank<sid_t>(graph, degree_array, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, 5);

}

void paper_test_hop1_chain(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph_paper_chain(idir, odir);
    
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
    create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    mem_hop1<sid_t>(graph, degree_array, snapshot, marker, blog->blog_beg, v_count);

}

void paper_test_hop1(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraph();
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
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));
    if (snapshot) {
        old_marker = snapshot->marker;
    }
    create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    mem_hop1<sid_t>(graph, degree_array, snapshot, marker, blog->blog_beg, v_count);

}

void paper_test_hop2_chain(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph_paper_chain(idir, odir);
    
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

}

void paper_test_hop2(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraph();
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
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t)); 
    if (snapshot) {
        old_marker = snapshot->marker;
    }
    create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg,degree_array);

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    mem_hop2<sid_t>(graph, degree_array, snapshot, marker, blog->blog_beg, v_count);

}

void llama_test_bfs(const string& odir);
void llama_test_pr(const string& odir);
void llama_test_pr_push(const string& odir);

void plain_test(vid_t v_count1, const string& idir, const string& odir, int job)
{
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
            split_graph<sid_t>(idir, odir);
            break;
        case 4:
            split_graph<lite_edge_t>(idir, odir);
            break;
        case 5:
            weight_dtest0(idir, odir);
            break;
        case 6:
            weight_dtest1(odir);
            break;
        case 7:
            plaind_test0(idir, odir);
            break;
        case 8:
            plaind_test1(odir);
            break;
        case 9:
            //stinger test
            weighted_dtest0(idir, odir);
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
        case 14:
            paper_test_chain_bfs(idir, odir);
            break;
        case 15:
            paper_test_pr_chain(idir, odir);
            break;
        case 16:
            paper_test_hop1_chain(idir, odir);
            break;
        case 17:
            paper_test_hop2_chain(idir, odir);
            break;
        case 18:
            llama_test_bfs(odir);
            break;
        case 19:
            llama_test_pr(odir);
            break;
        case 20:
            llama_test_pr_push(odir);
            break;
        
        case 100:
            //plain_test4(idir, odir);
            //plain_test5(odir);
            plain_test6(odir);
        default:
            break;
    }
}
