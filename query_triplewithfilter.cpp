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
            iset->set_status(sid);
            
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
            iset->set_status(sid);
            
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
    
    g->cf_info[pid]->transform_withfilter(iset, oset, direction, &filter_info);
	
    return eOK;
}

/******************* transform_withfilter ******************/
status_t cfinfo_t::transform_withfilter(srset_t* iset, srset_t* oset, direction_t direction, filter_info_t* graph)
{
    return eOK;
}

status_t ugraph_t::transform_withfilter(srset_t* iset, srset_t* oset, direction_t direction, filter_info_t* filter_info)
{
    int total_count = 0;
    if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
        return query_adjlist_td_filter(sgraph, flag1, flag2, iset, oset, filter_info);
    } else { //bottom up approach
        return query_adjlist_bu_filter(sgraph, flag2, iset, oset, filter_info);
    }
    return eOK;
}

//due to many2one structure, we give preference to bottom up approach
status_t many2one_t::transform_withfilter(srset_t* iset, srset_t* oset, direction_t direction, filter_info_t* filter_info)
{
    int total_count = 0;
    if (direction == eout) {
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td_filter(skv_out, flag1, flag2, iset, oset, filter_info);
        } else { //bottom up approach
            return query_adjlist_bu_filter(sgraph_in, flag2, iset, oset, filter_info);
        }
    } else {
        assert(direction == ein);
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td_filter(sgraph_in, flag2, flag1, iset, oset, filter_info);
        } else { //bottom up approach 
            return query_kv_bu_filter(skv_out, flag1, iset, oset, filter_info);
        }
    }
    return eOK;
}

status_t dgraph_t::transform_withfilter(srset_t* iset, srset_t* oset, direction_t direction, filter_info_t* filter_info)
{
    int total_count = 0;
    if (direction == eout) {
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td_filter(sgraph_out, flag1, flag2, iset, oset, filter_info);
        } else { //bottom up approach
            return query_adjlist_bu_filter(sgraph_in, flag2, iset, oset, filter_info);
        }
    } else {
        assert(direction == ein);
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td_filter(sgraph_in, flag2, flag1, iset, oset, filter_info);
        } else { //bottom up approach 
            return query_adjlist_bu_filter(sgraph_out, flag1, iset, oset, filter_info);
        }
    }
    return eOK;
}

status_t one2one_t::transform_withfilter(srset_t* iset, srset_t* oset, direction_t direction, filter_info_t* filter_info)
{
    int total_count = 0;
    if (direction == eout) {
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td_filter(skv_out, flag1, flag2, iset, oset, filter_info);
        } else { //bottom up approach
            return query_kv_bu_filter(skv_in, flag2, iset, oset, filter_info);
        }
    } else {
        assert(direction == ein);
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td_filter(skv_in, flag2, flag1, iset, oset, filter_info);
        } else { //bottom up approach 
            return query_kv_bu_filter(skv_out, flag1, iset, oset, filter_info);
        }
    }
    return eOK;
}

status_t one2many_t::transform_withfilter(srset_t* iset, srset_t* oset, direction_t direction, filter_info_t* filter_info)
{
    int total_count = 0;
    if (direction == eout) {
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td_filter(sgraph_out, flag1, flag2, iset, oset, filter_info);
        } else { //bottom up approach
            return query_kv_bu_filter(skv_in, flag2, iset, oset, filter_info);
        }
    } else {
        assert(direction == ein);
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td_filter(skv_in, flag2, flag1, iset, oset, filter_info);
        } else { //bottom up approach 
            return query_adjlist_bu_filter(sgraph_out, flag1, iset, oset, filter_info);
        }
    }
    return eOK;
}


