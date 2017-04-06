#include "query_triplewithfilter.h"
#include "graph.h"


status_t
query_triplewithfilter::execute()
{
    direction_t direction;
    sid_t sid;
    tid_t tid;
    sflag_t flag;
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
            flag = TID_TO_SFLAG(tid);
            iset = new srset_t; 
            iset->full_setup(flag);
            iset->add_frontier(sid);
            
            oset = q->get_srset(dst_qid);
            break;
        case 2:
            //dst is given, src is variable
            direction = ein;
            sid = g->get_sid(dst);
            if (sid == INVALID_SID) return eInvalidVID;
            tid = TO_TID(sid);
            flag = TID_TO_SFLAG(tid);
            
            iset = new srset_t; 
            iset->full_setup(flag);
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
    
    g->p_info[pid]->transform_withfilter(iset, oset, direction, &filter_info);
	
    return eOK;
}
