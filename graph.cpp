#include <omp.h>
#include <sys/stat.h>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <fstream>
#include <assert.h>
#include <sys/mman.h>
#include <asm/mman.h>
#include <fcntl.h>
#include <libaio.h>

#include "wtime.h"
#include "graph.h"
#include "bitmap.h"

using std::cout;
using std::endl;
using std::string;
using std::swap;
using std::sort;
using std::min;

//16, 2MB huge pages
#define mem_leaf 33554432
//#define mem_leaf 262144 
#define mem_inner 2730 


// 1<<28
//#define io_size 268435456 
static const index_t io_size = (1L<<28);
#define ALIGN_MASK 0xFFFFFFFFFFFFFF80
#define UPPER_ALIGN(x) (((x) + 127) & ALIGN_MASK)
#define LOWER_ALIGN(x) ((x) & ALIGN_MASK)

ugraph_t* g = 0;

index_t*  ugraph_t::read_csr_begpos(string csrfile, vertex_t vert_count)
{
    string file = csrfile + ".beg_pos";
    struct stat st_count;
    stat(file.c_str(), &st_count);
    assert(st_count.st_size == (vert_count +1)*sizeof(index_t));
	
	FILE* f = fopen(file.c_str(),"rb");
    assert(f != 0);
    index_t* beg_pos = (index_t*)mmap(NULL, st_count.st_size, 
                       PROT_READ|PROT_WRITE,
                       MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_1GB, 0 , 0);
    if (MAP_FAILED == beg_pos) {
        beg_pos = (index_t*) malloc(st_count.st_size);
    }
    assert(beg_pos);
    fread(beg_pos, sizeof(index_t), vert_count + 1, f);
    fclose(f);
    return beg_pos;
}

/*
vertex_t ugraph_t::read_csr_adj(int f, vertex_t v, index_t* beg_pos, vertex_t* buf)
{
    vertex_t        u = v;
    
    index_t     prior       = beg_pos[v];
    index_t     offset      = LOWER_ALIGN(prior);
    index_t     extra_read  = prior - offset;
    
    while (beg_pos[u+1] - offset <= io_size && u < udata.vert_count) {
        ++u;
    }

    index_t io_count = UPPER_ALIGN(beg_pos[u]) - offset;
    assert(io_count <= io_size);
    index_t size = io_count*sizeof(vertex_t);
    
    struct io_event event;
    io_context_t ctx = 0;
    if (io_setup(1, &ctx) < 0) {
        assert(0);
    }
   
    struct iocb** cb = new struct iocb*[1]; 
    cb[0] = new struct iocb;
    io_prep_pread(cb[0], f, buf, size, offset*sizeof(vertex_t));
    if (1 != io_submit(ctx, 1, cb)) {
        assert(0);
    }

    if (1 != io_getevents(ctx, 1, 1, &event, 0)) {
        assert(0);
    }
    //cout << "Read from io " << buf[0] << " " << buf[1] << " " << buf[2] << endl;
    io_destroy(ctx);
    free(cb[0]);
    free(cb);

    return u - v;
}
*/

