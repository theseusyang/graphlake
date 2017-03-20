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
#include "graph_csr.h"
#include "bitmap.h"

using std::cout;
using std::endl;
using std::string;
using std::swap;
using std::sort;
using std::min;

#define NUM_THDS 24

ugraph_t* g = 0;

int
ugraph_t::csr_from_file(string csrfile, vertex_t vert_count)
{
    int huge_page = 0;
    string file = csrfile + ".beg_pos";
    struct stat st_count;
    stat(file.c_str(), &st_count);
    assert(st_count.st_size == (vert_count +1)*sizeof(index_t));
	
	FILE* f = fopen(file.c_str(),"rb");
    assert(f != 0);
   
    index_t* beg_pos = (index_t*)mmap(NULL, st_count.st_size, 
                       PROT_READ|PROT_WRITE,
                       MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0 , 0);
    if (MAP_FAILED == beg_pos) {
        beg_pos = (index_t*) malloc(st_count.st_size);
        assert(beg_pos);
    }
    
    fread(beg_pos, sizeof(index_t), vert_count + 1, f);
    fclose(f);
    data.beg_pos = beg_pos;
    index_t edge_count = data.beg_pos[vert_count];
	
    file = csrfile + ".adj";
    struct stat st_edge;
    stat(file.c_str(), &st_edge);
    assert(st_edge.st_size == sizeof(vertex_t)*edge_count);
    
    f = fopen(file.c_str(), "rb");
    assert(f != 0);
    setbuf(f, 0);

    
    data.adj_list = (vertex_t*)mmap(NULL, st_edge.st_size, 
                       PROT_READ|PROT_WRITE,
                       MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0 , 0);
    if (MAP_FAILED == data.adj_list) {
        cout << "Huge page allocation failed" << endl;
        data.adj_list = (vertex_t*) malloc(st_edge.st_size);
        huge_page = 0;
    }

    assert(data.adj_list);
    fread(data.adj_list, sizeof(vertex_t), edge_count , f);
    fclose(f);
	
	data.vert_count = vert_count;
    return huge_page;
}

