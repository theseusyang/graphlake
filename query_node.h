#ifndef __QUERY_NODE_H_
#define __QUERY_NODE_H_

#include <iostream>
#include <string>

using std::cout;
using std::string;
using std::endl;


typedef int32_t status_t;

//using std::unique_ptr;
typedef int32_t idata;

class query_node {
public:
	inline query_node()
	{
		sibling = 0;
		child   = 0;
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
		query_node* place = child;
		if (0 == place) {
			place = node;
			return;
		}
		while(0 != place->sibling) {
			place = place->sibling;
		}
		place->sibling = node;
	}	

	inline void add_sibling(query_node* node)
	{
		query_node* place = sibling;
		if ( 0 == place) {
			place = node;
			return;
		}
		while(0 != place->sibling) {
			place = place->sibling;
		}
		place->sibling = node;
	}

private:
	query_node* sibling;
	query_node* child;
};
#endif
