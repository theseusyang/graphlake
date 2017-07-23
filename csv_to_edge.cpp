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
#include "graph.h"
#include "type.h"

using std::vector;

void csv_manager::prep_graph(const string& conf_file, 
                             const string& idirname, 
                             const string& odirname)
{
    vector<string> vfile_list;
    vector<string> efile_list;

    //Read conf_file
    char* line;
    size_t len;
    ssize_t read;
    int value = -1;

    FILE* fp = fopen(conf_file.c_str(), "r");
    if (NULL == fp) assert(0);
    
    while((read = getline(&line, &len, fp)) != -1) {
        if (line[0] == '%' and line[1] == '%') {
            if (strcmp(line, "%%vertex%%")) value = 0;
            else if (strcmp(line, "%%edge%%")) value = 1;
            else assert(0);
    
        } else {
            if(value == 0) {
                vfile_list.push_back(line);
            } else if (value == 1) {
                efile_list.push_back(line);
            }
        }      
    }
    
    //Read vertex file
    vector<string>::iterator iter = vfile_list.begin();
    for (; iter != vfile_list.end(); ++iter) {
        prep_vtable(idirname + *iter, odirname);
    }
    
    //Read edge file
    iter = efile_list.begin();
    for (; iter != efile_list.end(); ++iter) {
        prep_etable(idirname + *iter, odirname);
    }
}

void csv_manager::prep_vtable(const string& filename, const string& odir)
{

}

void csv_manager::prep_etable(const string& filename, const string& odir)
{

}
