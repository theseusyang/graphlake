#include "graph.h"

void dgraph_t::make_graph_baseline()
{
    flag1_count = __builtin_popcountll(flag1);
    flag2_count = __builtin_popcountll(flag2);

    //super bins memory allocation
    tid_t   t_count = g->get_total_types();
    
    sgraph_out  = (sgraph_t**) calloc (sizeof(sgraph_t*), t_count);
    prep_sgraph(flag1, sgraph_out);    
    
    sgraph_in  = (sgraph_t**) calloc (sizeof(sgraph_t*), t_count);
    prep_sgraph(flag2, sgraph_in);

    //estimate edge count
    calc_edge_count(sgraph_out, sgraph_in);
    
    
    //prefix sum then reset the count
    prep_sgraph_internal(sgraph_out);
    prep_sgraph_internal(sgraph_in);

    //populate and get the original count back
    fill_adj_list(sgraph_out, sgraph_in);
}

void dgraph_t::make_graph_update()
{
    //estimate edge count
    calc_edge_count(sgraph_out, sgraph_in);

    //allocate space for old+new adj list, 
    //Copy the old adj list to new one
    //keep the old count
    //prefix sum then reset the count
    prep_sgraph_internal(sgraph_out);
    prep_sgraph_internal(sgraph_in);
    

    //populate the adj list for new members at the end.
    fill_adj_list(sgraph_out, sgraph_in);

    //Do you want to sort it?, use merge sort
}

void dgraph_t::store_graph_baseline(string dir)
{
    if (batch_info[0].count == 0) return;
    string postfix = "out";
    store_sgraph(sgraph_out, dir, postfix);
    postfix = "in";
    store_sgraph(sgraph_in,  dir, postfix);
}

/*******************************************/
void ugraph_t::make_graph_baseline()
{
    flag1 = flag1 | flag2;
    flag2 = flag1;

    flag1_count = __builtin_popcountll(flag1);
    flag2_count = flag1_count;

    //super bins memory allocation
    tid_t   t_count = g->get_total_types();
    
    sgraph  = (sgraph_t**) calloc (sizeof(sgraph_t*), t_count);
    prep_sgraph(flag1, sgraph);    

    //estimate edge count
    calc_edge_count(sgraph, sgraph);
    
    
    //prefix sum then reset the count
    //Take symmetry into consideration
    prep_sgraph_internal(sgraph);

    //populate and get the original count back
    fill_adj_list(sgraph, sgraph);

    //clean up
    cleanup();
}

void ugraph_t::make_graph_update()
{

}

void ugraph_t::store_graph_baseline(string dir)
{
    if (batch_info[0].count == 0) return;
    string postfix = "";
    store_sgraph(sgraph, dir, postfix);
}

/***************************************/
void many2one_t::make_graph_baseline()
{
    if (batch_info[0].count == 0) return;
    flag1_count = __builtin_popcountll(flag1);
    flag2_count = __builtin_popcountll(flag2);

    //super bins memory allocation
    tid_t   t_count = g->get_total_types();
    
    sgraph_in  = (sgraph_t**) calloc (sizeof(sgraph_t*), t_count);
    prep_sgraph(flag2, sgraph_in);
    
    skv_out  = prep_skv(flag1, flag1_count);

    //estimate edge count
    calc_edge_count_in(sgraph_in);
    
    
    //prefix sum then reset the count
    prep_sgraph_internal(sgraph_in);

    //populate and get the original count back
    //handle kv_out as well.
    fill_adj_list_in(skv_out, sgraph_in);
}

void many2one_t::make_graph_update()
{

}

void many2one_t::store_graph_baseline(string dir)
{
    if (batch_info[0].count == 0) return;
    string postfix = "out";
    store_skv(skv_out, dir, postfix);
    postfix = "in";
    store_sgraph(sgraph_in, dir, postfix);
}

/*******************************************/
void one2many_t::make_graph_baseline()
{
    if (batch_info[0].count == 0) return;
    flag1_count = __builtin_popcountll(flag1);
    flag2_count = __builtin_popcountll(flag2);

    //super bins memory allocation
    tid_t   t_count = g->get_total_types();
    
    sgraph_out  = (sgraph_t**) calloc (sizeof(sgraph_t*), t_count);
    prep_sgraph(flag1, sgraph_out);
    
    skv_in   = prep_skv(flag2, flag2_count);

    //estimate edge count
    calc_edge_count_out(sgraph_out);
    
    
    //prefix sum then reset the count
    prep_sgraph_internal(sgraph_out);

    //populate and get the original count back
    //handle kv_in as well.
    fill_adj_list_out(sgraph_out, skv_in);
}

void one2many_t::make_graph_update()
{

}

void one2many_t::store_graph_baseline(string dir)
{
    if (batch_info[0].count == 0) return;
    string postfix = "out";
    store_sgraph(sgraph_out, dir, postfix);
    postfix = "in";
    store_skv(skv_in, dir, postfix);
}

/************************************************/
void one2one_t::make_graph_baseline()
{
    if (batch_info[0].count == 0) return;
    flag1_count = __builtin_popcountll(flag1);
    flag2_count = __builtin_popcountll(flag2);

    //super bins memory allocation
    skv_out = prep_skv(flag1, flag1_count);
    skv_in  = prep_skv(flag2, flag2_count);

    //handle kv_out as well as kv_in.
    fill_skv(skv_out, skv_in);
}

void one2one_t::make_graph_update()
{

}

void one2one_t::store_graph_baseline(string dir)
{
    if (batch_info[0].count == 0) return;
    string postfix = "out";
    store_skv(skv_out, dir, postfix);
    postfix = "in";
    store_skv(skv_in, dir, postfix);
}
