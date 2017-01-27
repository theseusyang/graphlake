#pragma once

#include "kbtree.h"

typedef int32_t vertex_t;
typedef int64_t index_t;

typedef __csr_t {
	index_t* beg_pos;
	vertex_t* adj_list;
	vertex_t vert_count;
} csr_t;


typedef kbtree_t adj_list_t;

typedef __ucsr_t {
	adj_list_t* adj_list;
	vertex_t vert_count;
} ucsr_t;


class ugraph_t {
public:
	void init_from_csr(csr_t* data, int sorted);
	void pagerank(int iteration_count);

ucsr_t udata;
}
