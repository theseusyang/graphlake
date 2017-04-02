#ifndef __QUERY_NODE_H_
#define __QUERY_NODE_H_

#include <iostream>
#include <string>
#include <assert.h>
#include "type.h"

using std::cout;
using std::string;
using std::endl;

class query_clause;

inline int is_var(const char* str) {
    assert(0 != str);
    return ('?' == str[0]);
}

class query_node {
public:
	inline query_node() {
		sibling = 0;
		child   = 0;
        q = 0;
	}
    inline void set_queryclause(query_clause* a_q) {
        q = a_q;
    }

    inline query_clause* get_queryclause() {
        return q;
    }

public:
	virtual status_t execute() = 0; 
	//virtual string get_text() = 0;

	virtual inline void  to_string() { };
/*		cout <<  get_text() << "(";
	{
		query_node* node = get_child();
		if (node) {
			node->to_string();
		}
		node = get_sibling();
		while (node) {
			node->to_string();
			node = node->get_sibling();
		}
		cout << ")";
	}
*/
	
	inline query_node* get_child() {return child;}

	inline query_node* get_sibling() {return sibling;}

	inline void add_child(query_node* node)
	{
		if (0 == child) {
			child = node;
			return;
		}
		
		query_node* place = child;
		while(0 != place->sibling) {
			place = place->sibling;
		}
		place->sibling = node;
	}	

	inline void add_sibling(query_node* node)
	{
		if ( 0 == sibling) {
			sibling = node;
			return;
		}
		query_node* place = sibling;
		while(0 != place->sibling) {
			place = place->sibling;
		}
		place->sibling = node;
	}


private:
	query_node* sibling;
	query_node* child;
    query_clause *q;
};
#endif
