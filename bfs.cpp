#include "graph.h"
#include "bitmap.h"


void
pgraph_t::bfs(sgraph_t* sgraph_out, sgraph_t* sgraph_in, sid_t root)
{
	int				level = 1;
	int				top_down = 1;
	vertex_t		frontier = 0;
	index_t			todo = 0;
	uint8_t*        status = 0;
	vid_t           v_count = 0;
	
	index_t		edge_count = (1<< 28);
    srset_t* level_array = new 	srset_t;
	level_array->full_setup(sgraph_in);
	tid_t iset_count = level_array->get_rset_count();
	
	level_array.set_8bitvalue(root, level);
	
    
	for (tid_t i = 0; i < iset_count; ++i) {
        rset = iset->rset + i;
        
		//get the graph where we will traverse
        tid_t        tid = rset->get_tid();
        if (0 == sgraph[tid]) continue;

        v_count = rset->get_vcount();
        status = rset->get_8bitarray();
        beg_pos_t* graph = sgraph[tid]->get_begpos();
        
		//Get the frontiers
        vid_t     frontier;
        for (vid_t v = 0; v < v_count; v++) {
            if (status[v] != level) continue;
			
            sid_t* adj_list = graph[v].get_adjlist();
            vid_t nebr_count = adj_list[0];
            ++adj_list;
            
            //traverse the adj list
            for (vid_t k = 0; k < nebr_count; ++k) {
				if (level_array.get_8bitvalue(adj_list[k]) == 0) {
					level_array.set_8bitvalue(adj_list[k], level + 1);
					++frontier;
				}
			}
        }
	}
	
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

	

}
