#pragma once

#include "graph.h"
#include "wtime.h"

#include "sgraph.h"
#include "p_sgraph.h"

template <class T>
degree_t* create_degreesnap(vert_table_t<T>* graph, vid_t v_count, snapid_t snap_id)
{
    degree_t*  degree_array = (degree_t*)calloc(v_count, sizeof(degree_t));

    snapT_t<T>*   snap_blob = 0;
    vid_t        nebr_count = 0;

    for (vid_t v = 0; v < v_count; ++v) {
        snap_blob = graph[v].get_snapblob();
        if (0 == snap_blob) { continue; }
        
        nebr_count = 0;
        if (snap_id >= snap_blob->snap_id) {
            nebr_count = snap_blob->degree; 
        } else {
            snap_blob = snap_blob->prev;
            while (snap_blob && snap_id < snap_blob->snap_id) {
                snap_blob = snap_blob->prev;
            }
            if (snap_blob) {
                nebr_count = snap_blob->degree; 
            }
        }
        degree_array[v] = nebr_count;
    }
    return degree_array;
}


template<class T>
void
ext_bfs(vert_table_t<T>* graph_out, degree_t* degree_out, 
        vert_table_t<T>* graph_in, degree_t* degree_in,
        snapshot_t* snapshot, index_t marker, edgeT_t<T>* edges,
        vid_t v_count, index_t edge_count, 
        uint8_t* status, sid_t root)
{
	int				level      = 1;
	int				top_down   = 1;
	sid_t			frontier   = 0;
	index_t			todo	   = 0;
    index_t         old_marker = snapshot->marker;
    
	status[root] = level;
    
	do {
		frontier = 0;
		todo = 0;
		double start = mywtime();
		//#pragma omp parallel reduction (+:todo) reduction(+:frontier)
		{
		    if (top_down) {
                sid_t sid;
                vert_table_t<T>* graph  = graph_out;
				
                #pragma omp for schedule (guided) nowait
				for (vid_t v = 0; v < v_count; v++) {
					if (status[v] != level) continue;
					
					T* adj_list = graph[v].get_adjlist();
					vid_t nebr_count = degree_out[v];
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
			} else {//bottom up
                sid_t  sid;
				vert_table_t<T>* graph = graph_in;
				
				#pragma omp for schedule (guided) nowait
				for (vid_t v = 0; v < v_count; v++) {
					if (status[v] != 0) continue;
					
					T* adj_list = graph[v].get_adjlist();
					vid_t nebr_count = degree_in[v];
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

            //on-the-fly snapshots should process this
            if (marker != 0) {
                #pragma omp for schedule (guided) nowait 
                for (index_t i = old_marker; i < marker; ++i) {
                    vid_t src = edges[i].src_id;
                    vid_t dst = edges[i].dst_id;
                    if (status[src] == 0 && status[dst] == level) {
                        status[src] = level + 1;
                        ++frontier;
                    } 
                    if (status[src] == level && status[dst] == 0) {
                        status[dst] = level + 1;
                        ++frontier;
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
		
		if (frontier >= 0.10*v_count) {//|| level == 2
			top_down = false;
		} else {
            top_down = true;
        }
		++level;
	} while (frontier);
}
