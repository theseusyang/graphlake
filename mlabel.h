#pragma once
#include "type.h"

class kv_t {
 public:
    propid_t   pid;//name
    char*      value;
};

class kvarray_t {
    kv_t* adj_list;
    
 public:
    inline void setup(vid_t a_count) {
        vid_t count = a_count;
        if (adj_list) {
            count += adj_list[0].pid;
            adj_list = (kv_t*) realloc(adj_list, sizeof(kv_t)*(count+1));
        } else {
            adj_list = (kv_t*) calloc(sizeof(kv_t), count+1);
        }
    }

    inline void add_nebr(vid_t index, propid_t pid, char* value) { 
        adj_list[index].pid = pid; 
        adj_list[index].value = value;
    }

    inline void set_nebrcount(vid_t count) {
        adj_list[0].pid = count;
    }

    inline vid_t get_nebrcount() {
        return adj_list[0].pid;
    }
    //
    inline kvarray_t() {
        adj_list = 0;
    }
};

class mkv_t {
    sid_t super_id;
    kvarray_t* kv_array;
    vid_t* nebr_count; 
    vid_t max_vcount;
 
public: 
    void setup(tid_t tid);
    void setup_adjlist();
    inline void increment_count(vid_t vid) { ++nebr_count[vid]; }
    inline void add_nebr(vid_t vid, propid_t pid, char* dst) {
        ++nebr_count[vid];
        kv_array[vid].add_nebr(nebr_count[vid], pid, dst);
    }
    
    inline void update_count(vid_t vid) {
        kv_array[vid].set_nebrcount(nebr_count[vid]);
    }
    
    inline void reset_count(vid_t vid) {
        nebr_count[vid] = kv_array[vid].get_nebrcount();
    }
    
    inline vid_t get_vcount() { return TO_VID(super_id);}
    inline tid_t get_tid() { return TO_TID(super_id);}
    
};

class manykv_t : public cfinfo_t {
    mkv_t**   mkv_out;
    
 public:
    inline manykv_t() {
        mkv_out = 0;
    }
    void prep_mkv();
    void fill_mkv_out();
    void calc_edge_count();
    void prep_mkv_internal();
    status_t batch_update(const string& src, const string& dst, propid_t pid = 0);
    void make_graph_baseline();
    void update_count();
};
