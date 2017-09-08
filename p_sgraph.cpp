#include "type.h"
#include "p_sgraph.h"
#include "sgraph.h"

p_pgraph_t::p_pgraph_t()
{
    MAXX_ECOUNT = MAX_PECOUNT;
    encoder = 0;
    
}

void p_pgraph_t::add_edge_property(const char* longname, prop_encoder_t* prop_encoder)
{
    edge_propname = longname;
    encoder = prop_encoder;
}

//Assuming only one edge property
status_t p_pgraph_t::batch_update(const string& src, const string& dst, propid_t pid,
                                propid_t count, prop_pair_t* prop_pair, int del /* = 0*/)
{
    ledge_t edge;
    
    map<string, vid_t>::iterator str2vid_iter = g->str2vid.find(src);
    if (g->str2vid.end() == str2vid_iter) {
        cout << src << " is not found. See above log if src was invalid. OR is it out of order?? " << endl;
        assert(0);
    } else {
        edge.src_id = str2vid_iter->second;
    }
    tid_t type_id = TO_TID(edge.src_id);
    flag1 |= TID_TO_SFLAG(type_id);
    
    str2vid_iter = g->str2vid.find(dst);
    if (g->str2vid.end() == str2vid_iter) {
        cout << dst << " is not found. See above log if dst was invalid. OR is it out of order?? " << endl; 
        assert(0);
    } else {
        edge.dst_id.first = str2vid_iter->second;
    }
    type_id = TO_TID(edge.dst_id.first);
    flag2 |= TID_TO_SFLAG(type_id);

    if (0 == del) {
        univ_t univ;
        encoder->encode(prop_pair->value.c_str(), univ);
        edge.dst_id.second = univ;
    } else {
        edge.src_id = DEL_SID(edge.src_id);
    }

    return batch_edge(edge);
}

void p_pgraph_t::fill_adj_list(lite_sgraph_t** sgraph_out, lite_sgraph_t** sgraph_in)
{
    sid_t     src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    univ_t    univ;
    
    ledge_t*   edges;
    index_t   count;

    for (int j = 0; j <= batch_count; ++j) { 
        edges = (ledge_t*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            src = edges[i].src_id;
            dst = get_sid(edges[i].dst_id);
            univ = edges[i].dst_id.second;
            src_index = TO_TID(src);
            dst_index = TO_TID(dst);
            vert1_id = TO_VID(src);
            vert2_id = TO_VID(dst);
            
            if (!IS_DEL(src)) {
                sgraph_out[src_index]->add_nebr_lite(vert1_id, dst, univ);
                sgraph_in[dst_index]->add_nebr_lite(vert2_id, src, univ);
            } else {
                //sgraph_out[src_index]->del_nebr_lite(vert1_id, dst, univ);
                //sgraph_in[dst_index]->del_nebr_lite(vert2_id, TO_SID(src), univ);
            }
        }
    }
}

void p_pgraph_t::fill_adj_list_in(lite_skv_t** skv_out, lite_sgraph_t** sgraph_in) 
{
    sid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    ledge_t*   edges;
    index_t   count;
    univ_t    univ;
    lite_edge_t lite_edge;

    for (int j = 0; j <= batch_count; ++j) { 
        edges = (ledge_t*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            src = edges[i].src_id;
            dst = get_sid(edges[i].dst_id);
            univ = edges[i].dst_id.second;
            src_index = TO_TID(src);
            dst_index = TO_TID(dst);
            vert1_id = TO_VID(src);
            vert2_id = TO_VID(dst);
            
            lite_edge.first = dst;
            lite_edge.second = univ; 
            
            if (!IS_DEL(src)) {
                skv_out[src_index]->set_value(vert1_id, lite_edge);
                sgraph_in[dst_index]->add_nebr_lite(vert2_id, src, univ);
            } else {
                //skv_out[src_index]->del_value(vert1_id, lite_edge);
                //sgraph_in[dst_index]->del_nebr_lite(vert2_id, TO_SID(src), univ);
            }
        }
    }
}

