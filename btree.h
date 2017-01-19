#ifndef __BTREE_H_
#define __BTREE_H_

/*
 *  * C++ Program to Implement B-Tree
 *
 */

typedef int32_t flag_t;
typedef int32_t key_t;
typedef int32_t value_t;
typedef int32_t status_t;
typedef struct __pair_t {
    key_t key; // predicate
    value_t value; //subject/object
} pair_t;

#define inner_keys_count 31
#define leaf_keys_count  28

//It seems that order-32/order-64 B-tree is faster than other configuration.
// due to locality (L1 and prefetching).

class btree_node_t {
};


//768 bytes.. 128 byte for key
class inner_node_t {
    flag_t      flag;    // 4 Byte
    key_t       key[31]; // 124 Bytes
    btree_node_t* btree_node[32]; // 256 Byte
};

//128 bytes
//bits in key[MSB] has special meaning
class leaf_node_t {
    key_t       key[28]; //60 might be better
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
class kbtree_t {
	private:
        inner_node_t* inner_node;//the root node.
        //First leaf node, so that all leaf nodes could be traversed easily.
        leaf_node_t* next; 
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