vertex_t ugraph_t::read_csr_adj(int f, vertex_t v, index_t* beg_pos, vertex_t* buf)
{
    vertex_t        u = v;
    
    index_t     new_io_size = io_size;
    index_t     prior       = beg_pos[v];
    index_t     offset      = UPPER_ALIGN(prior);
    index_t     extra_read  = offset - prior;
    vertex_t*   new_buf     = buf;   
    
    //Last stage read some bytes extra
    if (extra_read) {
        prior += extra_read;
        new_io_size = io_size - 128;
        new_buf = buf + 128;
    }
    assert(prior == offset);

    while (beg_pos[u+1] - prior <= new_io_size && u < udata.vert_count) {
        ++u;
    }

    index_t io_count = UPPER_ALIGN(beg_pos[u]) - prior;
    assert(io_count <= new_io_size);
    index_t size = io_count*sizeof(vertex_t);
    
    struct io_event event;
    io_context_t ctx = 0;
    if (io_setup(1, &ctx) < 0) {
        assert(0);
    }
   
    struct iocb cb;
    struct iocb* pcb = &cb;
     
    io_prep_pread(pcb, f, new_buf, size, offset*sizeof(vertex_t));
    if (1 != io_submit(ctx, 1, &pcb)) {
        assert(0);
    }

    if (1 != io_getevents(ctx, 1, 1, &event, 0)) {
        assert(0);
    }
    io_destroy(ctx);

    return u - v;
}
/*
vertex_t ugraph_t::read_csr_adj(FILE* f, vertex_t v, index_t* beg_pos, vertex_t* buf )
{
    index_t prior =  beg_pos[v];
    vertex_t u = v;
    while (beg_pos[u+1] - prior <= io_size && u < udata.vert_count) {
        ++u;
    }
    index_t io_count = beg_pos[u] - prior;
    assert(io_count <= io_size);
    fread(buf, sizeof(vertex_t), io_count , f);
    return u - v;
}
*/

void
ugraph_t::init_from_csr(string csrfile, vertex_t vert_count, int sorted)
{
	csr_t data;
    index_t* beg_pos = read_csr_begpos(csrfile, vert_count);
    index_t edge_count = beg_pos[vert_count];
    
    // New format
    adj_list_t* adj_list = (adj_list_t*)mmap(NULL, sizeof(adj_list_t)*vert_count, 
                       PROT_READ|PROT_WRITE,
                       MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_1GB, 0 , 0);
    
    if (MAP_FAILED == adj_list) {
    	adj_list = (adj_list_t*)malloc(sizeof(adj_list_t)*vert_count);
        cout << "Huge Page: udata.adj_list allocation failed " << endl;
    }

	udata.vert_count	= vert_count;
    udata.adj_list      = adj_list;

    //Read first chunk from csr adj list file
    string file = csrfile + ".adj";
    struct stat st_edge;
    stat(file.c_str(), &st_edge);
    assert(st_edge.st_size == sizeof(vertex_t)*edge_count);
    
    int f = open(file.c_str(), O_DIRECT|O_RDONLY);
    
    vertex_t* buf = (vertex_t*)mmap(NULL, sizeof(vertex_t)*vert_count, 
                       PROT_READ|PROT_WRITE,
                       MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_1GB, 0 , 0);
    
    if (MAP_FAILED == buf) {
        if(posix_memalign((void**)&buf, 512 , io_size*sizeof(vertex_t))) {
             perror("posix_memalign");
            assert(0);
        }
        cout << "1GB huge page for buf failed" << endl;
    }
    
    vertex_t* buf1 = (vertex_t*)mmap(NULL, sizeof(vertex_t)*vert_count, 
                       PROT_READ|PROT_WRITE,
                       MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_1GB, 0 , 0);
    
    if (MAP_FAILED == buf) {
        if(posix_memalign((void**)&buf1, 512 , io_size*sizeof(vertex_t))) {
             perror("posix_memalign");
            assert(0);
        }
        cout << "1GB huge page for buf1 failed" << endl;
    }

    index_t prior = 0;
    vertex_t u = 0, v = 0;
    v = read_csr_adj(f, v, beg_pos, buf1);
    data.beg_pos = beg_pos;
    data.adj_list = buf1;
    
    #pragma omp parallel num_threads(NUM_THDS)
    {
        int tid = omp_get_thread_num();
        mem_info[tid].inner_node_list = 0;
        mem_info[tid].inner_count = mem_inner;
        mem_info[tid].leaf_node_list = 0;
        mem_info[tid].leaf_count = mem_leaf;
    }
        
    do {
        vertex_t v1 = u;
        vertex_t v2 = v;
        cout << v1 << " " << v2 << endl;
        /*
        cout << data.adj_list[beg_pos[v1]] << " "  
             << data.adj_list[beg_pos[v1 + 1]] << " "
             << data.adj_list[beg_pos[v1 + 2]] << " " << endl;
        */
        #pragma omp parallel num_threads(NUM_THDS)
        {
        vertex_t* l_adj_list = 0;
        vertex_t degree = 0;
        int leaf_count = 0;
        int level1_count = 0;
        int tid = 0;

        #pragma omp master 
        {
            if (v < vert_count) {
                u = v + read_csr_adj(f, v, beg_pos, buf);
            }
        }

        #pragma omp for schedule (dynamic, 256)
        for (vertex_t i = v1; i < v2; ++i) {
            degree = data.beg_pos[i + 1] - data.beg_pos[i];
            l_adj_list = data.adj_list + data.beg_pos[i];
            adj_list[i].degree = degree;
            adj_list[i].leaf_count = 0;
            
            if (!sorted) sort(l_adj_list, l_adj_list + degree);
            
            if (degree <= kinline_keys) {
                for (degree_t j = 0; j < degree; ++j) {
                    adj_list[i].btree.inplace_keys[j] = l_adj_list[j];
                }
            } else if (degree <= max_kleaf_keys) {
                adj_list[i].btree.leaf_node = alloc_leaf(degree);
                memcpy(adj_list[i].btree.leaf_node,
                       l_adj_list, degree*sizeof(vertex_t));
                
            } else {
                leaf_count = degree/kleaf_keys + (0 != degree % kleaf_keys);
                kinner_node_t* inner_node = alloc_inner(leaf_count);
                adj_list[i].leaf_count = leaf_count;
                adj_list[i].btree.inner_node = inner_node;
                
                degree_t remaining = degree;
                degree_t count = kleaf_keys;
                kleaf_node_t* leaf_node = 0;
                
                for (int j = 0; j < leaf_count; ++j) {
                    count = min(kleaf_keys, remaining);
                    remaining -= count;
                    leaf_node = alloc_leaf(count);
                    memcpy(leaf_node, l_adj_list, count*sizeof(vertex_t));
                    inner_node[j].key = l_adj_list[0];
                    inner_node[j].count = count;
                    inner_node[j].value = leaf_node;
                    l_adj_list += count;
                }
            }
        }
        }
        prior =  beg_pos[v];
        
        index_t extra_read = UPPER_ALIGN(prior) - prior;
        if (extra_read) {
            vertex_t* new_buf = buf + 128 - extra_read; 
            memcpy(new_buf, data.adj_list + prior, extra_read*sizeof(vertex_t));
            data.adj_list = new_buf - prior;
        } else {
            data.adj_list = buf - prior;
        }
        
        swap(buf, buf1);
        swap(v, u);
    } while (u < vert_count);
}

