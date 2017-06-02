#pragma once
#include "type.h"


class disk_strkv_t {
    public:
    vid_t vid;
    sid_t offset;
};

class disk_manykv_t {
    public:
    vid_t    vid;
    propid_t size;
    propid_t degree;
    uint64_t file_offset;
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

    strkv_t** prep_strkv();
    void fill_kv_out();

    void get_raw_dst(tid_t tid, vid_t vid);
    inline void print_raw_dst(tid_t tid, vid_t vid, propid_t pid = 0) {
        cout << strkv_out[tid]->kv[vid];
    }
};


class kv_t {
 public:
    propid_t   pid;
    propid_t   offset;//character count offset from beg of blob
    //char*      value;
};

class kvarray_t {
    //It is an array of  blob. One blob per vertex. 
    // first 2bytes for total byte count
    // next 2bytes is the count of number of properties
    // from 5th bits onwards, it is an array of propid_t (2 bytes) and offset (2 bytes) from this pointer
    // All the string values (char*) are at the end.
    propid_t* adj_list;

 public:
    inline void add_nebr(vid_t index, propid_t pid, char* value) { 
        adj_list[index].pid = pid; 
        adj_list[index].value = value;
    }

    inline void set_nebrcount(vid_t count) {
        adj_list[0].pid = count;
    }

    inline propid_t get_size() {
        return adj_list[0];
    }
    
    inline propid_t get_nebrcount() {
        return adj_list[1].pid;
    }

    inline propid_t get_pid(propid_t i) {
        return adj_list[i].pid;
    }

    inline char* get_value(propid_t i) {
        return adj_list[i].value;
    }
    
    //
    inline kvarray_t() {
        adj_list = 0;
    }
};

class mkv_t {
    sid_t super_id;
    kvarray_t* kv_array;

    //number of properties, number of character for their values, allocated for blob
    kv_t* nebr_count;

    vid_t max_vcount;
    
    //edgetable file related log
    char*    log_beg;  //memory log pointer
    sid_t    log_count;//size of memory log
    sid_t    log_head; // current log write position
    sid_t    log_tail; //current log cleaning position
    sid_t    log_wpos; //Write this pointer for write persistency

    //vertex table file related log
    disk_manykv_t* dvt;
    vid_t    dvt_count; 
    vid_t    dvt_max_count;

    FILE*    vtf;   //vertex table file
    FILE*    etf;   //edge table file
    
    friend class mkv_t;
 
public: 
    inline mkv_t() {
        super_id = 0;
        kv_array = 0;
        nebr_count = 0;
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
    void setup(tid_t tid);
    void setup_adjlist();
    inline void increment_count(vid_t vid, propid_t size) { 
        nebr_count[vid].pid += 1;
        nebr_count[vid].offset += size + sizeof(propid_t);//size of value + size of key
    }

    void add_nebr(vid_t vid, propid_t pid, char* dst);
    
    inline void update_count(vid_t vid) {
        kv_array[vid].set_nebrcount(nebr_count[vid]);
    }
    
    inline void reset_count(vid_t vid) {
        nebr_count[vid] = kv_array[vid].get_nebrcount();
    }
    
    inline kvarray_t* get_nebrlist(vid_t vid) {
        return kv_array + vid;
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
    void update_count();
    
    status_t batch_update(const string& src, const string& dst, propid_t pid = 0);
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    
    void print_raw_dst(tid_t tid, vid_t vid, propid_t pid);
};
