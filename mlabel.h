#pragma once
#include "type.h"

class kv_t {
    propid_t   propid;//name
    uint8_t    value_type;
    univ_t     value;

 public:
    inline setup() {
    }
};

class mkv_t {
    kv_t* kv;
    vid_t* nebr_count; 
    sid_t super_id;
    vid_t max_vcount;
 
public: 
    void setup(tid_t tid);
    void setup_adjlist(vid_t count);
};

class manykv_t : public cfinfo_t {
    mkv_t**   mkv_out;
    vid_t*    nebr_count;
    
 public:
    inline manykv_t() {
        mkv_out = 0;
        nebr_count = 0;
    }
    mkv_t** prep_mkv();
    void fill_mkv_out();
    status_t batch_update(const string& src, const string& dst, propid_t pid = 0);
    void make_graph_baseline();
};
