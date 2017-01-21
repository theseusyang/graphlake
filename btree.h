#ifndef __BTREE_H_
#define __BTREE_H_

/*
 *  * C++ Program to Implement B-Tree
 *
 */

#include "type.h"

#define inner_keys 31
#define leaf_keys  28

#define kinner_keys 31
#define kleaf_keys  30

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
        leaf_node_t* next; 

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
    initial_setup(int level_count, int leaf_count) 
    {return 0;};
    //split
    //traverse
};

/**************************/
//Only Key B-Tree

//768 bytes.. 128 byte for key
class kinner_node_t {
public:
    flag_t      flag;    // 4 Byte
    key_t       key[31]; // 124 Bytes
    void*		value[32]; // 256 Byte
};

//128 bytes
//bits in key[MSB] has special meaning
class kleaf_node_t {
public:
    key_t		key[30]; //62 might be better
    kleaf_node_t* next;
};

class kbtree_t {
public:
        kinner_node_t* inner_node;//the root node.
        //First leaf node, so that all leaf nodes could be traversed easily.
        kleaf_node_t* next; 
public:
    inline void init() {}

    inline int 
    search(key_t key) {return 0;}

    inline status_t
    insert(key_t key)
    { return 0;}

    
    inline status_t
    remove(key_t key)
    { return 0;}
    
    inline status_t 
    initial_setup(int level_count, int leaf_count) 
    {return 0;};
    //split
    //traverse
};

#endif
