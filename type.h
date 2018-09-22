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
typedef uint16_t snapid_t ;
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
typedef uint16_t snapid_t ;
//typedef uint16_t rdegree_t; //relative degree
typedef uint32_t degree_t;
#endif

typedef uint16_t vflag_t;

#define HUB_COUNT  8192

#ifndef PLAIN_GRAPH 
#ifdef B64
#define VBIT 40
#define VMASK 0xffffffffff
#define THIGH_MASK 0x7FFFFF0000000000
#define DEL_MASK   0x8000000000000000
#define SID_MASK   0x7FFFFFFFFFFFFFFF
#define CL_COUNT   4
#define CL_ADJUST  1
#define CL_MASK    0xFFFFFFFFFFFFFFFC
#elif B32
#define VBIT 28
#define VMASK 0xfffffff
#define THIGH_MASK 0x70000000
#define DEL_MASK   0x80000000
#define SID_MASK   0x7FFFFFFF
#define CL_COUNT   8
#define CL_ADJUST  2
#define CL_MASK    0xFFFFFFFFFFFFFFF8
#endif
#else
#ifdef B64
#define VBIT 40
#define VMASK 0xffffffffff
#define THIGH_MASK 0x7FFFFF0000000000
#define DEL_MASK   0x8000000000000000
#define SID_MASK   0x7FFFFFFFFFFFFFFF
#define CL_COUNT   15 
#define CL_ADJUST  1 
#define CL_MASK    0xFFFFFFFFFFFFFFF0
#elif B32
#define VBIT 31
#define VMASK 0x7fffffff
#define THIGH_MASK 0x00000000
#define DEL_MASK   0x80000000
#define SID_MASK   0x7FFFFFFF
#define CL_COUNT   16 
#define CL_ADJUST  4
#define CL_MASK    0xFFFFFFFFFFFFFFF0
#endif
#endif

#ifdef OVER_COMMIT
#define TO_MAXCOUNT(X) ((((X)+CL_ADJUST+CL_COUNT-1) & CL_MASK) - CL_ADJUST)
#else
#define TO_MAXCOUNT(X) (X)
#endif

#define TO_MAXCOUNT1(X) ((((X) + CL_ADJUST+ 1024 - 1) & 0xFFFFFFFFFFFFFC00) - CL_ADJUST)

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
extern index_t  BATCH_MASK;//
extern index_t  BLOG_SHIFT;//
//extern index_t  BLOG_MASK;//
extern index_t  DELTA_SIZE;
extern index_t  SNAP_COUNT;

extern index_t  W_SIZE;//Durable edge log offset
extern index_t  DVT_SIZE;
extern index_t  DURABLE_SIZE;//

extern index_t  OFF_COUNT;
extern int      THD_COUNT;
extern index_t  LOCAL_VUNIT_COUNT;
extern index_t  LOCAL_DELTA_SIZE;

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

struct netflow_weight_t {
    uint32_t time;
    uint32_t duration;
    uint32_t protocol;
    uint16_t src_port;
    uint16_t dst_port;
    uint32_t src_packet;
    uint32_t dst_packet;
    uint32_t src_bytes;
    uint32_t dst_bytes;
};

//vid_t    src_user;
//vid_t    dst_user;
struct auth_weight_t {
    uint32_t time;
    vid_t    src_computer;
    vid_t    dst_computer;
    uint8_t  auth_type;
    uint8_t  logon_type;
    uint8_t  status;
};

//First can be nebr sid, while the second could be edge id/property
template <class T>
class dst_weight_t {
 public:
    sid_t first;
    T second;
};

//Feel free to name the derived types, but not required.
typedef dst_weight_t<univ_t> lite_edge_t;
typedef dst_weight_t<netflow_weight_t> netflow_dst_t;
typedef dst_weight_t<auth_weight_t> auth_dst_t;

typedef edgeT_t<sid_t> edge_t;
typedef edgeT_t<lite_edge_t> ledge_t;
typedef edgeT_t<netflow_dst_t> netflow_edge_t;
typedef edgeT_t<auth_dst_t> auth_edge_t;

inline sid_t get_dst(edge_t* edge) {
    return edge->dst_id;
}
inline void set_dst(edge_t* edge, sid_t dst_id) {
    edge->dst_id = dst_id;
}
inline void set_weight(edge_t* edge, sid_t dst_id) {
}

template <class T>
inline sid_t get_dst(edgeT_t<T>* edge) { 
    return edge->dst_id.first;
}
template <class T>
inline void set_dst(edgeT_t<T>* edge, sid_t dst_id) {
    edge->dst_id.first = dst_id;
}
template <class T>
inline void set_weight(edgeT_t<T>* edge, T dst_id) {
    edge->dst_id.second = dst_id.second;
}

