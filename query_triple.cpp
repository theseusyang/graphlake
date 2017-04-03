
#include "assert.h"
#include "query_triple.h"
#include "graph.h"



status_t
query_triple::execute()
{
    direction_t direction;
    sid_t sid;
    tid_t tid;
    sflag_t flag;
    srset_t iset;
    srset_t* oset;
    
    //get the property id
    propid_t pid = g->get_pid(pred);
    if (pid == INVALID_PID) return eInvalidPID; 
    
    int value = (src_qid == NO_QID) + ((dst_qid == NO_QID) << 1);

    switch(value) {
        case 0:
            //src is given, dst is given
            //XXX pred is variable
            assert(0);
            break;
        case 1:
            //src is given, dst is variable
            direction = eout;
            sid = g->get_sid(src);
            if (sid == INVALID_SID) return eInvalidVID;
            tid = TO_TID(sid);
            flag = TID_TO_SFLAG(tid);
            
            iset.full_setup(flag);
            iset.add_frontier(sid);
            
            oset = q->get_srset(dst_qid);
            break;
        case 2:
            //dst is given, src is variable
            direction = ein;
            sid = g->get_sid(dst);
            if (sid == INVALID_SID) return eInvalidVID;
            tid = TO_TID(sid);
            flag = TID_TO_SFLAG(tid);
            
            iset.full_setup(flag);
            iset.add_frontier(sid);
            
            oset = q->get_srset(src_qid);
            break;
        case 3:
            assert(0);
            break;
        default:
            assert(0);
            break;
    }
    
    g->p_info[pid]->transform(&iset, oset, direction);
    
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