void p_pgraph_t::fill_adj_list_out(lite_sgraph_t** sgraph_out, lite_skv_t** skv_in) 
{
    sid_t   src, dst;
    vid_t   vert1_id, vert2_id;
    tid_t   src_index, dst_index; 
    ledge_t*   edges;
    index_t   count;
    lite_edge_t lite_edge;
    univ_t  univ;
    
    
    for (int j = 0; j <= batch_count; ++j) { 
        edges = (ledge_t*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            src = edges[i].src_id;
            dst = get_sid(edges[i].dst_id);
            univ = edges[i].dst_id.second;
            src_index = TO_TID(src);
            dst_index = TO_TID(dst);
            
            vert1_id = TO_VID(src);
            vert2_id = TO_VID(dst);
            lite_edge.first = src;
            lite_edge.second = univ;
           
            if (!IS_DEL(src)) {
                sgraph_out[src_index]->add_nebr_lite(vert1_id, dst, univ);
                skv_in[dst_index]->set_value(vert2_id, lite_edge);
            } else {
                //sgraph_out[src_index]->del_nebr_lite(vert1_id, dst, univ);
                //skv_in[dst_index]->del_value_lite(vert2_id, TO_SID(src), univ);
            }
        }
    }
}

void p_pgraph_t::fill_skv(lite_skv_t** skv_out, lite_skv_t** skv_in)
{
    sid_t     src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    ledge_t*  edges;
    index_t   count;
    univ_t    univ;
    
    for (int j = 0; j <= batch_count; ++j) {
        edges = (ledge_t*)batch_info[j].buf;
        count = batch_info[j].count;
    
        for (index_t i = 0; i < count; ++i) {
            src = edges[i].src_id;
            dst = get_sid(edges[i].dst_id);
            univ = edges[i].dst_id.second;
            src_index = TO_TID(src);
            dst_index = TO_TID(dst);
            
            vert1_id = TO_VID(src);
            vert2_id = TO_VID(dst);
            
            if (!IS_DEL(src)) {
                skv_out[src_index]->set_value_lite(vert1_id, dst, univ); 
                skv_in[dst_index]->set_value_lite(vert2_id, src, univ);
            } else {
                skv_out[src_index]->del_value_lite(vert1_id, dst, univ); 
                skv_in[dst_index]->del_value_lite(vert2_id, TO_SID(src), univ);
            }
        }
    }
}

/*
void p_pgraph_t::update_count(lite_sgraph_t** sgraph)
{
    vid_t       v_count = 0;
    tid_t       t_count = g->get_total_types();
    
    for(tid_t i = 0; i < t_count; i++) {
        if (0 == sgraph[i]) continue;
        v_count = sgraph[i]->get_vcount();
        for (vid_t j = 0; j < v_count; ++j) {
            sgraph[i]->update_count(j);
        }
    }
}
void p_pgraph_t::store_sgraph(lite_sgraph_t** sgraph, string dir, string postfix)
{
    if (sgraph == 0) return;
    
    string   vtfile, etfile;
    tid_t    t_count = g->get_total_types();
    
    //base name using relationship type
    //const char* name = 0;
    //typekv_t* typekv = g->get_typekv();
    char name[8];
    string  basefile = dir + col_info[0]->p_name;

    
    // For each file.
    for (tid_t i = 0; i < t_count; ++i) {
        if (sgraph[i] == 0) continue;

        //name = typekv->get_type_name(i);
        sprintf(name, "%d.", i);
        vtfile = basefile + name + "vtable" + postfix;
        etfile = basefile + name + "etable" + postfix;
         
        sgraph[i]->persist_elog(etfile);
        sgraph[i]->persist_vlog(vtfile);
    }
}

void p_pgraph_t::read_sgraph(lite_sgraph_t** sgraph, string dir, string postfix)
{
    if (sgraph == 0) return;
    
    string   vtfile, etfile;
    tid_t    t_count = g->get_total_types();
    
    //base name using relationship type
    //const char* name = 0;
    //typekv_t* typekv = g->get_typekv();
    char name[8];
    string  basefile = dir + col_info[0]->p_name;

    
    // For each file.
    for (tid_t i = 0; i < t_count; ++i) {

        //name = typekv->get_type_name(i);
        sprintf(name, "%d.", i);
        vtfile = basefile + name + "vtable" + postfix;
        etfile = basefile + name + "etable" + postfix;
        
        FILE* vtf = fopen(vtfile.c_str(), "r+b");
        if (vtf == 0)  continue;
        fclose(vtf); 
        
        sgraph[i] = new lite_sgraph_t;
        sgraph[i]->setup(i);
        sgraph[i]->read_vtable(vtfile);
        sgraph[i]->read_etable(etfile);
    }
}
*/

