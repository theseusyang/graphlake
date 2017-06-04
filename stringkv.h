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
    inline strkv_t() {
        kv = 0;
        super_id = 0;
        max_vcount = 0;
        
        //XXX everything is in memory
        log_count = (1L << 25);//32*8 MB
        if (posix_memalign((void**)&log_beg, 2097152, log_count*sizeof(char))) {
            //log_beg = (sid_t*)calloc(sizeof(sid_t), log_count);
            perror("posix memalign edge log");
        }
        log_head = 0;
        log_tail = 0;
        log_wpos = 0;
        
        dvt_count = 0;
        dvt_max_count = (1L << 20);
        if (posix_memalign((void**) &dvt, 2097152, 
                           dvt_max_count*sizeof(disk_strkv_t*))) {
            perror("posix memalign vertex log");    
        }
        vtf = 0;
        etf = 0;
    }
    
    inline void setup(tid_t tid) {
        if ( 0 == super_id ) {
            super_id = g->get_type_scount(tid);
            vid_t v_count = TO_VID(super_id);
            max_vcount = (v_count << 1);
            kv = (char**)calloc(sizeof(char*), max_vcount);
        } else {
            super_id = g->get_type_scount(tid);
            vid_t v_count = TO_VID(super_id);
            if (max_vcount < v_count) {
                assert(0);
            }
        }
    }

    inline void set_value(vid_t vid, char* value) {
        char* ptr = log_beg + log_head;
        log_head += strlen(value) + 1;
        memcpy(ptr, value, strlen(value) + 1);
        free(value);

        kv[vid] = ptr;
        dvt[dvt_count].vid = vid;
        dvt[dvt_count].offset = ptr - log_beg; 
        ++dvt_count;
    }

    inline char* alloc_mem(size_t sz) {
        char* ptr = log_beg +  log_head;
        log_head += sz;
        return ptr;
    }

    void persist_vlog(const string& vtfile);
    void persist_elog(const string& etfile);
    void read_vtable(const string& vtfile);
    void read_etable(const string& etfile);

    void prep_str2sid(map<string, sid_t>& str2sid);
};

class stringkv_t : public cfinfo_t {
 protected:
     strkv_t** strkv_out;
 public:
    inline stringkv_t() {
        strkv_out = 0;
    }

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
