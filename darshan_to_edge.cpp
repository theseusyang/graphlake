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
#include "darshan_to_edge.h"
#include "graph.h"
#include "type.h"

using std::vector;

void 
darshan_manager::prep_graph(const string& conf_file, 
                            const string& idirname, 
                            const string& odirname)
{
    struct dirent *ptr;
    DIR *dir;
    vector<string> vfile_list;
    int file_count = 0;
    
    //Read graph file
    dir = opendir(idirname.c_str());
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        
        vfile_list.push_back(idirname + "/" + string(ptr->d_name));
        file_count++;
    }
    closedir(dir);
    
    //Read vertex file
    vector<string>::iterator iter = vfile_list.begin();
    for (; iter != vfile_list.end(); ++iter) {
        prep_vtable(*iter, odirname);
    }
    
    g->type_done();
    g->type_store(odirname);
    
    g->prep_graph_baseline();
    g->swap_log_buffer();
    g->calc_degree();
    g->make_graph_baseline();
    g->store_graph_baseline();
}

void 
darshan_manager::prep_vtable(const string& filename, const string& odir)
{
    FILE* fp = fopen(filename.c_str(), "r");
    char* line = 0;
    size_t len = 0;
    ssize_t read;

    //sid_t exe_id, uid, job_id, sub_job_id, file_id;
    string exe, user, job;
    string subject, object, predicate;

    
    //ignore 8 lines
    for (int i = 0; i < 8; i++) {
        getline(&line, &len, fp);
    }
        
    //exe id
    predicate = "exe";
    if (-1 != (read = getline(&line, &len, fp))) {
        if (line[read - 1] == '\n') line[read - 1] = 0;
        
        exe = line +7;
        //exe_id 
        g->type_update(exe, predicate);
    }

    //uid
    predicate = "uid";
    if (-1 != (read = getline(&line, &len, fp))) {
        if (line[read - 1] == '\n') line[read - 1] = 0;
        
        user = line +7;
        //uid = 
        g->type_update(user, predicate);
    }

    //job id
    predicate = "job_id";
    if (-1 != (read = getline(&line, &len, fp))) {
        if (line[read - 1] == '\n') line[read - 1] = 0;
        
        job = line +9;
        //job_id = 
        g->type_update(job, predicate);
    }
   
    //job id and exe
    predicate = "job_to_exe";
    g->batch_update(job, exe, predicate);
    
    //job id and uid
    predicate = "job_to_uid";
    g->batch_update(job, user, predicate);

    //start time
    predicate = "start_time";
    if (-1 != (read = getline(&line, &len, fp))) {
        if (line[read - 1] == '\n') line[read - 1] = 0;
        
        object = line +14;
        g->batch_update(job, object, predicate);
    }
    //start time in human readable format, skip it.
    if (-1 == (read = getline(&line, &len, fp))) {
        assert(0);
    }

    //end time
    predicate = "end_time";
    if (-1 != (read = getline(&line, &len, fp))) {
        if (line[read - 1] == '\n') line[read - 1] = 0;
        
        object = line +12;
        g->batch_update(job, object, predicate);
    }
    //end time in human readable format, skip it.
    if (-1 == (read = getline(&line, &len, fp))) {
        assert(0);
    }

    //nprocs
    predicate = "nprocs";
    if (-1 != (read = getline(&line, &len, fp))) {
        if (line[read - 1] == '\n') line[read - 1] = 0;
        
        object = line +10;
        g->batch_update(job, object, predicate);
    }

    //ignore 8 lines. 
    for (int i = 0; i < 8; i++) {
        getline(&line, &len, fp);
    }

    string delim = " \t";
    char* myline = 0;
    char* saveptr;
    char* token;
    prop_pair_t prop_pair;
    propid_t pid = 0;

    //Mount points
    while (1 != (read = getline(&line, &len, fp))) {//blank line
        if (line[read - 1] == '\n') line[read - 1] = 0;
         
        myline = line +15;//
        token = strtok_r(myline, delim.c_str(), &saveptr);
        if ( 0 == token) {
            assert(0);
        }
        predicate = "device_name";
        subject = token;
        g->type_update(subject, predicate);

        if ( 0 == (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
            //Few files don't have IO operations
            if (-1 == (read = getline(&line, &len, fp))) {//EOF
                return;
            }

            assert(0);
        }
        object = token;
        predicate = "mount_point";
        g->type_update(object, predicate);
        
        if( 0 == (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
            assert(0);
        }
        prop_pair.name = "fs_type";
        prop_pair.value = token;//file system type value
        
        predicate = "mounted_at";
        pid = g->get_cfid(predicate.c_str());
        g->batch_update(subject, object, pid, 1, &prop_pair);
    }

    //ignore 51 lines. 
    for (int i = 0; i < 56; i++) {
        getline(&line, &len, fp);
    }
    
    //IO operations
    string rank = "-1";
    string prev_rank = "-1";
    string filename_hash, prev_filename_hash;
    string sub_job, predicate_value, mount_fs, mount_point;
    double int_value;

    while (-1 != (read = getline(&line, &len, fp))) {
        if (line[read - 1] == '\n') line[read - 1] = 0;
        
        //rank
        if ( 0 == (token = strtok_r(line, delim.c_str(), &saveptr))) {
            assert(0);
        }
        rank = token;
        if (0 == rank.compare("-1")) {
            sub_job = job;
        } else if (0 != rank.compare(prev_rank)) {//not equal, create
            predicate = "sub_job_type";
            sub_job = job + rank; // make a unique sub process
            //sub_job_id = 
            g->type_update(sub_job, predicate);
            predicate = "sub_job";
            pid = g->get_cfid(predicate.c_str());
            prop_pair.name = "rank";
            prop_pair.value = rank;
            g->batch_update(job, sub_job, pid, 1, &prop_pair);
            prev_rank = rank;
        }
        
        //filename hash
        if(0 == (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
            assert(0);
        }
        filename_hash = token;

        //file operation type
        if ( 0 == (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
            assert(0);
        }
        predicate = token;
        
        //file operation value
        if ( 0 == (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
            assert(0);
        }
        predicate_value = token;
        sscanf(predicate_value.c_str(), "%lf", &int_value);
        
        if (int_value == 0 || int_value == -1) {
            continue;
        }
        prop_pair.name = "value";
        prop_pair.value = predicate_value;
       
        //ignore file suffix
        if ( 0 == (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
            assert(0);
        }
        
        //mount point
        if ( 0 == (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
            assert(0);
        }
        mount_point = token;
        
        //file system type.
        if ( 0 == (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
            assert(0);
        }
        mount_fs = token;

        //filename should be a vertex
        if( 0 != prev_filename_hash.compare(filename_hash)) {//not equal
            prev_filename_hash = filename_hash;
            // Any other predicate type for file names ??
            //file_id = 
            g->type_update(filename_hash, "file"); 
        }

        //Add this line and edge property value to db 
        pid = g->get_cfid(predicate.c_str());
        g->batch_update(sub_job, filename_hash, pid, 1, &prop_pair);
    }
}

