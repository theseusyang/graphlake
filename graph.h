#pragma once

#include <string>
#include "type.h"


using std::string;

#define NUM_THDS 24
#define kinline_keys 2
#define max_kleaf_keys 1024
#define kleaf_keys 256

typedef int32_t vertex_t;
typedef int64_t index_t;
typedef float rank_t;


/************** Only Key B-Tree ************/

typedef vertex_t kleaf_node_t;

typedef struct __kcv_t {
    key_t key;
    uint16_t count;
    uint16_t unused;
    kleaf_node_t* value;
}kcv_t;
                

typedef kcv_t kinner_node_t;

class kbtree_t {
public:
	degree_t degree; //Total vertex count
	int32_t leaf_count;// total number of leaves.
	union{
			kinner_node_t* inner_node;//the root node.
			//First leaf node, so that all leaf nodes could be traversed easily.
			kleaf_node_t* leaf_node; 
			key_t inplace_keys[2];
	} btree;
};

typedef struct __csr_t {
	index_t* beg_pos;
	vertex_t* adj_list;
	vertex_t vert_count;
} csr_t;


typedef kbtree_t adj_list_t;

typedef struct __ucsr_t {
	adj_list_t* adj_list;
	vertex_t vert_count;
} ucsr_t;

typedef struct __mem_info_t {
    kinner_node_t* inner_node_list;
    kleaf_node_t* leaf_node_list;
    index_t inner_count;
    index_t leaf_count;
    index_t unused[4];
} mem_info_t;

class ugraph_t {

private: 
    vertex_t read_csr_adj(int f, vertex_t v, index_t* beg_pos, vertex_t* buf); 
    index_t* read_csr_begpos(string csrfile, vertex_t vert_count);
    void init_from_csr(string csrfile, vertex_t vert_count, int sorted);

public:	
	void pagerank(int iteration_count);
	//void pagerank_async(int iteration_count);
	void bfs(vertex_t root);
	
    void init(int argc, char* argv[]);

private:
    kleaf_node_t* alloc_leaf(index_t count);
    kinner_node_t* alloc_inner(index_t count);

private:    
    ucsr_t udata;
    mem_info_t mem_info[NUM_THDS];
};
