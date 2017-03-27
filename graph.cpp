#include "graph.h"


map <string, vid_t> str2vid;

graph::graph()
{
    p_info = 0;
    p_count = 0;
    init_type(256);
    v_count = 0;
}
sid_t graph::get_type_scount(int type)
{
    return t_info[type].vert_id;
}

void graph::init_type(tid_t enumcount)
{
    max_count = enumcount;
    t_count = 0;
    t_info = new tinfo_t [enumcount];
}

void graph::batch_update(const string& src, const string& dst)
{
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
        ++v_count;
        str2vid[src] = src_id;
        //update the id
        t_info[type_id].vert_id = vert_id;
        v_graph->id2name(src_id, src);
    } else {
        //dublicate entry XXX
        src_id = str2vid_iter->second;
    }
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

static int 
is_literal(string str) {
       return ('<' != str[0]);
}

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

    map<string, vid_t>::iterator str2vid_iter = str2vid.find(src);
    if (str2vid.end() == str2vid_iter) {
        assert(0);
    } else {
        src_id = str2vid_iter->second;
    }
    tid_t type_id = TO_TID(src_id);
    flag1 |= (1L << type_id);
    
    str2vid_iter = str2vid.find(dst);
    if (str2vid.end() == str2vid_iter) {
        assert(0);
    } else {
        dst_id = str2vid_iter->second;
    }
    type_id = TO_TID(dst_id);
    flag2 |= (1L << type_id);

    index = count++;
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
}

//super bins memory allocation
sgraph_t* pgraph_t::prep_sgraph(sflag_t ori_flag, tid_t flag_count)
{
    vid_t vert_count;
    sflag_t flag = ori_flag;
    sgraph_t* sgraph  = (sgraph_t*) calloc (sizeof(sgraph_t), flag_count);
    tid_t   pos = 0;
    sid_t super_id;

    for(tid_t i = 0; i < flag_count; i++) {
        pos = __builtin_ctz(flag);
        flag ^= (1L << pos);//reset that position
        super_id = g->get_type_scount(pos);
        vert_count = TO_VID(super_id);
        sgraph[i].beg_pos = (beg_pos_t*)calloc(sizeof(beg_pos_t), vert_count);
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
    vid_t       vert_count = 0;
    
    for(tid_t i = 0; i < sgraph_count; i++) {
        beg_pos = sgraph[i].beg_pos;
        vert_count = TO_VID(sgraph[i].super_id); 
        for (vid_t j = 0; j < vert_count; ++j) {
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
    vid_t vert_count;
    //base name using relationship type
    string basefile = dir + p_name;
    string file;
    FILE* f;
    tid_t flag_count = __builtin_popcountll(flag);

    //Write individual files.
    for (tid_t i = 0; i < flag_count; ++i) {
        vert_count = TO_VID(sgraph[i].super_id);
        file = basefile + itoa(i) + "beg_pos" + postfix;
        f = fopen(file.c_str(), "wb");
        assert(f != 0);
        fwrite(sgraph[i].beg_pos, sizeof(), vert_count + 1);
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
    vid_t   vert_count;

    for(tid_t i = 0; i < flag_count; i++) {
        pos = __builtin_ctz(flag);
        flag ^= (1L << pos);//reset that position
        super_id = g->get_type_scount(pos);
        vert_count = TO_VID(super_id);
        skv[i].kv = (vid_t*)calloc(sizeof(vid_t), vert_count);
        skv[i].super_id = super_id;
    }
    return skv;
}

void pgraph_t::store_skv(skv_t* skv, sflag_t flag, string dir, string postfix)
{
    /*
    vid_t vert_count;
    //base name using relationship type
    string basefile = dir + p_name;
    string file;
    FILE* f;
    tid_t flag_count = __builtin_popcountll(flag);

    //Write individual files.
    for (tid_t i = 0; i < flag_count; ++i) {
        vert_count = TO_VID(sgraph[i].super_id);
        file = basefile + itoa(i) + "beg_pos" + postfix;
        f = fopen(file.c_str(), "wb");
        assert(f != 0);
        //fwrite(sgraph[i].beg_pos, sizeof(), vert_count + 1);
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
