#pragma once

#include "type.h"
#include "rset.h"

extern void* alloc_buf();
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

class batchinfo_t {
 public:
    void*    buf;
    uint32_t count;
};

class prop_encoder_t;

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
    int         batch_count;
    int         batch_count1;
    
    uint8_t     flag1_count;
    uint8_t     flag2_count;
    index_t     MAXX_ECOUNT;

 public: 
    cfinfo_t();   
    void reset();
    
    inline status_t alloc_batch() {
        if (batch_info1[batch_count1].count == MAXX_ECOUNT) {
            void* mem = alloc_buf();
            if (mem == 0) return eEndBatch;
            ++batch_count1;
            batch_info1[batch_count1].count = 0;
            batch_info1[batch_count1].buf = mem; 
        }
        return eOK;
    } 

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
    virtual status_t batch_update(const string& src, const string& dst, propid_t pid, 
                          propid_t count, prop_pair_t* prop_pair, int del = 0);
    
    
    virtual void prep_graph_baseline();
    virtual void calc_degree();
    virtual void make_graph_baseline();
    virtual status_t move_marker();
    virtual void store_graph_baseline(string dir);
    virtual void read_graph_baseline(const string& dir);


    //Graph specific
    virtual void add_edge_property(const char* longname, prop_encoder_t* prop_encoder);
    virtual status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    //virtual status_t transform_withfilter(srset_t* iset, srset_t* oset, direction_t direction, filter_info_t* filter_info);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
    
    //label specific
    virtual status_t filter(sid_t sid, univ_t value, filter_fn_t fn);
    virtual void print_raw_dst(tid_t tid, vid_t vid, propid_t pid = 0);
    virtual status_t get_encoded_value(const char* value, univ_t* univ);
};
