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

void 
darshan_manager::prep_graph(const string& conf_file, 
                            const string& idir, 
                            const string& odir)
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
    
    g->make_graph_baseline();
    g->store_graph_baseline(odirname);
}

void 
darshan_manager::prep_vtable(const string& filename, const string& odir)
{
    FILE* fp = fopen(filename.c_str(), "r");
    char* line = 0;
    size_t len = 0;
    ssize_t read;

    sid_t exe_id, uid, job_id;
    string exe, user, job;
    string subject, object, predicate;

    
    //ignore 8 lines
    for (int i = 0; i < 8; i++) {
        getline(&line, &len, fp);
    }
        
    //exe id
    object = "exe";
    if (-1 != (read = getline(&line, &len, fp))) {
        if (line[read - 1] == '\n') line[read - 1] = '0';
        
        exe = line +7;
        subject = exe;
        exe_id = g->type_update(subject, object);
    }

    //uid
    object = "uid";
    if (-1 != (read = getline(&line, &len, fp))) {
        if (line[read - 1] == '\n') line[read - 1] = '0';
        
        user = line +7;
        subject = user;
        uid = g->type_update(subject, object);
    }

    //job id
    object = "job_id";
    if (-1 != (read = getline(&line, &len, fp))) {
        if (line[read - 1] == '\n') line[read - 1] = '0';
        
        job = line +9;
        subject = job; 
        job_id = g->type_update(subject, object);
    }
   
    //job id and exe
    predicate = "job_to_exe";
    g->batch_update(job, exe, predicate);
    
    //job id and uid
    predicate = "job_to_uid";
    g->batch_update(job, uid, predicate);

    //start time
    predicate = "start_time";
    if (-1 != (read = getline(&line, &len, fp))) {
        if (line[read - 1] == '\n') line[read - 1] = '0';
        
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
        if (line[read - 1] == '\n') line[read - 1] = '0';
        
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
        if (line[read - 1] == '\n') line[read - 1] = '0';
        
        object = line +10;
        g->batch_update(job, object, predicate);
    }

    //ignore 8 lines. 
    for (int i = 0; i < 8; i++) {
        getline(&line, &len, fp);
    }

    //Mount points
    string delim = " ";
    char* myline = 0;
    char* saveptr;
    char* token;
    prop_pair_t prop_pair;

    if (-1 != (read = getline(&line, &len, fp))) {
        if (line[read - 1] == '\n') line[read - 1] = '0';
         
        myline = line +15;//
        token = strtok_r(myline, delim.c_str(), &saveptr);
        if ( 0 != token) {
            predicate = "device_name";
            subject = token;
            g->type_update(subject, predicate);
        }
        
        token = strtok_r(NULL, delim.c_str(), &saveptr);
        if ( 0 != token) {
            prdicate = "mounted_at"
            object = token;//mount point
        }
        
        token = strtok_r(NULL, delim.c_str(), &saveptr);
        if ( 0 == token) {
            assert(0);
        }
        prop_pair.name = "fs_type";
        prop_pair.value = token;//file system type value
        g->batch_update(subject, object, predicated, 1, &prop_pair);
    }

    //ignore 51 lines. 
    for (int i = 0; i < 51; i++) {
        getline(&line, &len, fp);
    }
    
    //IO operations
    string filename_hash;

    while (-1 != (read = getline(&line, &len, fp))) {
        if (line[read - 1] == '\n') line[read - 1] = '0';
        
        if ( 0 != (token = strtok_r(line, delim.c_str(), &saveptr))) {
            assert(0);
        }
        prop_pair[0].name = "rank";
        prop_pair[0].value = token;
        
        if(0 != (token = strtok_r(line, delim.c_str(), &saveptr))) {
            assert(0);
        }
        filename_hash = token;

        if ( 0 != (token = strtok_r(line, delim.c_str(), &saveptr))) {
            assert(0);
        }
        predicate = token;
        
        if ( 0 != (token = strtok_r(line, delim.c_str(), &saveptr))) {
            assert(0);
        }
        predicate_value = token;
        sscanf(predicate_value.c_str(), "%d", int_value);
        
        if (int_value == 0 || int_value) {
            continue;
        }
        prop_pair[1].name = ""; //XXX
        prop_pair[1].value = predicate_value;
       
        //ignore file suffix
        if ( 0 != (token = strtok_r(line, delim.c_str(), &saveptr))) {
            assert(0);
        }
        
        //mount point
        if ( 0 != (token = strtok_r(line, delim.c_str(), &saveptr))) {
            assert(0);
        }
        mount_point = token;

        
        if( 0 != prev_filename_hash.compare(filename_hash)) {//not equal
            prev_filename_hash = filename_hash;
            g->type_update(filename_hash, mount_point); //XXX
        }

        //ignore the last word, i.e. file system type.

        //Add this line to db
        g->batch_update(job_id, filename_hash, predicate, 2, &prop_pair);

    } 

}