int ugraph_t::rank_by_degree(string csrfile, vertex_t vert_count)
{
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
	
    file = csrfile + ".adj";
    struct stat st_edge;
    stat(file.c_str(), &st_edge);
    assert(st_edge.st_size == sizeof(vertex_t)*edge_count);
    
    f = fopen(file.c_str(), "rb");
    assert(f != 0);
    setbuf(f, 0);

    
    vertex_t*  adj_list = (vertex_t*) malloc(st_edge.st_size);

    assert(adj_list);
    fread(adj_list, sizeof(vertex_t), edge_count , f);
    fclose(f);
	
	data.vert_count = vert_count;
    data.beg_pos = beg_pos;
    data.adj_list = adj_list;
    
    index_t* beg_pos1 = 0;
    beg_pos1 = (index_t*)mmap(NULL, (vert_count+1)*sizeof(index_t), 
                       PROT_READ|PROT_WRITE,
                       MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0 , 0);
    if (MAP_FAILED == beg_pos) {
        beg_pos = (index_t*) malloc((vert_count + 1)*sizeof(index_t));
        assert(beg_pos);
    }
    
    #pragma omp parallel for num_threads(NUM_THDS) schedule (guided)
    for (vertex_t v = 0; v < vert_count; ++v) {
        vertex_t* nebrs = adj_list + beg_pos[v];
        vertex_t degree = beg_pos[v+1] - beg_pos[v];
        vertex_t nebr = 0;
        for (vertex_t i = 0; i < degree; ++i) {
            nebr = nebrs[i];
            beg_pos1[v] += (degree < (beg_pos[nebr + 1] - beg_pos[nebr]));
        }
    }

    //prefix sum
    index_t prefix = 0;
    index_t tmp = 0;
    for (vertex_t v = 0; v < vert_count; ++v) {
        tmp = beg_pos1[v];
        beg_pos1[v] = prefix;
        prefix += tmp;
    }
    
    vertex_t* adj_list1 = (vertex_t*)mmap(NULL, prefix*sizeof(vertex_t), 
                       PROT_READ|PROT_WRITE,
                       MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0 , 0);
    if (MAP_FAILED == adj_list1) {
        cout << "Huge page allocation failed" << endl;
        adj_list1 = (vertex_t*) malloc(prefix*sizeof(vertex_t));
    }

    #pragma omp parallel for num_threads(NUM_THDS) schedule (guided)
    for (vertex_t v = 0; v < vert_count; ++v) {
        vertex_t* nebrs  = adj_list + beg_pos[v];
        vertex_t* nebrs1 = adj_list1 + beg_pos1[v];
        vertex_t degree  = beg_pos[v+1] - beg_pos[v];
        vertex_t      j  = 0;
        vertex_t    nebr = 0;
        
        for (vertex_t i = 0; i < degree; ++i) {
            nebr = nebrs[i];
            if (degree < (beg_pos[nebr + 1] - beg_pos[nebr])) {
                nebrs1[j] = nebr;
                ++j;
            }
        }
		sort(nebrs1, nebrs1 + j);
    }

    data.beg_pos = beg_pos1;
    data.adj_list = adj_list1;
    free(beg_pos);
    free(adj_list);
    return 0;
}
/*
index_t* ugraph_t::read_csr_begpos(string csrfile, vertex_t vert_count)
{
    string file = csrfile + ".beg_pos";
    struct stat st_count;
    stat(file.c_str(), &st_count);
    assert(st_count.st_size == (vert_count +1)*sizeof(index_t));
	
	int f = open(file.c_str(), O_DIRECT|O_RDONLY);
    assert(f != -1);
    

    struct io_event event;
    io_context_t ctx = 0;
    if (io_setup(1, &ctx) < 0) {
        assert(0);
    }
   
    struct iocb cb;
    struct iocb* pcb = &cb;
    
    index_t size = UPPER_ALIGN_SZ(st_count.st_size);
    cout << st_count.st_size << " " << size << endl;
    index_t* beg_pos = 0;
    / *beg_pos = (index_t*)mmap(NULL, size, 
                       PROT_READ|PROT_WRITE,
                       MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_1GB, 0 , 0);
    
    if (MAP_FAILED == beg_pos) {* /
        if(posix_memalign((void**)&beg_pos, 512 , size)) {
            assert(0);
        }
    //}
    io_prep_pread(pcb, f, beg_pos, size, 0);
    if (1 != io_submit(ctx, 1, &pcb)) {
        assert(0);
    }

    if (1 != io_getevents(ctx, 1, 1, &event, 0)) {
        assert(0);
    }
    io_destroy(ctx);
    close(f);
    cout << beg_pos[0] << " " << beg_pos[1] << " " 
            << beg_pos[vert_count - 1]<<  " "
            << beg_pos[vert_count] << endl;
    return beg_pos;
}
*/

