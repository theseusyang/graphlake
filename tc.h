#pragma once

#include <string>
#include "kbtree.h"

using std::string;

#define NUM_THDS 24

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

class tc_t {

public:
    tc_t();
    index_t tc();
    init(int argc, argv);

private:
    index_t intersection(vertex_t v1, vertex_t v2);
    void init_from_csr2(csr_t* data, int sorted);
    
private:    
    ucsr_t udata;
    

};
