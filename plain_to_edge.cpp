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
using namespace std;


index_t residue = 0;

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

void plaingraph_manager::prep_weighted_rmat(const string& graph_file, const string& action_file)
{
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

    //Do ingestion
    propid_t cf_id = g->get_cfid("friend");
    pgraph_t<lite_edge_t>* graph = (pgraph_t<lite_edge_t>*)g->cf_info[cf_id];
    edgeT_t<lite_edge_t>   edge;
    
    double start = mywtime();
    for (int64_t v = 0; v < nv + 1; ++v) {
        for (int64_t i = v_offset[v]; i < v_offset[v+1]; ++i) {
            edge.src_id = v;
            edge.dst_id.first = index[i];
            edge.dst_id.second.value_64b = weight[i];
            status_t status = graph->batch_edge(edge);
        }
    }
    blog_t<lite_edge_t>* blog = graph->blog;
    index_t marker = blog->blog_head;
    cout << "make graph marker = " << marker << endl;
    index_t snap_marker = 0;
    if (marker == 0) return;

    graph->create_marker(marker);
    if (eOK == graph->move_marker(snap_marker)) {
        graph->make_graph_baseline();
        graph->store_graph_baseline();
        g->incr_snapid(snap_marker, snap_marker);
    }
    double end = mywtime();
    cout << "Make graph time = " << end - start << endl;


    //Graph Updates
    int fd1 = open(graph_file.c_str(), O_RDONLY);
    assert(fd1 != -1);
    index_t size1 = fsize(fd1);
    int64_t* buf1 = (int64_t*)malloc(size1);
    pread(fd1, buf1, size1, 0);
    int64_t little_endian1 = buf1[0];
    assert(little_endian1 == 0x1234ABCD);

    int64_t na = buf[1];
    edge_t* edges = (edge_t*)(buf + 2);

    //Do ingestion

    
}

void plaingraph_manager::prep_graph_sync(const string& idirname, const string& odirname)
{
    struct dirent *ptr;
    DIR *dir;
    int file_count = 0;
    string filename;
    propid_t cf_id = g->get_cfid("friend");
    pgraph_t<sid_t>* ugraph = (pgraph_t<sid_t>*)g->cf_info[cf_id];
        
    FILE* file = 0;
    index_t size =  0;
    index_t edge_count = 0;
    
    
    //Read graph files
    double start = mywtime();
    dir = opendir(idirname.c_str());
    blog_t<sid_t>* blog = ugraph->blog;
    edge_t* edge = blog->blog_beg;
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        filename = idirname + "/" + string(ptr->d_name);
        file_count++;
        
        file = fopen((idirname + "/" + string(ptr->d_name)).c_str(), "rb");
        assert(file != 0);
        size = fsize(filename);
        edge_count = size/sizeof(edge_t);
        edge = blog->blog_beg + blog->blog_head;
        if (edge_count != fread(edge, sizeof(edge_t), edge_count, file)) {
            assert(0);
        }
        blog->blog_head += edge_count;
    }
    closedir(dir);
    double end = mywtime();
    cout << "Reading "  << file_count  << " file time = " << end - start << endl;
    start = mywtime();

    index_t marker = blog->blog_head - residue;
    cout << "End marker = " << blog->blog_head;
    cout << "make graph marker = " << marker << endl;
    index_t snap_marker = 0;
    if (marker == 0) return;

    ugraph->create_marker(marker);
    if (eOK == ugraph->move_marker(snap_marker)) {
        ugraph->make_graph_baseline();
        ugraph->store_graph_baseline();
        g->incr_snapid(snap_marker, snap_marker);
    }
    end = mywtime ();
    cout << "Make graph time = " << end - start << endl;

    
    //Second one
    if (residue == 0) return;
    marker = blog->blog_head;
    cout << "make graph marker = " << marker << endl;
    ugraph->create_marker(marker);
    if (eOK == ugraph->move_marker(snap_marker)) {
        ugraph->make_graph_baseline();
        ugraph->store_graph_baseline();
        g->incr_snapid(snap_marker, snap_marker);
    }
}

