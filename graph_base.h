#pragma once
#include <iostream>
#include <libaio.h>
#include "type.h"

using std::cout;
using std::endl;

////
inline void add_nebr1(sid_t* adj_list, vid_t index, sid_t value) {
    //degree_t index = __sync_fetch_and_add(adj_list, 1L);
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
 private:
    //nebr list of one vertex. First member is a spl member
    //count, flag for snapshot, XXX: smart pointer count
    snapT_t<T>*   snap_blob;

 public:
	vunit_t<T>*   v_unit;
    inline vert_table_t() { snap_blob = 0; v_unit = 0;}

    inline vid_t get_nebrcount() {
        if (snap_blob) return snap_blob->degree;
        else  return 0; 
    }
    
    inline index_t get_offset() { return v_unit->offset; }
	inline void set_offset(index_t adj_list1) { 
		v_unit->offset = adj_list1; 
	}
    
    //XXX
    inline T* get_adjlist() { return 0;}
	
	inline delta_adjlist_t<T>* get_delta_adjlist() {return v_unit->delta_adjlist;}
	inline void set_delta_adjlist(delta_adjlist_t<T>* delta_adjlist1) {
		v_unit->delta_adjlist = delta_adjlist1;
	}
	
	inline vunit_t<T>* get_vunit() {return v_unit;}
	inline vunit_t<T>* set_vunit(vunit_t<T>* v_unit1) {
        //prev value will be cleaned later
		vunit_t<T>* v_unit2 = v_unit;
		v_unit = v_unit1;//Atomic XXX
		return v_unit2;
	}

	inline snapT_t<T>* get_snapblob() { return snap_blob; } 
    
    /*
    //The incoming is composite or simple, depends on if/else
    inline void set_snapblob(snapT_t<T>* snap_blob1) { 
        if (0 == snap_blob) {
            snap_blob = snap_blob1; 
        } else {
            snap_blob1->prev->prev = snap_blob->prev;
            if (snap_blob->prev) {
                snap_blob->prev->next = snap_blob1->prev;
            }
            snapT_t<T>* old_blob = snap_blob;
            snap_blob = snap_blob1;
            free(old_blob);
        }
    }*/ 
    
    //The incoming is simple, called from read_stable
    inline void set_snapblob1(snapT_t<T>* snap_blob1) { 
        if (0 == snap_blob) {
            snap_blob1->prev  = 0;
            //snap_blob1->next = 0;
        } else {
            snap_blob1->prev = snap_blob;
            //snap_blob1->next = 0;
            //snap_blob->next = snap_blob1;
        }
        snap_blob = snap_blob1; 
    } 
    
    inline snapT_t<T>* recycle_snapblob(snapid_t snap_id) { 
        if (0 == snap_blob || 0 == snap_blob->prev) return 0;
        
        int snap_count = 2;
        snapT_t<T>* snap_blob1 = snap_blob;
        snapT_t<T>* snap_blob2 = snap_blob->prev;

        while (snap_blob2->prev != 0) {
            snap_blob1 = snap_blob2;
            snap_blob2 = snap_blob2->prev;
            ++snap_count;
        }
        if (snap_count < SNAP_COUNT) {
            return 0;
        }

        snap_blob1->prev = 0;
        snap_blob2->snap_id = snap_id;
        snap_blob2->del_count = snap_blob->del_count;
        snap_blob2->degree = snap_blob->degree;
        set_snapblob1(snap_blob2);
        return snap_blob2;
    } 
    
    //Will go away soon.
	inline void copy(vert_table_t<T>* beg_pos) {
        v_unit = beg_pos->v_unit;
    }
};

template <class T>
class nebrcount_t {
 public:
    degree_t    add_count;
    degree_t    del_count;
	//delta_adjlist_t<T>* adj_list;
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

    vid_t    max_vcount;
    
