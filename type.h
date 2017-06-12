#pragma once
#include <stdint.h>
#include <limits.h>
#include <string>
#include "bitmap.h"

using std::string;


typedef uint16_t propid_t;
typedef uint64_t vid_t;
typedef uint64_t sid_t;
typedef uint64_t eid_t;
typedef uint64_t index_t;
typedef uint32_t tid_t;
typedef uint64_t sflag_t;
typedef uint16_t qid_t;
typedef uint32_t pos_t; //adj list position, how long an adj list can be
//typedef int32_t status_t;

#define VBIT 40
#define VMASK 0xffffffffff
#define THIGH_MASK 0xFFFFFF0000000000


#define TO_TID(sid) (sid >> VBIT)
#define TO_VID(sid)  (sid & VMASK)
#define TO_SUPER(tid) (((sid_t)(tid)) << VBIT)
#define TO_THIGH(sid) (sid & THIGH_MASK)

#define TID_TO_SFLAG(tid) (1L << tid)
#define WORD_COUNT(count) ((count + 63) >> 6)


#define INVALID_PID 0xFFFF
#define INVALID_TID 0xFFFFFFFF
#define INVALID_SID 0xFFFFFFFFFFFFFFFF

#define NO_QID 0xFFFF

class cfinfo_t;

off_t fsize(const string& fname);

enum direction_t {
    eout = 0, 
    ein
};

enum status_t {
    eOK = 0,
    eInvalidPID,
    eInvalidVID,
    eQueryFail,
    eEndBatch,
    eDelete,
    eUnknown        
};

typedef union __univeral_type {
    char*    value_charp;
    char     value_string;
    uint64_t value_64b;
    uint8_t  value_8b;
    uint16_t value16b;
    tid_t    value_tid;
    vid_t    value_vid;
    sid_t    value_sid;
    eid_t    value_eid;
}univ_t;


template <class T>
class  edgeT_t {
 public:
    sid_t src_id;
    T     dst_id;
};

typedef edgeT_t<sid_t> edge_t;

/*
class edge_t {
public:
    sid_t src_id;
    sid_t dst_id;
};
*/

class pedge_t {
 public:
    propid_t pid;
    sid_t src_id;
    univ_t dst_id;
};

class ledge_t {
 public:
     sid_t src_id;
     sid_t dst_id;
     univ_t prop;
};

//property name value pair
struct prop_pair_t {
    char* name;
    char* value;
};

typedef struct __sid_set_t {
public:
    int count;
    sid_t* sids;
} sid_set_t;

enum filter_fn_t {
    fn_out = 0,//simple lookup 
    fn_ein, //simple inward lookup
    //More coming soon such as regex
};

//required when src and dst both are variable 
//but one is populated from another query.
enum queryplan_t {
    eOutward = 0,
    eInward,
    eDefault,
};

enum traverse_t {
    eTransform = 0,
    eExtend,
};

class filter_info_t {
 public:
    //always one count
    cfinfo_t* rgraph;

    qid_t count;
    //these could be more, controlled by count
    univ_t   value;
    filter_fn_t filter_fn;
    
    inline filter_info_t() {
        rgraph = 0;
        count = 0;
    }
 
 private:
    inline void set_filterobj(cfinfo_t* a_graph, univ_t a_value, filter_fn_t fn) {
        rgraph = a_graph;
        value = a_value;
        filter_fn = fn;
    }
};

class type_filter_t {
 public:
     tid_t tid_value;
};

typedef struct __select_info_t {
    cfinfo_t* rgraph;
    propid_t pid;
    string name; 
} select_info_t;


//#include "sgraph.h"

class disk_vtable_t {
    public:
    vid_t    vid;
    uint64_t degree;
    uint64_t file_offset;
};

//First can be nebr sid, while the second could be edge id/property
class lite_edge_t {
 public:
    sid_t first;
    sid_t second;
};

////
inline void add_nebr1(sid_t* adj_list, vid_t index, sid_t value) {
    adj_list[index] = value;
}

inline void add_nebr1(lite_edge_t* adj_list, vid_t index, sid_t value) {
    adj_list[index].first = value;
}

