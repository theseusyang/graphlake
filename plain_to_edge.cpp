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


void plaingraph_manager::setup_graph(vid_t v_count)
{
    //do some setup for plain graphs
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    ugraph->flag1 = 1;
    ugraph->flag2 = 1;
    typekv_t* typekv = g->get_typekv();
    typekv->manual_setup(v_count);
    g->prep_graph_baseline();
    g->make_graph_baseline();
    g->store_graph_baseline(); 
    
}

void plaingraph_manager::prep_graph(const string& idirname, const string& odirname)
{
    struct dirent *ptr;
    DIR *dir;
    int file_count = 0;
    string filename;
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
        
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

    /*
    ugraph->fill_adj_list(ugraph->sgraph, ugraph->sgraph);
    ugraph->create_snapshot();
    ugraph->store_graph_baseline(odirname);
    */
    
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
    ugraph->create_marker(ugraph->blog_head);
    sleep(5);
    
    //g->create_snapshot();
    
}

/*
void plaingraph_manager::prep_graph(const string& idirname, const string& odirname)
{
    struct dirent *ptr;
    DIR *dir;
    int file_count = 0;
    string filename;
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
        
    FILE* file = 0;
    index_t size =  0;
    index_t edge_count = 0;
    index_t size1 = 0;
    index_t size2 = 0;
    
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
            if (eOK != ugraph->alloc_batch()) {
                g->swap_log_buffer();
                g->calc_degree();
                g->make_graph_baseline();
                g->store_graph_baseline(odirname);
            }

            index_t count = ugraph->batch_info1[ugraph->batch_count1].count;
            edge_t* edge = (edge_t*)(ugraph->batch_info1[ugraph->batch_count1].buf) + count;
            size2 = min(ugraph->MAXX_ECOUNT - count, edge_count);
            size1 = fread(edge, sizeof(edge_t), size2, file);
            ugraph->batch_info1[ugraph->batch_count1].count += size1;
            edge_count -= size1;
        } while (edge_count > 0);
    }
    closedir(dir);

    ugraph->swap_log_buffer();
    / *
    ugraph->fill_adj_list(ugraph->sgraph, ugraph->sgraph);
    ugraph->create_snapshot();
    ugraph->store_graph_baseline(odirname);
    * /
    
    ugraph->calc_degree();
    ugraph->make_graph_baseline();
    ugraph->store_graph_baseline(odirname);
}
*/
