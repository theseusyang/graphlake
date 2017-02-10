#include <omp.h>
#include <sys/stat.h>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
#include <assert.h>

#include "wtime.h"
#include "graph.h"

using std::cout;
using std::endl;
using std::string;

using std::sort;
using std::min;

ugraph_t* g = 0;


void ugraph_t::csr_from_file(string csrfile, vertex_t vert_count, csr_t* data)
{

	string file = csrfile + ".beg_pos";
    struct stat st_count;
    stat(file.c_str(), &st_count);
    assert(st_count.st_size == vert_count +1);
	
	FILE* f = fopen(file.c_str(),"rb");
    assert(f != 0);
    data->beg_pos = (index_t*) malloc(st_count.st_size);
    assert(data->beg_pos);
    fread(data->beg_pos, sizeof(index_t), vert_count + 1, f);
    fclose(f);

	index_t edge_count = data->beg_pos[vert_count];
	file = csrfile + ".adj";
    struct stat st_edge;
    stat(file.c_str(), &st_edge);
    assert(st_edge.st_size == sizeof(vertex_t)*edge_count);
    
    f = fopen(file.c_str(), "rb");
    assert(f != 0);
    data->adj_list = (vertex_t*) malloc(st_edge.st_size);
    assert(data->adj_list);
    fread(data->adj_list, sizeof(vertex_t), edge_count , f);
    fclose(f);
	
	data->vert_count = vert_count;
}

