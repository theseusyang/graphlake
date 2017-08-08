#include "graph.h"
#include "sgraph.h"
#include "p_sgraph.h"
#include "lite_sgraph.h"



void graph::run_query(query_clause* q)
{
   q->execute();
   q->print_result(); 
}

status_t query_clause::execute()
{
    if (where_clause)
    where_clause->execute();

    return eOK;
}

void query_clause::print_result()
{
    tid_t rset_count = srset->get_rset_count();
    vid_t frontier = 0;
    select_info_t* select_info = srset->select_info;
    qid_t         select_count = srset->select_count;

    srset->bitwise2vlist();

    if (!srset->filter_done) {
        filter_info_t* filter_info = srset->filter_info;
        sid_t sid;
        for (tid_t i = 0; i < rset_count; i++) {
            rset_t* rset = srset->rset + i;
            vid_t v_count = rset->get_vcount();
            tid_t tid = rset->get_tid();
            sid_t tid_high = TO_SUPER(tid);
            vid_t* varray = rset->get_vlist();

            for (vid_t j = 0; j < v_count; ++j) {
                frontier = varray[j];
                sid = tid_high + frontier;

                if (eOK != filter_info->rgraph->filter(sid, 
                     filter_info->value, filter_info->filter_fn)) {
                    continue;
                }
                
                for (int m = 0; m < select_count; ++m) {
                    select_info[m].rgraph->print_raw_dst(tid, frontier, select_info[m].pid);
                    cout << "\t";
                }

                for (int k = 1; k < qid_count; ++k) {
                    cout << "\t";
                    srset[k].print_result(i,j) ;
                }
                cout << endl << endl;
            }
        }
    } else {
        for (tid_t i = 0; i < rset_count; i++) {
            rset_t* rset = srset->rset + i;
            
            vid_t v_count = rset->get_vcount();
            tid_t tid = rset->get_tid();
            vid_t* varray = rset->get_vlist();

            for (vid_t j = 0; j < v_count; ++j) {
                frontier = varray[j];
                
                for (int m = 0; m < select_count; ++m) {
                    select_info[m].rgraph->print_raw_dst(tid, frontier, select_info[m].pid);
                    cout << "\t";
                }
                 
                for (int k = 1; k < qid_count; ++k) {
                    cout << "\t";
                    srset[k].print_result(i,j) ;
                }
                cout << endl << endl;
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
status_t cfinfo_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    assert(0);
    return eOK;
}

status_t ugraph_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    return extend_adjlist_td(sgraph, iset, oset);
}

//due to many2one structure, we give preference to bottom up approach
status_t many2one_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    if (direction == eout) {
        return extend_kv_td(skv_out,  iset, oset);
    } else {
        assert(direction == ein);
        return extend_adjlist_td(sgraph_in, iset, oset);
    }
    return eOK;
}

status_t dgraph_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    if (direction == eout) {
        return extend_adjlist_td(sgraph_out, iset, oset);
    } else {
        assert(direction == ein);
        return extend_adjlist_td(sgraph_in, iset, oset);
    }
    return eOK;
}

status_t one2one_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    if (direction == eout) {
        return extend_kv_td(skv_out, iset, oset);
    } else {
        assert(direction == ein);
        return extend_kv_td(skv_in, iset, oset);
    }
    return eOK;
}

status_t one2many_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    if (direction == eout) {
        return extend_adjlist_td(sgraph_out, iset, oset);
    } else {
        assert(direction == ein);
        return extend_kv_td(skv_in, iset, oset);
    }
    return eOK;
}

status_t lite_ugraph_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    return extend_adjlist_td(sgraph, iset, oset);
}

//due to many2one structure, we give preference to bottom up approach
status_t lite_many2one_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    if (direction == eout) {
        return extend_kv_td(skv_out,  iset, oset);
    } else {
        assert(direction == ein);
        return extend_adjlist_td(sgraph_in, iset, oset);
    }
    return eOK;
}

status_t lite_dgraph_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    if (direction == eout) {
        return extend_adjlist_td(sgraph_out, iset, oset);
    } else {
        assert(direction == ein);
        return extend_adjlist_td(sgraph_in, iset, oset);
    }
    return eOK;
}

status_t lite_one2one_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    if (direction == eout) {
        return extend_kv_td(skv_out, iset, oset);
    } else {
        assert(direction == ein);
        return extend_kv_td(skv_in, iset, oset);
    }
    return eOK;
}

