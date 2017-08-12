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

#include "type.h"
#include "sgraph.h"

using namespace std;

class plaingraph_manager {
    public:
    static void prep_graph(const string& idirname, const string& odirname);
};

void plaingraph_manager::prep_graph(const string& idirname, const string& odirname)
{
    struct dirent *ptr;
    DIR *dir;
    sid_t subject, object;
    int file_count = 0;
    string filename;
    dgraph_t* dgraph = new dgraph_t;
    
    //Read graph file
    dir = opendir(idirname.c_str());
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        filename = idirname + "/" + string(ptr->d_name);
        FILE* file = fopen((idirname + "/" + string(ptr->d_name)).c_str(), "rb");
        uint64_t size = fsize(filename);
        uint64_t edge_count = size/sizeof(edge_t);
        file_count++;
        fread(dgraph->batch_info[0].buf, sizeof(edge_t), size, file);    
    }
    closedir(dir);
    
    dgraph->make_graph_baseline();
    dgraph->store_graph_baseline(odirname);
}
