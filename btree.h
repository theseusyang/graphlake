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

#define kinplace_keys 4
#define kinner_keys 31
#define kinner_values 32
#define kleaf_keys  30

typedef struct __split_info_t {
	key_t key;
	void* value;
}split_info_t;

//It seems that order-32/order-64 B-tree is faster than other configuration.
// due to locality (L1 and prefetching).

class btree_node_t {
};


//768 bytes.. 128 byte for key
class inner_node_t {
public:
    flag_t      flag;    // 4 Byte
    key_t       key[31]; // 124 Bytes
    btree_node_t* btree_node[32]; // 256 Byte
};

//128 bytes
//bits in key[MSB] has special meaning
class leaf_node_t {
public:
    key_t       key[28]; //60 might be better
	//XXX
    value_t*     pvalue;//Many keys will have more than one value.
    leaf_node_t* next;
};

class btree_t {
    private:
        inner_node_t* inner_node;//the root node.
        //First leaf node, so that all leaf nodes could be traversed easily.
        leaf_node_t* leaf_node; 

public:
    inline void init() {}

    inline value_t 
    search(key_t key) {return 0;}

    inline status_t
    insert(key_t key, value_t value)
    { return 0;}

    inline status_t 
    insert(pair_t pair)
    { return 0 ; }
    
    inline status_t
    remove(key_t key, value_t value)
    { return 0;}

    inline status_t
    remove(pair_t pair)
    { return 0;}
    
    inline status_t 
    initial_setup(degree_t degree) 
    {return 0;};
    //split
    //traverse
};

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

    inline int 
    search(key_t key) {return 0;}
	
    status_t insert(key_t key);
    status_t initial_insert(key_t key) {return 0;};

    
    inline status_t
    remove(key_t key)
    { return 0;}
    
    status_t initial_setup(degree_t degree); 
    
	void insert_inplace(key_t key);
    status_t split_leaf(kleaf_node_t* leaf_node1, key_t key, split_info_t* split_info);
    status_t split_innernode(kinner_node_t* leaf_node1, int i, split_info_t* split_info);
    void insert_in_leaf(kleaf_node_t* leaf_node1, key_t key);
	status_t insert_traverse(kinner_node_t* root, key_t key);

    //traverse
};

#endif
