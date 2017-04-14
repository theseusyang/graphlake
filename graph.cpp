#include "graph.h"

graph::graph()
{
    p_info = 0;
    p_count = 0;
    vert_count = 0;
    v_graph =  new vgraph_t;
}
sid_t graph::get_type_scount(tid_t type)
{
    typekv_t* typekv = dynamic_cast<typekv_t*>(p_info[0]);
    return typekv->get_type_scount(type);
}

void graph::type_update(const string& src, const string& dst)
{
    p_info[0]->batch_update(src, dst);
    /*
    vid_t       src_id;
    tid_t       type_id;
    vid_t       vert_id = 0;

    map<string, tid_t>::iterator str2enum_iter = str2enum.find(dst);
    if (str2enum.end() == str2enum_iter) {
        type_id = t_count++;
        vert_id = TO_SUPER(type_id);
        str2enum[dst] = type_id;
        t_info[type_id].vert_id = vert_id; 
        t_info[type_id].type_name = gstrdup(dst.c_str());
    } else {
        type_id = str2enum_iter->second;
        vert_id = t_info[type_id].vert_id;
    }

    //allocate class specific ids.
    map<string, vid_t>::iterator str2vid_iter = str2vid.find(src);
    if (str2vid.end() == str2vid_iter) {
        src_id = vert_id++;
        ++vert_count;
        str2vid[src] = src_id;
        //update the id
        t_info[type_id].vert_id = vert_id;
        v_graph->id2name(src_id, src);
    } else {
        //dublicate entry XXX
        src_id = str2vid_iter->second;
    }
    */
}

void graph::type_done()
{
    v_graph->make_graph_baseline();
}
    
propid_t graph::get_pid(const char* predicate)
{
    map<string, propid_t>::iterator str2pid_iter = str2pid.find(predicate);
    if (str2pid_iter == str2pid.end()) {
        return INVALID_PID;
    }
    return str2pid_iter->second;
}

sid_t graph::get_sid(const char* src)
{
    map<string, sid_t>::iterator str2vid_iter = str2vid.find(src);
    if (str2vid_iter == str2vid.end()) {
        return INVALID_SID;
    }
    return str2vid_iter->second;
}

/////////////////////////////////////////
void pinfo_t::batch_update(const string& src, const string& dst)
{
    assert(0);
}
    
void pinfo_t::make_graph_baseline()
{
    assert(0);
}

void pinfo_t::store_graph_baseline(string dir)
{
    assert(0);
}

/*
static int 
is_literal(string str) {
       return ('<' != str[0]);
}
*/
void pinfo_t::populate_property(const char* longname, const char* property_name)
{
    g->p_info[g->p_count] = this;
    g->str2pid[longname] = g->p_count;
    g->p_count++;
    
    p_name = gstrdup(property_name);
    p_longname = gstrdup(longname);

    buf = calloc(sizeof(vid_t), 1000000);
    count = 0; 

}


/************* Semantic graphs  *****************/
pgraph_t::pgraph_t()
{
    flag1 = 0;
    flag2 = 0;
    flag1_count = 0;
    flag2_count = 0;
}

//Applicable to graphs only, labels should be aware of it.
void pgraph_t::batch_update(const string& src, const string& dst)
{
    vid_t src_id, dst_id;
    index_t index = 0;
    edge_t* edges = (edge_t*) buf;

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

    index = count++;
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
}

//super bins memory allocation
sgraph_t* pgraph_t::prep_sgraph(sflag_t ori_flag, tid_t flag_count)
{
    vid_t v_count;
    sflag_t flag = ori_flag;
    sgraph_t* sgraph  = (sgraph_t*) calloc (sizeof(sgraph_t), flag_count);
    tid_t   pos = 0;
    sid_t super_id;

    for(tid_t i = 0; i < flag_count; i++) {
        pos = __builtin_ctzll(flag);
        flag ^= (1L << pos);//reset that position
        super_id = g->get_type_scount(pos);
        v_count = TO_VID(super_id);
        sgraph[i].beg_pos = (beg_pos_t*)calloc(sizeof(beg_pos_t), v_count);
        sgraph[i].super_id = super_id;
    } 
    return sgraph;
}

//estimate edge count
void pgraph_t::calc_edge_count(sgraph_t* sgraph_out, sgraph_t* sgraph_in) 
{
    sid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t src_index, dst_index;
    edge_t*   edges = (edge_t*) buf;  
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
		
		src_index = get_sindex(src, flag1);
		dst_index = get_sindex(dst,flag2);
		vert1_id = TO_VID(src);
		vert2_id = TO_VID(dst);
        
        sgraph_out[src_index].increment_count(vert1_id);
        sgraph_in[dst_index].increment_count(vert2_id);
    }
}