status_t lite_one2many_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    if (direction == eout) {
        return extend_adjlist_td(sgraph_out, iset, oset);
    } else {
        assert(direction == ein);
        return extend_kv_td(skv_in, iset, oset);
    }
    return eOK;
}

status_t p_ugraph_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    return extend_adjlist_td(sgraph, iset, oset);
}

//due to many2one structure, we give preference to bottom up approach
status_t p_many2one_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    if (direction == eout) {
        return extend_kv_td(skv_out,  iset, oset);
    } else {
        assert(direction == ein);
        return extend_adjlist_td(sgraph_in, iset, oset);
    }
    return eOK;
}

status_t p_dgraph_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    if (direction == eout) {
        return extend_adjlist_td(sgraph_out, iset, oset);
    } else {
        assert(direction == ein);
        return extend_adjlist_td(sgraph_in, iset, oset);
    }
    return eOK;
}

status_t p_one2one_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    if (direction == eout) {
        return extend_kv_td(skv_out, iset, oset);
    } else {
        assert(direction == ein);
        return extend_kv_td(skv_in, iset, oset);
    }
    return eOK;
}

status_t p_one2many_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    if (direction == eout) {
        return extend_adjlist_td(sgraph_out, iset, oset);
    } else {
        assert(direction == ein);
        return extend_kv_td(skv_in, iset, oset);
    }
    return eOK;
}

/*************************** transform ****************/
status_t cfinfo_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    assert(0);
    return eOK;
}


status_t ugraph_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    //prepare the output 1,2;
    oset->full_setup(sgraph);
    int total_count = 0;
    
    if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
        return query_adjlist_td(sgraph, iset, oset);
    } else { //bottom up approach
        return query_adjlist_bu(sgraph, iset, oset);
    }
    return eOK;
}

//due to many2one structure, we give preference to bottom up approach
status_t many2one_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    int total_count = 0;

    if (direction == eout) {
        oset->full_setup(sgraph_in);
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td(skv_out, iset, oset);
        } else { //bottom up approach
            return query_adjlist_bu(sgraph_in, iset, oset);
        }
    } else {
        assert(direction == ein);
        oset->full_setup(skv_out);
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td(sgraph_in, iset, oset);
        } else { //bottom up approach 
            return query_kv_bu(skv_out, iset, oset);
        }
    }
    return eOK;
}

status_t dgraph_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    int total_count = 0;
    if (direction == eout) {
        total_count = 0;
        oset->full_setup(sgraph_in);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td(sgraph_out, iset, oset);
        } else { //bottom up approach
            return query_adjlist_bu(sgraph_in, iset, oset);
        }
    } else {
        assert(direction == ein);
        total_count = 0;
        oset->full_setup(sgraph_out);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td(sgraph_in, iset, oset);
        } else { //bottom up approach 
            return query_adjlist_bu(sgraph_out, iset, oset);
        }
    }
    return eOK;
}

status_t one2one_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    int total_count = 0;
    if (direction == eout) {
        total_count = 0;
        oset->full_setup(skv_in);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td(skv_out, iset, oset);
        } else { //bottom up approach
            return query_kv_bu(skv_in, iset, oset);
        }
    } else {
        assert(direction == ein);
        total_count = 0;
        oset->full_setup(skv_out);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td(skv_in, iset, oset);
        } else { //bottom up approach 
            return query_kv_bu(skv_out, iset, oset);
        }
    }
    return eOK;
}

status_t one2many_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    int total_count = 0;
    if (direction == eout) {
        total_count = 0;
        oset->full_setup(skv_in);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td(sgraph_out, iset, oset);
        } else { //bottom up approach
            return query_kv_bu(skv_in, iset, oset);
        }
    } else {
        assert(direction == ein);
        total_count = 0;
        oset->full_setup(sgraph_out);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td(skv_in, iset, oset);
        } else { //bottom up approach 
            return query_adjlist_bu(sgraph_out, iset, oset);
        }
    }
    return eOK;
}

status_t lite_ugraph_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    //prepare the output 1,2;
    oset->full_setup(sgraph);
    int total_count = 0;
    
    if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
        return query_adjlist_td(sgraph, iset, oset);
    } else { //bottom up approach
        return query_adjlist_bu(sgraph, iset, oset);
    }
    return eOK;
}

