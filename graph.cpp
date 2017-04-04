#include "graph.h"



inline tid_t get_sindex(tid_t tid, sflag_t sflag)
{
    sflag_t flag_mask = sflag & ((1L << (tid +1)) - 1);
    tid_t        pos = __builtin_popcountll(flag_mask) - 1;
    return pos;
}
    
/*
inline void add_dst(sid_t sid, sflag_t flag, skv_t* skv) 
{
    vid_t vert2_id = TO_VID(sid);
    tid_t type2_id = TO_TID(sid) + 1;
    sflag_t flag2_mask = flag & ( (1L << type2_id) - 1);
    tid_t dst_index = __builtin_popcountll(flag2_mask) - 1;
    skv[dst_index].kv[vert2_id] = src; 
}

inline void add_dst_count(sid_t sid, sflag_t flag, skv_t* skv) 
{
    vid_t vert2_id = TO_VID(sid);
    tid_t type2_id = TO_TID(sid) + 1;
    sflag_t flag2_mask = flag & ( (1L << type2_id) - 1);
    tid_t dst_index = __builtin_popcountll(flag2_mask) - 1;
    skvn[dst_index].kv[vert2_id].count += 1; 
}
*/
graph::graph()
{
    p_info = 0;
    p_count = 0;
    vert_count = 0;
    v_graph =  new vgraph_t;
}
sid_t graph::get_type_scount(int type)
{
    typekv_t* typekv = dynamic_cast<typekv_t*>(p_info[0]);
    return typekv->t_info[type].vert_id;
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
    v_graph->type_done();
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
    tid_t     type1_id, type2_id;
    sflag_t   flag1_mask, flag2_mask;
    tid_t src_index, dst_index;
    edge_t*   edges = (edge_t*) buf;  
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        
        vert1_id = TO_VID(src);
        type1_id = TO_TID(src) + 1;
        flag1_mask = flag1 & ( (1L << type1_id) - 1);
        src_index = __builtin_popcountll(flag1_mask) - 1;
        sgraph_out[src_index].beg_pos[vert1_id].count += 1;
        
        vert2_id = TO_VID(dst);
        type2_id = TO_TID(dst) + 1;
        flag2_mask = flag2 & ( (1L << type2_id) - 1);
        dst_index = __builtin_popcountll(flag2_mask) - 1;
        sgraph_in[dst_index].beg_pos[vert2_id].count  += 1;
    }
}

//estimate edge count
void pgraph_t::calc_edge_count_out(sgraph_t* sgraph_out)
{
    sid_t     src;
    vid_t     vert1_id;
    tid_t     type1_id;
    sflag_t   flag1_mask;
    tid_t     src_index;

    edge_t*  edges = (edge_t*) buf;

    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        
        vert1_id = TO_VID(src);
        type1_id = TO_TID(src) + 1;
        flag1_mask = flag1 & ( (1L << type1_id) - 1);
        src_index = __builtin_popcountll(flag1_mask) - 1;
        sgraph_out[src_index].beg_pos[vert1_id].count += 1;
        
    }
}
//estimate edge count
void pgraph_t::calc_edge_count_in(sgraph_t* sgraph_in)
{
    sid_t     dst;
    vid_t     vert2_id;
    tid_t     type2_id;
    sflag_t   flag2_mask;
    tid_t     dst_index;
    edge_t*   edges = (edge_t*) buf;
    for (index_t i = 0; i < count; ++i) {
        dst = edges[i].dst_id;
        
        vert2_id = TO_VID(dst);
        type2_id = TO_TID(dst) + 1;
        flag2_mask = flag2 & ( (1L << type2_id) - 1);
        dst_index = __builtin_popcountll(flag2_mask) - 1;
        sgraph_in[dst_index].beg_pos[vert2_id].count  += 1;
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
            beg_pos[j].adj_list = adj_list + prefix;
            prefix += beg_pos[j].count;
            beg_pos[j].count = 0;
        }
    }
}