void
ugraph_t::bfs(vertex_t root)
{
	vertex_t	vert_count = data.vert_count;
	vertex_t*   adj_list   = data.adj_list;
    index_t*    beg_pos    = data.beg_pos;
	index_t		edge_count = (1<< 28);
	
    uint8_t* status = (uint8_t*)mmap(NULL, vert_count, 
                       PROT_READ|PROT_WRITE,
                       MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0 , 0);
    if (MAP_FAILED == status) {
	    status = (uint8_t*)calloc(sizeof(uint8_t), vert_count);
        cout << "bfs status array, huge page failed" << endl;
    }
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
			#pragma omp parallel num_threads(NUM_THDS) reduction (+:todo) reduction(+:frontier)
            {
            vertex_t*		nebrs   = 0; 
	        vertex_t	    degree	= 0;
            index_t			count   = 0;
            #pragma omp for schedule (guided) nowait
			for (vertex_t v = 0; v < vert_count; ++v) {
				if (status[v] != level) continue;
		
				//based on degree, we need to take alternate paths
				count = beg_pos[v];
                degree = beg_pos[v+1] - count;
				todo += degree;

				nebrs = adj_list + count;
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
			}
            }
		} else { //bottom up
			#pragma omp parallel num_threads(NUM_THDS) reduction (+:todo) reduction(+:frontier) 
            {
            vertex_t*		nebrs = 0; 
	        vertex_t	    degree	   = 0;
            index_t				count = 0;
            #pragma omp for schedule (static)
			for (vertex_t v = 0; v < vert_count; ++v) {
				if (status[v] != 0) continue;
		
				//based on degree, we need to take alternate paths
        
                count  = beg_pos[v];
                degree = beg_pos[v+1] - count;
                nebrs  = adj_list + count;
				todo += degree;
                count  = degree;
                for (int j = 0; j < count; ++j) {
                    if (status[nebrs[j]] == level) {
                        status[v] = level + 1;
                        ++frontier;
                        break;
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
		
		if (todo >= 0.03*edge_count || level == 2) {
			top_down = false;
		} else {
            top_down = true;
        }
		++level;
	} while(frontier);

}

void
ugraph_t::pagerank_async(int iteration_count)
{
	vertex_t	vert_count  = data.vert_count;
	vertex_t*   adj_list    = data.adj_list;
    index_t*    beg_pos     = data.beg_pos;
    rank_t*     pr          = 0;
    rank_t*     prior_pr    = 0;
    
    /*pr = (rank_t*)mmap(NULL, sizeof(rank_t)*vert_count, 
                       PROT_READ|PROT_WRITE,
                       MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0 , 0);
    if (MAP_FAILED == pr) {
    }*/
	    pr  = (rank_t*)malloc(sizeof(rank_t)*vert_count);
        cout << "PR Huge page allocation failed" << endl;
    
    /*prior_pr = (rank_t*)mmap(NULL, sizeof(rank_t)*vert_count, 
                       PROT_READ|PROT_WRITE,
                       MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0 , 0);

    if (MAP_FAILED == prior_pr) {
    }*/
	    prior_pr   = (rank_t*)malloc(sizeof(rank_t)*vert_count);
        cout << "PR_PRIOR Huge page allocation failed" << endl;
	
	rank_t	inv_v_count = 1.0f/vert_count;
	for (vertex_t v = 0; v < vert_count; ++v) {
		pr[v] = inv_v_count;
	}

	
	for (int iter_count = 0; iter_count < iteration_count; ++iter_count) {
        double start = mywtime();
        vertex_t high_degree = 0;
        #pragma omp parallel num_threads(NUM_THDS) reduction(+:high_degree)
        {
        rank_t			rank    = 0.0f;
        rank_t      inv_degree  = 0.0f;
        vertex_t*		nebrs   = 0;
        index_t			count   = 0;
        vertex_t	    degree  = 0;

        #pragma omp for schedule (static) 
		for (vertex_t v = 0; v < vert_count; ++v) {
            count = beg_pos[v];
            nebrs = adj_list + count;
            degree = beg_pos[v+1] - count;
            if (degree == 0) continue;
            inv_degree = 1.0f/degree;
            count = degree;
            high_degree += (degree > 4096);
            rank = 0;
            for (int j = 0; j < count; ++j) {
                rank += prior_pr[nebrs[j]];
			}

			//if (iter_count != iteration_count - 1) {
				//rank = (0.15 + 0.85*rank)*inv_degree[v];
				rank = (0.15 + 0.85*rank)*inv_degree;
			//} else {
			//	rank = (0.15 + 0.85*rank);
			//}
			pr[v] = rank;//XXX
		}
        }
        double end = mywtime();
        cout << "Iteration Time = " << end - start << endl;
        cout << "High degree count = " << high_degree << endl;
	}
	cout << "PR[0] = " << pr[0] << endl;
}

void
ugraph_t::pagerank(int iteration_count)
{
	vertex_t	vert_count  = data.vert_count;
	vertex_t*   adj_list    = data.adj_list;
    index_t*    beg_pos     = data.beg_pos;
    rank_t*     pr          = 0;
    rank_t*     prior_pr    = 0;
    
    /*pr = (rank_t*)mmap(NULL, sizeof(rank_t)*vert_count, 
                       PROT_READ|PROT_WRITE,
                       MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0 , 0);
    if (MAP_FAILED == pr) {
    }*/
	    pr  = (rank_t*)malloc(sizeof(rank_t)*vert_count);
        cout << "PR Huge page allocation failed" << endl;
    
    /*prior_pr = (rank_t*)mmap(NULL, sizeof(rank_t)*vert_count, 
                       PROT_READ|PROT_WRITE,
                       MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0 , 0);

    if (MAP_FAILED == prior_pr) {
    }*/
	    prior_pr   = (rank_t*)malloc(sizeof(rank_t)*vert_count);
        cout << "PR_PRIOR Huge page allocation failed" << endl;
	
	rank_t	inv_v_count = 1.0f/vert_count;
	for (vertex_t v = 0; v < vert_count; ++v) {
		prior_pr[v] = inv_v_count;
	}

	
	for (int iter_count = 0; iter_count < iteration_count; ++iter_count) {
        double start = mywtime();
        vertex_t high_degree = 0;
        #pragma omp parallel num_threads(NUM_THDS) reduction(+:high_degree)
        {
        rank_t			rank    = 0.0f;
        rank_t      inv_degree  = 0.0f;
        vertex_t*		nebrs   = 0;
        index_t			count   = 0;
        vertex_t	    degree  = 0;

        #pragma omp for schedule (static) 
		for (vertex_t v = 0; v < vert_count; ++v) {
            count = beg_pos[v];
            nebrs = adj_list + count;
            degree = beg_pos[v+1] - count;
            if (degree == 0) continue;
            inv_degree = 1.0f/degree;
            count = degree;
            high_degree += (degree > 4096);
            rank = 0;
            for (int j = 0; j < count; ++j) {
                rank += prior_pr[nebrs[j]];
			}

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
        cout << "High degree count = " << high_degree << endl;
	}
	cout << "PR[0] = " << pr[0] << endl;
}


index_t ugraph_t::tc()
{
	vertex_t vert_count = data.vert_count;
	vertex_t* adj_list   = data.adj_list;
    index_t*    beg_pos  = data.beg_pos; 
	
	index_t			tc_count = 0;
    
    //#pragma omp parallel for num_threads(NUM_THDS) schedule(static) reduction(+:tc_count)
	for(vertex_t v = 0; v < 1; ++v) {
        vertex_t* nebrs = adj_list + beg_pos[v];
        vertex_t degree =  beg_pos[v+1] - beg_pos[v];
        cout << degree << endl;
	    vertex_t v1, v2;

        for (int j = 0; j < degree; ++j) {
            v1 = v;
            v2 = nebrs[j];
            tc_count += intersection(v1, v2);
            cout << v2 << " : " << tc_count << endl;
        }
	}
	return tc_count;
}

index_t ugraph_t::intersection(vertex_t v1, vertex_t v2)
{
    vertex_t* nebr1 = data.adj_list + data.beg_pos[v1];
    vertex_t* nebr2 = data.adj_list + data.beg_pos[v2];
    vertex_t count1  = data.beg_pos[v1+1] - data.beg_pos[v1];
    vertex_t count2  = data.beg_pos[v2+1] - data.beg_pos[v2];
    vertex_t vert1, vert2;
    vertex_t icount1 = 0;
    vertex_t icount2 = 0;
    index_t tc = 0;
    
    cout << count1 << " " << count2 << endl; 

    while (icount1 < count1 && icount2 < count2) {
        vert1 = nebr1[icount1]; 
        vert2 = nebr2[icount2]; 
        icount1 += (vert1 <= vert2);
        icount2 += (vert1 >= vert2);
        tc += (vert1 == vert2);
        if (vert1 == vert2) cout << vert1 << endl;
    }
	return tc;
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
    string inputfile;
	vertex_t vert_count;
	int arg = -1;
    
	while ((o = getopt (argc, argv, "s:o:hi:j:m:v:a:")) != -1) {
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

    
    double start, end;
	index_t tc_count = 0;
  
    switch(job) {
    case 0:
        start = mywtime();
        csr_from_file(inputfile, vert_count);
        end = mywtime();
        cout << "read time = " << end - start << endl;
        
        start = mywtime();
        bfs(arg);
        end = mywtime();
        cout << "BFS CSR time = " << end-start << endl;
        break;    
    case 1:
        start = mywtime();
        csr_from_file(inputfile, vert_count);
        end = mywtime();
        cout << "read time = " << end - start << endl;
        
        start = mywtime();
        pagerank(arg);
        end = mywtime();
        cout << "PageRank time = " << end-start << endl;
        break;    
    case 2:
        start = mywtime();
        csr_from_file(inputfile, vert_count);
        end = mywtime();
        cout << "read time = " << end - start << endl;
        
        start = mywtime();
        pagerank_async(arg);
        end = mywtime();
        cout << "PageRank time = " << end-start << endl;
        break; 
    case 3:
        start = mywtime();
        rank_by_degree(inputfile, vert_count);
        end = mywtime();
        cout << "read time = " << end - start << endl;
        
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

