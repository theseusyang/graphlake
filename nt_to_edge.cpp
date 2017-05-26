#include <algorithm>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <assert.h>
#include <string>
#include <map>
#include "graph.h"


using std::ifstream;

void fill_lubm_inference_type();

void graph::prep_type(string typefile)
{
    string subject, predicate, object, useless_dot;
    int file_count = 0;
    
    //Read typefile for types 
    ifstream file(typefile.c_str());
    int nt_count= 0;
    file_count++;
    file >> subject >> predicate >> object >> useless_dot;
    file >> subject >> predicate >> object >> useless_dot;
    propid_t pid;
    map<string, propid_t>::iterator str2pid_iter;
    while (file >> subject >> predicate >> object >> useless_dot) {
        str2pid_iter = str2pid.find(predicate);
        if (str2pid_iter == str2pid.end()) {
            assert(0);
        }
        pid = str2pid_iter->second;
        if( pid == 0) { // type
            g->type_update(subject, object);
            ++nt_count;
        }
    }
    g->type_done();

}

void graph::prep_graph(string idirname, string odirname)
{
    struct dirent *ptr;
    DIR *dir;
    string subject, predicate, object, useless_dot;
    int file_count = 0;
    
    
    //Read graph file
    dir = opendir(idirname.c_str());
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        
        ifstream file((idirname + "/" + string(ptr->d_name)).c_str());
        int nt_count= 0;
        file_count++;
        file >> subject >> predicate >> object >> useless_dot;
        file >> subject >> predicate >> object >> useless_dot;
        propid_t pid;
        map<string, propid_t>::iterator str2pid_iter;
        while (file >> subject >> predicate >> object >> useless_dot) {
            str2pid_iter = str2pid.find(predicate);
            if (str2pid_iter == str2pid.end()) {
                assert(0);
            }
            pid = str2pid_iter->second;
            if (pid != 0) { //non-type
                cf_info[pid]->batch_update(subject, object);
                ++nt_count;
            //} else { //Is already handled above
            }
        }
    }
    closedir(dir);

    //swap 
    for (int i = 0; i < cf_count; i++) {
        cf_info[i]->swap_log_buffer();
    }
    
    //make graph
    for (int i = 0; i < cf_count; i++) {
        cf_info[i]->make_graph_baseline();
    }

    //Store graph
    for (int i = 0; i < cf_count; i++) {
        cf_info[i]->store_graph_baseline(odirname);
    }
}

void graph::update_graph(string idirname, string odirname)
{
    struct dirent *ptr;
    DIR *dir;
    string subject, predicate, object, useless_dot;
    int file_count = 0;

    //reset the log buffer, flags
    for (int i = 0; i < cf_count; i++) {
        cf_info[i]->reset();
    }
    
    //Read graph file for types 
    dir = opendir(idirname.c_str());
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        
        ifstream file((idirname + "/" + string(ptr->d_name)).c_str());
        int nt_count= 0;
        file_count++;
        file >> subject >> predicate >> object >> useless_dot;
        file >> subject >> predicate >> object >> useless_dot;
        propid_t pid;
        map<string, propid_t>::iterator str2pid_iter;
        while (file >> subject >> predicate >> object >> useless_dot) {
            str2pid_iter = str2pid.find(predicate);
            if (str2pid_iter == str2pid.end()) {
                assert(0);
            }
            pid = str2pid_iter->second;
            if( pid == 0) { // type
                g->type_update(subject, object);
                ++nt_count;
            }
        }
    }
    closedir(dir);
    g->type_done();
    
    
    //Read graph file
    dir = opendir(idirname.c_str());
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        
        ifstream file((idirname + "/" + string(ptr->d_name)).c_str());
        int nt_count= 0;
        file_count++;
        file >> subject >> predicate >> object >> useless_dot;
        file >> subject >> predicate >> object >> useless_dot;
        propid_t pid;
        map<string, propid_t>::iterator str2pid_iter;
        while (file >> subject >> predicate >> object >> useless_dot) {
            str2pid_iter = str2pid.find(predicate);
            if (str2pid_iter == str2pid.end()) {
                assert(0);
            }
            pid = str2pid_iter->second;
            if (pid != 0) { //non-type
                cf_info[pid]->batch_update(subject, object);
                ++nt_count;
            }
        }
    }
    closedir(dir);

    //swap 
    for (int i = 0; i < cf_count; i++) {
        cf_info[i]->swap_log_buffer();
    }
    //make graph
    for (int i = 0; i < cf_count; i++) {
        cf_info[i]->make_graph_update();
    }

    //Store graph
    for (int i = 0; i < cf_count; i++) {
        cf_info[i]->store_graph_update(odirname);
    }
}