/******************** super kv *************************/
/*
void p_pgraph_t::read_skv(lite_skv_t** skv, string dir, string postfix)
{
    if (skv == 0) return;

    //const char* name = 0;
    //typekv_t*   typekv = g->get_typekv();
    char name[8];
    tid_t       t_count = g->get_total_types();
    
    //base name using relationship type
    string basefile = dir + col_info[0]->p_name;
    string vtfile;

    // For each file.
    for (tid_t i = 0; i < t_count; ++i) {
        
        //name = typekv->get_type_name(i);
        sprintf(name, "%d.", i);
        vtfile = basefile + name + "kv" + postfix;
        
        FILE* vtf = fopen(vtfile.c_str(), "r+b");
        if (vtf == 0)  continue; 
        fclose(vtf); 

        skv[i] = new lite_skv_t;
        skv[i]->setup(i);
        skv[i]->read_kv(vtfile);
    }
}

void p_pgraph_t::store_skv(lite_skv_t** skv, string dir, string postfix)
{
    if (skv == 0) return;

    //const char* name = 0;
    //typekv_t*   typekv = g->get_typekv();
    char name[8];
    tid_t       t_count = g->get_total_types();
    
    //base name using relationship type
    string basefile = dir + col_info[0]->p_name;
    string vtfile;

    // For each file.
    for (tid_t i = 0; i < t_count; ++i) {
        if (skv[i] == 0) continue;
        //name = typekv->get_type_name(i);
        sprintf(name, "%d.", i);
        vtfile = basefile + name + "kv" + postfix;

        skv[i]->persist_kvlog(vtfile);
    }
}

//super bins memory allocation
lite_skv_t** p_pgraph_t::prep_skv(sflag_t ori_flag, lite_skv_t** skv)
{
    tid_t   pos  = 0;
    sflag_t flag       = ori_flag;
    tid_t   flag_count = __builtin_popcountll(flag);

    for(tid_t i = 0; i < flag_count; i++) {
        pos = __builtin_ctz(flag);
        flag ^= (1L << pos);//reset that position
        if (0 == skv[pos]) {
            skv[pos] = new lite_skv_t;
        }
        skv[pos]->setup(pos);
    }
    return skv;
}
*/

/************* Semantic graphs  *****************/
void p_dgraph_t::prep_graph_baseline()
{
    if (batch_info[0].count == 0) return;
    flag1_count = __builtin_popcountll(flag1);
    flag2_count = __builtin_popcountll(flag2);

    //super bins memory allocation
    tid_t   t_count = g->get_total_types();
    
    if (0 == sgraph_out) {
        sgraph_out  = (lite_sgraph_t**) calloc (sizeof(lite_sgraph_t*), t_count);
    }
    prep_sgraph(flag1, sgraph_out);    
    
    if (0 == sgraph_in) {
        sgraph_in  = (lite_sgraph_t**) calloc (sizeof(lite_sgraph_t*), t_count);
    }
    prep_sgraph(flag2, sgraph_in);
}