kleaf_node_t* ugraph_t::alloc_leaf(index_t count)
{
    int tid = omp_get_thread_num();
    kleaf_node_t* leaf_node = mem_info[tid].leaf_node_list;
    
    //Out of memory
    if (mem_info[tid].leaf_count + count > mem_leaf) {
        leaf_node = (kleaf_node_t*)mmap(NULL, mem_leaf*sizeof(kleaf_node_t), 
                       PROT_READ|PROT_WRITE,
                       MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0 , 0);
        if (MAP_FAILED == leaf_node) {
            leaf_node = (kleaf_node_t*)calloc (mem_leaf, sizeof(kleaf_node_t));
            //cout << "leaf huge page failed" << endl;
        }
        mem_info[tid].leaf_count = 0;
        mem_info[tid].leaf_node_list = leaf_node;
    }

    //allocate
    leaf_node = leaf_node + mem_info[tid].leaf_count;
    mem_info[tid].leaf_count += count;
    return leaf_node;
}

kinner_node_t* ugraph_t::alloc_inner(index_t count)
{
    /*
    int tid = omp_get_thread_num();
    kinner_node_t* inner_node = mem_info[tid].inner_node_list;

    if (mem_info[tid].inner_count == mem_inner) {
        inner_node = (kinner_node_t*)mmap(NULL, (1<<20), 
                       PROT_READ|PROT_WRITE,
                       MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0 , 0);
        
        if (MAP_FAILED == inner_node) {
            inner_node = (kinner_node_t*)calloc (mem_inner, sizeof(kinner_node_t));
            //cout << "inner huge page failed" << endl;
        }
        mem_info[tid].inner_count = 0;
        mem_info[tid].inner_node_list = inner_node;
    }

    inner_node = inner_node + mem_info[tid].inner_count;
    mem_info[tid].inner_count += 1;

    return inner_node;*/
    return (kinner_node_t*) malloc(sizeof(kcv_t)*count);
}



