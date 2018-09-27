
#include <iostream>
#include "all.h"
#include "util.h"
#include "multi_graph.h"

using namespace std;

template <class T>
void update_fromtext_multi(const string& idir, const string& odir,
                     typename callback<T>::parse_fn_t parsefile_fn)
{
    multi_graph_t manager;
    THD_COUNT = omp_get_max_threads() - 1;
    manager.schema();
    //do some setup for plain graphs
    manager.prep_graph_fromtext(idir, odir, parsefile_fn); 
    //manager.run_bfs();    
}

void multigraph_test(vid_t v_count1, const string& idir, const string& odir, int job)
{
    switch(job) {
        case 0://text to our format
            update_fromtext_multi<wls_dst_t>(idir, odir, parsefile_and_multi_insert);
            break;
        default:
            break;
    }
}
