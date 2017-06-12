#include "graph.h"

lite_pgraph_t::lite_pgraph_t()
{
    cf_info = 0;
    p_info = 0;

    cf_count = 0;
    p_count = 0;
    edge_count = 0;
}

//Applicable to graphs only, labels should be aware of it.
status_t lite_pgraph_t::batch_update(const string& src, const string& dst, propid_t pid /* = 0 */)
{
    vid_t src_id, dst_id;
    index_t index = 0;
    ledge_t* edges;

    if (batch_info1[batch_count1].count == MAX_PECOUNT) {
        void* mem = alloc_buf();
        if (mem == 0) return eEndBatch;
        ++batch_count1;
        batch_info1[batch_count1].count = 0;
        batch_info1[batch_count1].buf = mem; 
    }
    
    map<string, vid_t>::iterator str2vid_iter = g->str2vid.find(src);
    if (g->str2vid.end() == str2vid_iter) {
        assert(0);
    } else {
        src_id = str2vid_iter->second;
    }
    tid_t type_id = TO_TID(src_id);
    flag1 |= TID_TO_SFLAG(type_id);
    
    str2vid_iter = g->str2vid.find(dst);
    if (g->str2vid.end() == str2vid_iter) {
        assert(0);
    } else {
        dst_id = str2vid_iter->second;
    }
    type_id = TO_TID(dst_id);
    flag2 |= TID_TO_SFLAG(type_id);
    
    index = batch_info1[batch_count1].count++;
    edges = (ledge_t*) batch_info1[batch_count1].buf;

    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
    edges[index].prop.value_eid = edge_count;//edge id is increment somewhere else.
    return eOK;
}

status_t lite_pgraph_t::batch_update(const string& src, const string& dst, propid_t pid,
                                propid_t count, prop_pair_t* prop_pair)
{
    //edge id is implicit. How ???
    batch_update(src, dst, pid);
    
    propid_t edge_pid;
    propid_t cf_id;
    map<string, propid_t>::iterator str2pid_iter;
    
    for (propid_t i = 0; i < count; i++) {
        str2pid_iter = str2pid.find(prop_pair[i].name);
        if (str2pid.end() == str2pid_iter) {
            assert(0);
        }
        edge_pid = str2pid_iter->second;
        cf_id = p_info[edge_pid].cf_id;
        
        cf_info[cf_id]->batch_update(edge_count, prop_pair[i].value, edge_pid);
    }
    
    ++edge_count;
    return eOK;
}

lite_sgraph_t** lite_pgraph_t::prep_sgraph(sflag_t ori_flag, lite_sgraph_t** sgraph)
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
void lite_pgraph_t::calc_edge_count(lite_sgraph_t** sgraph_out, lite_sgraph_t** sgraph_in) 
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
void lite_pgraph_t::calc_edge_count_out(lite_sgraph_t** sgraph_out)
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
            sgraph_out[src_index]->increment_count(vert1_id);
        }
    }
}
//estimate edge count
void lite_pgraph_t::calc_edge_count_in(lite_sgraph_t** sgraph_in)
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
            dst = edges[i].dst_id;
            dst_index = TO_TID(dst);
            vert2_id = TO_VID(dst);
            sgraph_in[dst_index]->increment_count(vert2_id);
        }
    }
}

//prefix sum, allocate adj list memory then reset the count
void lite_pgraph_t::prep_sgraph_internal(lite_sgraph_t** sgraph)
{
    tid_t       t_count = g->get_total_types();
    
    for(tid_t i = 0; i < t_count; i++) {
        if (0 == sgraph[i]) continue;
        sgraph[i]->setup_adjlist();
    }
}

void lite_pgraph_t::fill_adj_list(lite_sgraph_t** sgraph_out, lite_sgraph_t** sgraph_in)
{
    sid_t     src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    eid_t     eid;
    
    ledge_t*   edges;
    index_t   count;

    for (int j = 0; j <= batch_count; ++j) { 
        edges = (ledge_t*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            src = edges[i].src_id;
            dst = edges[i].dst_id;
            eid = edges[i].prop.value_eid;
            src_index = TO_TID(src);
            dst_index = TO_TID(dst);
            vert1_id = TO_VID(src);
            vert2_id = TO_VID(dst);
            
            
            sgraph_out[src_index]->add_nebr_lite(vert1_id, dst, eid);
            sgraph_in[dst_index]->add_nebr_lite(vert2_id, src, eid);
        }
    }
}

void lite_pgraph_t::fill_adj_list_in(lite_skv_t** skv_out, lite_sgraph_t** sgraph_in) 
{
    sid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    eid_t     eid;
    
    ledge_t*   edges;
    index_t   count;
    for (int j = 0; j <= batch_count; ++j) { 
        edges = (ledge_t*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            src = edges[i].src_id;
            dst = edges[i].dst_id;
            eid = edges[i].prop.value_eid;
            src_index = TO_TID(src);
            dst_index = TO_TID(dst);
            
            vert1_id = TO_VID(src);
            skv_out[src_index]->set_value_lite(vert1_id, dst, eid);
            
            vert2_id = TO_VID(dst);
            sgraph_in[dst_index]->add_nebr_lite(vert2_id, src, eid);
        }
    }
}

void lite_pgraph_t::fill_adj_list_out(lite_sgraph_t** sgraph_out, lite_skv_t** skv_in) 
{
    sid_t   src, dst;
    vid_t   vert1_id, vert2_id;
    tid_t   src_index, dst_index; 
    eid_t   eid;
    
    ledge_t*   edges;
    index_t   count;
    
    for (int j = 0; j <= batch_count; ++j) { 
        edges = (ledge_t*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            src = edges[i].src_id;
            dst = edges[i].dst_id;
            eid = edges[i].prop.value_eid;
            src_index = TO_TID(src);
            dst_index = TO_TID(dst);
            
            vert1_id = TO_VID(src);
            sgraph_out[src_index]->add_nebr_lite(vert1_id, dst, eid);
            
            vert2_id = TO_VID(dst);
            skv_in[dst_index]->set_value_lite(vert2_id, src, eid); 
        }
    }
}

void lite_pgraph_t::update_count(lite_sgraph_t** sgraph)
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

void lite_pgraph_t::store_sgraph(lite_sgraph_t** sgraph, string dir, string postfix)
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

void lite_pgraph_t::read_sgraph(lite_sgraph_t** sgraph, string dir, string postfix)
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

/******************** super kv *************************/
void lite_pgraph_t::read_skv(lite_skv_t** skv, string dir, string postfix)
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

void lite_pgraph_t::store_skv(lite_skv_t** skv, string dir, string postfix)
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
lite_skv_t** lite_pgraph_t::prep_skv(sflag_t ori_flag, lite_skv_t** skv)
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

void lite_pgraph_t::fill_skv(lite_skv_t** skv_out, lite_skv_t** skv_in)
{
    sid_t     src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    eid_t     eid;
    ledge_t*   edges;
    index_t   count;
    
    for (int j = 0; j <= batch_count; ++j) {
        edges = (ledge_t*)batch_info[j].buf;
        count = batch_info[j].count;
    
        for (index_t i = 0; i < count; ++i) {
            src = edges[i].src_id;
            dst = edges[i].dst_id;
            eid = edges[i].prop.value_eid;
            src_index = TO_TID(src);
            dst_index = TO_TID(dst);
            
            vert1_id = TO_VID(src);
            skv_out[src_index]->set_value_lite(vert1_id, dst, eid); 
            
            vert2_id = TO_VID(dst);
            skv_in[dst_index]->set_value_lite(vert2_id, src, eid); 
        }
    }
}