//estimate edge count
void pgraph_t::calc_edge_count_out(sgraph_t* sgraph_out)
{
    sid_t     src;
    vid_t     vert1_id;
    tid_t     src_index;

    edge_t*  edges = (edge_t*) buf;

    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
		src_index = get_sindex(src, flag1);
		vert1_id = TO_VID(src);
        sgraph_out[src_index].increment_count(vert1_id);
    }
}
//estimate edge count
void pgraph_t::calc_edge_count_in(sgraph_t* sgraph_in)
{
    sid_t     dst;
    vid_t     vert2_id;
    tid_t     dst_index;
    edge_t*   edges = (edge_t*) buf;
    for (index_t i = 0; i < count; ++i) {
        dst = edges[i].dst_id;
		dst_index = get_sindex(dst,flag2);
		vert2_id = TO_VID(dst);
        sgraph_in[dst_index].increment_count(vert2_id);
    }
}

//prefix sum, allocate adj list memory then reset the count
void pgraph_t::prep_sgraph_internal(sgraph_t* sgraph, index_t edge_count, tid_t sgraph_count)
{
    vid_t* adj_list = (vid_t*) calloc (sizeof(vid_t), edge_count);
    index_t     prefix = 0;
    beg_pos_t*  beg_pos = 0;
    vid_t       v_count = 0;
    
    for(tid_t i = 0; i < sgraph_count; i++) {
        beg_pos = sgraph[i].beg_pos;
        v_count = TO_VID(sgraph[i].super_id); 
        for (vid_t j = 0; j < v_count; ++j) {
            beg_pos[j].set_adjlist(adj_list + prefix);
            prefix += beg_pos[j].get_count();
            beg_pos[j].set_count(0);
        }
    }
}

void pgraph_t::fill_adj_list(sgraph_t* sgraph_out, sgraph_t* sgraph_in)
{
    sid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    edge_t*    edges = (edge_t*) buf;
    
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
		src_index = get_sindex(src, flag1);
		dst_index = get_sindex(dst,flag2);
        vert1_id = TO_VID(src);
        vert2_id = TO_VID(dst);
        
        sgraph_out[src_index].add_nebr(vert1_id, dst);
        sgraph_in[dst_index].add_nebr(vert2_id, src);
    }
}

void pgraph_t::fill_adj_list_in(skv_t* skv_out, sgraph_t* sgraph_in) 
{
    sid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    edge_t*   edges = (edge_t*) buf;
    
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
		src_index = get_sindex(src, flag1);
		dst_index = get_sindex(dst,flag2);
        
        vert1_id = TO_VID(src);
        skv_out[src_index].kv[vert1_id] = dst;
        
        vert2_id = TO_VID(dst);
        sgraph_in[dst_index].add_nebr(vert2_id, src);
    }
}

void pgraph_t::fill_adj_list_out(sgraph_t* sgraph_out, skv_t* skv_in) 
{
    sid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t src_index, dst_index; 
    edge_t*   edges = (edge_t*) buf;

    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
		src_index = get_sindex(src, flag1);
		dst_index = get_sindex(dst,flag2);
        
        vert1_id = TO_VID(src);
        sgraph_out[src_index].add_nebr(vert1_id, dst);
        
        vert2_id = TO_VID(dst);
        skv_in[dst_index].kv[vert2_id] = src; 
    }
}

void pgraph_t::store_sgraph(sgraph_t* sgraph, sflag_t flag, string dir, string postfix)
{
    /*
    vid_t v_count;
    //base name using relationship type
    string basefile = dir + p_name;
    string file;
    FILE* f;
    tid_t flag_count = __builtin_popcountll(flag);

    //Write individual files.
    for (tid_t i = 0; i < flag_count; ++i) {
        v_count = TO_VID(sgraph[i].super_id);
        file = basefile + itoa(i) + "beg_pos" + postfix;
        f = fopen(file.c_str(), "wb");
        assert(f != 0);
        fwrite(sgraph[i].beg_pos, sizeof(), v_count + 1);
    }

    */
    
}

/******************** super kv *************************/
//super bins memory allocation
skv_t* pgraph_t::prep_skv(sflag_t ori_flag, tid_t flag_count)
{
    sflag_t flag = ori_flag;
    skv_t*  skv  = (skv_t*) calloc (sizeof(skv_t), flag_count);
    tid_t   pos  = 0;
    sid_t   super_id;
    vid_t   v_count;

    for(tid_t i = 0; i < flag_count; i++) {
        pos = __builtin_ctz(flag);
        flag ^= (1L << pos);//reset that position
        super_id = g->get_type_scount(pos);
        v_count = TO_VID(super_id);
        skv[i].kv = (vid_t*)calloc(sizeof(vid_t), v_count);
        skv[i].super_id = super_id;
    }
    return skv;
}

