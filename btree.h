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

//256 bytes
//Some bits in key[0] has special meaning
class leaf_node_t {
    key_t       key[31];
    value_t     value[31];
    leaf_node_t* next;
};

class btree_t {
    private:
        inner_node_t* inner_node;//the root node.
        leaf_node_t* next; //so that all leaf nodes could be traversed easily.

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

    //split
    //traverse

};

btree_node_t * init()
{
    return NULL;
}

void traverse(btree_node_t *p)
{
    return;
}

void sort(int *p, int n)
{
    return ;
}

int split_child(btree_node_t *x, int i)
{
    return 0;
}

void insert(int a)
{
    return ;
}


#endif
