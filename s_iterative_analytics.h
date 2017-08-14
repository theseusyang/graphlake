#pragma once

#include "graph.h"
#include "wtime.h"

#include "sgraph.h"
#include "p_sgraph.h"

template<class T>
void
s_bfs(vert_table_t<T>* graph_out, vert_table_t<T>* graph_in, 
      vid_t v_count, index_t edge_count, uint8_t* status, sid_t root)
{
	int				level      = 1;
	int				top_down   = 1;
	sid_t			frontier   = 0;
	index_t			todo	   = 0;
    
	status[root] = level;
    
	do {
		frontier = 0;
		todo = 0;
		double start = mywtime();
		if (top_down) {
			//#pragma omp parallel \
		   	//reduction (+:todo) reduction(+:frontier)
			{
                sid_t sid;
                vert_table_t<T>* graph  = graph_out;
                //Get the frontiers
				//#pragma omp for schedule (guided) nowait
				for (vid_t v = 0; v < v_count; v++) {
					if (status[v] != level) continue;
					
					T* adj_list = graph[v].get_adjlist();
					//vid_t nebr_count = get_nebrcount1(adj_list);
					vid_t nebr_count = graph[v].degree;
					++adj_list;
					todo += nebr_count;
				    
					//traverse the adj list
					for (vid_t k = 0; k < nebr_count; ++k) {
                        sid = get_nebr(adj_list, k);
						if (status[sid] == 0) {
							status[sid] = level + 1;
							++frontier;
						}
					}
				}
			}
		} else {//bottom up
			#pragma omp parallel \
		   	reduction (+:todo) reduction(+:frontier)
			{
                sid_t  sid;
				vert_table_t<T>* graph = graph_in;
				
				//Get the frontiers
				#pragma omp for schedule (guided) nowait
				for (vid_t v = 0; v < v_count; v++) {
					if (status[v] != 0) continue;
					
					T* adj_list = graph[v].get_adjlist();
					vid_t nebr_count = get_nebrcount1(adj_list);
					//vid_t nebr_count = graph[v].degree;
					++adj_list;
					todo += nebr_count;
					
					//traverse the adj list
					for (vid_t k = 0; k < nebr_count; ++k) {
                        sid = get_nebr(adj_list, k);
						if (status[sid] == level) {
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
        cout << " Frontier Count = " << frontier;
        cout << " ToDo = " << todo;
		cout << " Time = " << end - start;
		cout << endl;
		
		if (todo >= 0.03*edge_count) {//|| level == 2
			top_down = false;
		} else {
            top_down = true;
        }
		++level;
	} while (frontier);
}
