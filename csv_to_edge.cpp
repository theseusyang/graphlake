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
    char splchar = '%'; 

    string v_str = "%%vertex%%";
    string e_str = "%%edge%%";
    string delim = " \n";
    string filename, predicate;
    
    vconf_t v_conf;
    econf_t e_conf;
    
    vector<vconf_t> vfile_list;
    vector<econf_t> efile_list;

    //Read conf_file
    char* line = 0;
    size_t len = 0;
    ssize_t read;
    char* saveptr;
    char* token;
    int value = -1;

    FILE* fp = fopen(conf_file.c_str(), "r");
    if (NULL == fp) assert(0);
    
    while((read = getline(&line, &len, fp)) != -1) {
        if (line[0] == splchar && line[1] == splchar) {
            if (0 == strncmp(line, v_str.c_str(), 10)) value = 0;
            else if (0 == strncmp(line, e_str.c_str(), 8 )) value = 1;
            else assert(0);
    
        } else {
            if (value == 0) {
                token = strtok_r(line, delim.c_str(), &saveptr);
                if ( 0 != token) {
                   v_conf.filename = token;
                }

                if (NULL != (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
                    v_conf.predicate = token;
                } else {
                    v_conf.predicate = "";
                }
                vfile_list.push_back(v_conf);
            } else if (value == 1) {
                token = strtok_r(line, delim.c_str(), &saveptr);
                if ( 0 != token) {
                   e_conf.filename = token;
                }

                if (NULL != (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
                    e_conf.predicate = token;
                }
                
                if (NULL != (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
                    e_conf.src_type = token;
                }
                
                if (NULL != (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
                    e_conf.dst_type = token;
                    
                    if (NULL != (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
                        e_conf.edge_prop = token;
                    }
                } else {
                    e_conf.dst_type = "";
                }
                
                
                efile_list.push_back(e_conf);
            }
        }      
    }

    fclose(fp);
    fp = 0;
    
    //Read vertex file
    vector<vconf_t>::iterator iter = vfile_list.begin();
    for (; iter != vfile_list.end(); ++iter) {
        prep_vtable(idirname + iter->filename, iter->predicate, odirname);
    }
    
    g->type_done();
    g->type_store(odirname);
    
    //Read edge file
    vector<econf_t>::iterator e_iter = efile_list.begin();
    for (; e_iter != efile_list.end(); ++e_iter) {
        e_conf = *e_iter;
        prep_etable(idirname + e_iter->filename, e_conf, odirname);
    }
    
    g->prep_graph_baseline();
    g->swap_log_buffer();
    g->calc_degree();
    g->make_graph_baseline();
    g->store_graph_baseline(odirname);
}

//predicate here is the vertex type
void csv_manager::prep_vtable(const string& filename, string predicate, const string& odir)
{
    string delim = "|\n";
    int pred_index = 0;

    string subject, object;

    //Read conf_file
    char* line = 0;
    size_t len = 0;
    size_t line_count = 1;
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
        while (NULL != (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
            vtoken.push_back(token);
        }
    }
    
    //read the values now.
    while((read = getline(&line, &len, fp)) != -1) {
        ++line_count;
        //First token is the id, which will be treated as name.
        token = strtok_r(line, delim.c_str(), &saveptr);
        subject = predicate + token;

        //Couldn't insert successfully, don't add its property
        if (eOK != g->type_update(subject, predicate)) continue;

        //Other tokens are its properties value
        pred_index = 0;
        while (NULL != (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
            //property value
            //could be optimized, as we can easily pass propid, instead of property name
            g->batch_update(subject, token, vtoken[pred_index]);
            ++pred_index;
        }
    }

    fclose(fp);
}

//XXX We are avoiding the edge properties for time being.
//predicate here is the edge type
void csv_manager::prep_etable(const string& filename, const econf_t& e_conf, const string& odir)
{
    prop_pair_t prop_pair;
    string delim = "|\n";

    string subject, object;
    string predicate = e_conf.predicate;
    propid_t pid = g->get_pid(predicate.c_str());

    //Read conf_file
    char* line = 0;
    size_t len = 0;
    size_t line_count = 1;
    ssize_t read;

    char* saveptr;
    char* token;
    vector<string> prop_token;
    size_t prop_count = 0;
    size_t prop_index;

    FILE* fp = fopen(filename.c_str(), "r");
    if (NULL == fp) assert(0);
    
    //First line is special
    if ((read = getline(&line, &len, fp)) != -1) {
        
        //First token is "id"
        token = strtok_r(line, delim.c_str(), &saveptr);
        
        //second end of the edge, "id"
        token = strtok_r(NULL, delim.c_str(), &saveptr); 

        //Other tokens are edge properties
        while (NULL != (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
            prop_token.push_back(token);
        }
    }

    prop_count = prop_token.size();
    
    //read the edges now.
    while((read = getline(&line, &len, fp)) != -1) {
        ++line_count;
        //First token is the subject id, which will be treated as name.
        token = strtok_r(line, delim.c_str(), &saveptr);
        subject = e_conf.src_type + token;

        //Second token is the object id, which will be treated as name.
        token = strtok_r(NULL, delim.c_str(), &saveptr);
        object = e_conf.dst_type + token;

        if (0 == prop_count) {
            g->batch_update(subject, object, predicate);
        } else {

            //Other tokens are edge properties value
            prop_index = 0;
            while (NULL != (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
                prop_pair.name = prop_token[prop_index];
                prop_pair.value = token;
                g->batch_update(subject, object, pid, prop_count, &prop_pair);
                ++prop_index;
            }
        }
    }
    fclose(fp);
}