    //delta adj list
    char*      adjlog_beg;  //memory log pointer
    index_t    adjlog_count;//size of memory log
    index_t    adjlog_head; // current log write position
    index_t    adjlog_tail; //current log cleaning position

    //durable adj list, for writing to disk
    index_t    log_tail; //current log cleaning position
    index_t    log_count;//size of memory log
    
    /*
    T*         log_beg;  //memory log pointer
    index_t    log_head; // current log write position
    index_t    log_whead; //Write this pointer for write persistency
    index_t    log_wtail; //Write upto this point
    */
    //degree array related log, in-memory, fixed size logs
	//indirection will help better cleaning.
    snapT_t<T>* dlog_beg;  //memory log pointer
	index_t*    dlog_ind;  // The indirection table
    index_t     dlog_count;//size of memory log
    index_t     dlog_head; // current log write position
    index_t     dlog_tail; //current log cleaning position
    index_t     dlog_wpos; //Write this pointer for write persistency

    /*
    //degree array related log, for writing to disk
    disk_snapT_t<T>* snap_log;
    index_t snap_count;
    index_t snap_whead;
    index_t snap_wtail;
*/
	//v_unit log, in-memory, fixed size log
	//indirection will help better cleaning
	vunit_t<T>* vunit_beg;
    index_t     vunit_head1;
	vid_t*		vunit_ind; //The indirection table
	index_t     vunit_count;
	index_t     vunit_head;
	index_t     vunit_tail;
	index_t     vunit_wtail;


    //vertex table file related log
    write_seg_t  write_seg[3];
    //disk_vtable_t* dvt;
    //vid_t    dvt_count; 
    vid_t    dvt_max_count;

    int      vtf;   //vertex table file
    FILE*    stf;   //snapshot table file

    string   file;
public:
    int    etf;   //edge table file
    nebrcount_t<T>*   nebr_count;

private:    
    inline void del_nebr(vid_t vid, T sid) {
        sid_t actual_sid = TO_SID(get_sid(sid)); 
        degree_t location = find_nebr(vid, actual_sid);
        if (INVALID_DEGREE != location) {
            beg_pos[vid].v_unit->adj_list->add_nebr(sid);
        }
    }
    
    inline void del_nebr_noatomic(vid_t vid, T sid) {
        sid_t actual_sid = TO_SID(get_sid(sid)); 
        degree_t location = find_nebr(vid, actual_sid);
        if (INVALID_DEGREE != location) {
            beg_pos[vid].v_unit->adj_list->add_nebr_noatomic(sid);
        }
    }

public:
    inline onegraph_t() {
        super_id = 0;
        beg_pos = 0;
        nebr_count = 0;
        max_vcount = 0;
       
	    vunit_beg	= 0;
		vunit_count = 0;
		vunit_ind	= 0;
		vunit_head1  = 0;
		vunit_head  = 0;
		vunit_tail  = 0;
		vunit_wtail = 0;


        adjlog_count = 0;
        adjlog_head  = 0;
        adjlog_tail = 0;

        log_count = 0;
        /*
        log_head  = 0;
        log_tail  = 0;
        log_tail  = 0;
        log_whead = 0;
        log_wtail = 0;
        */
        dlog_count = 0;
        dlog_head = 0;
        dlog_tail = 0;
        dlog_wpos = 0;
       
       /* 
        snap_count = 0;
        snap_whead = 0;
        snap_wtail = 0;
       */
        
        //dvt_count = 0;
        dvt_max_count = 0;
		write_seg[0].reset();
		write_seg[1].reset();
		write_seg[2].reset();

        vtf = -1;
        etf = -1;
        stf = 0;
    }
    
    void setup(tid_t tid);
    //void setup_adjlist(vid_t vid_start, vid_t vid_end);
    void setup_adjlist();
    void setup_adjlist_noatomic(vid_t vid_start, vid_t vid_end);

