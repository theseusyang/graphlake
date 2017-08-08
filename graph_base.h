#pragma once

#include "type.h"

////
inline void add_nebr1(sid_t* adj_list, vid_t index, sid_t value) {
    adj_list[index] = value;
}

inline void add_nebr1(lite_edge_t* adj_list, vid_t index, sid_t value) {
    adj_list[index].first = value;
}

inline void add_nebr2(lite_edge_t* adj_list, vid_t index, sid_t value, univ_t univ)
{
    adj_list[index].first = value;
    adj_list[index].second = univ;
}


////
inline void set_nebrcount1(sid_t* adj_list, vid_t count) {
    adj_list[0] = count;
}

inline void set_nebrcount1(lite_edge_t* adj_list, vid_t count) {
    adj_list[0].first = count;
}

inline vid_t get_nebrcount1(sid_t* adj_list) {
    return adj_list[0];
}

inline vid_t get_nebrcount1(lite_edge_t* adj_list) {
    return adj_list[0].first;
}

inline sid_t get_nebr(sid_t* adj, vid_t k) {
    return adj[k];
}

inline sid_t get_nebr(lite_edge_t* adj, vid_t k) {
    return adj[k].first;
}
////
inline void set_value1(sid_t* kv, vid_t vid, sid_t value) {
    kv[vid] = value;
}

inline void set_value1(lite_edge_t* kv, vid_t vid, sid_t value, univ_t univ) {
    kv[vid].first = value;
    kv[vid].second = univ;
}

//One vertex's neighbor information
template <class T>
class vert_table_t {
public:
 private:
    //nebr list of one vertex. First member is a spl member
    //count, flag for snapshot, XXX: smart pointer count
    T*   adj_list;
 
 public:
    inline vert_table_t() { adj_list = 0; }

    /*
    inline void setup(vid_t a_count) {
        vid_t count = a_count;
        if (adj_list) {
            //count += adj_list[0];
            adj_list = (T*) realloc(adj_list, sizeof(T)*(count+1));
        } else {
            adj_list = (T*) calloc(sizeof(T), count+1);
        }
    }*/

    inline void add_nebr(vid_t index, sid_t sid) { 
        add_nebr1(adj_list, index, sid);
        //adj_list[index] = sid; 
    }

    inline void add_nebr_lite(vid_t index, sid_t sid, univ_t value) {
        add_nebr2(adj_list, index, sid, value);
        
    }

    inline void set_nebrcount(vid_t count) {
        set_nebrcount1(adj_list, count);
        //adj_list[0] = count;
    }

    inline vid_t get_nebrcount() {
        return get_nebrcount1(adj_list);
        //return adj_list[0];
    }
    
    inline T* get_adjlist() { return adj_list; }
    inline void set_adjlist(T* adj_list1) { adj_list =  adj_list1;}
    
    inline void copy(vert_table_t<T>* beg_pos) {
        adj_list = beg_pos->adj_list;
    }
};


//one type's graph
template <class T>
class onegraph_t {
private:
    //type id and vertices count together
    sid_t      super_id;

    //array of adj list of vertices
    vert_table_t<T>* beg_pos;

    //count in adj list. Used for book-keeping purpose during setup and update.
    vid_t*   nebr_count;

    vid_t    max_vcount;

    //edgetable file related log
    T*       log_beg;  //memory log pointer
    sid_t    log_count;//size of memory log
    sid_t    log_head; // current log write position
    sid_t    log_tail; //current log cleaning position
    sid_t    log_wpos; //Write this pointer for write persistency

    //vertex table file related log
    disk_vtable_t* dvt;
    vid_t    dvt_count; 
    vid_t    dvt_max_count;

    FILE*    vtf;   //vertex table file
    FILE*    etf;   //edge table file

public:
    inline onegraph_t() {
        super_id = 0;
        beg_pos = 0;
        nebr_count = 0;
        max_vcount = 0;
        
        //XXX everything is in memory
        log_count = (1L << 28);//256*8 MB
        if (posix_memalign((void**)&log_beg, 2097152, log_count*sizeof(T))) {
            //log_beg = (sid_t*)calloc(sizeof(sid_t), log_count);
            perror("posix memalign edge log");
        }
        log_head = 0;
        log_tail = 0;
        log_wpos = 0;
        
        dvt_count = 0;
        dvt_max_count = (1L << 28);
        if (posix_memalign((void**) &dvt, 2097152, 
                           dvt_max_count*sizeof(disk_vtable_t*))) {
            perror("posix memalign vertex log");    
        }
        vtf = 0;
        etf = 0;
    }
    
