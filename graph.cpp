#include <omp.h>
#include <algorithm>
#include "graph.h"

using std::sort;

//It will not do a deep copy, memory will be used.
void
ugraph_t::init_from_csr(csr_t* data, int sorted)
{
	vertex_t		vert_count = data.vert_count;
	adj_list_t*		adj_list = (adj_list_t*)malloc(sizeof(adj_list_t)*vert_count);
	
	udata.vert_count	= vert_count;
	udata.adj_list		= adj_list;

	#pragma omp parallel
	{
	vertex_t degree = 0;
	int leaf_count = 0;
	vertex_t* l_adj_list = 0;
	#pragma omp for
	for (int vertex_t i = 0; i < vert_count; ++i) {
		degree = data.beg_pos[i + 1] - beg_pos[i];
		l_adj_list = data.adj_list + beg_pos[i];
		if (!sorted) sort(l_adj_list, l_adj_list + degree);
		if (degree <= kinline_keys) {
			for (int j = 0; j < degree; ++j) {
				adj_list[i].btree.inplace_keys[j] = l_adj_list[j];
			}
		} else if (degree <= kleaf_keys) {
			adj_list[i].btree.leaf_node = l_adj_list;
		} else {
			leaf_count = degree/kleaf_keys; + (0 != degree % kleaf_keys);
			level1_count = leaf_count/kinner_values + (0 != leaf_count/kinner_values);
			kleaf_node_t* leaf_node = l_adj_list;
			kinner_node_t* inner_node = (kinner_node_t*)malloc(sizeof(kinner_node_t));
			udata.btree.inner_node = inner_node;
			kinner_node_t* prev = inner_node;
			for (int j = 0; j < level1_count; ++j) {
				for (int k = 0; k < leaf_count; ++k) {
					inner_node[k] = leaf_node;
					leaf_node += kleaf_keys;
				}
				prev = inner_node;
				inner_node = (kinner_node_t*)malloc(sizeof(kinner_node_t));
				prev->next = inner_node;
			}
			//delete last allocation and the link
			free(inner_node);
			prev->next = 0;
		}
	}
	}
}


void
ugraph_t::pagerank(int iteration_count)
{
	vertex_t	vert_count = udata.vert_count;
	vertex_t	degree	   = 0;
	adj_list_t  adj_list   = 0;
	rank_t		rank	   = 0.0;
	rank_t*		pr		   = (rank_t*)malloc(sizeof(rank_t)*vert_count);
	rank_t*		inv_degree = (rank_t*)malloc(sizeof(rank_t)*vert_count);
	
	for (vertex_t v = 0; v < udata.vert_count; ++v) {
		if (udata.adj_list[v].degree != 0) {
			inv_degree = 1.0/udata.adj_list[v].degree;
		}
	}

	kinner_node_t*	inner_node = 0;
	for (int iter_count = 0; iter_count < iteration_count) {
		for (vertex_t v = 0; v < udata.vert_count; ++v) {
			adj_list = udata.adj_list[v];
			degree = adj_list.degree;
			inner_node = adj_list.btree.inner_node;
			while (inner_node) {
				for (int i = 0; i < inner_node->count; ++i) {
					leaf_node = inner_node->values[i];//XXX
					for (int j = 0; j < leaf_node->count; ++j) {
						rank += pr[leaf_node->keys[i]];
					}
				}
			}
			if (iter_count != iteration_count - 1) {
				rank = (0.15 + 0.85*rank)*inv_degree[v];
			} else {
				rank = (0.15 + 0.85*rank);
			}
			rank[v] = rank;//XXX
		}
	}
}