void
ugraph_t::bfs(vertex_t root)
{
	vertex_t	vert_count = udata.vert_count;
	adj_list_t* adj_list   = udata.adj_list;
	index_t		edge_count = (1<< 28);
	
    uint8_t* status = (uint8_t*)mmap(NULL, vert_count, 
                       PROT_READ|PROT_WRITE,
                       MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0 , 0);
    if (MAP_FAILED == status) {
	    status = (uint8_t*)calloc(sizeof(uint8_t), vert_count);
        cout << "bfs status array, huge page failed" << endl;
    }
	//default status = INF
    Bitmap bitmap(vert_count);

	int				level = 1;
	int				top_down = 1;
	vertex_t		frontier = 0;
	index_t			todo = 0;

	status[root] = 1;
	
	do {
		frontier = 0;
		todo = 0;
		double start = mywtime();
		if (top_down) {
			#pragma omp parallel num_threads(NUM_THDS) reduction (+:todo) reduction(+:frontier) firstprivate(start)
            {
            kinner_node_t*	inner_node = 0;
            vertex_t*		nebrs   = 0; 
	        vertex_t	    degree	= 0;
            int				count   = 0;
            #pragma omp for schedule (guided) nowait
			for (vertex_t v = 0; v < udata.vert_count; ++v) {
				if (status[v] != level) continue;
		
				//based on degree, we need to take alternate paths
				degree = adj_list[v].degree;
				todo += degree;
			
				if (degree <= kinline_keys) {//Path 1:
					vertex_t* nebrs = adj_list[v].btree.inplace_keys;
					count = degree;
					for (int j = 0; j < count; ++j) {
						if (bitmap.get_bit(nebrs[j]) == 0) {
                            bitmap.set_bit(nebrs[j]);
                            if (status[nebrs[j]] == 0) {
							    status[nebrs[j]] = level + 1;
							    ++frontier;
                            }
						}
					}

				} else if (degree <= max_kleaf_keys) {//Path 2;
					nebrs = adj_list[v].btree.leaf_node;
					count = degree;
					for (int j = 0; j < count; ++j) {
						if (bitmap.get_bit(nebrs[j]) == 0) {
                            bitmap.set_bit(nebrs[j]);
                            if (status[nebrs[j]] == 0) {
							    status[nebrs[j]] = level + 1;
							    ++frontier;
                            }
						}
					}

				} else {//Path 3:
					inner_node = adj_list[v].btree.inner_node;
                    index_t leaf_count = adj_list[v].leaf_count;
                    for (int i = 0; i < leaf_count; ++i) {
                        nebrs = inner_node[i].value;
                        count = inner_node[i].count;
                        for (int j = 0; j < count; ++j) {
                            if (bitmap.get_bit(nebrs[j]) == 0) {
                                bitmap.set_bit(nebrs[j]);
                                if (status[nebrs[j]] == 0) {
                                    status[nebrs[j]] = level + 1;
                                    ++frontier;
                                }
                            }
                        }
                    }
				}
			}
            double end = mywtime() -start;
            if (level == 3)
            cout << end << endl;
            }
		} else { //bottom up
			#pragma omp parallel num_threads(NUM_THDS) reduction (+:todo) reduction(+:frontier) 
            {
            kinner_node_t*	inner_node = 0;
            vertex_t*		nebrs = 0; 
	        vertex_t	degree	   = 0;
            int				count = 0;
            #pragma omp for schedule (static)
			for (vertex_t v = 0; v < udata.vert_count; ++v) {
				if (status[v] != 0) continue;
		
				//based on degree, we need to take alternate paths
				degree = adj_list[v].degree;
				todo += degree;
			
				if (degree <= kinline_keys) {//Path 1:
					vertex_t* nebrs = adj_list[v].btree.inplace_keys;
					count = degree;
					for (int j = 0; j < count; ++j) {
						if (status[nebrs[j]] == level) {
							status[v] = level + 1;
							++frontier;
							break;
						}
					}

				} else if (degree <= max_kleaf_keys) {//Path 2;
					nebrs = adj_list[v].btree.leaf_node;
					count = degree;
					for (int j = 0; j < count; ++j) {
						if (status[nebrs[j]] == level) {
							status[v] = level + 1;
							++frontier;
							break;
						}
					}

				} else {//Path 3:
					inner_node = adj_list[v].btree.inner_node;
                    index_t leaf_count = adj_list[v].leaf_count;
                    for (int i = 0; i < leaf_count; ++i) {
                        nebrs = inner_node[i].value;
                        count = inner_node[i].count;
                        for (int j = 0; j < count; ++j) {
                            if (status[nebrs[j]] == 0 ) {
                                status[v] = level + 1;
                                ++frontier;
                                break;
                            }
                        }
                    }
				}
			}
		}
        }
		double end = mywtime();
	
		cout << "Top down = " << top_down;
		cout << " Level = " << level;
		cout << " Time = " << end - start;
        cout << " Frontier Count = " << frontier;
        cout << " ToDo = " << todo;
		cout << endl;
		
		if (todo >= 0.03*edge_count) {
			top_down = false;
		} else {
            top_down = true;
        }
		++level;
	} while(frontier);
}