////// filters ------------------------
status_t 
pgraph_t::query_adjlist_td_filter(sgraph_t* sgraph, sflag_t iflag, sflag_t oflag, 
                        srset_t* iset, srset_t* oset, filter_info_t* filter_info)
{
    tid_t    iset_count = iset->get_rset_count();
    rset_t*        rset = 0;

    //prepare the output 1,2;
    oset->full_setup(oflag);

    for (tid_t i = 0; i < iset_count; ++i) {
        rset = iset->rset + i;
        vid_t v_count = rset->get_vcount();
        vid_t* vlist = rset->get_vlist();
        
        //get the graph where we will traverse
        tid_t        tid = rset->get_tid();
        tid_t        pos = get_sindex(tid, iflag);
        tid_t  graph_tid = TO_TID(sgraph[pos].super_id);
        beg_pos_t* graph = sgraph[pos].beg_pos; 
        if (graph_tid != tid) continue;

        
        //Get the frontiers
        vid_t     frontier;
        for (vid_t v = 0; v < v_count; v++) {
            frontier = vlist[v];
            vid_t* adj_list = graph[frontier].adj_list;
            vid_t nebr_count = graph[frontier].count;
            
            //traverse the adj list
            for (vid_t k = 0; k < nebr_count; ++k) {
                sid_t sid = adj_list[k];
                if (eOK == filter_info->rgraph->filter(sid, 
                        filter_info->value, filter_info->filter_fn)) {
                    oset->set_status(sid);
                }
            }
        }
    }
    return eOK;
}

status_t 
pgraph_t::query_kv_td_filter(skv_t* skv, sflag_t iflag, sflag_t oflag, srset_t* iset, 
                             srset_t* oset, filter_info_t* filter_info)
{
    tid_t    iset_count = iset->get_rset_count();
    rset_t*        rset = 0;

    //prepare the output 1,2;
    oset->full_setup(oflag);

    for (tid_t i = 0; i < iset_count; ++i) {
        rset = iset->rset + i;
        vid_t v_count = rset->get_vcount();
        vid_t* vlist = rset->get_vlist();
        
        //get the graph where we will traverse
        tid_t        tid = rset->get_tid();
        tid_t        pos = get_sindex(tid, iflag);
        tid_t  graph_tid = TO_TID(skv[pos].super_id);
        sid_t* kv = skv[pos].kv; 
        if (graph_tid != tid) continue;

        //Get the frontiers
        sid_t     sid;
        for (vid_t v = 0; v < v_count; v++) {
            sid = kv[vlist[v]];
            if (eOK == filter_info->rgraph->filter(sid, 
                 filter_info->value, filter_info->filter_fn)) {
               oset->set_status(sid);
            }
        }
    }

    return eOK;
}

status_t 
pgraph_t::query_adjlist_bu_filter(sgraph_t* sgraph, sflag_t flag, srset_t* iset, 
                                  srset_t* oset, filter_info_t* filter_info)
{
    rset_t*        rset = 0;

    //prepare the output 1;
    tid_t oset_count = oset->setup(flag);
    
    for (tid_t i = 0; i < oset_count; ++i) {
        
        //get the graph where we will traverse
        beg_pos_t* graph = sgraph[i].beg_pos; 
        sid_t   super_id = sgraph[i].super_id;
        vid_t v_count = TO_VID(super_id);
        sid_t    tid_high = TO_THIGH(super_id);
        
        //set up the output 2
        rset = oset->rset + i;
        rset->setup(super_id);
        
        for (vid_t v = 0; v < v_count; v++) {
            //traverse the adj list
            vid_t* adj_list = graph[v].adj_list;
            vid_t nebr_count = graph[v].count;
            for (vid_t k = 0; k < nebr_count; ++k) {
                //apply the filter here.
                if (iset->get_status(adj_list[k]) && 
                    (eOK == filter_info->rgraph->filter(tid_high + v, 
                            filter_info->value, filter_info->filter_fn))) {
                    rset->set_status(v);
                    break;
                }
            }
        }
    }
    return eOK;
}

status_t 
pgraph_t::query_kv_bu_filter(skv_t* skv, sflag_t flag, srset_t* iset, 
                             srset_t* oset, filter_info_t* filter_info)
{
    rset_t*        rset = 0;

    //prepare the output 1;
    tid_t oset_count = oset->setup(flag);
    
    for (tid_t i = 0; i < oset_count; ++i) {

        //get the graph where we will traverse
        vid_t*        kv = skv[i].kv; 
        sid_t   super_id = skv[i].super_id;
        vid_t    v_count = TO_VID(super_id);
        sid_t    tid_high = TO_SUPER(TO_TID(super_id));
        
        //set up the output 2
        rset = oset->rset + i;
        rset->setup(super_id);
        
        for (vid_t v = 0; v < v_count; ++v) {
            if (iset->get_status(kv[v])
               && (eOK == filter_info->rgraph->filter(tid_high + v, 
                   filter_info->value, filter_info->filter_fn))) {
                rset->set_status(v);
                break;
            }
        }
    }
    return eOK;
}