void p_dgraph_t::calc_degree()
{
    //estimate edge count
    calc_edge_count(sgraph_out, sgraph_in);
}

//We assume that no new vertex type is defined
void p_dgraph_t::make_graph_baseline()
{
    if (batch_info[0].count == 0) return;

    //prefix sum then reset the count
    prep_sgraph_internal(sgraph_out);
    prep_sgraph_internal(sgraph_in);

    //populate and get the original count back
    fill_adj_list(sgraph_out, sgraph_in);
    update_count(sgraph_out);
    update_count(sgraph_in);
    
    //clean up
    cleanup();
}

void p_dgraph_t::store_graph_baseline()
{
    store_sgraph(sgraph_out);
    store_sgraph(sgraph_in);
}

void p_dgraph_t::read_graph_baseline()
{
    tid_t   t_count    = g->get_total_types();
    
    if (0 == sgraph_out) {
        sgraph_out  = (lite_sgraph_t**) calloc (sizeof(lite_sgraph_t*), t_count);
    }
    read_sgraph(sgraph_out);
    
    if (0 == sgraph_in) {
        sgraph_in  = (lite_sgraph_t**) calloc (sizeof(lite_sgraph_t*), t_count);
    }
    read_sgraph(sgraph_in);
}

/*******************************************/
void p_ugraph_t::prep_graph_baseline()
{
    if (batch_info[0].count == 0) return;
    flag1 = flag1 | flag2;
    flag2 = flag1;

    flag1_count = __builtin_popcountll(flag1);
    flag2_count = flag1_count;

    //super bins memory allocation
    tid_t   t_count = g->get_total_types();
    
    if (0 == sgraph) {
        sgraph  = (lite_sgraph_t**) calloc (sizeof(lite_sgraph_t*), t_count);
    }
    prep_sgraph(flag1, sgraph); 
}

void p_ugraph_t::calc_degree()
{
    //estimate edge count
    calc_edge_count(sgraph, sgraph);
}

void p_ugraph_t::make_graph_baseline()
{
    if (batch_info[0].count == 0) return;
    
    //prefix sum then reset the count
    prep_sgraph_internal(sgraph);

    //populate and get the original count back
    fill_adj_list(sgraph, sgraph);
    update_count(sgraph);

    //clean up
    cleanup();
}

void p_ugraph_t::store_graph_baseline()
{
    store_sgraph(sgraph);
}

void p_ugraph_t::read_graph_baseline()
{
    tid_t   t_count = g->get_total_types();
    
    if (0 == sgraph) {
        sgraph  = (lite_sgraph_t**) calloc (sizeof(lite_sgraph_t*), t_count);
    }
    read_sgraph(sgraph);
}

/***************************************/
void p_many2one_t::prep_graph_baseline()
{
    if (batch_info[0].count == 0) return;
    flag1_count = __builtin_popcountll(flag1);
    flag2_count = __builtin_popcountll(flag2);

    //super bins memory allocation
    tid_t   t_count = g->get_total_types();
    
    if (0 == sgraph_in) {
        sgraph_in  = (lite_sgraph_t**) calloc (sizeof(lite_sgraph_t*), t_count);
    }
    prep_sgraph(flag2, sgraph_in);
    
    if (0 == skv_out) {
        skv_out  = (lite_skv_t**) calloc (sizeof(lite_skv_t*), t_count);
    }

    skv_out  = prep_skv(flag1, skv_out);
}

void p_many2one_t::calc_degree()
{
    //estimate edge count
    calc_edge_count_in(sgraph_in);
}

void p_many2one_t::make_graph_baseline()
{
    if (batch_info[0].count == 0) return;
    
    //prefix sum then reset the count
    prep_sgraph_internal(sgraph_in);

    //populate and get the original count back
    //handle kv_out as well.
    fill_adj_list_in(skv_out, sgraph_in);
    update_count(sgraph_in);
    
    //clean up
    cleanup();
}