void pgraph_t::fill_adj_list(sgraph_t* sgraph_out, sgraph_t* sgraph_in)
{
    sid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     type1_id, type2_id;
    sflag_t   flag1_mask, flag2_mask;
    tid_t     src_index, dst_index;
    beg_pos_t* beg_pos_out = 0;
    beg_pos_t* beg_pos_in = 0;
    edge_t*    edges = (edge_t*) buf;
    
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;

        vert1_id = TO_VID(src);
        type1_id = TO_TID(src) + 1;
        flag1_mask = flag1 & ( (1L << type1_id) - 1);
        src_index = __builtin_popcountll(flag1_mask) - 1;
        
        beg_pos_out = sgraph_out[src_index].beg_pos + vert1_id; 
        beg_pos_out->adj_list[beg_pos_out->count++] = dst;
        
        vert2_id = TO_VID(dst);
        type2_id = TO_TID(dst) + 1;
        flag2_mask = flag2 & ( (1L << type2_id) - 1);
        dst_index = __builtin_popcountll(flag2_mask) - 1;
        
        beg_pos_in = sgraph_in[dst_index].beg_pos + vert2_id; 
        beg_pos_in->adj_list[beg_pos_in->count++] = src;
    }
}

void pgraph_t::fill_adj_list_in(skv_t* skv_out, sgraph_t* sgraph_in) 
{
    sid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     type1_id, type2_id;
    sflag_t   flag1_mask, flag2_mask;
    tid_t     src_index, dst_index;
    beg_pos_t* beg_pos_in = 0;
    edge_t*   edges = (edge_t*) buf;
    
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        
        vert1_id = TO_VID(src);
        type1_id = TO_TID(src) + 1;
        flag1_mask = flag1 & ( (1L << type1_id) - 1);
        src_index = __builtin_popcountll(flag1_mask) - 1;
        
        skv_out[src_index].kv[vert1_id] = dst;
        
        vert2_id = TO_VID(dst);
        type2_id = TO_TID(dst) + 1;
        flag2_mask = flag2 & ( (1L << type2_id) - 1);
        dst_index = __builtin_popcountll(flag2_mask) - 1 ;
        
        beg_pos_in = sgraph_in[dst_index].beg_pos + vert2_id; 
        beg_pos_in->adj_list[beg_pos_in->count++] = src;
    }
}

void pgraph_t::fill_adj_list_out(sgraph_t* sgraph_out, skv_t* skv_in) 
{
    sid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     type1_id, type2_id;
    sflag_t   flag1_mask, flag2_mask;
    beg_pos_t* beg_pos_out = 0;
    tid_t src_index, dst_index; 
    edge_t*   edges = (edge_t*) buf;

    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        
        vert1_id = TO_VID(src);
        type1_id = TO_TID(src) + 1;
        flag1_mask = flag1 & ( (1L << type1_id) - 1);
        src_index = __builtin_popcountll(flag1_mask) - 1;
        
        beg_pos_out = sgraph_out[src_index].beg_pos + vert1_id; 
        beg_pos_out->adj_list[beg_pos_out->count++] = dst;
        
        vert2_id = TO_VID(dst);
        type2_id = TO_TID(dst) + 1;
        flag2_mask = flag2 & ( (1L << type2_id) - 1);
        dst_index = __builtin_popcountll(flag2_mask) - 1;
        
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
    tid_t     type1_id, type2_id;
    sflag_t   flag1_mask, flag2_mask;
    tid_t     src_index, dst_index;
    edge_t*   edges = (edge_t*) buf;
    
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        
        vert1_id = TO_VID(src);
        type1_id = TO_TID(src) + 1;
        flag1_mask = flag1 & ( (1L << type1_id) - 1);
        src_index = __builtin_popcountll(flag1_mask) - 1;
        
        skv_out[src_index].kv[vert1_id] = dst; 
        
        vert2_id = TO_VID(dst);
        type2_id = TO_TID(dst) + 1;
        flag2_mask = flag2 & ( (1L << type2_id) - 1);
        dst_index = __builtin_popcountll(flag2_mask) - 1;
        
        skv_in[dst_index].kv[vert2_id] = src; 
    }
}

//////////// Labels //////////////////////
lgraph_t* pkv_t::prep_lgraph(index_t ecount)
{
    lgraph_t* lgraph  = (beg_pos_t*) calloc (sizeof(beg_pos_t), ecount);
    return lgraph;
}

void pkv_t::prep_lgraph_internal(lgraph_t* lgraph_in, index_t ecount, index_t edge_count)
{
    vid_t* adj_list = (vid_t*) calloc (sizeof(vid_t), edge_count);
    
    index_t     prefix = 0;
    beg_pos_t*  beg_pos = lgraph_in;
    
    for (vid_t j = 0; j < ecount; ++j) {
        beg_pos[j].adj_list = adj_list + prefix;
        prefix += beg_pos[j].count;
        beg_pos[j].count = 0;
    }
}

