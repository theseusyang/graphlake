#pragma once

#include <map>
#include <string>
#include <string.h>
#include <stdint.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>

#include "type.h"
#include "query_clause.h"

using std::map;
using std::cout;
using std::endl;
using std::string;

inline char* gstrdup(const char* str) 
{
    return strdup(str);
}
    
void* alloc_buf();

#define bu_factor 0.07
#define MAX_BCOUNT 256
#define MAX_ECOUNT 1000000
#define MAX_PECOUNT 670000
#define BUF_SCOUNT  2000000
#define BUF_SIZE   16000000

//class pkv_t;
class graph;
extern graph* g;

class batchinfo_t {
 public:
    void*    buf;
    uint32_t count;
};

/////////////////////////////////
//One relationship or label
class pinfo_t {
    public:
    char*        p_name;
    char*        p_longname;
    propid_t     cf_id;

 public:
    void populate_property(const char* longname, const char* property_name);
};

//Column Family
class cfinfo_t {
 public:
    pinfo_t**     col_info;
    propid_t      col_count;

    batchinfo_t* batch_info;
    batchinfo_t* batch_info1;
    
    sflag_t     flag1;
    sflag_t     flag2;
    
    propid_t    cf_id;
    uint8_t     batch_count;
    uint8_t     batch_count1;
    
    uint8_t     flag1_count;
    uint8_t     flag2_count;
   
 public: 
    cfinfo_t();   
    void reset();

 public:
    void create_columns(propid_t prop_count = 1);
    void add_column(pinfo_t* prop_info);
    
    void swap_log_buffer(); 
    void cleanup();
    void reset_buffer0();
    void reset_buffer1();

    //edges and vertex properties
    virtual status_t batch_update(const string& src, const string& dst, propid_t pid = 0);
    
    //For heavy weight edges.
    status_t batch_update(const string& src, const string& dst, propid_t pid, 
                          propid_t count, prop_pair_t* prop_pair);
    
    //This interface is for edge properties.
    virtual status_t batch_update(eid_t eid, const string& dst, propid_t pid) {return eOK;};
    
    virtual void make_graph_baseline();
    virtual void store_graph_baseline(string dir);
    virtual void read_graph_baseline(const string& dir);

    virtual status_t calc_deletededge_count(pedge_t* edge) {return eOK;};

    //Graph specific
    virtual status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    //virtual status_t transform_withfilter(srset_t* iset, srset_t* oset, direction_t direction, filter_info_t* filter_info);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
    
    //label specific
    virtual status_t filter(sid_t sid, univ_t value, filter_fn_t fn);
    virtual void print_raw_dst(tid_t tid, vid_t vid, propid_t pid = 0);
    virtual status_t get_encoded_value(const char* value, univ_t* univ);
};

class vgraph_t;
class typekv_t;
////////////main class/////////////////////
class graph {
 public:
    //graphs and labels store.
    cfinfo_t** cf_info;
    pinfo_t *  p_info;
    
    batchinfo_t* batch_info;
    batchinfo_t* batch_info1;
    
    uint8_t     batch_count;
    uint8_t     batch_count1;

    int   cf_count;
    propid_t   p_count;

    map <string, propid_t> str2pid;

    //vertex information
    vgraph_t* v_graph;

    //Other information
    map <string, sid_t> str2vid;
    vid_t     vert_count;

 public:
    graph();
    void add_columnfamily(cfinfo_t* cf);
    //void create_columnfamilies(propid_t a_cf_count);
    
    inline typekv_t* get_typekv() { return (typekv_t*)cf_info[0]; }
    sid_t get_type_scount(tid_t type);
    tid_t get_total_types();

    propid_t get_cfid(propid_t pid);
    propid_t get_cfid(const char* property);
    propid_t get_pid(const char* property);
    
    //void prep_graph(string idirname, string odirname);
    //void prep_graph_csv(string idirname, string odirname);
    status_t add_property(const char* longname);
    sid_t get_sid(const char* src);
     
    //void prep_type(string typefile, string odirname);
    //void prep_graph(string idirname, string odirname);
    //status_t remove_edge(const string& idir, const string& odir);

    //queries
    void run_query(query_clause* q);
    
    status_t type_update(const string& src, const string& dst);
    void type_done();
    void type_store(const string& odir);

    status_t batch_update(const string& src, const string& dst, const string& predicate);
    void make_graph_baseline();
    void store_graph_baseline(const string& odir);
    void read_graph_baseline(const string& odir);
};



#include "sgraph.h"
#include "lite_sgraph.h"
/*----------- labels ------------------ */
//#include "labelkv.h"
#include "typekv.h"
#include "stringkv.h"
#include "mlabel.h"
