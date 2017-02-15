#pragma once

#include <string>
#include "kbtree.h"

using std::string;


typedef int32_t vertex_t;
typedef int64_t index_t;
typedef float rank_t;

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


class ugraph_t {
public:
	void csr_from_file(string csrfile, vertex_t vert_count, csr_t *data);
	void init_from_csr(csr_t* data, int sorted);
	void init_from_csr2(csr_t* data, int sorted);
	void init(int argc, char* argv[]);

public:	
	void pagerank(int iteration_count);
	void bfs(vertex_t root);
	index_t tc();

private:
	index_t intersection(vertex_t v1, vertex_t v2);	
	ucsr_t udata;
};
