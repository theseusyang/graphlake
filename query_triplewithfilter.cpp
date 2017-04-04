#include "query_triplewithfilter.h"
#include "graph.h"


status_t
query_triplewithfilter::execute()
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
    
    int magic = (src_qid == NO_QID) + ((dst_qid == NO_QID) << 1);

    switch(magic) {
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
    
    g->p_info[pid]->transform_withfilter(&iset, oset, direction, &filter_info);
	return eOK;
}
