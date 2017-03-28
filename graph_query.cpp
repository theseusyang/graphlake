#include "graph.h"


status_t pinfo_t::execute(srset_t* iset, srset_t* oset)
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

srset_t::srset_t()
{
    flag = 0;
    count = 0;
    rset = 0;
}

status_t many2one_t::execute(srset_t* iset, srset_t* oset)
{
    return 0;
}

