#include "graph.h"


pgraph_t::pgraph_t()
{
}

//Applicable to graphs only, labels should be aware of it.
status_t pgraph_t::batch_update(const string& src, const string& dst, propid_t pid /* = 0 */)
{
    vid_t src_id, dst_id;
    index_t index = 0;
    edge_t* edges;

    if (batch_info1[batch_count1].count == MAX_ECOUNT) {
        void* mem = alloc_buf();
        if (mem == 0) return eEndBatch;
        ++batch_count1;
        batch_info1[batch_count1].count = 0;
        batch_info1[batch_count1].buf = mem; 
    }
    
    map<string, vid_t>::iterator str2vid_iter = g->str2vid.find(src);
    if (g->str2vid.end() == str2vid_iter) {
       cout << src << " is not found. See above log if src was invalid. OR is it out of order?? " << endl; 
    } else {
        src_id = str2vid_iter->second;
    }
    tid_t type_id = TO_TID(src_id);
    flag1 |= TID_TO_SFLAG(type_id);
    
    str2vid_iter = g->str2vid.find(dst);
    if (g->str2vid.end() == str2vid_iter) {
        assert(0);
       cout << dst << " is not found. See above log if dst was invalid. OR is it out of order?? " << endl; 
    } else {
        dst_id = str2vid_iter->second;
    }
    type_id = TO_TID(dst_id);
    flag2 |= TID_TO_SFLAG(type_id);
    
    index = batch_info1[batch_count1].count++;
    edges = (edge_t*) batch_info1[batch_count1].buf;

    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
    return eOK;
}

//super bins memory allocation
sgraph_t** pgraph_t::prep_sgraph(sflag_t ori_flag, sgraph_t** sgraph )
{
    tid_t   pos = 0;//it is tid
    
    sflag_t      flag = ori_flag;
    tid_t  flag_count = __builtin_popcountll(flag);
    
    for(tid_t i = 0; i < flag_count; i++) {
        pos = __builtin_ctzll(flag);
        flag ^= (1L << pos);//reset that position
        if (0 == sgraph[pos]) {
            sgraph[pos] = new sgraph_t;
        }
        sgraph[pos]->setup(pos);
    }
    return sgraph;
}

//estimate edge count
void pgraph_t::calc_edge_count(sgraph_t** sgraph_out, sgraph_t** sgraph_in) 
{
    sid_t     src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    edge_t*   edges;
    index_t   count;
    
    for (int j = 0; j <= batch_count; ++j) { 
        edges = (edge_t*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            src = edges[i].src_id;
            dst = edges[i].dst_id;
            
            src_index = TO_TID(src);
            dst_index = TO_TID(dst);
            vert1_id = TO_VID(src);
            vert2_id = TO_VID(dst);
            
            sgraph_out[src_index]->increment_count(vert1_id);
            sgraph_in[dst_index]->increment_count(vert2_id);
        }
    }
}

//estimate edge count
void pgraph_t::calc_edge_count_out(sgraph_t** sgraph_out)
{
    sid_t     src;
    vid_t     vert1_id;
    tid_t     src_index;
    edge_t*   edges;
    index_t   count;

    for (int j = 0; j <= batch_count; ++j) { 
        edges = (edge_t*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            src = edges[i].src_id;
            src_index = TO_TID(src);
            vert1_id = TO_VID(src);
            sgraph_out[src_index]->increment_count(vert1_id);
        }
    }
}
//estimate edge count
void pgraph_t::calc_edge_count_in(sgraph_t** sgraph_in)
{
    sid_t     dst;
    vid_t     vert2_id;
    tid_t     dst_index;
    edge_t*   edges;
    index_t   count;
    
    for (int j = 0; j <= batch_count; ++j) { 
        edges = (edge_t*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            dst = edges[i].dst_id;
            dst_index = TO_TID(dst);
            vert2_id = TO_VID(dst);
            sgraph_in[dst_index]->increment_count(vert2_id);
        }
    }
}

