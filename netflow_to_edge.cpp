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
map<string, vid_t> str2id;
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

index_t netflow_text_to_bin(const string& textfile, const string& ofile)
{
	size_t file_size = fsize(textfile.c_str());
	//fd = open( textfile.c_str(), O_RDWR, 00777);
	//ss_head = (char*)mmap(NULL,file_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    
    size_t estimated_count = file_size/sizeof(netflow_edge_t);
    FILE* file = fopen(textfile.c_str(), "r");
    netflow_edge_t* netflow_array = (netflow_edge_t*)calloc(estimated_count, 
                                                      sizeof(netflow_edge_t));
    netflow_edge_t* netflow = netflow_array;
    index_t icount = 0;
	char sss[256];
    char* line = sss;
    char* token = 0;
    //const char* del = ",\n";

    while (fgets(sss, sizeof(sss), file)) {
        line = sss;
        if (line[0] == '%') {
            continue;
        }
        
        token = strtok_r(line, ",\n", &line);
        netflow->dst_id.netflow.time = atoi(token);
        token = strtok_r(line, ",\n", &line);
        netflow->dst_id.netflow.duration = atoi(token);
        
        token = strtok_r(line, ",\n", &line);
        netflow->src_id = str2vid(token);
        token = strtok_r(line, ",\n", &line);
        netflow->dst_id.dst_id = str2vid(token);
        
        token = strtok_r(line, ",\n", &line);
        netflow->dst_id.netflow.protocol = atoi(token);
        
        token = strtok_r(line, ",\n", &line);
        if (token[0] == 'P') {
            netflow->dst_id.netflow.src_port = atoi(token+4);
        } else {
            netflow->dst_id.netflow.src_port = atoi(token);
        }
        token = strtok_r(line, ",\n", &line);
        if (token[0] == 'P') {
            netflow->dst_id.netflow.dst_port = atoi(token+4);
        } else {
            netflow->dst_id.netflow.dst_port = atoi(token);
        }
        token = strtok_r(line, ",\n", &line);
        
        netflow->dst_id.netflow.src_packet = atoi(token);
        token = strtok_r(line, ",\n", &line);
        netflow->dst_id.netflow.dst_packet = atoi(token);
        token = strtok_r(line, ",\n", &line);
        netflow->dst_id.netflow.src_bytes = atoi(token);
        token = strtok_r(line, ",\n", &line);
        netflow->dst_id.netflow.dst_bytes = atoi(token);
        //netflow++;
        icount++;
    }
    fclose(file);
    //write the binary file
    //file = fopen(ofile.c_str(), "wb");
    //fwrite(netflow_array, sizeof(netflow_edge_t), icount, file);
    //fclose(file);
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
        
    
    //Read graph files
    double start = mywtime();
    dir = opendir(idirname.c_str());
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        filename = idirname + "/" + string(ptr->d_name);
        file_count++;
        ofilename = odirname + "/" + string(ptr->d_name);
        netflow_text_to_bin(filename, ofilename);    
        double end = mywtime();
        cout << "ifile= "  << filename << endl 
                <<" ofile=" << ofilename << endl
                <<" Time = "<< end - start << endl;
    }
    closedir(dir);
    cout << "vertex count" << vid << endl;
    return file_count;
}


void netflow_manager_t::prep_graph(const string& idirname, const string& odirname)
{
//read_idir<netflow_dst_t>(idirname, odirname);

}
