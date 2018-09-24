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


#include "type.h"
#include "graph.h"
#include "typekv.h"
#include "sgraph.h"
#include "netflow_to_edge.h"

#include "util.h"

using namespace std;
/*map<string, vid_t> str2id;
vid_t vid = 0;

vid_t str2vid(string str) {
    map<string, vid_t>::iterator str2id_iter = str2id.find(str);
    if (str2id_iter == str2id.end()) {
        //insert
        return (str2id[str] = vid++);
        
    } else {
        return str2id_iter->second;
    }
}
*/

inline void parse_line(char* line, netflow_edge_t* netflow) 
{
    if (line[0] == '%') {
        return;
    }
    
    //const char* del = ",\n";
    char* token = 0;
    
    token = strtok_r(line, ",\n", &line);
    netflow->dst_id.second.time = atoi(token);
    token = strtok_r(line, ",\n", &line);
    netflow->dst_id.second.duration = atoi(token);
    
    token = strtok_r(line, ",\n", &line);
    netflow->src_id = g->type_update(token);
    token = strtok_r(line, ",\n", &line);
    netflow->dst_id.first = g->type_update(token);
    
    token = strtok_r(line, ",\n", &line);
    netflow->dst_id.second.protocol = atoi(token);
    
    token = strtok_r(line, ",\n", &line);
    if (token[0] == 'P') {
        netflow->dst_id.second.src_port = atoi(token+4);
    } else {
        netflow->dst_id.second.src_port = atoi(token);
    }
    token = strtok_r(line, ",\n", &line);
    if (token[0] == 'P') {
        netflow->dst_id.second.dst_port = atoi(token+4);
    } else {
        netflow->dst_id.second.dst_port = atoi(token);
    }
    token = strtok_r(line, ",\n", &line);
    
    netflow->dst_id.second.src_packet = atoi(token);
    token = strtok_r(line, ",\n", &line);
    netflow->dst_id.second.dst_packet = atoi(token);
    token = strtok_r(line, ",\n", &line);
    netflow->dst_id.second.src_bytes = atoi(token);
    token = strtok_r(line, ",\n", &line);
    netflow->dst_id.second.dst_bytes = atoi(token);

}

index_t netflow_text_to_bin(const string& textfile, const string& ofile)
{
	size_t file_size = fsize(textfile.c_str());
    size_t estimated_count = file_size/sizeof(netflow_edge_t);
    
    
    FILE* file = fopen(textfile.c_str(), "r");
    assert(file);
    
    netflow_edge_t* netflow_array = (netflow_edge_t*)calloc(estimated_count, 
                                                      sizeof(netflow_edge_t));
    assert(netflow_array);

    netflow_edge_t* netflow = netflow_array;
    
    index_t icount = 0;
	char sss[512];
    char* line = sss;

    while (fgets(sss, sizeof(sss), file)) {
        line = sss;
        parse_line(line, netflow);
        netflow++;
        icount++;
    }
    
    fclose(file);
    
    //write the binary file
    file = fopen(ofile.c_str(), "wb");
    fwrite(netflow_array, sizeof(netflow_edge_t), icount, file);
    fclose(file);
    
    free(netflow_array);
    return 0;
}

index_t netflow_parsefile_and_insert(const string& textfile, pgraph_t<netflow_dst_t>* pgraph)
{
    FILE* file = fopen(textfile.c_str(), "r");
    assert(file);
    
    netflow_edge_t netflow;
    
    index_t icount = 0;
	char sss[512];
    char* line = sss;

    while (fgets(sss, sizeof(sss), file)) {
        line = sss;
        parse_line(line, &netflow);
        pgraph->batch_edge(netflow);
        icount++;
    }
    
    fclose(file);
    return 0;
}

//XXX this is only to convert the text file to binary file     
index_t netflow_manager_t::netflow_text_to_bin_idir(const string& idirname, const string& odirname)
{
    struct dirent *ptr;
    DIR *dir;
    int file_count = 0;
    string filename;
    string ofilename;

    vid_t vid = 0;
        
    //Read graph files
    double start = mywtime();
    dir = opendir(idirname.c_str());
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        filename = idirname + "/" + string(ptr->d_name);
        file_count++;
        ofilename = odirname + "/" + string(ptr->d_name);
        cout << "ifile= "  << filename << endl 
                <<" ofile=" << ofilename << endl;
        netflow_text_to_bin(filename, ofilename);    
        double end = mywtime();
        cout <<" Time = "<< end - start;
        vid = g->get_type_scount();
        cout << " vertex count" << vid << endl;
    }
    closedir(dir);
    vid = g->get_type_scount();
    cout << "vertex count" << vid << endl;
    return file_count;
}


void netflow_manager_t::prep_graph(const string& idirname, const string& odirname)
{
    struct dirent *ptr;
    DIR *dir;
    int file_count = 0;
    string filename;
    string ofilename;

    vid_t vid = 0;
        
    //Read graph files
    double start = mywtime();
    dir = opendir(idirname.c_str());
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        filename = idirname + "/" + string(ptr->d_name);
        file_count++;
        ofilename = odirname + "/" + string(ptr->d_name);
        cout << "ifile= "  << filename << endl 
                <<" ofile=" << ofilename << endl;
        //netflow_parsefile_and_insert(filename, netflow_graph);    
        double end = mywtime();
        cout <<" Time = "<< end - start;
        vid = g->get_type_scount();
        cout << " vertex count" << vid << endl;
    }
    closedir(dir);
    vid = g->get_type_scount();
    cout << "vertex count" << vid << endl;
    return;

}
