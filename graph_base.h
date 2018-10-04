#pragma once
#include <omp.h>
#include <iostream>
#include <libaio.h>
#include <sys/mman.h>
#include <asm/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>
#include <stdio.h>
#include <errno.h>
#include "type.h"

using std::cout;
using std::endl;
using std::max;

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



////
inline void set_value1(sid_t* kv, vid_t vid, sid_t value) {
    kv[vid] = value;
}

inline void set_value1(lite_edge_t* kv, vid_t vid, sid_t value, univ_t univ) {
    kv[vid].first = value;
    kv[vid].second = univ;
}

inline void* alloc_huge(index_t size)
{   
    //void* buf = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0);
    //if (buf== MAP_FAILED) {
    //    cout << "huge page failed" << endl;
    //}
    //return buf;
    
    return MAP_FAILED;
}

//One vertex's neighbor information
template <class T>
class vert_table_t {
 public:
    //nebr list of one vertex. First member is a spl member
    //count, flag for snapshot, XXX: smart pointer count
    snapT_t<T>*   snap_blob;

	vunit_t<T>*   v_unit;

 public:   
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
        
        index_t snap_count = 2;
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
class thd_mem_t {
	public:
    
    vunit_t<T>* vunit_beg;
    snapT_t<T>* dlog_beg;
    char*       adjlog_beg;
	
    index_t    	delta_size1;
	uint32_t    vunit_count;
	uint32_t    dsnap_count;
	index_t     degree_count;
	index_t    	delta_size;
    
    char*       adjlog_beg1;

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
	
	//Thread local memory data structures
	thd_mem_t<T>* thd_mem;

#ifdef BULK
	//---------Global memory data structures
public:
    nebrcount_t*   nebr_count;//Only being used in BULK, remove it in future
private:
    //delta adj list
    char*      adjlog_beg;  //memory log pointer
    index_t    adjlog_count;//size of memory log
    index_t    adjlog_head; // current log write position
    index_t    adjlog_tail; //current log cleaning position

    //degree array related log, in-memory, fixed size logs
	//indirection will help better cleaning.
    snapT_t<T>* dlog_beg;  //memory log pointer
	index_t*    dlog_ind;  // The indirection table
    index_t     dlog_count;//size of memory log
    index_t     dlog_head; // current log write position
    index_t     dlog_tail; //current log cleaning position

	//v_unit log, in-memory, fixed size log
	//indirection will help better cleaning
	vunit_t<T>* vunit_beg;
    index_t     vunit_head;
	index_t     vunit_count;
	index_t     vunit_tail;
	//-----------
#endif

    //vertex table file related log
    write_seg_t  write_seg[3];
    vid_t    dvt_max_count;
    //durable adj list, for writing to disk
    index_t    log_tail; //current log cleaning position
    index_t    log_count;//size of memory log

    int      vtf;   //vertex table file
    FILE*    stf;   //snapshot table file

    string   file;
public:
    int    etf;   //edge table file

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
        max_vcount = 0;

#ifdef BULK
        nebr_count = 0;
	    vunit_beg	= 0;
		vunit_count = 0;
		vunit_head  = 0;
		vunit_tail  = 0;

        adjlog_count = 0;
        adjlog_head  = 0;
        adjlog_tail = 0;

        dlog_count = 0;
        dlog_head = 0;
        dlog_tail = 0;
       
        log_count = 0;
        dvt_max_count = 0;
		write_seg[0].reset();
		write_seg[1].reset();
		write_seg[2].reset();
#endif

        vtf = -1;
        etf = -1;
        stf = 0;
    }
    
    inline vid_t get_degree(vid_t vid) {
        return beg_pos[vid].get_nebrcount();
    }
    
    degree_t get_nebrs(vid_t vid, T* ptr);
    degree_t get_wnebrs(vid_t vid, T* ptr, degree_t start, degree_t count);
    void setup(tid_t tid);

    //void setup_adjlist(vid_t vid_start, vid_t vid_end);
    void setup_adjlist_noatomic(vid_t vid_start, vid_t vid_end);

	#ifdef BULK
    void setup_adjlist();
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
    inline void reset_count(vid_t vid) {
        nebr_count[vid].add_count = 0;
        nebr_count[vid].del_count = 0;
    }
	#else
	void increment_count_noatomic(vid_t vid);
    void decrement_count_noatomic(vid_t vid);
	#endif


    inline void add_nebr(vid_t vid, T sid) {
        if (IS_DEL(get_sid(sid))) { 
            return del_nebr(vid, sid);
        }
        beg_pos[vid].v_unit->adj_list->add_nebr(sid);
    }
    
