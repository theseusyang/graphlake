#ifndef __QUERY_NODE_H_
#define __QUERY_NODE_H_

#include <memory>

typedef int32_t status_t;

using std::unique_ptr;
typedef int32_t idata;

class query_node {
public:
	inline query_node()
	{
		sibling = 0;
		child   = 0;
	}

public:
	virtual status_t execute()=0; 
	
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
