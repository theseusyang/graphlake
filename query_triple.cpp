
#include "assert.h"
#include "query_triple.h"
#include "graph.h"



status_t
query_triple::execute()
{
    direction_t direction;
    sid_t sid;
    tid_t tid;
    srset_t* iset;
    srset_t* oset;
    
    //get the property id
    propid_t pid = g->get_pid(pred);
    if (pid == INVALID_PID) return eInvalidPID; 
    
    int value = (src_qid == NO_QID) + ((dst_qid == NO_QID) << 1);

    switch(value) {
        case 0:
            //src and dst both are variable
            //Some other query triple would have filled one, 
            //see query_plan
            if (query_plan == eOutward) {
                direction = eout;
                iset = q->get_srset(src_qid);
                oset = q->get_srset(dst_qid);

            } else {
                assert(query_plan == eInward);
                direction = ein;
                iset = q->get_srset(dst_qid);
                oset = q->get_srset(src_qid);
            }
            break;
        case 1:
            //src is given, dst is variable
            direction = eout;
            sid = g->get_sid(src);
            if (sid == INVALID_SID) return eInvalidVID;
            tid = TO_TID(sid);
            iset = new srset_t; 
            iset->setup(tid);
            iset->rset->setup_frontiers(tid, 1);
            iset->add_frontier(sid);
            
            oset = q->get_srset(dst_qid);
            break;
        case 2:
            //dst is given, src is variable
            direction = ein;
            sid = g->get_sid(dst);
            if (sid == INVALID_SID) return eInvalidVID;
            tid = TO_TID(sid);
            
            iset = new srset_t; 
            iset->setup(tid);
            iset->rset->setup_frontiers(tid, 1);
            iset->add_frontier(sid);
            
            oset = q->get_srset(src_qid);
            break;
        case 3:
            //src is given, dst is given
            //XXX pred could be variable??
            assert(0);
            break;
        default:
            assert(0);
            break;
    }
    
    if (traverse == eTransform) {
        g->p_info[pid]->transform(iset, oset, direction);

    } else if (traverse == eExtend) {
        g->p_info[pid]->extend(iset, oset, direction);
    }
    
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