    inline void add_nebr_noatomic(vid_t vid, T sid) {
		vunit_t<T>* v_unit = beg_pos[vid].v_unit; 
		#ifndef BULK 
		if (v_unit->adj_list == 0 || 
			v_unit->adj_list->get_nebrcount() >= v_unit->max_size) {
			
			delta_adjlist_t<T>* adj_list = 0;
			snapT_t<T>* curr = beg_pos[vid].get_snapblob();
			degree_t new_count = curr->degree + curr->del_count;
            degree_t max_count = new_count;
		    if (curr->prev) {
				max_count -= curr->prev->degree + curr->prev->del_count; 
			}
            
            if (new_count >= HUB_COUNT || max_count >= 256) {
                max_count = TO_MAXCOUNT1(max_count);
			    adj_list = new_delta_adjlist_local1(max_count);
            } else {
			    max_count = TO_MAXCOUNT(max_count);
			    adj_list = new_delta_adjlist_local(max_count);
            }
			adj_list->set_nebrcount(0);
			adj_list->add_next(0);
			v_unit->max_size = max_count;
			if (v_unit->adj_list) {
				v_unit->adj_list->add_next(adj_list);
				v_unit->adj_list = adj_list;
			} else {
				v_unit->delta_adjlist = adj_list;
				v_unit->adj_list = adj_list;
			}
		}
		#endif
        if (IS_DEL(get_sid(sid))) { 
            return del_nebr_noatomic(vid, sid);
        }
        v_unit->adj_list->add_nebr_noatomic(sid);
    }
    
    inline void add_nebr_bulk(vid_t vid, T* adj_list1, degree_t count) {
        beg_pos[vid].v_unit->adj_list->add_nebr_bulk(adj_list1, count);
    }

    degree_t find_nebr(vid_t vid, sid_t sid); 
    
#ifdef BULK    
    // -------------------- global data structure ------------------    
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
	
    //Used during read from disk
	inline vunit_t<T>* new_vunit() {
		index_t index = __sync_fetch_and_add(&vunit_head, 1L);
        assert(index < get_vcount());
		vunit_t<T>* v_unit = vunit_beg + index;
		v_unit->reset();
		return v_unit;
	}	

