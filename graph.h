#pragma once

#include <map>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>

#include "type.h"
#include "cf_info.h"
#include "rset.h"
#include "graph_base.h"
#include "query_clause.h"
#include "prop_encoder.h"

using std::map;
using std::cout;
using std::endl;
using std::string;
using std::swap;
using std::pair;

inline char* gstrdup(const char* str) 
{
    return strdup(str);
}
    
void* alloc_buf();


//class pkv_t;
class graph;
extern graph* g;

class vgraph_t;
class typekv_t;

typedef cfinfo_t* (*get_graph_instance)();
typedef prop_encoder_t* (*get_encoder_instance)();

extern map<string, get_graph_instance>  graph_instance;
extern map<string, get_encoder_instance>  encoder_instance;

////////////main class/////////////////////
class graph {
 public:
    //graphs and labels store.
    cfinfo_t** cf_info;
    pinfo_t *  p_info;
    
    batchinfo_t* batch_info;
    batchinfo_t* batch_info1;
    
    uint8_t      batch_count;
    uint8_t      batch_count1;
    int          cf_count;
    propid_t     p_count;

    snapshot_t*  snapshot;
    string       snapfile;
    FILE*        snap_f;
    map <string, propid_t> str2pid;

    //vertex information
    vgraph_t* v_graph;

    //Other information
    map <string, sid_t> str2vid;
    vid_t     vert_count;

    string odirname;
    
    //threads
    pthread_t snap_thread;
    pthread_mutex_t snap_mutex;
    pthread_cond_t  snap_condition;
    
    pthread_t w_thread;
    pthread_mutex_t w_mutex;
    pthread_cond_t  w_condition;

 public:
    graph();
    inline void set_odir(const string& odir) {
        odirname = odir;
        snapfile = odir + "graph.snap";
    }
    void register_instances();
    void create_schema(propid_t count, const string& conf_file);
    
    snapid_t get_snapid();
    inline snapshot_t* get_snapshot() {return snapshot;}
    void incr_snapid(index_t snap_marker, index_t durable_marker = 0);
    void read_snapshot();

    void add_columnfamily(cfinfo_t* cf);
    //void create_columnfamilies(propid_t a_cf_count);
    
    inline typekv_t* get_typekv() { return (typekv_t*)cf_info[0]; }
    sid_t get_type_scount(tid_t type);
    tid_t get_total_types();
	tid_t get_tid(const char* type);

    propid_t get_cfid(propid_t pid);
    propid_t get_cfid(const char* property);
    propid_t get_pid(const char* property);
    
    status_t add_property(const char* longname);
    sid_t get_sid(const char* src);
     
    //queries
    void run_query(query_clause* q);
    
    sid_t type_update(const string& src, const string& dst);
    void type_done();
    void type_store(const string& odir);

    status_t batch_update(const string& src, const string& dst, const string& predicate);
    //useful or properties
    status_t batch_update(sid_t src_id, const string& dst, const string& predicate);
    //For edges with properties.
    status_t batch_update(const string& src, const string& dst, propid_t pid, 
                          propid_t count, prop_pair_t* prop_pair);
    
    void prep_graph_baseline();
    void swap_log_buffer();
    void calc_degree();
    void make_graph_baseline();
    void create_snapshot();
    void write_edgelog();
    void store_graph_baseline();
    void read_graph_baseline();
    void file_open(bool trunc);
    
    void create_snapthread();
    static void* snap_func(void* arg);

    void create_wthread();
    static void* w_func(void* arg);
};


