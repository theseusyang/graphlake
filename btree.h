#pragma once

/*
 *  * C++ Program to Implement B-Tree
 *
 */

#include "type.h"
#include "kbtree.h"

#define inner_keys 31
#define inner_values 32
#define leaf_keys  28
#define inline_keys 1

//It seems that order-32/order-64 B-tree is faster than other configuration.
// due to locality (L1 and prefetching).

/**************************************/
//B-Tree with KV
//768 bytes.. 128 byte for key
class inner_node_t {
public:
    int8_t      count;
	int8_t		level;
	int16_t		unused1;
	int32_t		unused2;
    key_t       keys[30]; 
	inner_node_t* next;
    void*		values[31];
};

//128 bytes
//bits in key[MSB] has special meaning
class leaf_node_t {
public:
	int8_t		count;//5 bits needed
	int8_t		sorted;//one bit needed
	int16_t		unused;
	flag_t		flag; //one bit for each keys
    key_t       keys[31]; //60 might be better
	value_t		values[31];//will contain value or an index
};

class btree_t {
    private:
		//number of unique keys in the b-tree
		degree_t degree;

		//array index in values
		//if degree is just one and value_count is one as well, means
		// the pair does not contain value. values contain the value. 
		int32_t value_count;

		union {
			inner_node_t* inner_node;//the root node.
			leaf_node_t*  leaf_node;
			pair_t		  pair;
		};
		kbtree_t** values;

public:
    inline void init() {}

    inline value_t 
    search(key_t key) {return 0;}

    status_t insert(key_t key, value_t value);
    
    inline status_t
    remove(key_t key, value_t value)
    { return 0;}

    
    inline status_t 
    initial_setup(degree_t degree) 
    {return 0;};
    //split
    //traverse

private:

	status_t insert_traverse(inner_node_t* root, key_t key, value_t value);
	status_t insert_in_leaf1(leaf_node_t* leaf_node1, key_t key, value_t value);
	status_t insert_in_leaf2(leaf_node_t* leaf_node1, key_t key, value_t value, split_info_t* split_info);
	status_t insert_inplace2(key_t key, value_t value);
	status_t insert_inplace1(key_t key, value_t value);

	status_t split_leaf(leaf_node_t* leaf_node1, key_t key, value_t value, int i, split_info_t* split_info);
	status_t split_innernode(inner_node_t* inner_node1, int i, split_info_t* split_info);
};
