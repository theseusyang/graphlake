#include "graph.h"

void dgraph_t::make_graph_baseline()
{
    flag1_count = __builtin_popcountll(flag1);
    flag2_count = __builtin_popcountll(flag2);

    //super bins memory allocation
    sgraph_out = prep_sgraph(flag1, flag1_count);    
    sgraph_in  = prep_sgraph(flag2, flag2_count);

    //estimate edge count
    calc_edge_count(sgraph_out, sgraph_in);
    
    
    //prefix sum then reset the count
    prep_sgraph_internal(sgraph_out, count, flag1_count);
    prep_sgraph_internal(sgraph_in, count, flag2_count);

    //populate and get the original count back
    fill_adj_list(sgraph_out, sgraph_in);
}

void dgraph_t::store_graph_baseline(string dir)
{
    if (count == 0) return ;
    string postfix = "out";
    store_sgraph(sgraph_out, flag1, dir, postfix);
    postfix = "in";
    store_sgraph(sgraph_in,  flag2, dir, postfix);
}

/*******************************************/
void ugraph_t::make_graph_baseline()
{
    flag1 = flag1 | flag2;
    flag2 = flag1;

    flag1_count = __builtin_popcountll(flag1);
    flag2_count = flag1_count;

    //super bins memory allocation
    sgraph = prep_sgraph(flag1, flag1_count);    

    //estimate edge count
    calc_edge_count(sgraph, sgraph);
    
    
    //prefix sum then reset the count
    //Take symmetry into consideration
    prep_sgraph_internal(sgraph, 2*count, flag1_count);

    //populate and get the original count back
    fill_adj_list(sgraph, sgraph);
}

void ugraph_t::store_graph_baseline(string dir)
{
    if (count == 0) return ;
    string postfix = "";
    store_sgraph(sgraph, flag1, dir, postfix);
}

/***************************************/
void many2one_t::make_graph_baseline()
{
    if (count == 0) return;
    flag1_count = __builtin_popcountll(flag1);
    flag2_count = __builtin_popcountll(flag2);

    //super bins memory allocation
    skv_out  = prep_skv(flag1, flag1_count);
    sgraph_in  = prep_sgraph(flag2, flag2_count);

    //estimate edge count
    calc_edge_count_in(sgraph_in);
    
    
    //prefix sum then reset the count
    prep_sgraph_internal(sgraph_in, count, flag2_count);

    //populate and get the original count back
    //handle kv_out as well.
    fill_adj_list_in(skv_out, sgraph_in);
}

void many2one_t::store_graph_baseline(string dir)
{
    if (count == 0) return ;
    string postfix = "out";
    store_skv(skv_out, flag1, dir, postfix);
    postfix = "in";
    store_sgraph(sgraph_in, flag2, dir, postfix);
}

/*******************************************/
void one2many_t::make_graph_baseline()
{
    if (count == 0) return;
    flag1_count = __builtin_popcountll(flag1);
    flag2_count = __builtin_popcountll(flag2);

    //super bins memory allocation
    sgraph_out = prep_sgraph(flag1, flag1_count);
    skv_in   = prep_skv(flag2, flag2_count);

    //estimate edge count
    calc_edge_count_out(sgraph_out);
    
    
    //prefix sum then reset the count
    prep_sgraph_internal(sgraph_out, count, flag1_count);

    //populate and get the original count back
    //handle kv_in as well.
    fill_adj_list_out(sgraph_out, skv_in);
}

void one2many_t::store_graph_baseline(string dir)
{
    if (count == 0) return ;
    string postfix = "out";
    store_sgraph(sgraph_out, flag1, dir, postfix);
    postfix = "in";
    store_skv(skv_in, flag2, dir, postfix);
}

/************************************************/
void one2one_t::make_graph_baseline()
{
    if (count == 0) return;
    flag1_count = __builtin_popcountll(flag1);
    flag2_count = __builtin_popcountll(flag2);

    //super bins memory allocation
    skv_out = prep_skv(flag1, flag1_count);
    skv_in  = prep_skv(flag2, flag2_count);

    //handle kv_out as well as kv_in.
    fill_skv(skv_out, skv_in);
}

void one2one_t::store_graph_baseline(string dir)
{
    if (count == 0) return ;
    string postfix = "out";
    store_skv(skv_out, flag1, dir, postfix);
    postfix = "in";
    store_skv(skv_in, flag2, dir, postfix);
}