////
template <class T> sid_t get_sid(T dst);
template <class T> void set_sid(T& edge, sid_t sid1);
template <class T> void set_weight(T& edge, T& dst);
template <class T> sid_t get_nebr(T* adj, vid_t k); 

template <class T>
inline sid_t get_sid(T dst)
{
    return dst.first;
}

template <class T>
inline void set_sid(T& edge, sid_t sid1)
{
    edge.first = sid1;
}

template <class T>
inline void set_weight(T& edge, T& dst)
{
    edge.second = dst.second;
}

template <class T>
inline sid_t get_nebr(T* adj, vid_t k) {
    return adj[k].first;
}

//Specialized functions for plain graphs, no weights
template <>
inline void set_sid<sid_t>(sid_t& sid , sid_t sid1)
{
    sid = sid1;
}

template<>
inline void set_weight<sid_t>(sid_t& sid , sid_t& dst)
{
    return;
}

template<>
inline sid_t get_sid<sid_t>(sid_t sid)
{
    return sid;
}

template <>
inline sid_t get_nebr<sid_t>(sid_t* adj, vid_t k) {
    return adj[k];
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
    
    inline void add_nebr(T sid) { 
        T* adj_list1 = get_adjlist();
        degree_t index = incr_nebrcount();
        adj_list1[index] = sid;
    }
    
    inline void add_nebr_noatomic(T sid) { 
        T* adj_list1 = get_adjlist();
        degree_t index = incr_nebrcount_noatomic();
        adj_list1[index] = sid;
    }
    
    // XXX Should be used for testing purpose, be careful to use it,
    // as it avoids atomic instructions.
    inline void add_nebr_bulk(T* adj_list2, degree_t count) {
        if(count != 0) {
            T* adj_list1 = get_adjlist();
            degree_t old_count = incr_nebrcount_bulk(count);
            memcpy(adj_list1+old_count, adj_list2, count*sizeof(T));
        }
    }
    
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

//Special v-unit flags
//#define VUNIT_NORMAL 0
//#define VUNIT_SHORT  1
//#define VUNIT_LONG   2
//#define TO_VUNIT_FLAG(flag)  (flag & 0x3)
//#define TO_VUNIT_COUNT(flag) ((flag >> 2 ) & 0x7)

#ifdef BULK 
template <class T>
class vunit_t {
 public:
	//Durable adj list, and num of nebrs in that
	uint32_t      vflag;
	degree_t      count;
    index_t       offset;
	delta_adjlist_t<T>* delta_adjlist;
	delta_adjlist_t<T>* adj_list;//Last chain

	inline void reset() {
		vflag = 0;
		count = 0;
		offset = -1L;
		delta_adjlist = 0;
        adj_list = 0;
	}
};
#else
template <class T>
class vunit_t {
 public:
	//Durable adj list, and num of nebrs in that
	uint16_t      vflag;
	uint16_t      max_size; //max count in delta adj list
    degree_t      count;  //durable degree count
    index_t       offset; //file offset at which it was written
	delta_adjlist_t<T>* delta_adjlist;
	delta_adjlist_t<T>* adj_list;//Last chain

	inline void reset() {
		vflag = 0;
		count = 0;
		offset = -1L;
		delta_adjlist = 0;
        adj_list = 0;
	}
};
#endif

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
    snapT_t<T>*     prev;//prev snapshot of this vid 
    degree_t  degree;
    snapid_t  snap_id;
    uint16_t  del_count;
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
    //MASK
    index_t     blog_mask;

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

class nebrcount_t {
 public:
    degree_t    add_count;
    degree_t    del_count;
	//delta_adjlist_t<T>* adj_list;
};

template <class T>
class pgraph_t;

template <class T>
class vert_table_t;

template<class T>
class wsstream_t;

template<class T>
class sstream_t;

template<class T>
class wstream_t;

template<class T>
class stream_t;

template<class T>
struct callback {
      typedef void(*wsfunc)(wsstream_t<T>*);
      typedef void(*sfunc)(sstream_t<T>*);
      typedef void(*wfunc)(wstream_t<T>*);
      typedef void(*func)(stream_t<T>*);
};

template <class T>
struct snap_t {
    vert_table_t<T>* graph_out;
    vert_table_t<T>* graph_in;
    degree_t*        degree_out;
    degree_t*        degree_in;

    snapshot_t*      snapshot;
    pgraph_t<T>*     pgraph;  
    edgeT_t<T>*      edges; //mew edges
    vid_t            edge_count;//their count
    vid_t            v_count;
public:

    degree_t get_nebrs_out(vid_t vid, T*& ptr);
    degree_t get_nebrs_in (vid_t vid, T*& ptr);
    degree_t get_nebrs_length_out(vid_t vid);
    degree_t get_nebrs_length_in (vid_t vid);
     
    //Raw access, low level APIs
    nebrcount_t get_nebrs_archived_out(vid_t, T*& ptr);
    nebrcount_t get_nebrs_archived_in(vid_t, T*& ptr);
};

template <class T>
class sstream_t {
 public:
    vert_table_t<T>* graph_out;
    vert_table_t<T>* graph_in;
    degree_t*        degree_out;
    degree_t*        degree_in;

    snapshot_t*      snapshot;
    pgraph_t<T>*     pgraph;
    vid_t            v_count; 
    edgeT_t<T>*      edges; //new edges
    
    //For edge centric, zero otherwise
    index_t          edge_count;//their count
    
    //last few edges of above data-structure, 0 for stale
    index_t          non_archived_count;
    
    void*            algo_meta;//algorithm specific data
    typename callback<T>::sfunc   sstream_func; 

 public:
    sstream_t(){
        graph_out = 0;
        graph_in = 0;
        degree_out = 0;
        degree_in = 0;
        snapshot = 0;
        edges = 0;
        edge_count = 0;
        algo_meta = 0;
        pgraph = 0;
    }
 public:
    inline void    set_algometa(void* a_meta) {algo_meta = a_meta;}
    inline void*   get_algometa() {return algo_meta;}

    inline edgeT_t<T>* get_edges() { return edges;}
    inline void        set_edges(edgeT_t<T>*a_edges) {edges = a_edges;}
    
    inline index_t     get_edgecount() { return edge_count;}
    inline void        set_edgecount(index_t a_edgecount){edge_count = a_edgecount;}

 public:
    void update_sstream_view();

    degree_t get_nebrs_out(vid_t vid, T*& ptr);
    degree_t get_nebrs_in (vid_t vid, T*& ptr);
    degree_t get_nebrs_length_out(vid_t vid);
    degree_t get_nebrs_length_in (vid_t vid);
    nebrcount_t get_nebrs_archived_out(vid_t, T*& ptr);
    nebrcount_t get_nebrs_archived_in(vid_t, T*& ptr);
};

template <class T>
class wsstream_t {
 public:
    snapshot_t*      snapshot;
    pgraph_t<T>*     pgraph;
    vid_t            v_count; 
    void*            algo_meta;//algorithm specific data
    typename callback<T>::wsfunc   wsstream_func;
    
    //ending marker of the window
    vert_table_t<T>* graph_out;
    vert_table_t<T>* graph_in;
    degree_t*        degree_out;
    degree_t*        degree_in;
    
    edgeT_t<T>*      edges; //new edges
    
    //For edge centric, zero otherwise
    index_t          edge_count;//their count
    
    //last few edges of above data-structure, 0 for stale
    index_t          non_archived_count;
    
    //starting marker of the window
    degree_t*        degree_out1;
    degree_t*        degree_in1;
    
    edgeT_t<T>*      edges1; //old edges
    index_t          edge_count1; //their count

 public:
    wsstream_t(){
        graph_out = 0;
        graph_in = 0;
        degree_out = 0;
        degree_in = 0;
        snapshot = 0;
        edges = 0;
        edge_count = 0;
        algo_meta = 0;
        pgraph = 0;
    }
 public:
    inline void    set_algometa(void* a_meta) {algo_meta = a_meta;}
    inline void*   get_algometa() {return algo_meta;}
    
    degree_t get_nebrs_out(vid_t vid, T*& ptr);
    degree_t get_nebrs_in (vid_t vid, T*& ptr);
    degree_t get_nebrs_length_out(vid_t vid);
    degree_t get_nebrs_length_in (vid_t vid);
    
    nebrcount_t get_nebrs_archived_out(wsstream_t<T>* snaph, vid_t, T*& ptr);
    nebrcount_t get_nebrs_archived_in(wsstream_t<T>* snaph, vid_t, T*& ptr);
    
    void update_wsstream_view(wsstream_t<T>* wsstreamh);
};

template <class T>
class stream_t {
 public:
    index_t          edge_offset;//Compute starting offset
    edgeT_t<T>*      edges; //mew edges
    index_t          edge_count;//their count
    pgraph_t<T>*     pgraph;
    
    void*            algo_meta;//algorithm specific data
    typename callback<T>::func   stream_func;


 public:
    stream_t(){
        edges = 0;
        edge_count = 0;
        algo_meta = 0;
    }
 public:
    inline void    set_algometa(void* a_meta) {algo_meta = a_meta;}
    inline void*   get_algometa() {return algo_meta;}

    inline edgeT_t<T>* get_edges() { return edges;}
    inline void        set_edges(edgeT_t<T>*a_edges) {edges = a_edges;}
    
    inline index_t     get_edgecount() { return edge_count;}
    inline void        set_edgecount(index_t a_edgecount){edge_count = a_edgecount;}

 public:   
    void update_stream_view();
};
