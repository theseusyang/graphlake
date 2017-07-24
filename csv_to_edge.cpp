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

typedef struct __conf_t {
    string filename;
    string predicate;
} conf_t; 

void csv_manager::prep_graph(const string& conf_file, 
                             const string& idirname, 
                             const string& odirname)
{
    string delim = " ";
    string filename, predicate;
    
    conf_t v_conf;
    conf_t e_conf;
    
    vector<conf_t> vfile_list;
    vector<conf_t> efile_list;

    //Read conf_file
    char* line;
    size_t len;
    ssize_t read;
    char* saveptr;
    char* token;
    int value = -1;

    FILE* fp = fopen(conf_file.c_str(), "r");
    if (NULL == fp) assert(0);
    
    while((read = getline(&line, &len, fp)) != -1) {
        if (line[0] == '%' && line[1] == '%') {
            if (0 == strcmp(line, "%%vertex%%")) value = 0;
            else if (0 == strcmp(line, "%%edge%%")) value = 1;
            else assert(0);
    
        } else {
            token = strtok_r(line, delim.c_str(), &saveptr);
            if ( 0 != token) {
               filename = token;
            }

            if (NULL != (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
                predicate = token;
            }

            //Other configuratins for this file
            if(value == 0) {
                v_conf.filename = filename;
                v_conf.predicate = predicate;
                vfile_list.push_back(v_conf);
            } else if (value == 1) {
                e_conf.filename = filename;
                e_conf.predicate = predicate;
                efile_list.push_back(e_conf);
            }
        }      
    }
    
    //Read vertex file
    vector<conf_t>::iterator iter = vfile_list.begin();
    for (; iter != vfile_list.end(); ++iter) {
        prep_vtable(idirname + iter->filename, iter->predicate, odirname);
    }
    
    g->type_done();
    g->type_store(odirname);
    
    //Read edge file
    iter = efile_list.begin();
    for (; iter != efile_list.end(); ++iter) {
        prep_etable(idirname + iter->filename, iter->predicate, odirname);
    }
    
    g->make_graph_baseline();
    g->store_graph_baseline(odirname);
}

//predicate here is the vertex typpe
void csv_manager::prep_vtable(const string& filename, string predicate, const string& odir)
{
    propid_t pid = 0;//type
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
        //First token is "id"
        token = strtok_r(line, delim.c_str(), &saveptr);

        //Other tokens are its properties
        while (NULL == (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
            vtoken.push_back(token);
        }
    }
    
    //read the values now.
    while((read = getline(&line, &len, fp)) != -1) {
        
        //First token is the id, which will be treated as name.
        subject = strtok_r(line, delim.c_str(), &saveptr);
        if( pid == 0) { // type
            g->type_update(subject, predicate);
        }

        //Other tokens are its properties value
        pred_index = 0;
        while (NULL == (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
            //property value
            //could be optimized, as we can easily pass propid, instead of property name
            g->batch_update(subject, token, vtoken[pred_index]);
            ++pred_index;
        }
    }
}

//XXX We are avoiding the edge properties for time being.
//predicate here is the edge type
void csv_manager::prep_etable(const string& filename, string predicate, const string& odir)
{
    string delim = "|";

    string subject, object;

    //Read conf_file
    char* line;
    size_t len;
    ssize_t read;

    char* saveptr;
    //char* token;
    vector<string> vtoken;

    FILE* fp = fopen(filename.c_str(), "r");
    if (NULL == fp) assert(0);
    
    //First line is special
    if ((read = getline(&line, &len, fp)) != -1) {
        
        /* //Not required now
        //First token is "id"
        token = strtok_r(line, delim.c_str(), &saveptr);

        //Other tokens are its properties
        while (NULL == (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
            vtoken.push_back(token);
        }*/
    }
    
    //read the edges now.
    while((read = getline(&line, &len, fp)) != -1) {
        
        //First token is the subject id, which will be treated as name.
        subject = strtok_r(line, delim.c_str(), &saveptr);
        
        //Second token is the object id, which will be treated as name.
        object = strtok_r(NULL, delim.c_str(), &saveptr);
            
        g->batch_update(subject, object, predicate);

        /*
        //Other tokens are edge properties value
        pred_index = 0;
        while (NULL == (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
            //property value
            //could be optimized, as we can easily pass propid, instead of property name
            g->batch_update(subject, token, vtoken[pred_index]);
            ++pred_index;
        }*/
    }

}
