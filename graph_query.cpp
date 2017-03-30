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


status_t pinfo_t::execute(srset_t* iset, srset_t* oset, direction_t direction)
{
    assert(0);
    return 0;
}

void graph::run_query(query_clause* q)
{
   q->execute(); 
}


status_t query_clause::execute()
{
    where_clause->execute();

    return 0;
}

status_t query_whereclause::execute()
{
    query_node* node = get_child();
    if (node) {
        node->execute();
    }
    node = get_sibling();
    while (node) {
        node->execute();
        node = node->get_sibling();
    }
    cout << ")" << endl;

    return 0;
}

//due to many2one structure, we give preference to bottom up approach
status_t many2one_t::execute(srset_t* iset, srset_t* oset, direction_t direction)
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
    return 0;
}