void p_many2one_t::store_graph_baseline()
{
    store_skv(skv_out);
    store_sgraph(sgraph_in);
}

void p_many2one_t::read_graph_baseline()
{
    tid_t   t_count = g->get_total_types();
    
    if (0 == skv_out) {
        skv_out  = (lite_skv_t**) calloc (sizeof(lite_skv_t*), t_count);
    }
    read_skv(skv_out);
    
    if (0 == sgraph_in) {
        sgraph_in  = (lite_sgraph_t**) calloc (sizeof(lite_sgraph_t*), t_count);
    }
    read_sgraph(sgraph_in);
}

/*******************************************/
void p_one2many_t::prep_graph_baseline()
{
    if (batch_info[0].count == 0) return;
    flag1_count = __builtin_popcountll(flag1);
    flag2_count = __builtin_popcountll(flag2);

    //super bins memory allocation
    tid_t   t_count = g->get_total_types();
    
    if (0 == sgraph_out) {
        sgraph_out  = (lite_sgraph_t**) calloc (sizeof(lite_sgraph_t*), t_count);
    }
    prep_sgraph(flag1, sgraph_out);
    
    if (0 == skv_in) {
        skv_in  = (lite_skv_t**) calloc (sizeof(lite_skv_t*), t_count);
    }
    
    skv_in   = prep_skv(flag2, skv_in);
}
    
void p_one2many_t::calc_degree()
{
    //estimate edge count
    calc_edge_count_out(sgraph_out);
}
    
void p_one2many_t::make_graph_baseline()
{
    if (batch_info[0].count == 0) return;
    
    //prefix sum then reset the count
    prep_sgraph_internal(sgraph_out);

    //populate and get the original count back
    //handle kv_in as well.
    fill_adj_list_out(sgraph_out, skv_in);
    update_count(sgraph_out);
    
    //clean up
    cleanup();
}

void p_one2many_t::store_graph_baseline()
{
    store_sgraph(sgraph_out);
    store_skv(skv_in);
}

void p_one2many_t::read_graph_baseline()
{
    tid_t   t_count = g->get_total_types();
    
    if (0 == sgraph_out) {
        sgraph_out  = (lite_sgraph_t**) calloc (sizeof(lite_sgraph_t*), t_count);
    }
    read_sgraph(sgraph_out);
    
    if (0 == skv_in) {
        skv_in  = (lite_skv_t**) calloc (sizeof(lite_skv_t*), t_count);
    }
    read_skv(skv_in);
}

/************************************************/
void p_one2one_t::prep_graph_baseline()
{
    if (batch_info[0].count == 0) return;
    flag1_count = __builtin_popcountll(flag1);
    flag2_count = __builtin_popcountll(flag2);
    tid_t   t_count    = g->get_total_types();

    //super bins memory allocation
    
    if (0 == skv_in) {
        skv_in  = (lite_skv_t**) calloc (sizeof(lite_skv_t*), t_count);
    }
    skv_in  = prep_skv(flag2, skv_in);
    
    if (0 == skv_out) {
        skv_out  = (lite_skv_t**) calloc (sizeof(lite_skv_t*), t_count);
    }
    skv_out = prep_skv(flag1, skv_out);
}

void p_one2one_t::calc_degree()
{
}

void p_one2one_t::make_graph_baseline()
{
    if (batch_info[0].count == 0) return;

    //handle kv_out as well as kv_in.
    fill_skv(skv_out, skv_in);
    
    //clean up
    cleanup();
}

void p_one2one_t::store_graph_baseline()
{
    store_skv(skv_out);
    store_skv(skv_in);
}

void p_one2one_t::read_graph_baseline()
{
    tid_t   t_count    = g->get_total_types();
    
    if (0 == skv_out) {
        skv_out  = (lite_skv_t**) calloc (sizeof(lite_skv_t*), t_count);
    }
    read_skv(skv_out);
    
    if (0 == skv_in) {
        skv_in  = (lite_skv_t**) calloc (sizeof(lite_skv_t*), t_count);
    }
    read_skv(skv_in);
}

