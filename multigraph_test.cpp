
#include <iostream>
#include "all.h"
#include "util.h"
#include "multi_graph.h"

using namespace std;

void run_sample_wls_query()
{
    //0th index is: See schema
    typekv_t* typekv = g->get_typekv();
    
    //First graph is 
    pgraph_t<sid_t>* proc2parent = (pgraph_t<sid_t>*) g->get_sgraph(1);
    
    //second graph is 
    pgraph_t<wls_dst_t>* user2proc = (pgraph_t<wls_dst_t>*)g->get_sgraph(2);
    
    string user_name = "Comp607982$@Domain001"; //"user@domain";
    sid_t user_id = typekv->get_sid(user_name.c_str());

    degree_t proc_count = user2proc->get_degree_out(user_id);
    if (proc_count== 0) {
        cout << "the user has no process" << endl;
    }

    wls_dst_t* procs = (wls_dst_t*)calloc(sizeof(wls_dst_t), proc_count);
    user2proc->get_nebrs_out(user_id, procs);

    for(degree_t i = 0; i < proc_count; ++i) {
        cout << typekv->get_vertex_name(get_sid(procs[i])) << ", ";
    }

    cout << endl << endl;


    sid_t first_proc_id = get_sid(procs[0]);
    degree_t parent_count = proc2parent->get_degree_out(first_proc_id);

    if (0 == parent_count) {
        cout << "No Parent present" << endl;
    }
    cout << "Parent of First process is: ";
    
    sid_t* parent_procs = (sid_t*)calloc(sizeof(sid_t), parent_count);
    proc2parent->get_nebrs_out(first_proc_id, parent_procs);

    for(degree_t i = 0; i < parent_count; i++) {
        cout << typekv->get_vertex_name(parent_procs[i]) << ", ";
    }
    cout << endl;
   
}

template <class T>
void update_fromtext_multi(const string& idir, const string& odir,
                     typename callback<T>::parse_fn_t parsefile_fn)
{
    multi_graph_t manager;
    THD_COUNT = omp_get_max_threads() - 1;
    manager.schema();
    //do some setup for plain graphs
    manager.prep_graph_fromtext(idir, odir, parsefile_fn); 
    run_sample_wls_query();    
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
