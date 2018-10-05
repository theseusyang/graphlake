#pragma once

#include "type.h"

class disk_strkv_t {
    public:
    vid_t vid;
    sid_t offset;
};

class strkv_t {
 public:
    sid_t* kv;
    tid_t  tid;
    
    //edgetable file related log
    char*    log_beg;  //memory log pointer
    sid_t    log_count;//size of memory log
    sid_t    log_head; // current log write position
    sid_t    log_tail; //current log cleaning position
    sid_t    log_wpos; //Write this pointer for write persistency

    //vertex table file related log
    /*disk_strkv_t* dvt;
    vid_t    dvt_count; 
    vid_t    dvt_max_count;
    */

    int    vtf;   //vertex table file
    int    etf;   //edge table file
    
    friend class stringkv_t;

 public:
    strkv_t(); 
 
 public: 
    void setup(tid_t tid); 
    void set_value(vid_t vid, const char* value); 
    const char* get_value(vid_t vid);
    void persist_vlog();
    void persist_elog();
    void read_vtable();
    void read_etable();
    void prep_str2sid(map<string, sid_t>& str2sid);
    void file_open(const string& filename, bool trunc);
    
    /*
    inline char* alloc_mem(size_t sz) {
        char* ptr = log_beg +  log_head;
        log_head += sz;
        return ptr;
    }*/
};

class stringkv_t : public cfinfo_t {
 protected:
     strkv_t** strkv_out;
 public:
    inline stringkv_t() {
        strkv_out = 0;
    }
    static cfinfo_t* create_instance();
    status_t batch_edge(edgeT_t<char*>& edge);
    status_t batch_update(const string& src, const string& dst, propid_t pid = 1);
    void make_graph_baseline();
    void store_graph_baseline(bool clean = false);
    void read_graph_baseline();
    void file_open(const string& dir, bool trunc);

    void prep_graph_baseline();
    void fill_kv_out();

    //inline const char* get_value(tid_t tid, vid_t vid) 
    inline const char* get_value(sid_t sid) {
        vid_t vid = TO_VID(sid);
        tid_t tid = TO_TID(sid);
        return strkv_out[tid]->get_value(vid);
    }

    inline void print_raw_dst(tid_t tid, vid_t vid, propid_t pid = 0) {
        cout << strkv_out[tid]->kv[vid];
    }
};