    inline vunit_t<T>* new_vunit_bulk(vid_t count) {
		index_t index = __sync_fetch_and_add(&vunit_head, count);
		assert(index < get_vcount());
		vunit_t<T>* v_unit = vunit_beg + index;
		return v_unit;
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
#endif

    //------------------------ local allocation-------
	inline vunit_t<T>* new_vunit_local() {
		thd_mem_t<T>* my_thd_mem = thd_mem + omp_get_thread_num();
		if (my_thd_mem->vunit_count == 0) {
		    my_thd_mem->vunit_count = (1L << LOCAL_VUNIT_COUNT);
            my_thd_mem->vunit_beg = (vunit_t<T>*)alloc_huge(my_thd_mem->vunit_count*sizeof(vunit_t<T>));
            if (MAP_FAILED == my_thd_mem->vunit_beg) {
			    my_thd_mem->vunit_beg = (vunit_t<T>*)calloc(sizeof(vunit_t<T>), my_thd_mem->vunit_count);
            }
		}
		my_thd_mem->vunit_count--;
		return my_thd_mem->vunit_beg++;
	}
    
	inline snapT_t<T>* new_snapdegree_local() {
		thd_mem_t<T>* my_thd_mem = thd_mem + omp_get_thread_num();
		if (my_thd_mem->dsnap_count == 0) {
		    my_thd_mem->dsnap_count = (1L << LOCAL_VUNIT_COUNT);
			my_thd_mem->dlog_beg = (snapT_t<T>*)alloc_huge(sizeof(snapT_t<T>)*my_thd_mem->dsnap_count);
            if (MAP_FAILED == my_thd_mem->dlog_beg) {
			    my_thd_mem->dlog_beg = (snapT_t<T>*)calloc(sizeof(snapT_t<T>), 1L<< LOCAL_VUNIT_COUNT);
            }
		}
		my_thd_mem->dsnap_count--;
		return my_thd_mem->dlog_beg++;
	}

	inline delta_adjlist_t<T>* new_delta_adjlist_local(degree_t count) {
		thd_mem_t<T>* my_thd_mem = thd_mem + omp_get_thread_num();
		index_t size = count*sizeof(T) + sizeof(delta_adjlist_t<T>);
		if (size > my_thd_mem->delta_size) {
			my_thd_mem->delta_size = max(1UL << LOCAL_DELTA_SIZE, size);
			my_thd_mem->adjlog_beg = (char*)alloc_huge(my_thd_mem->delta_size);
            if (MAP_FAILED == my_thd_mem->adjlog_beg) {
			    my_thd_mem->adjlog_beg = (char*)malloc(my_thd_mem->delta_size);
            }
		}
		delta_adjlist_t<T>* adj_list = (delta_adjlist_t<T>*)my_thd_mem->adjlog_beg;
		assert(adj_list != 0);
		my_thd_mem->adjlog_beg += size;
		my_thd_mem->delta_size -= size;
		return adj_list;
	}
    
	inline delta_adjlist_t<T>* new_delta_adjlist_local1(degree_t count) {
		thd_mem_t<T>* my_thd_mem = thd_mem + omp_get_thread_num();
		index_t size = count*sizeof(T) + sizeof(delta_adjlist_t<T>);
		if (size > my_thd_mem->delta_size1) {
			my_thd_mem->delta_size1 = max(1UL << 32, size);
			my_thd_mem->adjlog_beg1 = (char*)malloc(my_thd_mem->delta_size1);
		}
		delta_adjlist_t<T>* adj_list = (delta_adjlist_t<T>*)my_thd_mem->adjlog_beg1;
		assert(adj_list != 0);
		my_thd_mem->adjlog_beg1 += size;
		my_thd_mem->delta_size1 -= size;
		return adj_list;
	}
    
    //-----------durability thing------------
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

	inline disk_vtable_t* new_dvt(write_seg_t* seg) {
        //index_t j = __sync_fetch_and_add(&seg->dvt_count, 1L);
        index_t j = seg->dvt_count;
        ++seg->dvt_count;
		//assert();
		return seg->dvt + j;
	}
	//------------------
    
    inline vert_table_t<T>* get_begpos() { return beg_pos;}
    inline vid_t get_vcount() { return TO_VID(super_id);}
    inline tid_t get_tid() { return TO_TID(super_id);}


    void prepare_dvt(write_seg_t* seg, vid_t& last_vid, bool clean = false);
	void adj_prep(write_seg_t* seg);
    void handle_write(bool clean = false);
    
	//void adj_update(write_seg_t* seg);
    //void update_count();
    void read_vtable();
    void file_open(const string& filename, bool trunc);
};

typedef vert_table_t<sid_t> beg_pos_t;
typedef beg_pos_t  lgraph_t;
typedef vert_table_t<lite_edge_t> lite_vtable_t;

typedef onegraph_t<sid_t> sgraph_t;
typedef onegraph_t<lite_edge_t>lite_sgraph_t;

template <class T>
class disk_kvT_t {
    public:
    vid_t    vid;
    T       dst;
};

typedef disk_kvT_t<sid_t> disk_kv_t;
typedef disk_kvT_t<lite_edge_t> disk_kvlite_t;

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
#define AIO_MAXIO 32768
#define IO_MAX    32768
#define AIO_BATCHIO 256
#define BUF_SIZE  (1L<< 29L)

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
    size_t random_read_aio(segment* seg, ext_vunit_t* ext_vunits);
    int wait_aio_completion(segment* seg);
    template <class T>
    int prep_random_read_aio(vid_t& last_read, vid_t v_count, 
                             uint8_t* status, uint8_t level, size_t to_read, 
                             segment* seg, ext_vunit_t* ext_vunit);

    template <class T>
    int prep_seq_read_aio(vid_t& last_read, vid_t v_count, size_t to_read,
                          segment* seg, ext_vunit_t* ext_vunit);
private:
    //aio_meta_t* aio_meta;

public:
    io_driver();
};