void pkv_t::calc_edge_count(lgraph_t* lgraph_in, edge_t* edges, index_t count)
{
    sid_t dst;
    
    for (index_t i = 0; i < count; ++i) {
        dst = edges[i].dst_id;
        lgraph_in[dst].count  += 1;
    }
}

void pkv_t::store_lgraph(lgraph_t* lgraph_in, string dir, string postfix)
{
    //base name using relationship type
    /*
    string basefile = dir + p_name;
    string file = basefile + "beg_pos";
    FILE* f;
    */
    
}

status_t pgraph_t::query_adjlist_td(sgraph_t* sgraph, sflag_t iflag, sflag_t oflag, srset_t* iset, srset_t* oset)
{
    tid_t    iset_count = iset->get_rset_count();
    rset_t*        rset = 0;
    vid_t total_frontiers = 0;

    //prepare the output 1,2;
    oset->full_setup(oflag);

    
    for (tid_t i = 0; i < iset_count; ++i) {
        rset = iset->rset + i;
        vid_t w_count = WORD_COUNT(rset->get_vcount());
        uint64_t* barray = rset->status_array;
        
        //get the graph where we will traverse
        tid_t        tid = rset->get_tid();
        tid_t        pos = get_sindex(tid, iflag);
        tid_t  graph_tid = TO_TID(sgraph[pos].super_id);
        beg_pos_t* graph = sgraph[pos].beg_pos; 
        if (graph_tid != tid) continue;

        
        //Get the frontiers
        vid_t     word, base, frontier;
        tid_t     count;
        
        for (vid_t w = 0; w < w_count; w++) {
            while( 0 == barray[w]) continue;
            
            word  = barray[w];
            count = __builtin_popcountll(w);
            base  = (w << 6);

            for (tid_t j = 0; j < count; ++j) {
                pos = __builtin_ctzll(word);
                word  ^= (1L << pos);//reset that position
                frontier = pos + base;
                
                //traverse the adj list
                vid_t* adj_list = graph[frontier].adj_list;
                vid_t nebr_count = graph[frontier].count;
                for (vid_t k = 0; k < nebr_count; ++k) {
                    total_frontiers += oset->add_frontier(adj_list[k]);
                }
            }
        }
    }
    oset->ccount |= TO_VID(total_frontiers);
    return eOK;
}

status_t pgraph_t::query_kv_td(skv_t* skv, sflag_t iflag, sflag_t oflag, srset_t* iset, srset_t* oset)
{
    tid_t    iset_count = iset->get_rset_count();
    rset_t*        rset = 0;
    vid_t total_frontiers = 0;

    //prepare the output 1,2;
    oset->full_setup(oflag);

    for (tid_t i = 0; i < iset_count; ++i) {
        rset = iset->rset + i;
        vid_t w_count = WORD_COUNT(rset->get_vcount());
        uint64_t* barray = rset->status_array;
        
        //get the graph where we will traverse
        tid_t        tid = rset->get_tid();
        tid_t        pos = get_sindex(tid, iflag);
        tid_t  graph_tid = TO_TID(skv[pos].super_id);
        vid_t*        kv = skv[pos].kv; 
        if (graph_tid != tid) continue;
        
        //Get the frontiers
        vid_t     word, base, frontier;
        tid_t     count;
        
        for (vid_t w = 0; w < w_count; w++) {
            if ( 0 == barray[w]) continue;
            
            word  = barray[w];
            count = __builtin_popcountll(word);
            base  = (w << 6);

            for (tid_t j = 0; j < count; ++j) {
                pos = __builtin_ctzll(word);
                word  ^= (1L << pos);//reset that position
                frontier = pos + base;
                total_frontiers += oset->add_frontier(kv[frontier]);
            }
        }
    }
    oset->ccount |= TO_VID(total_frontiers);
    return eOK;
}

