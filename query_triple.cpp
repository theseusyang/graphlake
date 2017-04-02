#include "query_triple.h"
#include "query_clause.h"
#include "graph.h"


status_t
query_triple::execute()
{
    //get the property id
    propid_t pid = g->get_pid(pred);
    if (pid == INVALID_PID) return eInvalidPID; 
	
    sid_t sid = g->get_sid(src);
    if (sid == INVALID_SID) return eInvalidVID;

    tid_t tid = TO_TID(sid);
    sflag_t flag = TID_TO_SFLAG(tid);
    
    srset_t iset;
    iset.full_setup(flag);
    iset.add_frontier(sid);
    
    srset_t* oset = q->get_srset(dst_qid);
    g->p_info[pid]->transform(&iset, oset, eout);
    
    return eOK;
}

void
query_triple::to_string()
{
	cout << "(";
	query_node* node = get_child();
	if (node) {
		node->to_string();
	}
	cout << src << " " << pred << " " << dst << ")" << endl;
    
	node = get_sibling();
	while (node) {
		node->to_string();
		node = node->get_sibling();
	}
}
