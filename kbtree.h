#pragma once

/*
 *  * C++ Program to Implement B-Tree
 *
 */

#include "type.h"

#define kinner_keys 31
#define kinner_values 31
#define kleaf_keys  31
#define kinline_keys 2 


typedef struct __inserction_info_t {
	key_t key;
	int i;
	void* inner_node;
} inserction_info_t;

typedef struct __traverse_info_t {
	key_t key;
	int i;
	void* inner_node;
} traverse_info;

typedef struct __split_info_t {
	key_t key;
	void* value;
}split_info_t;

//It seems that order-32/order-64 B-tree is faster than other configuration.
// due to locality (L1 and prefetching).

/**************************/
//Only Key B-Tree

//768 bytes.. 128 byte for key
class kinner_node_t {
public:
	uint8_t		count; // 1 bytes. 5 bits would be enough
	uint8_t		level; //1 byte
    uint16_t    unused;  // 2 Byte
    key_t       keys[31]; // 124 Bytes
	kinner_node_t* next;
    void*		values[31]; // 256 Byte
};

//128 bytes
class kleaf_node_t {
public:
	uint8_t		count;//One byte. 5 bit would be enough
	uint8_t		sorted;//one bit will be sufficient
	uint16_t	unused;//2 bytes
    key_t		keys[31]; //62 might be better
};

class kbtree_t {
public:
	degree_t degree;
	int32_t unused;
	union{
			kinner_node_t* inner_node;//the root node.
			//First leaf node, so that all leaf nodes could be traversed easily.
			kleaf_node_t* leaf_node; 
			key_t inplace_keys[2];
	} btree;
public:
    inline void init() {}
    status_t search(key_t key); 
    status_t insert(key_t key);
    status_t initial_insert(key_t key) {return 0;};
	static int intersection(kbtree_t* btree1, kbtree_t* btree2);

    inline status_t
    remove(key_t key)
    { return 0;}
    
    status_t initial_setup(degree_t degree); 

private:	
	status_t insert_inplace(key_t key);
	status_t split_inplace(key_t key); 
    status_t split_leaf(kleaf_node_t* leaf_node1, key_t key, split_info_t* split_info);
    status_t split_innernode(kinner_node_t* leaf_node1, int i, split_info_t* split_info);
    status_t insert_in_leaf(kleaf_node_t* leaf_node1, key_t key);
	status_t insert_traverse(kinner_node_t* root, key_t key);

	//Insertion related functions
private:
	int intersection00(kbtree_t* btree2);
	int intersection01(kbtree_t* btree2);
	int intersection11(kbtree_t* btree2);
	int intersection02(kbtree_t* btree2);
	int intersection12(kbtree_t* btree2);
	int intersection22(kbtree_t* btree2);
	static
	int intersection_leaf_inner(degree_t count1, key_t* keys1, 
								kbtree_t* btree2);
	static
	int intersection_leaf_leaf(degree_t count1, degree_t count2, 
									 key_t* keys1, key_t* keys2);

public: 
	inline void
	deep_copy(key_t key, value_t value) {
		degree = 1;
		btree.inplace_keys[0] = value;
		unused = key;
	}
	inline void
	shallow_copy(key_t key, kbtree_t* value) {
		degree = value->degree;
		unused = key;
		btree.leaf_node = value->btree.leaf_node;
	}
    //traverse
};

//search result, only value tree;
typedef kbtree_t res_t; 