//prefix sum, allocate adj list memory then reset the count
void pgraph_t::prep_sgraph_internal(sgraph_t** sgraph)
{
    tid_t       t_count = g->get_total_types();
    
    for(tid_t i = 0; i < t_count; i++) {
        if (0 == sgraph[i]) continue;
        sgraph[i]->setup_adjlist();
    }
}

void pgraph_t::fill_adj_list(sgraph_t** sgraph_out, sgraph_t** sgraph_in)
{
    sid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    
    edge_t*   edges;
    index_t   count;

    for (int j = 0; j <= batch_count; ++j) { 
        edges = (edge_t*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            src = edges[i].src_id;
            dst = edges[i].dst_id;
            src_index = TO_TID(src);
            dst_index = TO_TID(dst);
            vert1_id = TO_VID(src);
            vert2_id = TO_VID(dst);
            
            sgraph_out[src_index]->add_nebr(vert1_id, dst);
            sgraph_in[dst_index]->add_nebr(vert2_id, src);
        }
    }
}

void pgraph_t::fill_adj_list_in(skv_t** skv_out, sgraph_t** sgraph_in) 
{
    sid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    edge_t*   edges;
    index_t   count;
    
    for (int j = 0; j <= batch_count; ++j) { 
        edges = (edge_t*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            src = edges[i].src_id;
            dst = edges[i].dst_id;
            src_index = TO_TID(src);
            dst_index = TO_TID(dst);
            
            vert1_id = TO_VID(src);
            skv_out[src_index]->set_value(vert1_id, dst);
            
            vert2_id = TO_VID(dst);
            sgraph_in[dst_index]->add_nebr(vert2_id, src);
        }
    }
}

void pgraph_t::fill_adj_list_out(sgraph_t** sgraph_out, skv_t** skv_in) 
{
    sid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t src_index, dst_index; 
    edge_t*   edges;
    index_t   count;
    
    for (int j = 0; j <= batch_count; ++j) { 
        edges = (edge_t*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            src = edges[i].src_id;
            dst = edges[i].dst_id;
            src_index = TO_TID(src);
            dst_index = TO_TID(dst);
            
            vert1_id = TO_VID(src);
            sgraph_out[src_index]->add_nebr(vert1_id, dst);
            
            vert2_id = TO_VID(dst);
            skv_in[dst_index]->set_value(vert2_id, src); 
        }
    }
}

void pgraph_t::update_count(sgraph_t** sgraph)
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

void pgraph_t::store_sgraph(sgraph_t** sgraph, string dir, string postfix)
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

void pgraph_t::read_sgraph(sgraph_t** sgraph, string dir, string postfix)
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
        
        sgraph[i] = new sgraph_t;
        sgraph[i]->setup(i);
        sgraph[i]->read_vtable(vtfile);
        sgraph[i]->read_etable(etfile);
    }
}

/******************** super kv *************************/
void pgraph_t::read_skv(skv_t** skv, string dir, string postfix)
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

        skv[i] = new skv_t;
        skv[i]->setup(i);
        skv[i]->read_kv(vtfile);
    }
}

void pgraph_t::store_skv(skv_t** skv, string dir, string postfix)
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
skv_t** pgraph_t::prep_skv(sflag_t ori_flag, skv_t** skv)
{
    tid_t   pos  = 0;
    sflag_t flag       = ori_flag;
    tid_t   flag_count = __builtin_popcountll(flag);

    for(tid_t i = 0; i < flag_count; i++) {
        pos = __builtin_ctz(flag);
        flag ^= (1L << pos);//reset that position
        if (0 == skv[pos]) {
            skv[pos] = new skv_t;
        }
        skv[pos]->setup(pos);
    }
    return skv;
}

void pgraph_t::fill_skv(skv_t** skv_out, skv_t** skv_in)
{
    sid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    edge_t*   edges;
    index_t   count;
    
    for (int j = 0; j <= batch_count; ++j) { 
        edges = (edge_t*)batch_info[j].buf;
        count = batch_info[j].count;
    
        for (index_t i = 0; i < count; ++i) {
            src = edges[i].src_id;
            dst = edges[i].dst_id;
            src_index = TO_TID(src);
            dst_index = TO_TID(dst);
            
            vert1_id = TO_VID(src);
            skv_out[src_index]->set_value(vert1_id, dst); 
            
            vert2_id = TO_VID(dst);
            skv_in[dst_index]->set_value(vert2_id, src); 
        }
    }
}

