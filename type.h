#pragma once
#include <stdint.h>
#include <limits.h>
#include <string>
#include "bitmap.h"

using std::string;


typedef uint32_t propid_t;
typedef uint64_t vid_t;
typedef uint64_t sid_t;
typedef uint64_t index_t;
typedef uint32_t tid_t;
typedef uint64_t sflag_t;
typedef uint16_t qid_t;
//typedef int32_t status_t;

#define VBIT 40
#define VMASK 0xffffffffff


#define TO_TID(sid) (sid >> VBIT)
#define TO_VID(sid)  (sid & VMASK)
#define TO_SUPER(tid) (((sid_t)(tid)) << VBIT)

#define TID_TO_SFLAG(tid) (1L << tid)
#define WORD_COUNT(count) ((count + 63) >> 6)

#define INVALID_PID 0xFFFFFFFF
#define INVALID_SID 0xFFFFFFFFFFFFFFFF

#define NO_QID 0xFFFF

class pinfo_t;


enum direction_t {
    eout = 0, 
    ein
};

enum status_t {
    eOK = 0,
    eInvalidPID,
    eInvalidVID,
    eQueryFail,
    eUnknown        
};

typedef union __univeral_type {
    char*    value_charp;
    uint64_t value_64b;
    uint8_t  value_8b;
    uint16_t value16b;
    tid_t    value_tid;
    vid_t    value_vid;
    sid_t    value_sid;
}univ_t;

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

enum queryplan_t {
    eOutward = 0,
    eInward,
    eDefault,
};

typedef struct __filter_info_t {
    pinfo_t* rgraph;
    univ_t   value;
    filter_fn_t filter_fn;
} filter_info_t;

typedef struct __select_info_t {
    pinfo_t* rgraph;
    string name; 
} select_info_t;



class edge_t {
public:
    vid_t src_id;
    vid_t dst_id;
};

//One vertex's neighbor information
class beg_pos_t {
 public:
    //count in adj list
    index_t  count;

    //nebr list of one vertex
    sid_t*   adj_list;

 public:
    inline beg_pos_t() {
        count = 0;
        adj_list = 0;
    }
};

//one type's key-value store
class skv_t {
 public:
    sid_t super_id;
    sid_t* kv;
};

//one type's graph
class sgraph_t {
public:
    //type id and count together
    sid_t      super_id;

    //array of adj list of vertices
    beg_pos_t* beg_pos;
};

#define eStatusarray 0
#define eFrontiers  1
#define eAdjlist    2

//one type's result set
class rset_t {
    public:
    //few MSB bits = type
    //rest bits = frontiers count in frontiers, words count in status array
    sid_t scount;

    //few MSB bits: identify union
    //rest bits = frontier count for status array. XXX not correct
	//          = or maximum allocated memory count;
    sid_t count2;

    union {
        uint64_t* status_array;
        sid_t*    frontiers;
        beg_pos_t* adjlist;
    };

    public:
    inline rset_t() {
        scount = 0;
        count2 = 0;
        status_array = 0;
    }

    inline vid_t get_vcount() {return TO_VID(scount);}
    inline tid_t get_tid() {return TO_TID(scount);}
    
    inline vid_t set_status(vid_t vid) {
        status_array[word_offset(vid)] |= ((uint64_t) 1l << bit_offset(vid));
        return 0;
    }
	inline vid_t add_frontier(vid_t vid) {
		vid_t index = TO_VID(scount);
		frontiers[index] = vid;
		++scount;
		return 0;
	}
	
    inline vid_t add_adjlist_ro(vid_t index, beg_pos_t* begpos) {
		adjlist[index].count = begpos->count;
		adjlist[index].adj_list = begpos->adj_list;
		return 0;
	}
    
    inline vid_t add_kv(vid_t index, sid_t sid) {
		frontiers[index] = sid;
		return 0;
	}
    
    inline vid_t get_status(vid_t vid) {
        return status_array[word_offset(vid)] & ((uint64_t) 1l << bit_offset(vid));
    }
    
    inline void setup(sid_t super_id) {
        scount  = super_id;
        vid_t w_count = WORD_COUNT(TO_VID(super_id));
        status_array = (uint64_t*) calloc(sizeof(uint64_t*), w_count);
    }

	inline void setup_frontiers(tid_t tid, vid_t max_count) {
		scount = TO_SUPER(tid);
		count2 = TO_SUPER(1) + max_count;
		frontiers = (sid_t*)calloc(sizeof(sid_t), max_count);
	}
    
    inline void copy_setup(rset_t* iset, int union_type) {
		assert(eStatusarray == TO_TID(iset->count2));
        scount = iset->scount;
        vid_t v_count = TO_VID(scount);
		count2 = TO_SUPER(union_type) + v_count;
		switch(union_type) {
        case eFrontiers:
            adjlist = (beg_pos_t*)calloc(sizeof(beg_pos_t), v_count);
            break;
        case eAdjlist:
            adjlist = (beg_pos_t*)calloc(sizeof(beg_pos_t), v_count);
            break;
        default:
        assert(0);
        }
    }

};

class srset_t {
 public:
    sflag_t  flag;

    //Total result set count and total frontiers count
    //few MSB bits = index into rset
    //other bits = total frontier count. XXX not correct
    uint64_t ccount;
   
    //array of result sets
    rset_t*  rset; 

 public:
    inline srset_t() {
        flag = 0;
        ccount = 0;
        rset = 0;
    }

	inline tid_t get_sindex(sid_t sid)
	{
		tid_t type_id = TO_TID(sid) + 1;
		sflag_t flag_mask = flag & ((1L << type_id) - 1);
		tid_t index = __builtin_popcountll(flag_mask) - 1;
		return index;
	}

    inline vid_t get_status(sid_t sid) {
		tid_t index = get_sindex(sid);
		vid_t vert_id = TO_VID(sid);
        return rset[index].get_status(vert_id);
    } 
    
    inline vid_t add_frontier(sid_t sid) {
		tid_t index = get_sindex(sid);
		vid_t vert_id = TO_VID(sid);
        return rset[index].add_frontier(vert_id);
    }
    
    inline vid_t set_status(sid_t sid) {
		tid_t index = get_sindex(sid);
		vid_t vert_id = TO_VID(sid);
        return rset[index].set_status(vert_id);
    }
    
    inline tid_t setup(sflag_t sflag) {
        sid_t flag_count = __builtin_popcountll(sflag);
        ccount     |= TO_SUPER(flag_count);
        rset        = new rset_t [flag_count];
        flag        = sflag;
        return flag_count;
    }
    
    inline tid_t copy_setup(srset_t* iset, int union_type) {
        tid_t flag_count = setup(iset->flag);
        for (tid_t i = 0; i < flag_count; ++i) {
            rset->copy_setup(iset->rset, union_type);
        }
        return flag_count;
    }

    tid_t full_setup(sflag_t sflag);

    inline tid_t get_rset_count() {return TO_TID(ccount);}
    inline tid_t get_total_vcount() {return TO_VID(ccount);}
};


/////// Function//////////////
inline tid_t get_sindex(tid_t tid, sflag_t sflag)
{
    sflag_t flag_mask = sflag & ((1L << (tid +1)) - 1);
    tid_t        pos = __builtin_popcountll(flag_mask) - 1;
    return pos;
}

inline tid_t get_sindex(sid_t sid, sflag_t flag)
{
	tid_t type_id = TO_TID(sid) + 1;
	sflag_t flag_mask = flag & ((1L << type_id) - 1);
	tid_t index = __builtin_popcountll(flag_mask) - 1;
	return index;
}