    void increment_count_noatomic(vid_t vid) {
        ++nebr_count[vid].add_count;
    }
    void decrement_count_noatomic(vid_t vid) {
        ++nebr_count[vid].del_count;
    }

    inline void increment_count(vid_t vid) { 
        __sync_fetch_and_add(&nebr_count[vid].add_count, 1L);
    }

    inline void decrement_count(vid_t vid) { 
        __sync_fetch_and_add(&nebr_count[vid].del_count, 1L);
    }
    
    inline void add_nebr(vid_t vid, T sid) {
        if (IS_DEL(get_sid(sid))) { 
            return del_nebr(vid, sid);
        }
        beg_pos[vid].v_unit->adj_list->add_nebr(sid);
    }
    
    inline void add_nebr_noatomic(vid_t vid, T sid) {
        if (IS_DEL(get_sid(sid))) { 
            return del_nebr_noatomic(vid, sid);
        }
        beg_pos[vid].v_unit->adj_list->add_nebr_noatomic(sid);
    }
    
    inline void add_nebr_bulk(vid_t vid, T* adj_list1, degree_t count) {
        beg_pos[vid].v_unit->adj_list->add_nebr_bulk(adj_list1, count);
    }

    degree_t find_nebr(vid_t vid, sid_t sid); 
    
    /* don't use. free yourself
	inline void set_vunit(vid_t vid, vunit_t<T>* v_unit1) {
        //prev value will be cleaned later
		vunit_t<T>* v_unit2 = beg_pos[vid].set_vunit(v_unit1);
		if (0 != v_unit2) {
			index_t index  = __sync_fetch_and_add(&vunit_tail, 1L);
			vid_t index1 = index % vunit_count;
			vunit_ind[index1] = v_unit2 - vunit_beg;
		}
	}*/
   
    //durable adj list	
	inline durable_adjlist_t<T>* new_adjlist(write_seg_t* seg,  degree_t count) {
        degree_t new_count = count*sizeof(T)+sizeof(durable_adjlist_t<T>);
        //index_t index_log = __sync_fetch_and_add(&seg->log_head, new_count);
        //assert(index_log  < log_count); 
        index_t index_log = seg->log_head;
        seg->log_head += new_count;
        assert(seg->log_head  <= log_count); 
        return  (durable_adjlist_t<T>*)(seg->log_beg + index_log);
	}
	
    
    //delta adj list allocation
	inline delta_adjlist_t<T>* new_delta_adjlist(degree_t count) {
        degree_t new_count = count*sizeof(T) + sizeof(delta_adjlist_t<T>);
		index_t index_adjlog = __sync_fetch_and_add(&adjlog_head, new_count);
		assert(index_adjlog  < adjlog_count); 
		return (delta_adjlist_t<T>*)(adjlog_beg + index_adjlog);
	}
    
    
	//in-memory snap degree
	inline snapT_t<T>* new_snapdegree() {
		index_t index_dlog  = __sync_fetch_and_add(&dlog_head, 1L);
		assert(index_dlog   < dlog_count);
		return (dlog_beg + index_dlog);
	}

	inline disk_vtable_t* new_dvt(write_seg_t* seg) {
        //index_t j = __sync_fetch_and_add(&seg->dvt_count, 1L);
        index_t j = seg->dvt_count;
        ++seg->dvt_count;
		//assert();
		return seg->dvt + j;
	}
	
    //Used during read from disk
	inline vunit_t<T>* new_vunit() {
		index_t index = __sync_fetch_and_add(&vunit_head1, 1L);
        assert(index < get_vcount());
		vunit_t<T>* v_unit = vunit_beg + index;
		v_unit->reset();
		return v_unit;
	}	

    //don't reset    
    inline vunit_t<T>* new_vunit(write_seg_t* seg, vid_t v) {
		vid_t index1 = (seg->my_vunit_head + v) % vunit_count;
		return  (vunit_beg + vunit_ind[index1]);
	}	
    
