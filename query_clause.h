#pragma once

#include "type.h"
#include "query_node.h"
#include "bitmap.h"

typedef Bitmap bitset_t;

enum direction_t {
    eout, 
    ein
};

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

 public:
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
        vid_t v_count = TO_VID(super_id);
        status_array = (uint64_t*) calloc(sizeof(uint64_t*), (v_count >> 8));
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
    
    inline tid_t setup(sflag_t flag) {
        sid_t flag_count = __builtin_popcountll(flag);
        ccount     |= TO_SUPER(flag_count);
        rset        = new rset_t [flag_count];
        flag        = flag;
        return flag_count;
    }

    tid_t full_setup(sflag_t flag);

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
	//More coming soon

public:
	inline void print_where() {where_clause->to_string();}

    status_t execute();
    inline void add_whereclause(query_whereclause* where) {
        where_clause = where;
    };


};