    void setup(tid_t tid);
    void setup_adjlist();

    inline void increment_count(vid_t vid) { ++nebr_count[vid]; }
    inline void add_nebr(vid_t vid, sid_t sid) { 
        ++nebr_count[vid];
        beg_pos[vid].add_nebr(nebr_count[vid], sid);
    }
    inline void add_nebr_lite(vid_t vid, sid_t sid, univ_t value) { 
        ++nebr_count[vid];
        beg_pos[vid].add_nebr_lite(nebr_count[vid], sid, value);
    }

    inline void update_count(vid_t vid) {
        beg_pos[vid].set_nebrcount(nebr_count[vid]);
    }
    inline void reset_count(vid_t vid) {
        nebr_count[vid] = beg_pos[vid].get_nebrcount();
    }
    inline vert_table_t<T>* get_begpos() { return beg_pos;}
    inline vid_t get_vcount() { return TO_VID(super_id);}
    inline tid_t get_tid() { return TO_TID(super_id);}

    void persist_elog(const string& etfile);
    void persist_vlog(const string& vtfile);

    void read_etable(const string& etfile);
    void read_vtable(const string& vtfile); 
};

typedef vert_table_t<sid_t> beg_pos_t;
typedef beg_pos_t  lgraph_t;
typedef vert_table_t<lite_edge_t> lite_vtable_t;

typedef onegraph_t<sid_t> sgraph_t;
typedef onegraph_t<lite_edge_t>lite_sgraph_t;


class disk_kv_t {
    public:
    vid_t    vid;
    sid_t    dst;
};

//one type's key-value store
class skv_t {
 private:
    sid_t  super_id;
    vid_t  max_vcount;
    sid_t* kv;

    disk_kv_t* dvt;
    vid_t dvt_count;
    vid_t dvt_max_count;

    FILE* vtf;

 public:
    inline skv_t() {
        super_id = 0;
        max_vcount = 0;
        kv = 0;
        
        dvt_count = 0;
        dvt_max_count = (1L << 28);
        if (posix_memalign((void**) &dvt, 2097152, 
                           dvt_max_count*sizeof(disk_kv_t*))) {
            perror("posix memalign vertex log");    
        }
        vtf = 0;
    }

    void setup(tid_t tid);

    inline sid_t* get_kv() { return kv; }
    inline tid_t get_tid() { return TO_TID(super_id);}
    inline vid_t get_vcount() { return TO_VID(super_id); }
    
    inline void set_value(vid_t vert1_id, sid_t dst) {
        //set_value1(kv, vert1_id, dst);
        kv[vert1_id] = dst;
        dvt[dvt_count].vid = vert1_id;
        dvt[dvt_count].dst = dst; 
        ++dvt_count;
    }
    
    void persist_kvlog(const string& kvfile);
    void read_kv(const string& kvfile); 
};

class disk_kvlite_t {
    public:
    vid_t    vid;
    sid_t    dst;
    univ_t   univ; 
};


class lite_skv_t {
 private:
    sid_t  super_id;
    vid_t  max_vcount;
    lite_edge_t* kv;

    disk_kvlite_t* dvt;
    vid_t dvt_count;
    vid_t dvt_max_count;

    FILE* vtf;

 public:
    inline lite_skv_t() {
        super_id = 0;
        max_vcount = 0;
        kv = 0;
        
        dvt_count = 0;
        dvt_max_count = (1L << 20);
        if (posix_memalign((void**) &dvt, 2097152, 
                           dvt_max_count*sizeof(disk_kvlite_t*))) {
            perror("posix memalign vertex log");    
        }
        vtf = 0;
    }

    void setup(tid_t tid);

    inline lite_edge_t* get_kv() { return kv; }
    inline tid_t get_tid() { return TO_TID(super_id);}
    inline vid_t get_vcount() { return TO_VID(super_id); }
    
    inline void set_value_lite(vid_t vert1_id, sid_t dst, univ_t value) {
        kv[vert1_id].first = dst;
        kv[vert1_id].second = value;
        dvt[dvt_count].vid = vert1_id;
        dvt[dvt_count].dst = dst;
        dvt[dvt_count].univ = value;
        ++dvt_count;
    }
    void persist_kvlog(const string& kvfile);
    void read_kv(const string& kvfile); 
};

//typedef onekv_t<sid_t> skv_t; 
//typedef onekv_t<lite_edge_t> lite_skv_t; 


