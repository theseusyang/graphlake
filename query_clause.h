#pragma once

#include "type.h"
#include "query_node.h"
#include "bitmap.h"

typedef Bitmap bitset_t;

//one type's result set
typedef struct __result_set_t {
    //few MSB bits type
    //rest bits = frontiers count in frontiers, words count in status array
    sid_t scount;

    //frontier count for status array
    vid_t count2;
    union {
        uint64_t* status_array;
        vid_t*    frontiers;
    };

 public:
    inline __result_set_t() {
        scount = 0;
        count2 = 0;
        status_array = 0;
    }

    inline vid_t get_vcount() {return TO_VID(scount);}
    inline tid_t get_tid() {return TO_TID(scount);}
    
    inline vid_t add_frontier(vid_t vid) {
        status_array[word_offset(vid)] |= ((uint64_t) 1l << bit_offset(vid));
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

} rset_t;

class srset_t {
 public:
    sflag_t  flag;

    //Total result set count and total frontiers count
    uint64_t ccount;
   
    //array of result sets
    rset_t*  rset; 

 public:
    inline srset_t() {
        flag = 0;
        ccount = 0;
        rset = 0;
    }

    inline vid_t get_status(sid_t sid) {
        vid_t vert_id = TO_VID(sid);
        tid_t type_id = TO_TID(sid) + 1;
        sflag_t flag_mask = flag & ( (1L << type_id) - 1);
        tid_t index = __builtin_popcountll(flag_mask) - 1;
        return rset[index].get_status(vert_id);
    } 
    
    inline vid_t add_frontier(vid_t sid) {
        vid_t vert_id = TO_VID(sid);
        tid_t type_id = TO_TID(sid) + 1;
        sflag_t flag_mask = flag & ((1L << type_id) - 1);
        tid_t index = __builtin_popcountll(flag_mask) - 1;
        return rset[index].add_frontier(vert_id);
    }
    
    inline tid_t setup(sflag_t sflag) {
        sid_t flag_count = __builtin_popcountll(sflag);
        ccount     |= TO_SUPER(flag_count);
        rset        = new rset_t [flag_count];
        flag        = sflag;
        return flag_count;
    }

    tid_t full_setup(sflag_t sflag);

    inline tid_t get_rset_count() {return TO_TID(ccount);}
    inline tid_t get_total_vcount() {return TO_VID(ccount);}
};

class query_whereclause : public query_node
{
	public:
	status_t	execute();

	inline virtual 
	void to_string()
	{
		cout << "WHERE (";
		query_node* node = get_child();
		if (node) {
			node->to_string();
		}
		node = get_sibling();
		while (node) {
			node->to_string();
			node = node->get_sibling();
		}
		cout << ")" << endl;
	}
};

class query_clause
{
private:
	query_whereclause* where_clause;
    
    //result set for each variables
    srset_t* srset;
    //query variable count (in where clause)
    int      qid_count; 

	//More coming soon

public:
	inline void print_where() {where_clause->to_string();}

    status_t execute();
    void print_result();
    
    inline void add_whereclause(query_whereclause* where) {
        where_clause = where;
    };

    inline void setup_qid(qid_t qid) {
        qid_count = qid;
        srset = new srset_t [qid_count];
    }
    inline srset_t* get_srset(qid_t qid) {
        assert(qid < qid_count);
        return srset + qid;
    }
};