    // -------------------- BULK ------------------    
    inline vunit_t<T>* new_vunit_bulk(vid_t count) {
		index_t index = __sync_fetch_and_add(&vunit_head1, count);
		assert(index < get_vcount());
		vunit_t<T>* v_unit = vunit_beg + index;
		return v_unit;
	}	

	inline index_t new_vunit_bulk2(vid_t count) {
		index_t index = vunit_head;
        vunit_head += count; 
		return index;
	}

	inline char* new_delta_adjlist_bulk(index_t count) {
		index_t index_adjlog = __sync_fetch_and_add(&adjlog_head, count);
        index_t index = (index_adjlog % adjlog_count);
		//assert(index_adjlog  < adjlog_count); 
		return (adjlog_beg + index);
    }
    
    inline snapT_t<T>* new_snapdegree_bulk(vid_t count) {
		index_t index_dlog  = __sync_fetch_and_add(&dlog_head, count);
		assert(index_dlog   < dlog_count);
		return (dlog_beg + index_dlog);
	}
	
    inline void reset_count(vid_t vid) {
        nebr_count[vid].add_count = 0;
        nebr_count[vid].del_count = 0;
    }
    
    inline vert_table_t<T>* get_begpos() { return beg_pos;}
    inline vid_t get_vcount() { return TO_VID(super_id);}
    inline tid_t get_tid() { return TO_TID(super_id);}


    void prepare_dvt(write_seg_t* seg, vid_t& last_vid, bool clean = false);
	void adj_prep(write_seg_t* seg);
	void adj_update(write_seg_t* seg);
    void handle_write(bool clean = false);
    
    void update_count();
    /*
    void prepare_vlog();
	void persist_elog(const string& etfile);
    void persist_vlog(const string& vtfile);
    void persist_slog(const string& stfile);
    void read_etable(const string& etfile);
    void read_stable(const string& stfile);
    */
    void read_vtable();
    void file_open(const string& filename, bool trunc);
};

typedef vert_table_t<sid_t> beg_pos_t;
typedef beg_pos_t  lgraph_t;
typedef vert_table_t<lite_edge_t> lite_vtable_t;

typedef onegraph_t<sid_t> sgraph_t;
typedef onegraph_t<lite_edge_t>lite_sgraph_t;



/*
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
*/

template <class T>
class disk_kvT_t {
    public:
    vid_t    vid;
    T       dst;
};

typedef disk_kvT_t<sid_t> disk_kv_t;
typedef disk_kvT_t<lite_edge_t> disk_kvlite_t;

/*
class disk_kvlite_t {
    public:
    vid_t    vid;
    sid_t    dst;
    univ_t   univ; 
};
*/
//one type's key-value store
template <class T>
class onekv_t {
 private:
    sid_t  super_id;
    vid_t  max_vcount;
    T* kv;

    disk_kvT_t<T>* dvt;
    vid_t dvt_count;
    vid_t dvt_max_count;

    int  vtf;

 public:
    inline onekv_t() {
        super_id = 0;
        max_vcount = 0;
        kv = 0;
        
        dvt_count = 0;
        dvt_max_count = (1L << 9);
        if (posix_memalign((void**) &dvt, 2097152, 
                           dvt_max_count*sizeof(disk_kvT_t<T>*))) {
            perror("posix memalign vertex log");    
        }
        vtf = -1;
    }

    void setup(tid_t tid);

    inline T* get_kv() { return kv; }
    inline tid_t get_tid() { return TO_TID(super_id);}
    inline vid_t get_vcount() { return TO_VID(super_id); }
    
    inline void set_value(vid_t vert1_id, T dst) {
        //set_value1(kv, vert1_id, dst);
        kv[vert1_id] = dst;
        dvt[dvt_count].vid = vert1_id;
        dvt[dvt_count].dst = dst; 
        ++dvt_count;
    }
    
