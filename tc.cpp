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
#include "tc.h"

using std::cout;
using std::endl;
using std::string;
using std::swap;
using std::sort;
using std::min;


tc_t* g = 0; 

void
tc_t::init_from_csr2(string csrfile, vertex_t vert_count, int sorted)
{
    csr_t data;
    
    //beg pos read
    string file = csrfile + ".beg_pos";
    struct stat st_count;
    stat(file.c_str(), &st_count);
    assert(st_count.st_size == (vert_count +1)*sizeof(index_t));
	
	FILE* f = fopen(file.c_str(),"rb");
    assert(f != 0);
   
    index_t*  beg_pos = (index_t*) malloc(st_count.st_size);
    assert(beg_pos);
    
    fread(beg_pos, sizeof(index_t), vert_count + 1, f);
    fclose(f);

    index_t edge_count = beg_pos[vert_count];
	
    //Adj list read
    file = csrfile + ".adj";
    struct stat st_edge;
    stat(file.c_str(), &st_edge);
    assert(st_edge.st_size == sizeof(vertex_t)*edge_count);
    
    f = fopen(file.c_str(), "rb");
    assert(f != 0);
    setbuf(f, 0);
    
    data.adj_list = (vertex_t*) malloc(st_edge.st_size);

    assert(data.adj_list);
    fread(data.adj_list, sizeof(vertex_t), edge_count , f);
    fclose(f);
    	
	data.vert_count = vert_count;
    data.beg_pos = beg_pos;
	
    //new format
    adj_list_t*		adj_list = (adj_list_t*)malloc(sizeof(adj_list_t)*vert_count);
	udata.vert_count	= vert_count;
	udata.adj_list		= adj_list;

	#pragma omp parallel
	{
	vertex_t        degree = 0;
	int         leaf_count = 0;
	vertex_t*   l_adj_list = 0;
	int       level1_count = 0;
    vertex_t          vert = 0;

	#pragma omp for
	for (vertex_t i = 0; i < vert_count; ++i) {
		degree = beg_pos[i + 1] - beg_pos[i];
		l_adj_list = data.adj_list + beg_pos[i];
		adj_list[i].degree = degree;
        vertex_t m = 0;
        vertex_t n = 0;
		
		if (!sorted) sort(l_adj_list, l_adj_list + degree);
			
        for (degree_t j = 0; j < degree; ++j) {
            vert = l_adj_list[j];
            if (degree < (beg_pos[vert + 1] - beg_pos[vert])) {
                ++m;
            }
        }
        adj_list[i].degree = m;
        n = m;
        m = 0;
		
        if (n <= kinline_keys) {
			for (degree_t j = 0; j < degree; ++j) {
                vert = l_adj_list[j];
                if (degree < (beg_pos[vert + 1] - beg_pos[vert])) {
				    adj_list[i].btree.inplace_keys[m] = l_adj_list[j];
                    ++m;
                }
			}
		} else if (n <= kleaf_keys) {
			adj_list[i].btree.leaf_node = (kleaf_node_t*)malloc(sizeof(kleaf_node_t));
			adj_list[i].btree.leaf_node->count = degree;
			for (degree_t j = 0; j < degree; ++j) {
                vert = l_adj_list[j];
                if (degree < (beg_pos[vert + 1] - beg_pos[vert])) {
				    adj_list[i].btree.leaf_node->keys[m] = l_adj_list[j];
                    ++m;
                }
			}
			
		} else {
			leaf_count = n/kleaf_keys + (0 != n % kleaf_keys);
			level1_count = leaf_count/kinner_values + (0 != leaf_count % kinner_values);
			
			kinner_node_t* inner_node = (kinner_node_t*)malloc(sizeof(kinner_node_t));
			adj_list[i].btree.inner_node = inner_node;
			
			int    remaining_leaf = leaf_count;
			degree_t        count = kleaf_keys;
			int       inner_count = kinner_keys;
			kinner_node_t*   prev = 0;
			kleaf_node_t* leaf_node = 0;
            vertex_t a  = 0;
			
			for (int j = 0; j < level1_count; ++j) {
				inner_count = min(kinner_keys, remaining_leaf);
				remaining_leaf -= inner_count;
				inner_node->count = inner_count;
				inner_node->level = 1;
			
				for (int k = 0; k < inner_count; ++k) {
					leaf_node = (kleaf_node_t*)malloc(sizeof(kleaf_node_t));
					m = 0;
                    while (a < degree && m < kleaf_keys) {
                        vert = l_adj_list[a];
                        if (degree < (beg_pos[vert + 1] - beg_pos[vert])) {
                            leaf_node->keys[m] = l_adj_list[a];
                            ++m;
                        }
                        ++a;
                    }
					
                    inner_node->values[k] = leaf_node;
					inner_node->keys[k] = leaf_node->keys[0];
					
					leaf_node->count  = m;
					leaf_node->sorted = 1;
				}

				prev = inner_node;
				inner_node = (kinner_node_t*)malloc(sizeof(kinner_node_t));
				prev->next = inner_node;
			}

			//delete last allocation and the link
			free(inner_node);
			prev->next = 0;

            //Make higher node
            degree_t level_count = level1_count;
            while (level_count > kinner_values) {
                degree_t remaining = level_count;
                level_count = level_count/kinner_values + (0 != level_count % kinner_values);
                kinner_node_t* tmp_inner_node = (kinner_node_t*)malloc(sizeof(kinner_node_t));
                kinner_node_t* inner_node	  = udata.adj_list[i].btree.inner_node;
                int			   level		  = inner_node->level + 1; 
                
                udata.adj_list[i].btree.inner_node = tmp_inner_node;
                
                kinner_node_t* prev = 0;
                degree_t inner_count = kinner_keys;	
                
                for (int j = 0; j < level_count; ++j) {
                    inner_count = min(kinner_keys, remaining);
                    remaining -= inner_count;

                    tmp_inner_node->count = inner_count;
                    tmp_inner_node->level = level;
                
                    for (int k = 0; k < inner_count; ++k) {
                        tmp_inner_node->values[k] = inner_node;
                        tmp_inner_node->keys[k] = inner_node->keys[0];
                        inner_node = inner_node->next;	
                    }

                    prev = tmp_inner_node;
                    tmp_inner_node = (kinner_node_t*)malloc(sizeof(kinner_node_t));
                    prev->next = tmp_inner_node;
                }

                //delete last allocation and the link
                free(tmp_inner_node);
                prev->next = 0;
            }
		}
	}
	}
}

