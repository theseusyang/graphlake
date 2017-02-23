#pragma once

#include <string>
#include "type.h"


using std::string;

typedef int32_t vertex_t;
typedef int64_t index_t;
typedef float rank_t;


typedef struct __csr_t {
	index_t* beg_pos;
	vertex_t* adj_list;
	vertex_t vert_count;
} csr_t;


class ugraph_t {

private: 
    int csr_from_file(string csrfile, vertex_t vert_count);

public:	
	//void pagerank(int iteration_count);
	//void pagerank_async(int iteration_count);
	void bfs(vertex_t root);
	
    void init(int argc, char* argv[]);

private:    
    csr_t data;
};
