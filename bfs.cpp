#include "graph.h"
#include "wtime.h"

void
pgraph_t::bfs(sgraph_t** sgraph_out, sgraph_t** sgraph_in, sid_t root)
{
	int				level      = 1;
	int				top_down   = 1;
	sid_t			frontier   = 0;
	index_t			todo	   = 0;
	uint8_t*        status	   = 0;
	vid_t           v_count    = 0;
	index_t			edge_count = (1<< 28);
    
	srset_t* level_array = new 	srset_t;
	level_array->full_setup(sgraph_in);
	level_array->set_8bitvalue(root, level);
	
	tid_t iset_count = level_array->get_rset_count();
    
	do {
		frontier = 0;
		todo = 0;
		double start = mywtime();
		if (top_down) {
			#pragma omp parallel \
		   	reduction (+:todo) reduction(+:frontier)
			{
			for (tid_t i = 0; i < iset_count; ++i) {
				rset_t* rset = level_array->rset + i;
				
				//get the graph where we will traverse
				tid_t        tid = rset->get_tid();
				if (0 == sgraph_out[tid]) continue;

				v_count = rset->get_vcount();
				status = rset->get_levelarray();
				beg_pos_t* graph = sgraph_out[tid]->get_begpos();
				//Get the frontiers
				vid_t     frontier;
				#pragma omp for schedule (guided) nowait
				for (vid_t v = 0; v < v_count; v++) {
					if (status[v] != level) continue;
					
					sid_t* adj_list = graph[v].get_adjlist();
					vid_t nebr_count = adj_list[0];
					++adj_list;
					todo += nebr_count;
					
					//traverse the adj list
					for (vid_t k = 0; k < nebr_count; ++k) {
						if (level_array->get_8bitvalue(adj_list[k]) == 0) {
							level_array->set_8bitvalue(adj_list[k], level + 1);
							++frontier;
						}
					}
				}
			}
			}
		} else {//bottom up
			#pragma omp parallel \
		   	reduction (+:todo) reduction(+:frontier)
			{
			for (tid_t i = 0; i < iset_count; ++i) {
				rset_t* rset = level_array->rset + i;
				
				//get the graph where we will traverse
				tid_t        tid = rset->get_tid();
				if (0 == sgraph_in[tid]) continue;

				v_count = rset->get_vcount();
				status = rset->get_levelarray();
				beg_pos_t* graph = sgraph_out[tid]->get_begpos();
				
				//Get the frontiers
				vid_t     frontier;
				#pragma omp for schedule (guided) nowait
				for (vid_t v = 0; v < v_count; v++) {
					if (status[v] != 0) continue;
					
					sid_t* adj_list = graph[v].get_adjlist();
					vid_t nebr_count = adj_list[0];
					++adj_list;
					todo += nebr_count;
					
					//traverse the adj list
					for (vid_t k = 0; k < nebr_count; ++k) {
						if (level_array->get_8bitvalue(adj_list[k]) == level) {
							level_array->set_8bitvalue(v, level + 1);
							++frontier;
							break;
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
		
		if (todo >= 0.03*edge_count || level == 2) {
			top_down = false;
		} else {
            top_down = true;
        }
		++level;
	} while (frontier);
}