/************* Semantic graphs  *****************/

//We assume that no new vertex type is defined
void dgraph_t::make_graph_baseline()
{
    if (batch_info[0].count == 0) return;
    flag1_count = __builtin_popcountll(flag1);
    flag2_count = __builtin_popcountll(flag2);

    //super bins memory allocation
    tid_t   t_count = g->get_total_types();
    
    if (0 == sgraph_out) {
        sgraph_out  = (sgraph_t**) calloc (sizeof(sgraph_t*), t_count);
    }
    prep_sgraph(flag1, sgraph_out);    
    
    if (0 == sgraph_in) {
        sgraph_in  = (sgraph_t**) calloc (sizeof(sgraph_t*), t_count);
    }
    prep_sgraph(flag2, sgraph_in);

    //estimate edge count
    calc_edge_count(sgraph_out, sgraph_in);
    
    
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


void dgraph_t::store_graph_baseline(string dir)
{
    string postfix = "out";
    store_sgraph(sgraph_out, dir, postfix);
    postfix = "in";
    store_sgraph(sgraph_in,  dir, postfix);
}

void dgraph_t::read_graph_baseline(const string& dir)
{
    tid_t   t_count    = g->get_total_types();
    
    string postfix = "out";
    if (0 == sgraph_out) {
        sgraph_out  = (sgraph_t**) calloc (sizeof(sgraph_t*), t_count);
    }
    read_sgraph(sgraph_out, dir, postfix);
    
    postfix = "in";
    if (0 == sgraph_in) {
        sgraph_in  = (sgraph_t**) calloc (sizeof(sgraph_t*), t_count);
    }
    read_sgraph(sgraph_in,  dir, postfix);
}


/*******************************************/
void ugraph_t::make_graph_baseline()
{
    if (batch_info[0].count == 0) return;
    flag1 = flag1 | flag2;
    flag2 = flag1;

    flag1_count = __builtin_popcountll(flag1);
    flag2_count = flag1_count;

    //super bins memory allocation
    tid_t   t_count = g->get_total_types();
    
    if (0 == sgraph) {
        sgraph  = (sgraph_t**) calloc (sizeof(sgraph_t*), t_count);
    }
    prep_sgraph(flag1, sgraph);    

    //estimate edge count
    calc_edge_count(sgraph, sgraph);
    
    //prefix sum then reset the count
    //Take symmetry into consideration
    prep_sgraph_internal(sgraph);

    //populate and get the original count back
    fill_adj_list(sgraph, sgraph);
    update_count(sgraph);

    //clean up
    cleanup();
}

void ugraph_t::store_graph_baseline(string dir)
{
    string postfix = "";
    store_sgraph(sgraph, dir, postfix);
}

void ugraph_t::read_graph_baseline(const string& dir)
{
    tid_t   t_count = g->get_total_types();
    string postfix = "";
    
    if (0 == sgraph) {
        sgraph  = (sgraph_t**) calloc (sizeof(sgraph_t*), t_count);
    }
    read_sgraph(sgraph, dir, postfix);
}


/***************************************/
void many2one_t::make_graph_baseline()
{
    if (batch_info[0].count == 0) return;
    flag1_count = __builtin_popcountll(flag1);
    flag2_count = __builtin_popcountll(flag2);

    //super bins memory allocation
    tid_t   t_count = g->get_total_types();
    
    if (0 == sgraph_in) {
        sgraph_in  = (sgraph_t**) calloc (sizeof(sgraph_t*), t_count);
    }
    prep_sgraph(flag2, sgraph_in);
    
    if (0 == skv_out) {
        skv_out  = (skv_t**) calloc (sizeof(skv_t*), t_count);
    }

    skv_out  = prep_skv(flag1, skv_out);

    //estimate edge count
    calc_edge_count_in(sgraph_in);
    
    
    //prefix sum then reset the count
    prep_sgraph_internal(sgraph_in);

    //populate and get the original count back
    //handle kv_out as well.
    fill_adj_list_in(skv_out, sgraph_in);
    update_count(sgraph_in);
    
    //clean up
    cleanup();
}

void many2one_t::store_graph_baseline(string dir)
{
    string postfix = "out";
    store_skv(skv_out, dir, postfix);
    postfix = "in";
    store_sgraph(sgraph_in, dir, postfix);
}

void many2one_t::read_graph_baseline(const string& dir)
{
    tid_t   t_count = g->get_total_types();
    
    if (0 == skv_out) {
        skv_out  = (skv_t**) calloc (sizeof(skv_t*), t_count);
    }
    string postfix = "out";
    read_skv(skv_out, dir, postfix);
    
    if (0 == sgraph_in) {
        sgraph_in  = (sgraph_t**) calloc (sizeof(sgraph_t*), t_count);
    }
    postfix = "in";
    read_sgraph(sgraph_in, dir, postfix);
}

/*******************************************/
void one2many_t::make_graph_baseline()
{
    if (batch_info[0].count == 0) return;
    flag1_count = __builtin_popcountll(flag1);
    flag2_count = __builtin_popcountll(flag2);

    //super bins memory allocation
    tid_t   t_count = g->get_total_types();
    
    if (0 == sgraph_out) {
        sgraph_out  = (sgraph_t**) calloc (sizeof(sgraph_t*), t_count);
    }
    prep_sgraph(flag1, sgraph_out);
    
    if (0 == skv_in) {
        skv_in  = (skv_t**) calloc (sizeof(skv_t*), t_count);
    }
    
    skv_in   = prep_skv(flag2, skv_in);

    //estimate edge count
    calc_edge_count_out(sgraph_out);
    
    
    //prefix sum then reset the count
    prep_sgraph_internal(sgraph_out);

    //populate and get the original count back
    //handle kv_in as well.
    fill_adj_list_out(sgraph_out, skv_in);
    update_count(sgraph_out);
    
    //clean up
    cleanup();
}

void one2many_t::store_graph_baseline(string dir)
{
    string postfix = "out";
    store_sgraph(sgraph_out, dir, postfix);
    postfix = "in";
    store_skv(skv_in, dir, postfix);
}

void one2many_t::read_graph_baseline(const string& dir)
{
    tid_t   t_count = g->get_total_types();
    
    if (0 == sgraph_out) {
        sgraph_out  = (sgraph_t**) calloc (sizeof(sgraph_t*), t_count);
    }
    string postfix = "out";
    read_sgraph(sgraph_out, dir, postfix);
    
    if (0 == skv_in) {
        skv_in  = (skv_t**) calloc (sizeof(skv_t*), t_count);
    }
    postfix = "in";
    read_skv(skv_in, dir, postfix);
}

/************************************************/
void one2one_t::make_graph_baseline()
{
    if (batch_info[0].count == 0) return;
    flag1_count = __builtin_popcountll(flag1);
    flag2_count = __builtin_popcountll(flag2);
    tid_t   t_count    = g->get_total_types();

    //super bins memory allocation
    
    if (0 == skv_in) {
        skv_in  = (skv_t**) calloc (sizeof(skv_t*), t_count);
    }
    skv_in  = prep_skv(flag2, skv_in);
    
    if (0 == skv_out) {
        skv_out  = (skv_t**) calloc (sizeof(skv_t*), t_count);
    }
    skv_out = prep_skv(flag1, skv_out);

    //handle kv_out as well as kv_in.
    fill_skv(skv_out, skv_in);
    
    //clean up
    cleanup();
}

void one2one_t::store_graph_baseline(string dir)
{
    string postfix = "out";
    store_skv(skv_out, dir, postfix);
    postfix = "in";
    store_skv(skv_in, dir, postfix);
}

void one2one_t::read_graph_baseline(const string& dir)
{
    tid_t   t_count    = g->get_total_types();
    
    string postfix = "out";
    if (0 == skv_out) {
        skv_out  = (skv_t**) calloc (sizeof(skv_t*), t_count);
    }
    read_skv(skv_out, dir, postfix);
    
    postfix = "in";
    if (0 == skv_in) {
        skv_in  = (skv_t**) calloc (sizeof(skv_t*), t_count);
    }
    read_skv(skv_in, dir, postfix);
}

/////////// QUERIES ///////////////////////////
status_t pgraph_t::query_adjlist_td(sgraph_t** sgraph, srset_t* iset, srset_t* oset)
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
        beg_pos_t* graph = sgraph[tid]->get_begpos();

        
        //Get the frontiers
        vid_t     frontier;
        for (vid_t v = 0; v < v_count; v++) {
            frontier = vlist[v];
            sid_t* adj_list = graph[frontier].get_adjlist();
            vid_t nebr_count = adj_list[0];
            ++adj_list;
            
            //traverse the adj list
            for (vid_t k = 0; k < nebr_count; ++k) {
                oset->set_status(adj_list[k]);
            }
        }
    }
    return eOK;
}