template<class T>
int io_driver::prep_seq_read_aio(vid_t& last_read, vid_t v_count, size_t to_read,
                             segment* seg, ext_vunit_t* ext_vunit) 
{
    index_t disk_offset = 0;
    index_t sz_to_read = BUF_SIZE;
    meta_t* meta = seg->meta;
    int k = 0;
	int ctx_count = 0;
	index_t	size = (1<<20);
	index_t local_start = 0;

    
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
			disk_offset = offset - total_size;
            //cout << "Offset 1 = " << offset - total_size << endl;
        }

        local_size = total_count*sizeof(T) + sizeof(durable_adjlist_t<T>);

        if (total_size + local_size > to_read) {
            //disk_offset =  ext_vunit[seg->meta[0].vid].offset - (seg->meta[0].offset);
            //io_prep_pread(seg->cb_list[0], seg->etf, seg->buf, sz_to_read, disk_offset);
			
			sz_to_read = UPPER_ALIGN(total_size);
			ctx_count = (sz_to_read >> 20) + (0 != (sz_to_read & 0xFFFFF));
			for (int i = 0; i < ctx_count; ++i) {
				local_size = UPPER_ALIGN(std::min(size, sz_to_read));

				io_prep_pread(seg->cb_list[i], seg->etf, seg->buf + local_start,
							  local_size, disk_offset + local_start);
				//disk_offset += local_size;
				local_start += local_size; 
				sz_to_read  -= local_size;
			}
            
			seg->ctx_count = ctx_count;
            seg->meta_count = k;
            last_read = vid;
            return k;
        }

        meta[k].vid = vid;
        meta[k].offset = total_size;
        total_size += local_size;
        ++k;
    }
    
    //disk_offset =  ext_vunit[seg->meta[0].vid].offset - (seg->meta[0].offset);
    //io_prep_pread(seg->cb_list[0], seg->etf, seg->buf, sz_to_read, disk_offset);
	sz_to_read = UPPER_ALIGN(total_size);
	ctx_count = (sz_to_read >> 20) + (0 != (sz_to_read & 0xFFFFF));
	for (int i = 0; i < ctx_count; ++i) {
		local_size = UPPER_ALIGN(std::min(size, sz_to_read));
		io_prep_pread(seg->cb_list[i], seg->etf, seg->buf + local_start,
					  local_size, disk_offset + local_start);
		//disk_offset += local_size;
		local_start += local_size; 
		sz_to_read  -= local_size;
	}
    
	seg->ctx_count = ctx_count;
    seg->meta_count = k;
    last_read = v_count;
    return k;
}

template<class T>
int io_driver::prep_random_read_aio(vid_t& last_read, vid_t v_count, 
                             uint8_t* status, uint8_t level, size_t to_read, 
                             segment* seg, ext_vunit_t* ext_vunit)
{
    index_t disk_offset = 0;
    index_t sz_to_read = BUF_SIZE;
    meta_t* meta = seg->meta;
    int k = 0;
    int ctx_count = 0;
    
    index_t total_count = 0;
    index_t offset;
    index_t super_size = 0;
    index_t local_size = 0;
    index_t total_size = 0;
    bool started = false;
	index_t cont = 0;

    for (vid_t vid = last_read; vid < v_count; ++vid) {
        total_count = ext_vunit[vid].count + ext_vunit[vid].del_count;
        if (total_count == 0) continue;
        
        offset = ext_vunit[vid].offset;
		local_size = total_count*sizeof(T) + sizeof(durable_adjlist_t<T>);
        
		if(status[vid] != level) { 
			cont +=  local_size;
			if (cont > 1024) {
				if(started)  {
					started = false;
					sz_to_read = UPPER_ALIGN(total_size);
					io_prep_pread(seg->cb_list[ctx_count], seg->etf, seg->buf + super_size, 
								  sz_to_read, disk_offset);
				
					super_size += sz_to_read;
					total_size = 0;
					++ctx_count;
					cont = 0;
				}
			}
			continue;
        }
		
        if (started == false) {
            started = true;
            total_size = TO_RESIDUE(offset);
            disk_offset = offset - total_size;
			cont = 0;
            //super_size += total_size;
		}

        total_size += cont;
	    cont = 0;	

        if ((super_size + total_size + local_size > to_read)
            || (ctx_count == AIO_MAXIO - 1) ) {
            sz_to_read = UPPER_ALIGN(total_size);
            io_prep_pread(seg->cb_list[ctx_count], seg->etf, seg->buf + super_size, 
                          sz_to_read, disk_offset);
            
            super_size += sz_to_read;
            total_size = 0;
            ++ctx_count;
            seg->ctx_count = ctx_count;
            seg->meta_count = k;
            last_read = vid;
            return k;
        }

        meta[k].vid = vid;
        meta[k].offset = super_size + total_size;
        total_size += local_size;
        ++k;
    }
   
    if (started) { 
        //disk_offset =  ext_vunit[seg->meta[0].vid].offset - (seg->meta[0].offset);
        sz_to_read = UPPER_ALIGN(total_size);
        io_prep_pread(seg->cb_list[ctx_count], seg->etf, seg->buf + super_size, 
                      sz_to_read, disk_offset);
        
        super_size += sz_to_read;
        total_size = 0;
        ++ctx_count;
    }

    seg->ctx_count = ctx_count;
    seg->meta_count = k;
    last_read = v_count;
    return k;

}
