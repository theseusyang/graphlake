#pragma once

#include <algorithm>
#include "graph.h"
#include "wtime.h"

#include "sgraph.h"
#include "p_sgraph.h"

using std::min;

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
        //cout << v << " " << degree_array[v] << endl;
    }
    return degree_array;
}


template<class T>
void
ext_bfs(vert_table_t<T>* graph_out, degree_t* degree_out, 
        vert_table_t<T>* graph_in, degree_t* degree_in,
        snapshot_t* snapshot, index_t marker, edgeT_t<T>* edges,
        vid_t v_count, uint8_t* status, sid_t root)
{
	int				level      = 1;
	int				top_down   = 1;
	sid_t			frontier   = 0;
    degree_t      delta_degree = 0;
    index_t         old_marker = 0;

    if (snapshot) { 
        old_marker = snapshot->marker;
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
            degree_t nebr_count = 0;
            degree_t local_degree = 0;

            vert_table_t<T>* graph  = 0;
            T* adj_list = 0;
            T* local_adjlist = 0;
		    
            if (top_down) {
                graph  = graph_out;
				
                #pragma omp for schedule (guided) nowait
				for (vid_t v = 0; v < v_count; v++) {
					if (status[v] != level) continue;
					
                    adj_list = graph[v].get_adjlist();
                    durable_degree = 0;
                    if (0 != adj_list) {
                        durable_degree = get_nebrcount1(adj_list);
					    ++adj_list;
                    }
					nebr_count = degree_out[v];
				    //cout << "Nebr list of " << v <<" degree = " << nebr_count << endl;	
                    
                    //traverse the delta adj list
                    delta_degree = nebr_count - durable_degree;
				    //cout << "delta adjlist " << delta_degree << endl;	
                    delta_adjlist_t<T>* delta_adjlist = graph[v].delta_adjlist;
                    
                    while (delta_adjlist != 0 && delta_degree > 0) {
                        local_adjlist = delta_adjlist->get_adjlist();
                        local_degree = delta_adjlist->get_nebrcount();
                        degree_t i_count = min(local_degree, delta_degree);
                        for (degree_t i = 0; i < i_count; ++i) {
                            sid = get_nebr(local_adjlist, i);
                            if (status[sid] == 0) {
                                status[sid] = level + 1;
                                ++frontier;
                                //cout << " " << sid << endl;
                            }
                        }
                        delta_adjlist = delta_adjlist->get_next();
                        delta_degree -= local_degree;
                    }

                    degree_t k_count = min(nebr_count, durable_degree);
				    //cout << "durable adjlist " << durable_degree << endl;	
					//traverse the adj list
					for (vid_t k = 0; k < k_count; ++k) {
                        sid = get_nebr(adj_list, k);
						if (status[sid] == 0) {
							status[sid] = level + 1;
							++frontier;
                            //cout << " " << sid << endl;
						}
					}
				}
			} else {//bottom up
				graph = graph_in;
				
				#pragma omp for schedule (guided) nowait
				for (vid_t v = 0; v < v_count; v++) {
					if (status[v] != 0 ) continue;
					adj_list = graph[v].get_adjlist();
					nebr_count = degree_in[v];
                    durable_degree = 0;
                    if (0 != adj_list) {
                        durable_degree = get_nebrcount1(adj_list);
					    ++adj_list;
                    }
                    
                    //traverse the delta adj list
                    delta_degree = nebr_count - durable_degree;
                    delta_adjlist_t<T>* delta_adjlist = graph[v].delta_adjlist;
                    while (delta_adjlist != 0 && delta_degree > 0) {
                        local_adjlist = delta_adjlist->get_adjlist();
                        local_degree = delta_adjlist->get_nebrcount();
                        degree_t i_count = min(local_degree, delta_degree);
                        for (degree_t i = 0; i < i_count; ++i) {
                            sid = get_nebr(local_adjlist, i);
                            if (status[sid] == level) {
                                status[v] = level + 1;
                                ++frontier;
                                break;
                            }
                        }
                        delta_adjlist = delta_adjlist->get_next();
                        delta_degree -= local_degree;
                    }
					
                    if (status[v] == level + 1) continue;

					//traverse the adj list
                    degree_t k_count = min(nebr_count, durable_degree);
					for (vid_t k = 0; k < k_count; ++k) {
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
            //cout << "On the Fly" << endl;
            vid_t src, dst;
            #pragma omp for schedule (guided) nowait 
            for (index_t i = old_marker; i < marker; ++i) {
                src = edges[i].src_id;
                dst = edges[i].dst_id;
                if (status[src] == 0 && status[dst] == level) {
                    status[src] = level + 1;
                    ++frontier;
                    //cout << " " << src << endl;
                } 
                if (status[src] == level && status[dst] == 0) {
                    status[dst] = level + 1;
                    ++frontier;
                    //cout << " " << dst << endl;
                }
            }
        }

		double end = mywtime();
	
		cout << "Top down = " << top_down
		     << " Level = " << level
             << " Frontier Count = " << frontier
		     << " Time = " << end - start
		     << endl;
		
		if (frontier >= 0.05*v_count) {//|| level == 2
			top_down = false;
		} else {
            top_down = true;
        }
		++level;
	} while (frontier);
		
    double end1 = mywtime();
    cout << "Total Time = " << end1 - start1 << endl;

    for (int l = 1; l < level; ++l) {
        vid_t vid_count = 0;
        #pragma omp parallel for reduction (+:vid_count) 
        for (vid_t v = 0; v < v_count; ++v) {
            if (status[v] == l) ++vid_count;
        }
        cout << " Level = " << l << " count = " << vid_count << endl;
    }
}