//sgraph_in and oset share the same flag.
status_t pgraph_t::query_adjlist_bu(sgraph_t* sgraph, sflag_t flag, srset_t* iset, srset_t* oset)
{
    rset_t*        rset = 0;
    vid_t new_frontiers = 0;
    vid_t total_frontiers = 0;

    //prepare the output 1;
    tid_t oset_count = oset->setup(flag);
    
    for (tid_t i = 0; i < oset_count; ++i) {
        
        //get the graph where we will traverse
        beg_pos_t* graph = sgraph[i].beg_pos; 
        sid_t   super_id = sgraph[i].super_id;
        vid_t v_count = TO_VID(super_id);
        
        //set up the output 2
        rset = oset->rset + i;
        rset->setup(super_id);
        
        for (vid_t v = 0; v < v_count; v++) {
            //traverse the adj list
            vid_t* adj_list = graph[v].adj_list;
            vid_t nebr_count = graph[v].count;
            for (vid_t k = 0; k < nebr_count; ++k) {
                if (iset->get_status(adj_list[k])) {
                    rset->add_frontier(v);
                    new_frontiers++;
                    total_frontiers++;
                    break;
                }
            }
        }
        rset->count2 = new_frontiers;
        new_frontiers = 0;
    }
    oset->ccount |= TO_VID(total_frontiers);
    return eOK;
}

status_t pgraph_t::query_kv_bu(skv_t* skv, sflag_t flag, srset_t* iset, srset_t* oset) 
{
    rset_t*        rset = 0;
    vid_t new_frontiers = 0;
    vid_t total_frontiers = 0;

    //prepare the output 1;
    tid_t oset_count = oset->setup(flag);
    
    for (tid_t i = 0; i < oset_count; ++i) {

        //get the graph where we will traverse
        vid_t*        kv = skv[i].kv; 
        sid_t   super_id = skv[i].super_id;
        vid_t    v_count = TO_VID(super_id);
        
        //set up the output 2
        rset = oset->rset + i;
        rset->setup(super_id);
        
        for (vid_t v = 0; v < v_count; ++v) {
            if (iset->get_status(kv[v])) {
                rset->add_frontier(v);
                new_frontiers++;
                total_frontiers++;
                break;
            }
        }
        rset->count2 = new_frontiers;
        new_frontiers = 0;
    }
    oset->ccount |= TO_VID(total_frontiers);
    return eOK;
}

////// filters ------------------------
status_t 
pgraph_t::query_adjlist_td_filter(sgraph_t* sgraph, sflag_t iflag, sflag_t oflag, 
                        srset_t* iset, srset_t* oset, filter_info_t* filter_info)
{
    tid_t    iset_count = iset->get_rset_count();
    rset_t*        rset = 0;
    vid_t total_frontiers = 0;
    sid_t sid = 0;

    //prepare the output 1,2;
    oset->full_setup(oflag);

    
    for (tid_t i = 0; i < iset_count; ++i) {
        rset = iset->rset + i;
        vid_t w_count = WORD_COUNT(rset->get_vcount());
        uint64_t* barray = rset->status_array;
        
        //get the graph where we will traverse
        tid_t        tid = rset->get_tid();
        tid_t        pos = get_sindex(tid, iflag);
        tid_t  graph_tid = TO_TID(sgraph[pos].super_id);
        beg_pos_t* graph = sgraph[pos].beg_pos; 
        if (graph_tid != tid) continue;

        
        //Get the frontiers
        vid_t     word, base, frontier;
        tid_t     count;
        
        for (vid_t w = 0; w < w_count; w++) {
            while( 0 == barray[w]) continue;
            
            word  = barray[w];
            count = __builtin_popcountll(w);
            base  = (w << 6);

            for (tid_t j = 0; j < count; ++j) {
                pos = __builtin_ctzll(word);
                word  ^= (1L << pos);//reset that position
                frontier = pos + base;
                
                //traverse the adj list
                vid_t* adj_list = graph[frontier].adj_list;
                vid_t nebr_count = graph[frontier].count;
                for (vid_t k = 0; k < nebr_count; ++k) {
                    sid = adj_list[k];
                    if (eOK == filter_info->rgraph->filter(sid, 
                            filter_info->value, filter_info->filter_fn)) {
                        total_frontiers += oset->add_frontier(sid);
                    }
                }
            }
        }
    }
    oset->ccount |= TO_VID(total_frontiers);
    return eOK;
}

