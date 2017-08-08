#pragma once

#include "type.h"
#include "graph_base.h"

class cfinfo_t;

#define eStatusarray 0
#define eFrontiers  1
#define eAdjlist    2
#define eKV         3
#define eLevelarray 4
#define eFloatarray 5
#define eLiteadjlist 6
#define eLiteKV     7

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
        uint64_t*   status_array;
        vid_t*      vlist;
        beg_pos_t*  adjlist;
        sid_t*      kv;
		uint8_t*    level_array;
		float*       float_array;
        lite_vtable_t* lite_adjlist;
        lite_edge_t* lite_kv;
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
    inline lite_vtable_t* get_lite_graph() { return lite_adjlist;}
    inline lite_edge_t*   get_lite_kv() { return lite_kv; }

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

	inline void set_8bitvalue(sid_t vid, uint8_t value) {
		level_array[vid] = value;
	}
	
	inline uint8_t get_8bitvalue(sid_t vid) {
		return level_array[vid];
	}

	inline uint8_t* get_levelarray() {
		return level_array;
	}
	
	inline void set_floatvalue(sid_t vid, float value) {
		float_array[vid] = value;
	}
	
	inline float get_floatvalue(sid_t vid) {
		return float_array[vid];
	}

	inline float* get_floatarray() {
		return float_array;
	}
	
    inline void setup_frontiers(tid_t tid, vid_t max_count) {
		scount = TO_SUPER(tid) + max_count;
		count2 = TO_SUPER(1) + 0;
		vlist = (vid_t*)calloc(sizeof(sid_t), max_count);
	}
	
    inline void add_adjlist_ro(vid_t index, beg_pos_t* begpos) {
        adjlist[index].copy(begpos);
	}
    
    inline void add_adjlist_ro(vid_t index, lite_vtable_t* begpos) {
        lite_adjlist[index].copy(begpos);
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
    void print_lite_adjlist(select_info_t* select_info, qid_t select_count, vid_t pos);
    void print_lite_kv(select_info_t* select_info, qid_t select_count, vid_t pos);
    void print_barray(select_info_t* select_info, qid_t select_count);
    void print_vlist(select_info_t* select_info, qid_t select_count);
    
    void bitwise2vlist();
    
    inline void setup(sid_t super_id, int union_type = eStatusarray) {
        tid_t tid = TO_TID(super_id);
		vid_t vert_count = TO_VID(super_id);
        vid_t w_count = WORD_COUNT(TO_VID(super_id));
        scount  = super_id;

		switch (union_type) {
		case eStatusarray:
            w_count = WORD_COUNT(TO_VID(super_id));
            scount  = TO_SUPER(tid) + w_count;
			count2 = TO_SUPER(eStatusarray);
			status_array = (uint64_t*) calloc(sizeof(uint64_t), w_count);
			break;
		case eLevelarray:
			count2 = TO_SUPER(eLevelarray);
			level_array = (uint8_t*) calloc(sizeof(uint8_t), vert_count);
			break;
		case eFloatarray:
			count2 = TO_SUPER(eLevelarray);
			float_array = (float*) calloc(sizeof(float), vert_count);
			break;
		default:
			assert(0);
			break;

		}
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
    
	inline void set_8bitvalue(sid_t sid, uint8_t value) {
        tid_t index = get_sindex(sid);
        vid_t vert_id = TO_VID(sid);
        rset[index].set_8bitvalue(vert_id, value);
	}

	inline uint8_t get_8bitvalue(sid_t sid) {
        tid_t index = get_sindex(sid);
        vid_t vert_id = TO_VID(sid);
        return rset[index].get_8bitvalue(vert_id);
	}
	
	inline float get_floatvalue(sid_t sid) {
        tid_t index = get_sindex(sid);
        vid_t vert_id = TO_VID(sid);
        return rset[index].get_floatvalue(vert_id);
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
  
    //tid_t full_setup(sflag_t sflag, int union_type = eStatusarray);
    tid_t full_setup(sgraph_t** sgraph, int union_type = eStatusarray);
    tid_t full_setup(lite_sgraph_t** sgraph, int union_type = eStatusarray);
    tid_t full_setup(skv_t** skv, int union_type = eStatusarray);
    tid_t full_setup(lite_skv_t** skv, int union_type = eStatusarray);
    tid_t copy_setup(srset_t* iset, int union_type);
    
    
    //Dont call directly
    tid_t setup(tid_t tid); 

};