/*
lite_sgraph_t** p_pgraph_t::prep_sgraph(sflag_t ori_flag, lite_sgraph_t** sgraph)
{
    tid_t   pos = 0;//it is tid
    
    sflag_t      flag = ori_flag;
    tid_t  flag_count = __builtin_popcountll(flag);
    
    for(tid_t i = 0; i < flag_count; i++) {
        pos = __builtin_ctzll(flag);
        flag ^= (1L << pos);//reset that position
        if (0 == sgraph[pos]) {
            sgraph[pos] = new lite_sgraph_t;
        }
        sgraph[pos]->setup(pos);
    }
    return sgraph;
}

//estimate edge count
void p_pgraph_t::calc_edge_count(lite_sgraph_t** sgraph_out, lite_sgraph_t** sgraph_in) 
{
    sid_t     src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    ledge_t*   edges;
    index_t   count;
    
    for (int j = 0; j <= batch_count; ++j) { 
        edges = (ledge_t*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            src = edges[i].src_id;
            dst = get_sid(edges[i].dst_id);
            
            src_index = TO_TID(src);
            dst_index = TO_TID(dst);
            vert1_id = TO_VID(src);
            vert2_id = TO_VID(dst);
            
            if (!IS_DEL(src)) { 
                sgraph_out[src_index]->increment_count(vert1_id);
                sgraph_in[dst_index]->increment_count(vert2_id);
            } else { 
            }
        }
    }
}

//estimate edge count
void p_pgraph_t::calc_edge_count_out(lite_sgraph_t** sgraph_out)
{
    sid_t     src;
    vid_t     vert1_id;
    tid_t     src_index;
    ledge_t*   edges;
    index_t   count;

    for (int j = 0; j <= batch_count; ++j) { 
        edges = (ledge_t*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            src = edges[i].src_id;
            src_index = TO_TID(src);
            vert1_id = TO_VID(src);
            if (!IS_DEL(src)) {
                sgraph_out[src_index]->increment_count(vert1_id);
            } else {
            }
        }
    }
}
//estimate edge count
void p_pgraph_t::calc_edge_count_in(lite_sgraph_t** sgraph_in)
{
    sid_t     dst;
    vid_t     vert2_id;
    tid_t     dst_index;
    ledge_t*  edges;
    index_t   count;
    
    for (int j = 0; j <= batch_count; ++j) { 
        edges = (ledge_t*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            dst = get_sid(edges[i].dst_id);
            dst_index = TO_TID(dst);
            vert2_id = TO_VID(dst);
            sgraph_in[dst_index]->increment_count(vert2_id);
        }
    }
}


//prefix sum, allocate adj list memory then reset the count
void p_pgraph_t::prep_sgraph_internal(lite_sgraph_t** sgraph)
{
    tid_t       t_count = g->get_total_types();
    
    for(tid_t i = 0; i < t_count; i++) {
        if (0 == sgraph[i]) continue;
        sgraph[i]->setup_adjlist();
    }
}
*/