status_t 
pgraph_t::query_kv_td_filter(skv_t* skv, sflag_t iflag, sflag_t oflag, srset_t* iset, 
                             srset_t* oset, filter_info_t* filter_info)
{
    tid_t    iset_count = iset->get_rset_count();
    rset_t*        rset = 0;
    vid_t total_frontiers = 0;

    //prepare the output 1,2;
    oset->full_setup(oflag);

    for (tid_t i = 0; i < iset_count; ++i) {
        rset = iset->rset + i;
        vid_t w_count = WORD_COUNT(rset->get_vcount());
        uint64_t* barray = rset->status_array;
        
        //get the graph where we will traverse
        tid_t        tid = rset->get_tid();
        tid_t        pos = get_sindex(tid, iflag);
        tid_t  graph_tid = TO_TID(skv[pos].super_id);
        vid_t*        kv = skv[pos].kv; 
        if (graph_tid != tid) continue;
        
        //Get the frontiers
        vid_t     word, base, frontier;
        tid_t     count;
        
        for (vid_t w = 0; w < w_count; w++) {
            if ( 0 == barray[w]) continue;
            
            word  = barray[w];
            count = __builtin_popcountll(word);
            base  = (w << 6);

            for (tid_t j = 0; j < count; ++j) {
                pos = __builtin_ctzll(word);
                word  ^= (1L << pos);//reset that position
                frontier = pos + base;
                //
                if (eOK == filter_info->rgraph->filter(frontier, 
                     filter_info->value, filter_info->filter_fn)) {
                   total_frontiers += oset->add_frontier(kv[frontier]);
                }
            }
        }
    }
    oset->ccount |= TO_VID(total_frontiers);
    return eOK;
}

status_t 
pgraph_t::query_adjlist_bu_filter(sgraph_t* sgraph, sflag_t flag, srset_t* iset, 
                                  srset_t* oset, filter_info_t* filter_info)
{
    rset_t*        rset = 0;
    vid_t new_frontiers = 0;
    vid_t total_frontiers = 0;
    sid_t sid = 0;
  

    //prepare the output 1;
    tid_t oset_count = oset->setup(flag);
    
    for (tid_t i = 0; i < oset_count; ++i) {
        //get the graph where we will traverse
        beg_pos_t* graph = sgraph[i].beg_pos; 
        sid_t   super_id = sgraph[i].super_id;
        vid_t v_count = TO_VID(super_id);
        sid_t tid_high = super_id & VMASK;
        
        //set up the output 2
        rset = oset->rset + i;
        rset->setup(super_id);
        
        for (vid_t v = 0; v < v_count; v++) {
            //traverse the adj list
            vid_t* adj_list = graph[v].adj_list;
            vid_t nebr_count = graph[v].count;
            sid = v + tid_high;
            for (vid_t k = 0; k < nebr_count; ++k) {

                //apply the filter here.
                if (iset->get_status(adj_list[k]) && 
                    (eOK == filter_info->rgraph->filter(sid, 
                            filter_info->value, filter_info->filter_fn))) {
                    rset->add_frontier(v);
                    new_frontiers++;
                    total_frontiers++;
                    break;
                }
            }
        }
        rset->count2 = new_frontiers;
        new_frontiers = 0;
    }
    oset->ccount |= TO_VID(total_frontiers);
    return eOK;
}

status_t 
pgraph_t::query_kv_bu_filter(skv_t* skv, sflag_t flag, srset_t* iset, 
                             srset_t* oset, filter_info_t* filter_info)
{
    rset_t*        rset = 0;
    vid_t new_frontiers = 0;
    vid_t total_frontiers = 0;
    sid_t sid;

    //prepare the output 1;
    tid_t oset_count = oset->setup(flag);
    
    for (tid_t i = 0; i < oset_count; ++i) {

        //get the graph where we will traverse
        vid_t*        kv = skv[i].kv; 
        sid_t   super_id = skv[i].super_id;
        vid_t    v_count = TO_VID(super_id);
        sid_t tid_high = super_id & VMASK;
        
        //set up the output 2
        rset = oset->rset + i;
        rset->setup(super_id);
        
        for (vid_t v = 0; v < v_count; ++v) {
            sid = v + tid_high;
            if (iset->get_status(kv[v])
               && (eOK == filter_info->rgraph->filter(sid, 
                   filter_info->value, filter_info->filter_fn))) {
                rset->add_frontier(v);
                new_frontiers++;
                total_frontiers++;
                break;
            }
        }
        rset->count2 = new_frontiers;
        new_frontiers = 0;
    }
    oset->ccount |= TO_VID(total_frontiers);
    return eOK;
}
