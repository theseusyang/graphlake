#include <getopt.h>
#include <iostream>
#include <dirent.h>

#include "all.h"
#include "csv_to_edge.h"

extern vid_t v_count;


template<class T>
void
llama_bfs(ext_vunit_t* v_units, int etf, vid_t v_count, uint8_t* status, sid_t root)
{
	int		level      = 1;
	sid_t	frontier   = 0;
    char*   edges = 0;
    size_t   size = fsize(etf);
    
    if (size == -1L) {
        assert(0);
    }

    edges = (char*)mmap(0, size, PROT_READ, MAP_PRIVATE, etf, 0);
    if (MAP_FAILED == edges) {
        assert(0);
    }

	double start1 = mywtime();
	status[root] = level;
    
	do {
		frontier = 0;
		double start = mywtime();
		#pragma omp parallel reduction(+:frontier)
		{
            sid_t sid;
            degree_t durable_degree = 0;
            T*            adj_list  = 0;
            index_t         offset  = 0;
            ext_vunit_t*     v_unit  = 0;
            
            durable_adjlist_t<T>* durable_adjlist = 0;
				
            #pragma omp for nowait
            for (vid_t v = 0; v < v_count; v++) {
                if (status[v] != level) continue;
                v_unit = v_units+v;
                if (0 == v_unit) continue;

                durable_degree = v_unit->count;
                offset = v_unit->offset;
                durable_adjlist = (durable_adjlist_t<T>*)(edges + offset);
                adj_list = durable_adjlist->get_adjlist();
                
                //traverse the adj list
                for (vid_t k = 0; k < durable_degree; ++k) {
                    sid = get_nebr(adj_list, k);
                    if (status[sid] == 0) {
                        status[sid] = level + 1;
                        ++frontier;
                    }
                }
            }
        }

		double end = mywtime();
	
		cout << " Level = " << level
             << " Frontier Count = " << frontier
		     << " Time = " << end - start
		     << endl;
	
		++level;
	} while (frontier);
		
    double end1 = mywtime();
    cout << "BFS Time = " << end1 - start1 << endl;

    for (int l = 1; l < level; ++l) {
        vid_t vid_count = 0;
        #pragma omp parallel for reduction (+:vid_count) 
        for (vid_t v = 0; v < v_count; ++v) {
            if (status[v] == l) ++vid_count;
        }
        cout << " Level = " << l << " count = " << vid_count << endl;
    }
}

//Only directed graph
//LLAMA uses mmap, so we are writing new hook to be fair
void llama_test_bfs(const string& odir)
{
    double start = mywtime();
    // READ vtable
    string vtfile = odir + "friend0out.vtable";
    int vtf = open(vtfile.c_str(), O_RDONLY);
    assert(-1 != vtf);

    off_t size = fsize(vtf);
    if (size == -1L) {
        assert(0);
    }
    vid_t count = (size/sizeof(disk_vtable_t));
	vid_t vid = 0;
	ext_vunit_t* v_unit = (ext_vunit_t*)calloc(v_count, sizeof(ext_vunit_t));
    disk_vtable_t* dvt =  (disk_vtable_t*)calloc((1<<24), sizeof(disk_vtable_t));

    //read in batches
    while (count != 0 ) {
        //vid_t read_count = read(dvt, sizeof(disk_vtable_t), dvt_max_count, vtf);
        vid_t read_count = read(vtf, dvt, sizeof(disk_vtable_t)*(1<<24));
        read_count /= sizeof(disk_vtable_t); 

        for (vid_t v = 0; v < read_count; ++v) {
			vid = dvt[v].vid;
			v_unit[vid].offset     = dvt[v].file_offset;
			v_unit[vid].count      = dvt[v].count;
            v_unit[vid].del_count  = dvt[v].del_count;
        }
        count -= read_count;
    }
   
    free(dvt);
    
    // READ etable
    string etfile = odir + "friend0out.etable";
    int etf = open(etfile.c_str(), O_RDONLY);
    assert(-1 != etf);
    

    //Run BFS
    uint8_t* level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    llama_bfs<sid_t>(v_unit, etf, v_count, level_array, 1);
    
    double end = mywtime();
    cout << "total time = " << end - start << endl;
    return ;
}
