#pragma once

#include "type.h"

class disk_strkv_t {
    public:
    vid_t vid;
    sid_t offset;
};

class strkv_t {
 public:
    char** kv;
    sid_t super_id;
    vid_t max_vcount;
    
    //edgetable file related log
    char*    log_beg;  //memory log pointer
    sid_t    log_count;//size of memory log
    sid_t    log_head; // current log write position
    sid_t    log_tail; //current log cleaning position
    sid_t    log_wpos; //Write this pointer for write persistency

    //vertex table file related log
    disk_strkv_t* dvt;
    vid_t    dvt_count; 
    vid_t    dvt_max_count;

    FILE*    vtf;   //vertex table file
    FILE*    etf;   //edge table file
    
    friend class stringkv_t;

 public:
    strkv_t(); 
 
 public: 
    void setup(tid_t tid); 
    void set_value(vid_t vid, char* value); 
    void persist_vlog(const string& vtfile);
    void persist_elog(const string& etfile);
    void read_vtable(const string& vtfile);
    void read_etable(const string& etfile);
    void prep_str2sid(map<string, sid_t>& str2sid);
    
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
    status_t batch_update(const string& src, const string& dst, propid_t pid = 0);
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);

    strkv_t** prep_strkv();
    void fill_kv_out();

    inline const char* get_value(tid_t tid, vid_t vid) {
        return strkv_out[tid]->kv[vid];
    }

    inline void print_raw_dst(tid_t tid, vid_t vid, propid_t pid = 0) {
        cout << strkv_out[tid]->kv[vid];
    }
};

/*---------------vinfo--------------------*/
class vgraph_t: public stringkv_t 
{

 public:    
    void id2name(vid_t src_id, const string& src); 
    void prep_str2sid(map<string, sid_t>& str2sid);
 public:
    const char* get_value(tid_t tid, vid_t vid);

 public:
    vgraph_t();
    ~vgraph_t();
};
