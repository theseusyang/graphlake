#include <algorithm>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <assert.h>
#include <string>
#include <map>
#include "graph.h"

using std::ifstream;

map <string, vid_t> str2vid;
vid_t vert_count = 0;

graph::graph()
{
    p_info = 0;
    p_count = 0;
}

//Applicable to mostly graphs, labels should be aware of it.
void p_info_t::batch_update(const string& src, const string& dst)
{
    vid_t src_id, dst_id;
    index_t index = 0;
    edge_t* edges = (edge_t*) buf;

    map<string, vid_t>::iterator str2vid_iter = str2vid.find(src);
    if (str2vid.end() == str2vid_iter) {
        src_id = vert_count++;
        str2vid[src] = src_id;
    } else {
        src_id = str2vid_iter->second;
    }

    str2vid_iter = str2vid.find(dst);
    if (str2vid.end() == str2vid_iter) {
        dst_id = vert_count++;
        str2vid[dst] = dst_id;
    } else {
        dst_id = str2vid_iter->second;
    }

    index = count++;
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
}
    
void p_info_t::make_graph_baseline()
{
}

void p_info_t::store_graph_baseline(string dir)
{
}

static int 
is_literal(string str) {
       return ('<' != str[0]);
}

void graph::prep_graph(string idirname)
{
    struct dirent *ptr;
    DIR *dir;
    dir = opendir(idirname.c_str());
    string subject, predicate, object, useless_dot;
    int file_count = 1;
    
    //Read graph file
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        
        ifstream file((idirname + "/" + string(ptr->d_name)).c_str());
        file_count++;
        propid_t pid;
        while (file >> subject >> predicate >> object >> useless_dot) {
            pid = str2pid[predicate];
            p_info[pid]->batch_update(subject, object);
        }
    }

    //make graph
    for (int i = 0; i < p_count; i++) {
        p_info[i]->make_graph_baseline();
    }

    //Store graph
    for (int i = 0; i < p_count; i++) {
        p_info[i]->store_graph_baseline(idirname);
    }
}

void p_info_t::populate_property(const char* property_name)
{
    g->p_info[g->p_count] = this;
    g->p_count++;
    g->str2pid[property_name] = g->p_count;
    
    p_name = gstrdup(property_name);
}