inline void add_nebr2(lite_edge_t* adj_list, vid_t index, sid_t value, eid_t eid)
{
    adj_list[index].first = value;
    adj_list[index].second = eid;
}

inline void add_nebr3(lite_edge_t* adj_list, vid_t index, sid_t value, sid_t weight)
{
    adj_list[index].first = value;
    adj_list[index].second = weight;
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

////
inline void set_value1(sid_t* kv, vid_t vid, sid_t value) {
    kv[vid] = value;
}

inline void set_value1(lite_edge_t* kv, vid_t vid, sid_t value, eid_t eid) {
    kv[vid].first = value;
    kv[vid].second = eid;
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

    inline void add_nebr_lite(vid_t index, sid_t sid, eid_t eid) {
        add_nebr2(adj_list, index, sid, eid);
        
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
        log_count = (1L << 25);//32*8 MB
        if (posix_memalign((void**)&log_beg, 2097152, log_count*sizeof(T))) {
            //log_beg = (sid_t*)calloc(sizeof(sid_t), log_count);
            perror("posix memalign edge log");
        }
        log_head = 0;
        log_tail = 0;
        log_wpos = 0;
        
        dvt_count = 0;
        dvt_max_count = (1L << 20);
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
    inline void add_nebr_lite(vid_t vid, sid_t sid, eid_t eid) { 
        ++nebr_count[vid];
        beg_pos[vid].add_nebr_lite(nebr_count[vid], sid, eid);
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
        dvt_max_count = (1L << 20);
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
    eid_t    eid; 
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
    
    inline void set_value_lite(vid_t vert1_id, sid_t dst, eid_t eid) {
        kv[vert1_id].first = dst;
        kv[vert1_id].second = eid;
        dvt[dvt_count].vid = vert1_id;
        dvt[dvt_count].dst = dst;
        dvt[dvt_count].eid = eid;
        ++dvt_count;
    }
    void persist_kvlog(const string& kvfile);
    void read_kv(const string& kvfile); 
};

//typedef onekv_t<sid_t> skv_t; 
//typedef onekv_t<lite_edge_t> lite_skv_t; 

class sdegree_t {
    //type id and vertex count together
    sid_t  super_id;

    //array of degrees
    vid_t* degree;
};

#define eStatusarray 0
#define eFrontiers  1
#define eAdjlist    2
#define eKV         3


class srset_t;

//one type's result set
class rset_t {
    private:
    //few MSB bits = type
    //rest bits = words count in status array, maximum count in other cases
    sid_t scount;

    //few MSB bits: identify union
    //rest bits = frontier count  XXX not correct
    sid_t count2;

    //Notes: in td transform, vlist is used (input), status_array is produced;
    // in bu transform, status array is used in both (input and output)
    //In extend, input is vlist, output is kv or adjlist
    union {
        uint64_t* status_array;
        vid_t*    vlist;
        beg_pos_t* adjlist;
        sid_t*    kv;
    };

 public:
    friend class srset_t;
    inline rset_t() {
        scount = 0;
        count2 = 0;
        status_array = 0;
    }
    inline vid_t* get_vlist() { return vlist;}
    inline beg_pos_t* get_graph() { return adjlist;}
    inline uint64_t* get_barray() {return status_array;} 
    inline sid_t* get_kv() { return kv;};
    inline vid_t get_vcount() {return TO_VID(count2);}
    inline int   get_uniontype() {return TO_TID(count2);}
    inline tid_t get_tid() {return TO_TID(scount);}
    inline vid_t get_wcount() {return TO_VID(scount);}
    
    inline vid_t set_status(vid_t vid) {
        if(!get_status(vid)) {
            status_array[word_offset(vid)] |= ((uint64_t) 1L << bit_offset(vid));
            ++count2;
            return 1L;
        }
        return 0L;
    }
	inline void add_frontier(sid_t sid) {
		vid_t index = TO_VID(count2);
		vlist[index] = sid;
		++count2;
	}
	
    inline void setup_frontiers(tid_t tid, vid_t max_count) {
		scount = TO_SUPER(tid) + max_count;
		count2 = TO_SUPER(1) + 0;
		vlist = (vid_t*)calloc(sizeof(sid_t), max_count);
	}
	
    inline void add_adjlist_ro(vid_t index, beg_pos_t* begpos) {
        adjlist[index].copy(begpos);
	}
    
    inline void add_kv(vid_t index, sid_t sid) {
		kv[index] = sid;
	}
    
   
    private:
    inline vid_t get_status(vid_t vid) {
        return status_array[word_offset(vid)] & ((uint64_t) 1L << bit_offset(vid));
    }
    void copy_setup(rset_t* iset, int union_type); 
    void print_result(select_info_t* select_info, qid_t select_count, vid_t pos);
    void print_adjlist(select_info_t* select_info, qid_t select_count, vid_t pos);
    void print_kv(select_info_t* select_info, qid_t select_count, vid_t pos);
    void print_barray(select_info_t* select_info, qid_t select_count);
    void print_vlist(select_info_t* select_info, qid_t select_count);
    
    void bitwise2vlist();
    
    inline void setup(sid_t super_id) {
        tid_t tid = TO_TID(super_id);
        vid_t w_count = WORD_COUNT(TO_VID(super_id));
        scount  = TO_SUPER(tid) + w_count;
        count2 = TO_SUPER(eStatusarray);
        status_array = (uint64_t*) calloc(sizeof(uint64_t*), w_count);
    }

        
};

class srset_t {
 public:
    //array of result sets
    rset_t*  rset; 
    
    filter_info_t* filter_info;
    
    //type filters
    tid_t*  tfilter;
    
    select_info_t* select_info;
    
    uint8_t filter_count;
    uint8_t filter_done;
    uint8_t tfilter_count;
    uint8_t select_count;
    
 private:
    tid_t*  flag;
    //Total result set count and total frontiers count
    //few MSB bits = index into rset
    //other bits = total frontier count. XXX not correct
    uint64_t ccount;

 public:
    inline srset_t() {
        flag = 0;
        ccount = 0;
        rset = 0;
        filter_info = 0;
        filter_done = 1;
        tfilter = 0;
        tfilter_count = 0;
    }
    void setup_select(qid_t a_count); 
    void create_select(qid_t index, const char* a_name, const char* prop_name);
    
    inline void set_filter(filter_info_t* info) {
        filter_info = info;
        filter_done = 0;
    } 

    inline void setup_tfilter(tid_t count) {
        tfilter_count = count;
        tfilter = new tid_t[count];
    }
    inline void create_tfilter(tid_t index, tid_t tid) {
        assert(index < tfilter_count);
        tfilter[index] = tid;
    }
    
	inline tid_t get_sindex(sid_t sid) {
		tid_t tid = TO_TID(sid);
		return flag[tid];
	}

    inline vid_t get_status(sid_t sid) {
		tid_t index = get_sindex(sid);
		vid_t vert_id = TO_VID(sid);
        return rset[index].get_status(vert_id);
    } 
    
    inline void add_frontier(sid_t sid) {
		tid_t index = get_sindex(sid);
		vid_t vert_id = TO_VID(sid);
        rset[index].add_frontier(vert_id);
    }
    
    inline vid_t set_status(sid_t sid) {
        if (tfilter_count > 0 && eOK != apply_typefilter(TO_TID(sid))) {
            return 0L;
        }
        tid_t index = get_sindex(sid);
        vid_t vert_id = TO_VID(sid);
        return rset[index].set_status(vert_id);
    }

    inline tid_t get_rset_count() {return TO_TID(ccount);}
    inline tid_t get_total_vcount() {return TO_VID(ccount);}
    
    void bitwise2vlist();
    void print_result(tid_t tid_pos, vid_t vid_pos);
    status_t apply_typefilter(tid_t tid);
  
    tid_t full_setup(sflag_t sflag);
    tid_t full_setup(sgraph_t** sgraph);
    tid_t full_setup(skv_t** skv);
    tid_t copy_setup(srset_t* iset, int union_type);
    
    
    //Dont call directly
    tid_t setup(tid_t tid); 

};
