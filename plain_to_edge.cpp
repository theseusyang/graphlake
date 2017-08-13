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
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];

    
    //Read graph file
    dir = opendir(idirname.c_str());
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        filename = idirname + "/" + string(ptr->d_name);
        FILE* file = fopen((idirname + "/" + string(ptr->d_name)).c_str(), "rb");
        uint64_t size = fsize(filename);
        uint64_t edge_count = size/sizeof(edge_t);
        file_count++;
        uint64_t size1 = fread(ugraph->batch_info[0].buf, sizeof(edge_t), edge_count, file);
        ugraph->batch_info[0].count = size1;
        ugraph->make_graph_baseline();
        ugraph->store_graph_baseline(odirname);

    }
    closedir(dir);
    
}
