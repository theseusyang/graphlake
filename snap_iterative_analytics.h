#pragma once


#include "graph.h"
#include "wtime.h"

#include "sgraph.h"
#include "p_sgraph.h"

using std::max;

template<class T>
void
snap_bfs(vert_table_t<T>* graph_out, vert_table_t<T>* graph_in, 
      vid_t v_count, index_t edge_count, uint8_t* status, snapid_t snap_id, sid_t root)
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
			//#pragma omp parallel reduction (+:todo) reduction(+:frontier)
			{
                sid_t sid;
                vert_table_t<T>* graph  = graph_out;
                //Get the frontiers
				//#pragma omp for schedule (guided) nowait
				for (vid_t v = 0; v < v_count; v++) {
					if (status[v] != level) continue;
					
                    snapT_t<T>*snap_blob = graph[v].get_snapblob();
					T* adj_list = snap_blob->adj_list;
					
                    vid_t nebr_count;
                    if (snap_id >= snap_blob->snap_id) {
                        nebr_count = snap_blob->degree; 
                    } else {
                        snap_blob = snap_blob->prev;
                        while (snap_blob->prev && snap_id < snap_blob->prev->snap_id) {
                            snap_blob = snap_blob->prev;
                        }
                        nebr_count = snap_blob->degree; 
                    }
					
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
			#pragma omp parallel reduction (+:todo) reduction(+:frontier)
			{
                sid_t  sid;
				vert_table_t<T>* graph = graph_in;
				
				//Get the frontiers
				#pragma omp for schedule (guided) nowait
				for (vid_t v = 0; v < v_count; v++) {
					if (status[v] != 0) continue;
					
                    snapT_t<T>*snap_blob = graph[v].get_snapblob();
					T* adj_list = snap_blob->adj_list;
					
                    vid_t nebr_count;
                    if (snap_id >= snap_blob->snap_id) {
                        nebr_count = snap_blob->degree; 
                    } else {
                        snap_blob = snap_blob->prev;
                        while (snap_blob->prev && snap_id < snap_blob->prev->snap_id) {
                            snap_blob = snap_blob->prev;
                        }
                        nebr_count = snap_blob->degree; 
                    }

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

struct mbfs_status_t {
    uint8_t status[2];
};

template<class T>
void
multisnap_bfs(vert_table_t<T>* graph_out, vert_table_t<T>* graph_in, 
      vid_t v_count, index_t edge_count, snapid_t snap_id1, snapid_t snap_id2, sid_t root)
{
	int				level      = 1;
	int				top_down   = 1;
	sid_t			frontier   = 0;
	index_t			todo	   = 0;
    snapid_t        snap_count = snap_id2 - snap_id1 + 1;
    
    mbfs_status_t* mbfs = (mbfs_status_t*) calloc(v_count, sizeof(mbfs_status_t));
    uint8_t* bitmap = (uint8_t*)calloc(v_count, sizeof(uint8_t));
    uint8_t* bitmap1 = (uint8_t*)calloc(v_count, sizeof(uint8_t));
    uint8_t* bitmap2 = (uint8_t*)calloc(v_count, sizeof(uint8_t));

    for(snapid_t i = 0; i < snap_count; ++i) {
        mbfs[root].status[i] = level;
        bitmap[root] = 3;//2 snapshots
        bitmap1[root] = 3;//2 snapshots
        bitmap2[root] = 3;//2 snapshots
    }
    
	do {
		frontier = 0;
		todo = 0;
		double start = mywtime();
		if (top_down) {
			//#pragma omp parallel reduction (+:todo) reduction(+:frontier)
			{
                sid_t sid;
                vert_table_t<T>* graph  = graph_out;
                uint8_t local_bitmap = 0;
                degree_t degree[2];
                snapid_t snap_id = snap_id2;
                snapid_t snap = 0;
                //Get the frontiers
				//#pragma omp for schedule (guided) nowait
				for (vid_t v = 0; v < v_count; v++) {
					if (bitmap[v] == 0) continue;
					
                    snapT_t<T>*snap_blob = graph[v].get_snapblob();
					T* adj_list = snap_blob->adj_list;
					
                    degree_t nebr_count = 0;
                    for (snap_id = snap_id2; snap_id >= snap_id1; --snap_id) {
                        snap = snap_id - snap_id1;
                        if (snap_id >= snap_blob->snap_id) {
                            degree[snap] = snap_blob->degree;
                            nebr_count = max(nebr_count, snap_blob->degree);
                        } else {
                            snap_blob = snap_blob->prev;
                            while ((snap_blob->prev) && (snap_id < snap_blob->prev->snap_id)) {
                                snap_blob = snap_blob->prev;
                            }
                            degree[snap] = snap_blob->degree;
                            nebr_count = max(nebr_count, snap_blob->degree);
                        }
                    }
					
                    ++adj_list;
					todo += nebr_count;
				    
					//traverse the adj list
					for (vid_t k = 0; k < nebr_count; ++k) {
                        sid = get_nebr(adj_list, k);
						for (snap_id = snap_id2; snap_id >= snap_id1; --snap_id) {
                            snap = snap_id - snap_id1;
                            if ((0 == mbfs[sid].status[snap]) && k < degree[snap]) {
                                mbfs[sid].status[snap] = level + 1;
                                local_bitmap |= (1 << snap);
                                ++frontier;
                            }
                        }
                        __sync_fetch_and_or(bitmap2 + sid, local_bitmap);
                        local_bitmap = 0;
					}
				}
			}
		} 
        /*
        else {//bottom up
			#pragma omp parallel reduction (+:todo) reduction(+:frontier)
			{
                sid_t  sid;
				vert_table_t<T>* graph = graph_in;
				
				//Get the frontiers
				#pragma omp for schedule (guided) nowait
				for (vid_t v = 0; v < v_count; v++) {
					if (status[v] != 0) continue;
					
                    snapT_t<T>*snap_blob = graph[v].get_snapblob();
					T* adj_list = snap_blob->adj_list;
					
                    vid_t nebr_count;
                    if (snap_id >= snap_blob->snap_id) {
                        nebr_count = snap_blob->degree; 
                    } else {
                        snap_blob = snap_blob->prev;
                        while (snap_blob->prev && snap_id < snap_blob->prev->snap_id) {
                            snap_blob = snap_blob->prev;
                        }
                        nebr_count = snap_blob->degree; 
                    }

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
		}*/
		double end = mywtime();
	
		cout << "Top down = " << top_down;
		cout << " Level = " << level;
        cout << " Frontier Count = " << frontier;
        cout << " ToDo = " << todo;
		cout << " Time = " << end - start;
		cout << endl;

        if(frontier) {
            for (vid_t v = 0; v < v_count; v++) {
                bitmap[v] = bitmap1[v] ^ bitmap2[v]; 
                bitmap1[v] = bitmap2[v]; 
            }
        }
		
		if (todo >= 0.03*edge_count) {//|| level == 2
			top_down = true;
		} else {
            top_down = true;
        }
		++level;
	} while (frontier);

    //print the BFS for snap2
    vid_t vid_count = 0;
    for (int l = 1; l < level; ++l) {
        vid_count = 0;
        for (vid_t v = 0; v < v_count; ++v) {
            if (mbfs[v].status[snap_id2 -  snap_id1] == l) ++vid_count;
        }
        cout << " Level = " << l << " count = " << vid_count << endl;
    }
}
