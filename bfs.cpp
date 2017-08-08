#include <algorithm>
#include "graph.h"
#include "wtime.h"
#include "sgraph.h"
#include "p_sgraph.h"

using std::swap;
void
pgraph_t::bfs(sgraph_t** sgraph_out, sgraph_t** sgraph_in, sid_t root)
{
	int				level      = 1;
	int				top_down   = 1;
	sid_t			frontier   = 0;
	index_t			todo	   = 0;
	index_t			edge_count = 1024;
    
	srset_t* level_array = new 	srset_t;
	level_array->full_setup(sgraph_in, eLevelarray);
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

				vid_t v_count = rset->get_wcount();
				uint8_t* status = rset->get_levelarray();
				beg_pos_t* graph = sgraph_out[tid]->get_begpos();

                //Get the frontiers
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

				vid_t v_count = rset->get_wcount();
				uint8_t* status = rset->get_levelarray();
				beg_pos_t* graph = sgraph_out[tid]->get_begpos();
				
				//Get the frontiers
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
							status[v] = level + 1;
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
		
		if (todo >= 0.03*edge_count) {//|| level == 2
			top_down = false;
		} else {
            top_down = true;
        }
		++level;
	} while (frontier);
}

/*
void
p_pgraph_t::bfs(p_sgraph_t** sgraph_out, p_sgraph_t** sgraph_in, sid_t root)
{
	int				level      = 1;
	int				top_down   = 1;
	sid_t			frontier   = 0;
	index_t			todo	   = 0;
	index_t			edge_count = 1024;
    
	srset_t* level_array = new 	srset_t;
	level_array->full_setup(sgraph_in, eLevelarray);
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

				vid_t v_count = rset->get_wcount();
				uint8_t* status = rset->get_levelarray();
				beg_pos_t* graph = sgraph_out[tid]->get_begpos();

                //Get the frontiers
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

				vid_t v_count = rset->get_wcount();
				uint8_t* status = rset->get_levelarray();
				beg_pos_t* graph = sgraph_out[tid]->get_begpos();
				
				//Get the frontiers
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
							status[v] = level + 1;
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
		
		if (todo >= 0.03*edge_count) {//|| level == 2
			top_down = false;
		} else {
            top_down = true;
        }
		++level;
	} while (frontier);
}
*/
typedef float rank_t;

void pgraph_t::pagerank(sgraph_t** sgraph_out, sgraph_t** sgraph_in, int iteration_count)
{
	srset_t* rank_array = new srset_t;
	srset_t* prior_rank_array = new srset_t;
	rank_array->full_setup(sgraph_in, eFloatarray);
	prior_rank_array->full_setup(sgraph_in, eFloatarray);
	
	srset_t* degree_array = new srset_t;
	degree_array->full_setup(sgraph_in, eFloatarray);//
	
	tid_t iset_count = rank_array->get_rset_count();
	
	rank_t	inv_v_count = 0.15;//1.0f/vert_count;
	
    double start = mywtime();
	
	//initialize the rank, and get the degree information
	for (tid_t i = 0; i < iset_count; ++i) {
		rset_t* rset = prior_rank_array->rset + i;
		rset_t* rset1 = degree_array->rset + i;
		//get the graph where we will traverse
		tid_t        tid = rset->get_tid();
		if (0 == sgraph_in[tid]) continue;

		float* prior_pr = rset->get_floatarray();
		float* dset = rset1->get_floatarray();
		uint32_t degree = 0;
		
		vid_t v_count = rset->get_wcount();
		beg_pos_t* graph = sgraph_out[tid]->get_begpos();
		for (vid_t v = 0; v < v_count; ++v) {
			degree = graph[v].get_nebrcount();
			if (degree != 0) {
				dset[v] = 1.0f/degree;
				prior_pr[v] = inv_v_count;//XXX
			} else {
				dset[v] = 0;
				prior_pr[v] = 0;
			}
		}
	}

	//let's run the pagerank
	for (int iter_count = 0; iter_count < iteration_count; ++iter_count) {
		//#pragma omp parallel
		{
			float rank;
			for (tid_t i = 0; i < iset_count; ++i) {
				rset_t* rset = rank_array->rset + i;
		        rset_t* rset1 = degree_array->rset + i;
				
				//get the graph where we will traverse
				tid_t        tid = rset->get_tid();
				if (0 == sgraph_in[tid]) continue;

				float* pr = rset->get_floatarray();
				float* dset = rset1->get_floatarray();
				
                vid_t v_count = rset->get_wcount();
				beg_pos_t* graph = sgraph_in[tid]->get_begpos();

				//#pragma omp for schedule (guided) nowait
				for (vid_t v = 0; v < v_count; v++) {
					sid_t* adj_list = graph[v].get_adjlist();
					vid_t nebr_count = adj_list[0];
					++adj_list;
					rank = 0.0f;
					
					//traverse the adj list
					for (vid_t k = 0; k < nebr_count; ++k) {
						rank += prior_rank_array->get_floatvalue(adj_list[k]);
					}

					if (iter_count != iteration_count -1)	
						pr[v] = (0.15 + 0.85*rank)*dset[v];
					else 
						pr[v] = (0.15 + 0.85*rank);
				}
			}
		}
        swap(prior_rank_array, rank_array);
	}
	
    double end = mywtime();

	cout << "Iteration time = " << end - start << endl;
	cout << endl;
}