//It will not do a deep copy, memory will be used.
void
ugraph_t::init_from_csr(csr_t* data, int sorted)
{
	vertex_t		vert_count = data->vert_count;
	adj_list_t*		adj_list = (adj_list_t*)malloc(sizeof(adj_list_t)*vert_count);
	
	udata.vert_count	= vert_count;
	udata.adj_list		= adj_list;

	#pragma omp parallel
	{
	vertex_t degree = 0;
	int leaf_count = 0;
	vertex_t* l_adj_list = 0;
	int level1_count = 0;
	#pragma omp for
	for (vertex_t i = 0; i < vert_count; ++i) {
		degree = data->beg_pos[i + 1] - data->beg_pos[i];
		l_adj_list = data->adj_list + data->beg_pos[i];
		if (!sorted) sort(l_adj_list, l_adj_list + degree);
		if (degree <= kinline_keys) {
			for (degree_t j = 0; j < degree; ++j) {
				adj_list[i].btree.inplace_keys[j] = l_adj_list[j];
			}
		} else if (degree <= kleaf_keys) {
			adj_list[i].btree.leaf_node = (kleaf_node_t*)l_adj_list;
		} else {
			leaf_count = degree/kleaf_keys; + (0 != degree % kleaf_keys);
			level1_count = leaf_count/kinner_values + (0 != leaf_count/kinner_values);
			kleaf_node_t* leaf_node = (kleaf_node_t*)l_adj_list;
			kinner_node_t* inner_node = (kinner_node_t*)malloc(sizeof(kinner_node_t));
			udata.adj_list[i].btree.inner_node = inner_node;
			kinner_node_t* prev = inner_node;
			for (int j = 0; j < level1_count; ++j) {
				for (int k = 0; k < leaf_count; ++k) {
					inner_node->values[k] = leaf_node;
					inner_node->keys[k] = leaf_node->keys[0];
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
ugraph_t::bfs(vertex_t root)
{
	vertex_t	vert_count = udata.vert_count;
	vertex_t	degree	   = 0;
	adj_list_t* adj_list   = udata.adj_list;
	
	int* status = 0; //XXX
	//default status = INF
	
	kinner_node_t*	inner_node = 0;
	kleaf_node_t*	leaf_node = 0;
	vertex_t*		nebrs = 0; 
	int				level = 0;
	int				count = 0;
	vertex_t		frontier = 0;
	
	while(frontier) {
		frontier = 0;

		for (vertex_t v = 0; v < udata.vert_count; ++v) {
			if (status[v] == level) continue;
	
			//based on degree, we need to take alternate paths
			degree = adj_list[v].degree;
		
			if (degree <= kinline_keys) {//Path 1:
				vertex_t* nebrs = adj_list[v].btree.inplace_keys;
				count = degree;
				for (int j = 0; j < count; ++j) {
					if (status[nebrs[j]] == level) {
						status[nebrs[j]] = level + 1;
						++frontier;
					}
				}

			} else if (degree <= kleaf_keys) {//Path 2;
				nebrs = adj_list[v].btree.leaf_node->keys;
				count = adj_list[v].btree.leaf_node->count;
				for (int j = 0; j < leaf_node->count; ++j) {
					if (status[nebrs[j]] == level) {
						status[nebrs[j]] = level + 1;
						++frontier;
					}
				}

			} else {//Path 3:
				inner_node = udata.adj_list[v].btree.inner_node;
				while (inner_node) {
					for (int i = 0; i < inner_node->count; ++i) {
						nebrs = ((kleaf_node_t*)inner_node->values[i])->keys;
						count = ((kleaf_node_t*)inner_node->values[i])->count;
						for (int j = 0; j < leaf_node->count; ++j) {
							if (status[nebrs[j]] == level) {
								status[nebrs[j]] = level + 1;
								++frontier;
							}
						}
					}
					inner_node = inner_node->next;
				}
			}
			//end path
			cout << "Level Count = " << level << " Frontier Count = " << frontier << endl;

		}
	}
}


void
ugraph_t::pagerank(int iteration_count)
{
	vertex_t	vert_count = udata.vert_count;
	vertex_t	degree	   = 0;
	adj_list_t* adj_list   = udata.adj_list;
	rank_t*		pr		   = (rank_t*)malloc(sizeof(rank_t)*vert_count);
	rank_t*		inv_degree = (rank_t*)malloc(sizeof(rank_t)*vert_count);
	
	for (vertex_t v = 0; v < udata.vert_count; ++v) {
		if (udata.adj_list[v].degree != 0) {
			inv_degree[v] = 1.0f/udata.adj_list[v].degree;
		}
	}

	kinner_node_t*	inner_node = 0;
	kleaf_node_t*	leaf_node = 0;
	rank_t			rank = 0.0;
	vertex_t*		nebrs = 0;
	int				count = 0;
	
	for (int iter_count = 0; iter_count < iteration_count; ++iter_count) {
		for (vertex_t v = 0; v < udata.vert_count; ++v) {
			degree = adj_list[v].degree;
			
			//based on degree, we need to take alternate paths
			
			if (degree <= kinline_keys) {//Path 1:
				nebrs = adj_list[v].btree.inplace_keys;
				count = degree;
				for (int j = 0; j < count; ++j) {
					rank += pr[nebrs[j]];
				}

			} else if (degree <= kleaf_keys) {//Path 2;
				nebrs = adj_list[v].btree.leaf_node->keys;
				count = adj_list[v].btree.leaf_node->count;
				for (int j = 0; j < count; ++j) {
					rank += pr[nebrs[j]];
				}

			} else {//Path 3:
				inner_node = udata.adj_list[v].btree.inner_node;
				while (inner_node) {
					for (int i = 0; i < inner_node->count; ++i) {
						nebrs = ((kleaf_node_t*)inner_node->values[i])->keys;
						count = ((kleaf_node_t*)inner_node->values[i])->count;
						for (int j = 0; j < count; ++j) {
							rank += pr[nebrs[j]];
						}
					}
					inner_node = inner_node->next;
				}
			}

			//end path

			if (iter_count != iteration_count - 1) {
				rank = (0.15 + 0.85*rank)*inv_degree[v];
			} else {
				rank = (0.15 + 0.85*rank);
			}
			pr[v] = rank;//XXX
		}
	}
}

int main(int argc, char* argv[])
{
	g = new ugraph_t;
	g->init(argc, argv);
	return 0;
}

void ugraph_t::init(int argc, char* argv[])
{
    int o;
    int job = 0;
    uint32_t scale;
    int c = 0;
    string inputfile;
	vertex_t vert_count;
	int arg = -1;
    
	while ((o = getopt (argc, argv, "s:o:hi:j:c:m:v:a:")) != -1) {
        switch(o) {
            case 's': //scale
                scale = atoi(optarg);
                vert_count = (1L << scale);
                break;
            case 'v'://vert count
				sscanf(optarg, "%ld", &vert_count);
                break;
            case 'i':
                inputfile = optarg;
                break;
            case 'j':
                job = atoi(optarg);
                break;
            case 'h':
                cout << "Coming soon" << endl;
                return;
            case 'a':
                arg = atoi(optarg);
                break;
            default:
               assert(0); 
        }
    }

	csr_t data;
	csr_from_file(inputfile, vert_count, &data);
	init_from_csr(&data, true);
    double start, end;
  
    switch(job) {
    case 0:
            start = mywtime();
            bfs(arg);
            end = mywtime();
            cout << "BFS time = " << end-start << endl;
            break;    
    default:
            assert(0);
    }
	return ;
}