    inline void del_value(vid_t vert1_id, T dst) {
        //set_value1(kv, vert1_id, dst);
        kv[vert1_id] = dst;
        dvt[dvt_count].vid = vert1_id;
        dvt[dvt_count].dst = dst; 
        ++dvt_count;
    }
    
    void persist_kvlog();
    void read_kv(); 
    void file_open(const string& filename, bool trunc);
};

typedef onekv_t<sid_t> skv_t; 
typedef onekv_t<lite_edge_t> lite_skv_t;

#define ALIGN_MASK 0xFFFFFFFFFFFE00
#define TO_RESIDUE(x) (x & 0x1FF)
#define UPPER_ALIGN(x) (((x) + 511) & ALIGN_MASK)
#define LOWER_ALIGN(x) ((x) & ALIGN_MASK)

#define IO_THDS 1
#define AIO_MAXIO 256
#define BUF_SIZE  (1L<< 25L)

class meta_t {
    public:
    vid_t vid;
    index_t offset;
};

class segment {
  public:
      char* buf;
      meta_t* meta;
      int     meta_count;
      int     ctx_count;
      io_context_t  ctx;
      struct  io_event* events;
      struct  iocb** cb_list;
      int     etf;
      int     busy;
};

typedef struct __aio_meta {
    struct io_event* events;
    struct iocb** cb_list;
    io_context_t  ctx;
    int busy;
} aio_meta_t;

class io_driver {
public:
    size_t seq_read_aio(segment* seg, ext_vunit_t* ext_vunits);
    size_t read_random_aio(segment* seg);
    int wait_aio_completion(segment* seg);
    template <class T>
    int prep_random_read_aio(vid_t& last_read, size_t to_read, uint8_t* control_read, 
                             meta_t* meta, ext_vunit_t* ext_vunit, 
                             int& iteration_done,  size_t& start_address);

    template <class T>
    int prep_seq_read_aio(vid_t& last_read, vid_t v_count, size_t to_read,
                          segment* seg, ext_vunit_t* ext_vunit, vid_t v_count1, vid_t v_count2);
private:
    aio_meta_t* aio_meta;

public:
    io_driver();
};

template<class T>
int io_driver::prep_seq_read_aio(vid_t& last_read, vid_t v_count, size_t to_read,
                             segment* seg, ext_vunit_t* ext_vunit, vid_t v_count1, vid_t v_count2) 
{
    //index_t disk_offset;
    //index_t sz_to_read = BUF_SIZE;
    meta_t* meta = seg->meta;
    int k = 0;
    
    index_t local_size = 0;
    index_t total_count = 0;
    index_t offset;
    index_t total_size = 0;

    for (vid_t vid = last_read; vid < v_count; ++vid) {
        total_count = ext_vunit[vid].count + ext_vunit[vid].del_count;
        if (total_count == 0) continue;
        
        offset = ext_vunit[vid].offset;
        if (k == 0) {
            total_size = TO_RESIDUE(offset);
            //cout << "Offset 1 = " << offset - total_size << endl;
        }

        local_size = total_count*sizeof(T) + sizeof(durable_adjlist_t<T>);

        if (total_size + local_size > to_read) {
            seg->meta_count = k;
            last_read = vid;
            //last_read = seg->meta[k - 1].vid;
            seg->ctx_count = 1;
            //disk_offset =  ext_vunit[seg->meta[0].vid].offset - (seg->meta[0].offset);
            //io_prep_pread(seg->cb_list[0], seg->etf, seg->buf, sz_to_read, disk_offset);
            return k;
        }

        meta[k].vid = vid;
        meta[k].offset = total_size;
        total_size += local_size;
        ++k;
    }
    
    seg->meta_count = k;
    seg->ctx_count = 1;
    last_read = v_count;
    //disk_offset =  ext_vunit[seg->meta[0].vid].offset - (seg->meta[0].offset);
    //io_prep_pread(seg->cb_list[0], seg->etf, seg->buf, sz_to_read, disk_offset);
    return k;
}
