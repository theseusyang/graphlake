#include <algorithm>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <assert.h>
#include <string>
#include <map>
#include "graph.h"
#include "type.h"

using std::ifstream;

void graph::prep_type(string typefile, string odir)
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

    v_graph->make_graph_baseline();
    v_graph->store_graph_baseline(odir);
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
        propid_t cf_id;
        map<string, propid_t>::iterator str2pid_iter;
        while (file >> subject >> predicate >> object >> useless_dot) {
            str2pid_iter = str2pid.find(predicate);
            if (str2pid_iter == str2pid.end()) {
                assert(0);
            }
            pid = str2pid_iter->second;
            cf_id = get_cfid(pid);
            if (pid != 0) { //non-type
                cf_info[cf_id]->batch_update(subject, object, pid);
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

status_t graph::remove_edge(const string& idirname, const string& odirname)
{
    struct dirent *ptr;
    DIR *dir;
    string subject, predicate, object, useless_dot;
    int file_count = 0;
    sid_t src_id, dst_id;
    pedge_t* edges;
    sid_t index;
    //propid_t cf_id;
    
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
                assert(0);//can't delete
            }
            pid = str2pid_iter->second;
            //cf_id = get_cfid(pid);
            if (pid != 0) { //non-type
                if (batch_info1[batch_count1].count == MAX_PECOUNT) {
                    void* mem = alloc_buf();
                    if (mem == 0) return eEndBatch;
                    ++batch_count1;
                    batch_info1[batch_count1].count = 0;
                    batch_info1[batch_count1].buf = mem; 
                }
                
                map<string, vid_t>::iterator str2vid_iter = str2vid.find(subject);
                if (str2vid.end() == str2vid_iter) {
                    assert(0);
                } else {
                    src_id = str2vid_iter->second;
                }
                //tid_t type_id = TO_TID(src_id);
                //flag1 |= (1L << type_id);

                str2vid_iter = str2vid.find(object);
                if (str2vid.end() == str2vid_iter) {
                    assert(0);
                } else {
                    dst_id = str2vid_iter->second;
                }
                
                index = batch_info1[batch_count1].count++;
                edges = (pedge_t*) batch_info1[batch_count1].buf;
                edges[index].pid = pid;
                edges[index].src_id = src_id; 
                edges[index].dst_id.value_sid = dst_id;
                
                //cf_info[cf_id]->batch_update(subject, object, pid);
                ++nt_count;
            //} else { //don't delete a type!!!
            }
        }
    }
    closedir(dir);
    return eOK;
}

void graph::make_graph_baseline()
{
    propid_t  cf_id;
    pedge_t*  edges;
    index_t   count;

    for (int j = 0; j <= batch_count; ++j) { 
        edges = (pedge_t*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            cf_id = 0;//XXX
            if (eOK != cf_info[cf_id]->calc_deletededge_count(edges+i)) {
                //delete this one,
            }
        }
    }
    
}