void pgraph_t::store_skv(skv_t* skv, sflag_t flag, string dir, string postfix)
{
    /*
    vid_t v_count;
    //base name using relationship type
    string basefile = dir + p_name;
    string file;
    FILE* f;
    tid_t flag_count = __builtin_popcountll(flag);

    //Write individual files.
    for (tid_t i = 0; i < flag_count; ++i) {
        v_count = TO_VID(sgraph[i].super_id);
        file = basefile + itoa(i) + "beg_pos" + postfix;
        f = fopen(file.c_str(), "wb");
        assert(f != 0);
        //fwrite(sgraph[i].beg_pos, sizeof(), v_count + 1);
    }
    */
}

void pgraph_t::fill_skv(skv_t* skv_out, skv_t* skv_in)
{
    sid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    edge_t*   edges = (edge_t*) buf;
    
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
		src_index = get_sindex(src, flag1);
		dst_index = get_sindex(dst,flag2);
        
        vert1_id = TO_VID(src);
        skv_out[src_index].kv[vert1_id] = dst; 
        
        vert2_id = TO_VID(dst);
        skv_in[dst_index].kv[vert2_id] = src; 
    }
}


status_t pgraph_t::query_adjlist_td(sgraph_t* sgraph, sflag_t iflag, sflag_t oflag, srset_t* iset, srset_t* oset)
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
            vid_t* adj_list = graph[frontier].get_adjlist();
            vid_t nebr_count = graph[frontier].get_count();
            
            //traverse the adj list
            for (vid_t k = 0; k < nebr_count; ++k) {
                oset->set_status(adj_list[k]);
            }
        }
    }
    return eOK;
}

status_t pgraph_t::query_kv_td(skv_t* skv, sflag_t iflag, sflag_t oflag, srset_t* iset, srset_t* oset)
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
        vid_t     frontier;
        for (vid_t v = 0; v < v_count; v++) {
            frontier = vlist[v];
            oset->set_status(kv[frontier]);
        }
    }
    return eOK;
}

//sgraph_in and oset share the same flag.
status_t pgraph_t::query_adjlist_bu(sgraph_t* sgraph, sflag_t flag, srset_t* iset, srset_t* oset)
{
    rset_t*        rset = 0;

    //prepare the output 1,2;
    tid_t oset_count = oset->full_setup(flag);
    
    for (tid_t i = 0; i < oset_count; ++i) {
        
        //get the graph where we will traverse
        beg_pos_t* graph = sgraph[i].beg_pos; 
        sid_t   super_id = sgraph[i].super_id;
        vid_t    v_count = TO_VID(super_id);
        
        rset = oset->rset + i;
        
        for (vid_t v = 0; v < v_count; v++) {
            //traverse the adj list
            vid_t* adj_list = graph[v].get_adjlist();
            vid_t nebr_count = graph[v].get_count();
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

status_t pgraph_t::query_kv_bu(skv_t* skv, sflag_t flag, srset_t* iset, srset_t* oset) 
{
    rset_t*        rset = 0;

    //prepare the output 1;
    tid_t oset_count = oset->full_setup(flag);
    
    for (tid_t i = 0; i < oset_count; ++i) {

        //get the graph where we will traverse
        vid_t*        kv = skv[i].kv; 
        sid_t   super_id = skv[i].super_id;
        vid_t    v_count = TO_VID(super_id);
        
        rset = oset->rset + i;
        
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
pgraph_t::extend_adjlist_td(sgraph_t* sgraph, sflag_t iflag, srset_t* iset, srset_t* oset)
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
        tid_t        pos = get_sindex(tid, iflag);
        beg_pos_t* graph = sgraph[pos].beg_pos; 
        
        //get_sindex() is not full proof
        tid_t  graph_tid = TO_TID(sgraph[pos].super_id);
        if (graph_tid != tid) continue;

        for (vid_t v = 0; v < v_count; v++) {
            rset2->add_adjlist_ro(v, graph+varray[v]);
        }
    }
    return eOK;
}

status_t 
pgraph_t::extend_kv_td(skv_t* skv, sflag_t iflag, srset_t* iset, srset_t* oset)
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
        tid_t     pos = get_sindex(tid, iflag);
        sid_t*  graph = skv[pos].kv; 
        
        //get_sindex() is not full proof
        tid_t  graph_tid = TO_TID(skv[pos].super_id);
        if (graph_tid != tid) continue;

        for (vid_t v = 0; v < v_count; v++) {
            rset2->add_kv(v, graph[varray[v]]);
        }
    }
    return eOK;
}

/*******label specific **********/
status_t pinfo_t::filter(sid_t sid, univ_t value, filter_fn_t fn)
{
    assert(0);
    return eOK;
}

void pinfo_t::print_raw_dst(tid_t tid, vid_t vid)
{
    assert(0);
}

status_t pinfo_t::get_encoded_value(const char* value, univ_t* univ)
{
    assert(0);
    return eQueryFail;
}