status_t pgraph_t::query_kv_td(skv_t** skv, srset_t* iset, srset_t* oset)
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
        sid_t* kv = skv[tid]->get_kv(); 

        //Get the frontiers
        vid_t     frontier;
        for (vid_t v = 0; v < v_count; v++) {
            frontier = vlist[v];
            oset->set_status(kv[frontier]);
        }
    }
    return eOK;
}

//sgraph_in and oset share the same flag.
status_t pgraph_t::query_adjlist_bu(sgraph_t** sgraph, srset_t* iset, srset_t* oset)
{
    rset_t* rset = 0;
    tid_t   tid  = 0;
    tid_t oset_count = oset->get_rset_count();

    for (tid_t i = 0; i < oset_count; ++i) {
        
        //get the graph where we will traverse
        rset = oset->rset + i;
        tid  = rset->get_tid();
        if (0 == sgraph[tid]) continue; 

        beg_pos_t* graph = sgraph[tid]->get_begpos(); 
        vid_t    v_count = sgraph[tid]->get_vcount();
        
        
        for (vid_t v = 0; v < v_count; v++) {
            //traverse the adj list
            sid_t* adj_list = graph[v].get_adjlist();
            vid_t nebr_count = adj_list[0];
            ++adj_list;
            for (vid_t k = 0; k < nebr_count; ++k) {
                if (iset->get_status(adj_list[k])) {
                    rset->set_status(v);
                    break;
                }
            }
        }
    }
    return eOK;
}

