#include "graph.h"


tid_t srset_t::full_setup(sflag_t flag) {
    sid_t flag_count = setup(flag);
    tid_t pos = 0;
    sid_t super_id;
    for (tid_t i = 0; i < flag_count; ++i) {
        pos = __builtin_ctzll(flag);
        flag ^= (1L << pos);//reset that position
        super_id = g->get_type_scount(pos);
        rset[i].setup(super_id);
    }
    return flag_count;
}


void graph::run_query(query_clause* q)
{
   q->execute();
   q->print_result(); 
}

status_t query_clause::execute()
{
    where_clause->execute();

    return eOK;
}
/*
void query_clause::print_result()
{
    //Printing only one var(vertex) and more labels
    srset_t* srset = get_srset(0);
    tid_t rset_count = srset->get_rset_count();
    vid_t word, count, pos, base, frontier = 0;

    
    for (tid_t i = 0; i < rset_count; i++) {
       rset_t* rset = srset->rset + i;
       vid_t v_count = rset->get_vcount();
       tid_t tid = rset->get_tid();
       vid_t w_count = WORD_COUNT(v_count);
       vid_t* barray = rset->status_array;

       for (vid_t w = 0; w < w_count; w++) {
           if (barray[w] == 0) continue;
            word  = barray[w];
            count = __builtin_popcountll(word);
            base  = (w << 6);

            for (tid_t j = 0; j < count; ++j) {
                pos = __builtin_ctzll(word);
                word  ^= (1L << pos);//reset that position
                frontier = pos + base;
                
                cout << g->v_graph->get_value(tid, frontier) << "\t";
                for (int j = 0; j < select_count; ++j) {
                    select_info[j].rgraph->print_raw_dst(tid, frontier);
                    cout << "\t";
                }
                cout << endl;
            }
       }
    }
    cout << endl;
}
*/

void query_clause::print_result()
{
    //Printing only one var(vertex) and more labels
    srset_t* srset = get_srset(0);
    tid_t rset_count = srset->get_rset_count();
    vid_t frontier = 0;
    sid_t sid= 0;
    filter_info_t* filter_info = srset->filter_info;

    if (filter_info) {
        for (tid_t i = 0; i < rset_count; i++) {
            rset_t* rset = srset->rset + i;
            vid_t v_count = rset->get_vcount();
            tid_t tid = rset->get_tid();
            vid_t* varray = rset->get_vlist();

            for (vid_t j = 0; j < v_count; ++j) {
                sid = varray[j];

                if (eOK != filter_info->rgraph->filter(sid, 
                     filter_info->value, filter_info->filter_fn)) {
                    continue;
                }
                
                frontier = TO_VID(sid);
                cout << g->v_graph->get_value(TO_TID(sid), frontier) << "\t";
                for (int j = 0; j < select_count; ++j) {
                    select_info[j].rgraph->print_raw_dst(tid, frontier);
                    cout << "\t";
                }
                cout << endl;
            }
        }
    } else {
        for (tid_t i = 0; i < rset_count; i++) {
            rset_t* rset = srset->rset + i;
            vid_t v_count = rset->get_vcount();
            tid_t tid = rset->get_tid();
            vid_t* varray = rset->get_vlist();

            for (vid_t j = 0; j < v_count; ++j) {
                sid = varray[j];
                frontier = TO_VID(sid);
                cout << g->v_graph->get_value(TO_TID(sid), frontier) << "\t";
                for (int j = 0; j < select_count; ++j) {
                    select_info[j].rgraph->print_raw_dst(tid, frontier);
                    cout << "\t";
                }
                cout << endl;
            }
        }
    }
    cout << endl;
}

status_t query_whereclause::execute()
{
    query_node* node = get_child();
    if (node) {
        node->execute();
    }
    node = node->get_sibling();
    while (node) {
        node->execute();
        node = node->get_sibling();
    }

    return eOK;
}
/*************************** extend *******************/
status_t pinfo_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    assert(0);
    return eOK;
}

status_t ugraph_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    return extend_adjlist_td(sgraph, flag1, iset, oset);
}

//due to many2one structure, we give preference to bottom up approach
status_t many2one_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    if (direction == eout) {
        return extend_kv_td(skv_out, flag1,  iset, oset);
    } else {
        assert(direction == ein);
        return extend_adjlist_td(sgraph_in, flag2, iset, oset);
    }
    return eOK;
}

status_t dgraph_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    if (direction == eout) {
        return extend_adjlist_td(sgraph_out, flag1, iset, oset);
    } else {
        assert(direction == ein);
        return extend_adjlist_td(sgraph_in, flag2, iset, oset);
    }
    return eOK;
}

status_t one2one_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    if (direction == eout) {
        return extend_kv_td(skv_out, flag1, iset, oset);
    } else {
        assert(direction == ein);
        return extend_kv_td(skv_in, flag2, iset, oset);
    }
    return eOK;
}

status_t one2many_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    if (direction == eout) {
        return extend_adjlist_td(sgraph_out, flag1, iset, oset);
    } else {
        assert(direction == ein);
        return extend_kv_td(skv_in, flag2, iset, oset);
    }
    return eOK;
}
/*************************** transform ****************/
status_t pinfo_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    assert(0);
    return eOK;
}


status_t ugraph_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    int total_count = 0;
    if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
        return query_adjlist_td(sgraph, flag1, flag2, iset, oset);
    } else { //bottom up approach
        return query_adjlist_bu(sgraph, flag2, iset, oset);
    }
    return eOK;
}

//due to many2one structure, we give preference to bottom up approach
status_t many2one_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    int total_count = 0;
    if (direction == eout) {
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td(skv_out, flag1, flag2, iset, oset);
        } else { //bottom up approach
            return query_adjlist_bu(sgraph_in, flag2, iset, oset);
        }
    } else {
        assert(direction == ein);
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td(sgraph_in, flag2, flag1, iset, oset);
        } else { //bottom up approach 
            return query_kv_bu(skv_out, flag1, iset, oset);
        }
    }
    return eOK;
}

status_t dgraph_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    int total_count = 0;
    if (direction == eout) {
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td(sgraph_out, flag1, flag2, iset, oset);
        } else { //bottom up approach
            return query_adjlist_bu(sgraph_in, flag2, iset, oset);
        }
    } else {
        assert(direction == ein);
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td(sgraph_in, flag2, flag1, iset, oset);
        } else { //bottom up approach 
            return query_adjlist_bu(sgraph_out, flag1, iset, oset);
        }
    }
    return eOK;
}

status_t one2one_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    int total_count = 0;
    if (direction == eout) {
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td(skv_out, flag1, flag2, iset, oset);
        } else { //bottom up approach
            return query_kv_bu(skv_in, flag2, iset, oset);
        }
    } else {
        assert(direction == ein);
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td(skv_in, flag2, flag1, iset, oset);
        } else { //bottom up approach 
            return query_kv_bu(skv_out, flag1, iset, oset);
        }
    }
    return eOK;
}

status_t one2many_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    int total_count = 0;
    if (direction == eout) {
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td(sgraph_out, flag1, flag2, iset, oset);
        } else { //bottom up approach
            return query_kv_bu(skv_in, flag2, iset, oset);
        }
    } else {
        assert(direction == ein);
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td(skv_in, flag2, flag1, iset, oset);
        } else { //bottom up approach 
            return query_adjlist_bu(sgraph_out, flag1, iset, oset);
        }
    }
    return eOK;
}

/******************* transform_withfilter ******************/
status_t pinfo_t::transform_withfilter(srset_t* iset, srset_t* oset, direction_t direction, filter_info_t* graph)
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



