#ifndef __BTREE_H_
#define __BTREE_H_

/*
 *  * C++ Program to Implement B-Tree
 *
 */

#include "type.h"


#define inner_keys 31
#define inner_values 32
#define leaf_keys  28
#define inline_keys 1

#define kinplace_keys 4
#define kinner_keys 31
#define kinner_values 32
#define kleaf_keys  30

#define success 0
#define keyExist 1 
#define keyvalueExist 2
#define splitLeaf	3


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
	uint8_t		level; //1 byte
	uint8_t		count; // 1 bytes. 5 bits would be enough
    uint16_t    unused;  // 2 Byte
    key_t       keys[31]; // 124 Bytes
    void*		values[32]; // 256 Byte
};

//128 bytes
class kleaf_node_t {
public:
	uint8_t		count;//One byte. 5 bit would be enough
	uint8_t		sorted;//one bit will be sufficient
	uint16_t	unused;//2 bytes
    key_t		keys[29]; //62 might be better
    kleaf_node_t* next;
};

class kbtree_t {
public:
	degree_t degree;
	int32_t unused;
	union{
		struct {
			kinner_node_t* inner_node;//the root node.
			
			//First leaf node, so that all leaf nodes could be traversed easily.
			kleaf_node_t* leaf_node; 
		} btree;
		key_t inplace_keys[4];
	};
public:
    inline void init() {}
    int search(key_t key); 
    status_t insert(key_t key);
    status_t initial_insert(key_t key) {return 0;};

    inline status_t
    remove(key_t key)
    { return 0;}
    
    status_t initial_setup(degree_t degree); 

private:	
	void insert_inplace(key_t key);
	status_t split_inplace(key_t key); 
    status_t split_leaf(kleaf_node_t* leaf_node1, key_t key, split_info_t* split_info);
    status_t split_innernode(kinner_node_t* leaf_node1, int i, split_info_t* split_info);
    void insert_in_leaf(kleaf_node_t* leaf_node1, key_t key);
	status_t insert_traverse(kinner_node_t* root, key_t key);

    //traverse
};

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


#endif
