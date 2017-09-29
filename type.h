#pragma once
#include <stdint.h>
#include <limits.h>
#include <string>
#include <time.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include "bitmap.h"

using std::string;

#ifdef B64
typedef uint16_t propid_t;
typedef uint64_t vid_t;
typedef uint64_t sid_t;
typedef uint64_t eid_t;
typedef uint64_t index_t;
typedef uint32_t tid_t;
typedef uint64_t sflag_t;
typedef uint16_t qid_t;
typedef uint32_t snapid_t ;
//typedef uint16_t rdegree_t; //relative degree
typedef int32_t degree_t;
#elif B32
typedef uint8_t propid_t;
typedef uint32_t vid_t;
typedef uint32_t sid_t;
typedef uint32_t eid_t;
typedef uint64_t index_t;
typedef uint8_t tid_t;
typedef uint64_t sflag_t;
typedef uint16_t qid_t;
typedef uint32_t snapid_t ;
//typedef uint16_t rdegree_t; //relative degree
typedef uint32_t degree_t;
#endif

typedef uint32_t vflag_t;

#ifndef PLAIN_GRAPH 
#ifdef B64
#define VBIT 40
#define VMASK 0xffffffffff
#define THIGH_MASK 0x7FFFFF0000000000
#define DEL_MASK   0x8000000000000000
#define SID_MASK   0x7FFFFFFFFFFFFFFF
#elif B32
#define VBIT 28
#define VMASK 0xfffffff
#define THIGH_MASK 0x70000000
#define DEL_MASK   0x80000000
#define SID_MASK   0x7FFFFFFF
#endif
#else
#ifdef B64
#define VBIT 40
#define VMASK 0xffffffffff
#define THIGH_MASK 0x7FFFFF0000000000
#define DEL_MASK   0x8000000000000000
#define SID_MASK   0x7FFFFFFFFFFFFFFF
#elif B32
#define VBIT 31
#define VMASK 0x7fffffff
#define THIGH_MASK 0x00000000
#define DEL_MASK   0x80000000
#define SID_MASK   0x7FFFFFFF
#endif
#endif

#define TO_TID(sid)  ((sid & THIGH_MASK) >> VBIT)
#define TO_VID(sid)  (sid & VMASK)
#define TO_SID(sid)  (sid & SID_MASK)
#define TO_SUPER(tid) (((sid_t)(tid)) << VBIT)
#define TO_THIGH(sid) (sid & THIGH_MASK)
#define DEL_SID(sid) (sid | DEL_MASK)
#define IS_DEL(sid) (sid & DEL_MASK)

#define TID_TO_SFLAG(tid) (1L << tid)
#define WORD_COUNT(count) ((count + 63) >> 6)

extern propid_t INVALID_PID;
extern tid_t    INVALID_TID;
extern sid_t    INVALID_SID;
extern degree_t INVALID_DEGREE;
//#define INVALID_PID 0xFFFF
//#define INVALID_TID 0xFFFFFFFF
//#define INVALID_SID 0xFFFFFFFFFFFFFFFF

#define NO_QID 0xFFFF

extern double  bu_factor;
extern int32_t MAX_BCOUNT; //256
extern uint64_t MAX_ECOUNT; //1000000
extern uint64_t MAX_PECOUNT;//670000

extern index_t  BATCH_SIZE;//
extern index_t  BLOG_SIZE;//
extern index_t  DELTA_SIZE;
extern index_t  DEGREE_SIZE;
extern index_t  VUNIT_SIZE;

extern index_t  W_SIZE;//Durable edge log offset
extern index_t  DVT_SIZE;
extern index_t  DURABLE_SIZE;//


void free_buf(void* buf);
void* alloc_buf();

off_t fsize(const string& fname);
off_t fsize(int fd);

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
    eOOM,
    eDelete,
    eNoWork,
    eUnknown        
};

typedef union __univeral_type {
    uint8_t  value_8b;
    uint16_t value16b;
    tid_t    value_tid;
    vid_t    value_vid;
    sid_t    value_sid;
    sid_t    value;
    float    value_float;

#ifdef B32   
    char     value_string[4];
    sid_t    value_charp;
#else     
    char     value_string[8];
    int64_t  value_64b;
    eid_t    value_eid;
    time_t   value_time;
    char*    value_charp;
    double   value_double;
#endif
}univ_t;


template <class T>
class  edgeT_t {
 public:
    sid_t src_id;
    T     dst_id;
};

//First can be nebr sid, while the second could be edge id/property
class lite_edge_t {
 public:
    sid_t first;
    univ_t second;
};

typedef edgeT_t<sid_t> edge_t;
typedef edgeT_t<lite_edge_t> ledge_t;

inline sid_t get_dst(edge_t* edge) { 
    return edge->dst_id;
}
inline void set_dst(edge_t* edge, sid_t dst_id) {
    edge->dst_id = dst_id;
}
inline void set_weight(edge_t* edge, sid_t dst_id) {
}

inline sid_t get_dst(ledge_t* edge) { 
    return edge->dst_id.first;
}
inline void set_dst(ledge_t* edge, sid_t dst_id) {
    edge->dst_id.first = dst_id;
}
inline void set_weight(ledge_t* edge, lite_edge_t dst_id) {
    edge->dst_id.second = dst_id.second;
}