/////////// QUERIES ///////////////////////////
/*
status_t p_pgraph_t::query_adjlist_td(lite_sgraph_t** sgraph, srset_t* iset, srset_t* oset)
{
    tid_t    iset_count = iset->get_rset_count();
    rset_t*        rset = 0;

    for (tid_t i = 0; i < iset_count; ++i) {
        rset = iset->rset + i;
        vid_t v_count = rset->get_vcount();
        vid_t* vlist = rset->get_vlist();
        
        //get the graph where we will traverse
        tid_t        tid = rset->get_tid();
        if (0 == sgraph[tid]) continue;
        lite_vtable_t* graph = sgraph[tid]->get_begpos();

        
        //Get the frontiers
        vid_t     frontier;
        for (vid_t v = 0; v < v_count; v++) {
            frontier = vlist[v];
            lite_edge_t* adj_list = graph[frontier].get_adjlist();
            vid_t nebr_count = get_nebrcount1(adj_list);
            ++adj_list;
            
            //traverse the adj list
            for (vid_t k = 0; k < nebr_count; ++k) {
                oset->set_status(get_nebr(adj_list, k));
            }
        }
    }
    return eOK;
}
status_t p_pgraph_t::query_kv_td(lite_skv_t** skv, srset_t* iset, srset_t* oset)
{
    tid_t    iset_count = iset->get_rset_count();
    rset_t*        rset = 0;

    for (tid_t i = 0; i < iset_count; ++i) {
        rset = iset->rset + i;
        vid_t v_count = rset->get_vcount();
        vid_t* vlist = rset->get_vlist();
        
        //get the graph where we will traverse
        tid_t        tid = rset->get_tid();
        if (0 == skv[tid]) continue;
        lite_edge_t* kv = skv[tid]->get_kv(); 

        //Get the frontiers
        vid_t     frontier;
        for (vid_t v = 0; v < v_count; v++) {
            frontier = vlist[v];
            oset->set_status(get_nebr(kv, frontier));
        }
    }
    return eOK;
}

//sgraph_in and oset share the same flag.
status_t p_pgraph_t::query_adjlist_bu(lite_sgraph_t** sgraph, srset_t* iset, srset_t* oset)
{
    rset_t* rset = 0;
    tid_t   tid  = 0;
    tid_t oset_count = oset->get_rset_count();

    for (tid_t i = 0; i < oset_count; ++i) {
        
        //get the graph where we will traverse
        rset = oset->rset + i;
        tid  = rset->get_tid();
        if (0 == sgraph[tid]) continue; 

        lite_vtable_t* graph = sgraph[tid]->get_begpos(); 
        vid_t    v_count = sgraph[tid]->get_vcount();
        
        
        for (vid_t v = 0; v < v_count; v++) {
            //traverse the adj list
            lite_edge_t* adj_list = graph[v].get_adjlist();
            vid_t nebr_count = get_nebrcount1(adj_list);
            ++adj_list;
            for (vid_t k = 0; k < nebr_count; ++k) {
                if (iset->get_status(get_nebr(adj_list, k))) {
                    rset->set_status(v);
                    break;
                }
            }
        }
    }
    return eOK;
}

status_t p_pgraph_t::query_kv_bu(lite_skv_t** skv, srset_t* iset, srset_t* oset) 
{
    rset_t*  rset = 0;
    tid_t    tid  = 0;
    tid_t    oset_count = oset->get_rset_count();
    for (tid_t i = 0; i < oset_count; ++i) {

        //get the graph where we will traverse
        rset = oset->rset + i;
        tid  = rset->get_tid(); 
        if (0 == skv[tid]) continue;

        lite_edge_t* kv = skv[tid]->get_kv(); 
        sid_t   v_count = skv[tid]->get_vcount();
        
        for (vid_t v = 0; v < v_count; ++v) {
            if (iset->get_status(get_nebr(kv, v))) {
                rset->set_status(v);
                break;
            }
        }
    }
    return eOK;
}

//////extend functions ------------------------
status_t 
p_pgraph_t::extend_adjlist_td(lite_sgraph_t** sgraph, srset_t* iset, srset_t* oset)
{
    tid_t    iset_count = iset->get_rset_count();
    rset_t*        rset = 0;
    rset_t*        rset2 = 0;

    iset->bitwise2vlist();
    //prepare the output 1,2;
    oset->copy_setup(iset, eAdjlist);

    for (tid_t i = 0; i < iset_count; ++i) {
        rset = iset->rset + i;
        rset2 = oset->rset + i;
        vid_t v_count = rset->get_vcount();
        sid_t* varray = rset->get_vlist();
        
        //get the graph where we will traverse
        tid_t        tid = rset->get_tid();
        if (0 == sgraph[tid]) continue;
        lite_vtable_t* graph = sgraph[tid]->get_begpos(); 
        
        for (vid_t v = 0; v < v_count; v++) {
            rset2->add_adjlist_ro(v, graph+varray[v]);
        }
    }
    return eOK;
}

status_t 
p_pgraph_t::extend_kv_td(lite_skv_t** skv, srset_t* iset, srset_t* oset)
{
    tid_t    iset_count = iset->get_rset_count();
    rset_t*        rset = 0;
    rset_t*       rset2 = 0;

    iset->bitwise2vlist();
    //prepare the output 1,2;
    oset->copy_setup(iset, eKV);

    for (tid_t i = 0; i < iset_count; ++i) {
        rset = iset->rset + i;
        rset2 = oset->rset + i;
        vid_t v_count = rset->get_vcount();
        sid_t* varray = rset->get_vlist();
        
        //get the graph where we will traverse
        tid_t     tid = rset->get_tid();
        if (0 == skv[tid]) continue;
        lite_edge_t*  graph = skv[tid]->get_kv(); 
        
        for (vid_t v = 0; v < v_count; v++) {
            rset2->add_kv(v, get_nebr(graph, varray[v]));
        }
    }
    return eOK;
}
*/
cfinfo_t* p_ugraph_t::create_instance()
{
    return new p_ugraph_t;
}