//due to many2one structure, we give preference to bottom up approach
status_t lite_many2one_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    int total_count = 0;

    if (direction == eout) {
        oset->full_setup(sgraph_in);
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td(skv_out, iset, oset);
        } else { //bottom up approach
            return query_adjlist_bu(sgraph_in, iset, oset);
        }
    } else {
        assert(direction == ein);
        oset->full_setup(skv_out);
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td(sgraph_in, iset, oset);
        } else { //bottom up approach 
            return query_kv_bu(skv_out, iset, oset);
        }
    }
    return eOK;
}

status_t lite_dgraph_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    int total_count = 0;
    if (direction == eout) {
        total_count = 0;
        oset->full_setup(sgraph_in);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td(sgraph_out, iset, oset);
        } else { //bottom up approach
            return query_adjlist_bu(sgraph_in, iset, oset);
        }
    } else {
        assert(direction == ein);
        total_count = 0;
        oset->full_setup(sgraph_out);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td(sgraph_in, iset, oset);
        } else { //bottom up approach 
            return query_adjlist_bu(sgraph_out, iset, oset);
        }
    }
    return eOK;
}

status_t lite_one2one_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    int total_count = 0;
    if (direction == eout) {
        total_count = 0;
        oset->full_setup(skv_in);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td(skv_out, iset, oset);
        } else { //bottom up approach
            return query_kv_bu(skv_in, iset, oset);
        }
    } else {
        assert(direction == ein);
        total_count = 0;
        oset->full_setup(skv_out);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td(skv_in, iset, oset);
        } else { //bottom up approach 
            return query_kv_bu(skv_out, iset, oset);
        }
    }
    return eOK;
}

status_t lite_one2many_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    int total_count = 0;
    if (direction == eout) {
        total_count = 0;
        oset->full_setup(skv_in);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td(sgraph_out, iset, oset);
        } else { //bottom up approach
            return query_kv_bu(skv_in, iset, oset);
        }
    } else {
        assert(direction == ein);
        total_count = 0;
        oset->full_setup(sgraph_out);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td(skv_in, iset, oset);
        } else { //bottom up approach 
            return query_adjlist_bu(sgraph_out, iset, oset);
        }
    }
    return eOK;
}

status_t p_ugraph_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    //prepare the output 1,2;
    oset->full_setup(sgraph);
    int total_count = 0;
    
    if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
        return query_adjlist_td(sgraph, iset, oset);
    } else { //bottom up approach
        return query_adjlist_bu(sgraph, iset, oset);
    }
    return eOK;
}

//due to many2one structure, we give preference to bottom up approach
status_t p_many2one_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    int total_count = 0;

    if (direction == eout) {
        oset->full_setup(sgraph_in);
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td(skv_out, iset, oset);
        } else { //bottom up approach
            return query_adjlist_bu(sgraph_in, iset, oset);
        }
    } else {
        assert(direction == ein);
        oset->full_setup(skv_out);
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td(sgraph_in, iset, oset);
        } else { //bottom up approach 
            return query_kv_bu(skv_out, iset, oset);
        }
    }
    return eOK;
}

status_t p_dgraph_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    int total_count = 0;
    if (direction == eout) {
        total_count = 0;
        oset->full_setup(sgraph_in);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td(sgraph_out, iset, oset);
        } else { //bottom up approach
            return query_adjlist_bu(sgraph_in, iset, oset);
        }
    } else {
        assert(direction == ein);
        total_count = 0;
        oset->full_setup(sgraph_out);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td(sgraph_in, iset, oset);
        } else { //bottom up approach 
            return query_adjlist_bu(sgraph_out, iset, oset);
        }
    }
    return eOK;
}

status_t p_one2one_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    int total_count = 0;
    if (direction == eout) {
        total_count = 0;
        oset->full_setup(skv_in);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td(skv_out, iset, oset);
        } else { //bottom up approach
            return query_kv_bu(skv_in, iset, oset);
        }
    } else {
        assert(direction == ein);
        total_count = 0;
        oset->full_setup(skv_out);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td(skv_in, iset, oset);
        } else { //bottom up approach 
            return query_kv_bu(skv_out, iset, oset);
        }
    }
    return eOK;
}

status_t p_one2many_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    int total_count = 0;
    if (direction == eout) {
        total_count = 0;
        oset->full_setup(skv_in);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td(sgraph_out, iset, oset);
        } else { //bottom up approach
            return query_kv_bu(skv_in, iset, oset);
        }
    } else {
        assert(direction == ein);
        total_count = 0;
        oset->full_setup(sgraph_out);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td(skv_in, iset, oset);
        } else { //bottom up approach 
            return query_adjlist_bu(sgraph_out, iset, oset);
        }
    }
    return eOK;
}