void plaingraph_manager::prep_graph(const string& idirname, const string& odirname)
{
    struct dirent *ptr;
    DIR *dir;
    int file_count = 0;
    string filename;
    propid_t cf_id = g->get_cfid("friend");
    pgraph_t<sid_t>* ugraph = (pgraph_t<sid_t>*)g->cf_info[cf_id];
        
    FILE* file = 0;
    index_t size =  0;
    index_t edge_count = 0;
    index_t size1 = 0;
    index_t size2 = 0;
    
    batchinfo_t* batch_info;
    int     batch_count = 0;
    batch_info = (batchinfo_t*)calloc(sizeof(batchinfo_t), MAX_BCOUNT);
    batch_info[0].buf = calloc(sizeof(edge_t), MAX_ECOUNT);
    batch_info[0].count = 0; 
    g->create_snapthread();
    
    //Read graph files
    dir = opendir(idirname.c_str());
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        filename = idirname + "/" + string(ptr->d_name);
        file_count++;
        
        file = fopen((idirname + "/" + string(ptr->d_name)).c_str(), "rb");
        size = fsize(filename);
        edge_count = size/sizeof(edge_t);
        size1 = 0;
        size2 = 0;

        do {
            if (batch_info[batch_count].count == MAX_ECOUNT) {
                void* mem = alloc_buf();
                if (mem == 0) {
                    assert(0); 
                } 
                ++batch_count;
                batch_info[batch_count].count = 0;
                batch_info[batch_count].buf = mem; 
            }

            index_t count = batch_info[batch_count].count;
            edge_t* edge = (edge_t*)(batch_info[batch_count].buf) + count;
            size2 = min(MAX_ECOUNT - count, edge_count);
            size1 = fread(edge, sizeof(edge_t), size2, file);
            batch_info[batch_count].count += size1;
            edge_count -= size1;
        } while (edge_count > 0);
    }
    closedir(dir);

    //
    //ugraph->fill_adj_list(ugraph->sgraph, ugraph->sgraph);
    //ugraph->create_snapshot();
    //ugraph->store_graph_baseline();
    //
    blog_t<sid_t>* blog = ugraph->blog;
    
    for (int j = 0; j <= batch_count; ++j) {
        edge_t* edges = (edge_t*)batch_info[j].buf;
        index_t count = batch_info[j].count; 
        for (index_t i = 0; i < count; ++i) {
            status_t status = ugraph->batch_edge(edges[i]);
            if (eEndBatch == status) {
            } else if (eOOM == status) {
                sleep(10);
            }
        }
    }
    ugraph->create_marker(blog->blog_head);
    sleep(10);
}

void plaingraph_manager::prep_graph_paper_num(const string& idirname, const string& odirname)
{
    struct dirent *ptr;
    DIR *dir;
    int file_count = 0;
    string filename;
    propid_t cf_id = g->get_cfid("friend");
    pgraph_t<sid_t>* ugraph = (pgraph_t<sid_t>*)g->cf_info[cf_id];
        
    FILE* file = 0;
    index_t size =  0;
    index_t edge_count = 0;
    blog_t<sid_t>* blog = ugraph->blog;
    
    
    //Read graph files
    double start = mywtime();
    dir = opendir(idirname.c_str());
    edge_t* edge = blog->blog_beg;
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        filename = idirname + "/" + string(ptr->d_name);
        file_count++;
        
        file = fopen((idirname + "/" + string(ptr->d_name)).c_str(), "rb");
        assert(file != 0);
        size = fsize(filename);
        edge_count = size/sizeof(edge_t);
        edge = blog->blog_beg + blog->blog_head;
        if (edge_count != fread(edge, sizeof(edge_t), edge_count, file)) {
            assert(0);
        }
        blog->blog_head += edge_count;
    }
    closedir(dir);
    double end = mywtime();
    cout << "Reading "  << file_count  << " file time = " << end - start << endl;
    start = mywtime();

    index_t marker = blog->blog_head - residue;
    cout << "End marker = " << blog->blog_head;
    cout << "make graph marker = " << marker << endl;
    index_t snap_marker = 0;
    if (marker == 0) return;

    ugraph->create_marker(marker);
    if (eOK == ugraph->move_marker(snap_marker)) {
        ugraph->make_graph_baseline();
        //ugraph->store_graph_baseline();
        g->incr_snapid(snap_marker, snap_marker);
    }
    end = mywtime ();
    cout << "Make graph time = " << end - start << endl;
}
