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
#include "csv_to_edge.h"
#include "type.h"
#include "graph.h"
#include "typekv.h"
#include "sgraph.h"

#include "iterative_analytics.h"
using namespace std;


void plaingraph_manager::prep_graph(const string& idirname, const string& odirname)
{
    struct dirent *ptr;
    DIR *dir;
    int file_count = 0;
    string filename;
    propid_t cf_id = g->get_cfid("friend");
        
    FILE* file = 0;
    index_t size =  0;
    index_t edge_count = 0;
    index_t size1 = 0;
    index_t size2 = 0;
    
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    
    //Read graph file
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
                ugraph->swap_log_buffer();
                ugraph->make_graph_baseline();
                ugraph->store_graph_baseline(odirname);
            }
            size2 = min(ugraph->MAXX_ECOUNT, edge_count);
            size1 = fread(ugraph->batch_info1[ugraph->batch_count1].buf, 
                               sizeof(edge_t), size2, file);
            ugraph->batch_info1[ugraph->batch_count1].count = size1;
            edge_count -= size1;
        } while (edge_count > 0);
    }
    closedir(dir);
    ugraph->swap_log_buffer();

    ugraph->make_graph_baseline();
    ugraph->store_graph_baseline(odirname);
}