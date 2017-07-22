#pragma once

#include "type.h"
#include "query_node.h"

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

    int select_qids;
	//More coming soon

public:
    inline query_clause() {
        where_clause = 0;
        srset = 0;
        qid_count = 0;
        select_qids = 0;
    }

	inline void print_where() {where_clause->to_string();}

    status_t execute();
    void print_result();
    
    inline void 
    add_whereclause(query_whereclause* where) {
        where_clause = where;
    };

    inline void 
    add_selectclause(select_info_t* info, int a_select_count, int a_select_qids) {
        select_qids = a_select_qids;
    }

    inline void setup_qid(qid_t qid, qid_t a_select_qids) {
        select_qids = a_select_qids;
        qid_count = qid;
        srset = new srset_t [qid_count];
    }
    inline srset_t* get_srset(qid_t qid) {
        assert(qid < qid_count);
        return srset + qid;
    }
};
