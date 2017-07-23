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
        if (line[0] == '%' && line[1] == '%') {
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
    
    g->type_done();
    g->type_store(odirname);
    
    //Read edge file
    iter = efile_list.begin();
    for (; iter != efile_list.end(); ++iter) {
        prep_etable(idirname + *iter, odirname);
    }
    
    g->make_graph_baseline();
    g->store_graph_baseline(odirname);
}

void csv_manager::prep_vtable(const string& filename, const string& odir)
{
    propid_t pid = 0;//type
    string type_value = "";//XXX 
    string delim = "|";
    int pred_index = 0;

    string subject;

    //Read conf_file
    char* line;
    size_t len;
    ssize_t read;

    char* saveptr;
    char* token;
    vector<string> vtoken;

    FILE* fp = fopen(filename.c_str(), "r");
    if (NULL == fp) assert(0);
    
    //First line is special
    if ((read = getline(&line, &len, fp)) != -1) {
        //First token is the id
        token = strtok_r(line, delim.c_str(), &saveptr);

        //Other tokens are its properties
        while (NULL == (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
            vtoken.push_back(token);
        }
    }
    
    //read the values now.
    while((read = getline(&line, &len, fp)) != -1) {
        
        //First token is the id
        subject = strtok_r(line, delim.c_str(), &saveptr);
        if( pid == 0) { // type
            g->type_update(token, type_value);
        }

        //Other tokens are its properties value
        pred_index = 0;
        while (NULL == (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
            //property value
            g->batch_update(subject, token, vtoken[pred_index]);
            ++pred_index;
        }
    }

}

void csv_manager::prep_etable(const string& filename, const string& odir)
{

}