cfinfo_t* p_dgraph_t::create_instance()
{
    return new p_dgraph_t;
}

cfinfo_t* p_one2one_t::create_instance()
{
    return new p_one2one_t;
}

cfinfo_t* p_one2many_t::create_instance()
{
    return new p_one2many_t;
}

cfinfo_t* p_many2one_t::create_instance()
{
    return new p_many2one_t;
}
//////
void p_ugraph_t::incr_count(sid_t src, sid_t dst, int del /*= 0*/)
{
    vid_t vert1_id = TO_VID(src);
    vid_t vert2_id = TO_VID(dst);
    
    tid_t src_index = TO_TID(src);
    tid_t dst_index = TO_TID(dst);
    
    
    if (del) { 
        sgraph[src_index]->increment_count(vert1_id);
        sgraph[dst_index]->increment_count(vert2_id);
    } else { 
        sgraph[src_index]->decrement_count(vert1_id);
        sgraph[dst_index]->decrement_count(vert2_id);
    }
}

void p_dgraph_t::incr_count(sid_t src, sid_t dst, int del /*= 0*/)
{
    tid_t src_index = TO_TID(src);
    tid_t dst_index = TO_TID(dst);
    
    vid_t vert1_id = TO_VID(src);
    vid_t vert2_id = TO_VID(dst);
    
    if (del) { 
        sgraph_out[src_index]->increment_count(vert1_id);
        sgraph_in[dst_index]->increment_count(vert2_id);
    } else { 
        sgraph_out[src_index]->decrement_count(vert1_id);
        sgraph_in[dst_index]->decrement_count(vert2_id);
    }
}

void p_one2one_t::incr_count(sid_t src, sid_t dst, int del /*= 0*/)
{
}

void p_one2many_t::incr_count(sid_t src, sid_t dst, int del /*= 0*/)
{
    tid_t dst_index = TO_TID(dst);
    
    vid_t vert2_id = TO_VID(dst);
    
    if (del) { 
        sgraph_in[dst_index]->increment_count(vert2_id);
    } else { 
        sgraph_in[dst_index]->decrement_count(vert2_id);
    }
}

void p_many2one_t::incr_count(sid_t src, sid_t dst, int del /*= 0*/)
{
    tid_t src_index = TO_TID(src);
    
    vid_t vert1_id = TO_VID(src);
    
    if (del) { 
        sgraph_out[src_index]->increment_count(vert1_id);
    } else { 
        sgraph_out[src_index]->decrement_count(vert1_id);
    }
}