index_t tc_t::tc()
{
	vertex_t vert_count = udata.vert_count;
	adj_list_t* adj_list   = udata.adj_list;
	index_t			tc_count = 0;
	
    
    //#pragma omp parallel num_threads(NUM_THDS) reduction (+:tc_count)
    {
	vertex_t v1, v2;
	degree_t degree;
	kinner_node_t*	inner_node = 0;
	vertex_t*		nebrs = 0;
	int				count = 0;
    //#pragma omp for schedule (guided)
	for(vertex_t v = 0; v < 1; ++v) {
		degree = udata.adj_list[v].degree;
		if (degree <= kinline_keys) {//Path 1:
			nebrs = adj_list[v].btree.inplace_keys;
			count = degree;
			for (int j = 0; j < count; ++j) {
				v1 = v;
				v2 = nebrs[j];
				tc_count += intersection(v1, v2);
                cout << v2 << " : " << tc_count << endl;
			}

		} else if (degree <= kleaf_keys) {//Path 2;
			nebrs = adj_list[v].btree.leaf_node->keys;
			count = adj_list[v].btree.leaf_node->count;
			for (int j = 0; j < count; ++j) {
				v1 = v;
				v2 = nebrs[j];
				tc_count += intersection(v1, v2);
                cout << v2 << " : " << tc_count << endl;
			}

		} else {//Path 3:
			inner_node = udata.adj_list[v].btree.inner_node;
			while (inner_node) {
				for (int i = 0; i < inner_node->count; ++i) {
					nebrs = ((kleaf_node_t*)inner_node->values[i])->keys;
					count = ((kleaf_node_t*)inner_node->values[i])->count;
					for (int j = 0; j < count; ++j) {
						v1 = v;
						v2 = nebrs[j];
						tc_count += intersection(v1, v2);
                        cout << v2 << " : " << tc_count << endl;

					}
				}
				inner_node = inner_node->next;
			}
		}
	}
    }
	return tc_count;
}

index_t tc_t::intersection(vertex_t v1, vertex_t v2)
{
    adj_list_t* list1 = udata.adj_list + v1;
    adj_list_t* list2 = udata.adj_list + v2;
    cout << list1->degree << " " << list2->degree << endl;; 
    return adj_list_t::intersection(list1, list2); 
}

int main(int argc, char* argv[])
{
	g = new tc_t;
	g->init(argc, argv);
	return 0;
}

void tc_t::init(int argc, char* argv[])
{
    int o;
    int job = 0;
    uint32_t scale;
    int c = 0;
    string inputfile;
	vertex_t vert_count;
	int arg = -1;
    
	while ((o = getopt (argc, argv, "s:a:hi:j:v:")) != -1) {
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
	index_t tc_count = 0;
        
    start = mywtime();
    init_from_csr2(inputfile, vert_count, false);
    end = mywtime();
    cout << "Conversion time = " << end - start << endl;
  
    switch(job) {
    case 0:
        start = mywtime();
        tc_count = tc();
        end = mywtime();
        cout << "TC time = " << end-start << endl;
        cout << "TC count = " << tc_count << endl;
        break;    
    default:
        assert(0);
    }
	return ;
}