/*
void
ugraph_t::pagerank_async(int iteration_count)
{
	vertex_t	vert_count = udata.vert_count;
	adj_list_t* adj_list   = udata.adj_list;
	rank_t		inv_v_count= 1.0f/vert_count;
	rank_t*		pr		   = (rank_t*)malloc(sizeof(rank_t)*vert_count);
	rank_t*		inv_degree = (rank_t*)malloc(sizeof(rank_t)*vert_count);
	
	for (vertex_t v = 0; v < udata.vert_count; ++v) {
		pr[v] = inv_v_count;
		if (udata.adj_list[v].degree != 0) {
			inv_degree[v] = 1.0f/udata.adj_list[v].degree;
		}
	}

	
	for (int iter_count = 0; iter_count < iteration_count; ++iter_count) {
        #pragma omp parallel num_threads(NUM_THDS)
        {
        kinner_node_t*	inner_node = 0;
        rank_t			rank    = 0.0;
        vertex_t*		nebrs   = 0;
        int				count   = 0;
        vertex_t	    degree  = 0;
        #pragma omp for schedule (static) 
		for (vertex_t v = 0; v < vert_count; ++v) {
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

			//if (iter_count != iteration_count - 1) {
				rank = (0.15 + 0.85*rank)*inv_degree[v];
			//} else {
			//	rank = (0.15 + 0.85*rank);
			//}
			pr[v] = rank;//XXX
		}
        }
	}
	cout << "PR[0] = " << pr[0] << endl;
}

void
ugraph_t::pagerank(int iteration_count)
{
	vertex_t	vert_count = udata.vert_count;
	adj_list_t* adj_list   = udata.adj_list;
    
    rank_t* pr = (rank_t*)mmap(NULL, sizeof(rank_t)*vert_count, 
                       PROT_READ|PROT_WRITE,
                       MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0 , 0);
    if (MAP_FAILED == pr) {
	    pr  = (rank_t*)malloc(sizeof(rank_t)*vert_count);
        cout << "PR Huge page allocation failed" << endl;
    }
    
    rank_t* prior_pr = (rank_t*)mmap(NULL, sizeof(rank_t)*vert_count, 
                       PROT_READ|PROT_WRITE,
                       MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0 , 0);

    if (MAP_FAILED == prior_pr) {
	    prior_pr   = (rank_t*)malloc(sizeof(rank_t)*vert_count);
        cout << "PR_PRIOR Huge page allocation failed" << endl;
    }
	
	rank_t	inv_v_count = 1.0f/vert_count;
	for (vertex_t v = 0; v < udata.vert_count; ++v) {
		prior_pr[v] = inv_v_count;
	}

	
	for (int iter_count = 0; iter_count < iteration_count; ++iter_count) {
        double start = mywtime();
        #pragma omp parallel num_threads(NUM_THDS)
        {
        kinner_node_t*	inner_node = 0;
        rank_t			rank    = 0.0f;
        rank_t      inv_degree  = 0.0f;
        vertex_t*		nebrs   = 0;
        int				count   = 0;
        vertex_t	    degree  = 0;
        #pragma omp for schedule (static) 
		for (vertex_t v = 0; v < vert_count; ++v) {
            
			degree = adj_list[v].degree;
            if (degree == 0) continue;
            inv_degree = 1.0f/degree;
			
			//based on degree, we need to take alternate paths
			
			if (degree <= kinline_keys) {//Path 1:
				nebrs = adj_list[v].btree.inplace_keys;
				count = degree;
				for (int j = 0; j < count; ++j) {
					rank += prior_pr[nebrs[j]];
				}

			} else if (degree <= kleaf_keys) {//Path 2;
				nebrs = adj_list[v].btree.leaf_node->keys;
				count = adj_list[v].btree.leaf_node->count;
				for (int j = 0; j < count; ++j) {
					rank += prior_pr[nebrs[j]];
				}

			} else {//Path 3:
				inner_node = udata.adj_list[v].btree.inner_node;
				while (inner_node) {
					for (int i = 0; i < inner_node->count; ++i) {
						nebrs = ((kleaf_node_t*)inner_node->values[i])->keys;
						count = ((kleaf_node_t*)inner_node->values[i])->count;
						for (int j = 0; j < count; ++j) {
							rank += prior_pr[nebrs[j]];
						}
					}
					inner_node = inner_node->next;
				}
			}

			//end path

			//if (iter_count != iteration_count - 1) {
				//rank = (0.15 + 0.85*rank)*inv_degree[v];
				rank = (0.15 + 0.85*rank)*inv_degree;
			//} else {
			//	rank = (0.15 + 0.85*rank);
			//}
			pr[v] = rank;//XXX
		}
        }
        swap(pr, prior_pr);
        double end = mywtime();
        cout << "Iteration Time = " << end - start << endl;
	}
	cout << "PR[0] = " << pr[0] << endl;
}
*/
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
				sscanf(optarg, "%d", &vert_count);
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
    int huge_page = 0;
    double start, end;
    start = mywtime();

    start = mywtime();
	init_from_csr(inputfile, vert_count, true);
    end = mywtime();
    cout << "Conversion time = " << end - start << endl;
    
    /*
    if(huge_page) {
        munmap(data.adj_list, data.beg_pos[vert_count]*sizeof(vertex_t));
    } else {
        free(data.adj_list);
    }
    */
	index_t tc_count = 0;
  
    switch(job) {
    case 0:
            start = mywtime();
            bfs(arg);
            end = mywtime();
            cout << "BFS time = " << end-start << endl;
            break;    
/*    case 1:
            start = mywtime();
            pagerank(arg);
            end = mywtime();
            cout << "PageRank time = " << end-start << endl;
            break;    
    case 2:
            start = mywtime();
            pagerank_async(arg);
            end = mywtime();
            cout << "PageRank time = " << end-start << endl;
            break;   */ 
    default:
            assert(0);
    }
	return ;
}