status_t pgraph_t::query_kv_bu(skv_t** skv, srset_t* iset, srset_t* oset) 
{
    rset_t*  rset = 0;
    tid_t    tid  = 0;
    tid_t    oset_count = oset->get_rset_count();
    for (tid_t i = 0; i < oset_count; ++i) {

        //get the graph where we will traverse
        rset = oset->rset + i;
        tid  = rset->get_tid(); 
        if (0 == skv[tid]) continue;

        vid_t*       kv = skv[tid]->get_kv(); 
        sid_t   v_count = skv[tid]->get_vcount();
        
        for (vid_t v = 0; v < v_count; ++v) {
            if (iset->get_status(kv[v])) {
                rset->set_status(v);
                break;
            }
        }
    }
    return eOK;
}
//////extend functions ------------------------
status_t 
pgraph_t::extend_adjlist_td(sgraph_t** sgraph, srset_t* iset, srset_t* oset)
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
        beg_pos_t* graph = sgraph[tid]->get_begpos(); 
        
        for (vid_t v = 0; v < v_count; v++) {
            rset2->add_adjlist_ro(v, graph+varray[v]);
        }
    }
    return eOK;
}

status_t 
pgraph_t::extend_kv_td(skv_t** skv, srset_t* iset, srset_t* oset)
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
        sid_t*  graph = skv[tid]->get_kv(); 
        
        for (vid_t v = 0; v < v_count; v++) {
            rset2->add_kv(v, graph[varray[v]]);
        }
    }
    return eOK;
}