////
inline sid_t get_sid(lite_edge_t lite_edge)
{
    return lite_edge.first;
}

inline sid_t get_sid(sid_t sid)
{
    return sid;
}

inline void set_sid(lite_edge_t& lite_edge, sid_t sid1)
{
    lite_edge.first = sid1;
}

inline void set_sid(sid_t& sid , sid_t sid1)
{
    sid = sid1;
}

inline void set_weight(lite_edge_t& lite_edge, lite_edge_t dst)
{
    lite_edge.second = dst.second;
}

inline void set_weight(sid_t& sid , sid_t dst)
{
    return;
}

class snapshot_t {
 public:
    snapid_t snap_id;
    index_t marker;
    index_t durable_marker;
    snapshot_t* next;
};

class disk_snapshot_t {
 public:
    snapid_t snap_id;
    index_t  marker;
    index_t  durable_marker;
};

template <class T>
class delta_adjlist_t {
	delta_adjlist_t<T>* next;
	sid_t count;
	//T  adj_list;

 public:
	inline delta_adjlist_t<T>() {next = 0; count = 0;}
	inline degree_t get_nebrcount() { return count;}
	inline void set_nebrcount(degree_t degree) {count = degree;}

	inline degree_t incr_nebrcount_noatomic() {
        return count++;
    }
	inline degree_t incr_nebrcount() {
        return  __sync_fetch_and_add(&count, 1);
    }
    inline degree_t incr_nebrcount_bulk(degree_t count1) {
        degree_t old_count = count;
        count += count1;
        return old_count;
    }
	inline T* get_adjlist() { return (T*)(&count + 1); }
	inline void add_next(delta_adjlist_t<T>* ptr) {next = ptr; }
	inline delta_adjlist_t<T>* get_next() { return next; }
};

template <class T>
class durable_adjlist_t {
    sid_t vid;
	sid_t count;
	//T  adj_list;

 public:
	inline durable_adjlist_t<T>() {count = 0;}
	inline degree_t get_nebrcount() { return count;}
	void set_nebrcount(degree_t degree) {count = degree;}
	inline T* get_adjlist() { return (T*)(&count + 1); }
};

template <class T>
class vunit_t {
 public:
	//Durable adj list, and num of nebrs in that
	vflag_t       vflag;
	degree_t      count;
    index_t       offset;
	delta_adjlist_t<T>* delta_adjlist;

	inline void reset() {
		vflag = 0;
		count = 0;
		offset = -1L;
		delta_adjlist = 0;
	}
};

class pedge_t {
 public:
    propid_t pid;
    sid_t src_id;
    univ_t dst_id;
};


class disk_vtable_t {
    public:
    vid_t    vid;
	//Length of durable adj list
    degree_t count;
    degree_t del_count;
    uint64_t file_offset;
    //uint64_t old_offset;//for cleaning
};

//used for offline processing
class ext_vunit_t {
    public:
    degree_t  count;
    degree_t  del_count;
    index_t   offset;
};

//property name value pair
struct prop_pair_t {
    string name;
    string value;
};


template <class T>
class delentry_t {
 public:
    degree_t pos;
    T dst_id;
};

template <class T>
class  snapT_t {
 public:
    //snapT_t<T>*     next;//next snapshot of this vid 
    snapT_t<T>*     prev;//prev snapshot of this vid 
    //T*        adj_list;//validity depends on cleaning state 
    snapid_t  snap_id;
    degree_t  degree;
    degree_t  del_count;
};

//This will be used as disk write structure
template <class T>
class  disk_snapT_t {
 public:
    vid_t     vid;
    snapid_t  snap_id;
    degree_t  degree;
    degree_t del_count;
};

snapid_t get_snapid();

//Used for writing adj list to disk
class write_seg_t {
 public:
     disk_vtable_t* dvt;
     index_t        dvt_count;
     char*          log_beg;
     index_t        log_head;
	 //This is file offset at which to start writing
	 index_t        log_tail;
	 //allocated from main vunit
	 index_t        my_vunit_head;

     inline write_seg_t() {
        dvt = 0;
        dvt_count = 0;
        log_beg = 0;
        log_head = 0;
		log_tail = 0;
		my_vunit_head = 0;
     }
	 inline void reset() {
        dvt = 0;
        dvt_count = 0;
        log_beg = 0;
        log_head = 0;
		log_tail = 0;
		my_vunit_head = 0;
	 }
};

//edge batching buffer
template <class T>
class blog_t {
 public:
    edgeT_t<T>* blog_beg;
    //In memory size
    index_t     blog_count;
    //current batching position
    index_t     blog_head;
    //Make adj list from this point
    index_t     blog_tail;
    //Make adj list upto this point
    index_t     blog_marker;
    //Make edge durable from this point
    index_t     blog_wtail;
    //Make edge durable upto this point
    index_t     blog_wmarker;

    blog_t() {
        blog_beg = 0;
        blog_count = 0;
        blog_head = 0;
        blog_tail = 0;
        blog_marker = 0;
        blog_wtail = 0;
        blog_wmarker = 0;
    }
};

typedef struct __econf_t {
    string filename;
    string predicate;
    string src_type;
    string dst_type;
    string edge_prop;
} econf_t; 

typedef struct __vconf_t {
    string filename;
    string predicate;
} vconf_t; 

