#pragma once

#include <map>
#include "type.h"

using  std::map;

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
