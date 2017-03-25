#include "graph.h"


map <string, vid_t> str2vid;
vid_t vert_count = 0;

graph::graph()
{
    p_info = 0;
    p_count = 0;
}
v_id_t graph::get_type_scount(int type)
{
    typekv_t* typekv = (typekv_t*)p_info[0];
    return (typekv->vert_id);
}

//Applicable to mostly graphs, labels should be aware of it.
void p_info_t::batch_update(const string& src, const string& dst)
{
    vid_t src_id, dst_id;
    index_t index = 0;
    edge_t* edges = (edge_t*) buf;

    map<string, vid_t>::iterator str2vid_iter = str2vid.find(src);
    if (str2vid.end() == str2vid_iter) {
        src_id = vert_count++;
        str2vid[src] = src_id;
        assert(0);
    } else {
        src_id = str2vid_iter->second;
    }
    tid_t type_id = TO_TYPE(src_id);
    flag1 |= (1L << type_id);
    
    str2vid_iter = str2vid.find(dst);
    if (str2vid.end() == str2vid_iter) {
        dst_id = vert_count++;
        str2vid[dst] = dst_id;
        assert(0);
    } else {
        dst_id = str2vid_iter->second;
    }
    type_id = TO_TYPE(dst_id);
    flag2 |= (1L << type_id);

    index = count++;
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
}
    
void p_info_t::make_graph_baseline()
{
}

void p_info_t::store_graph_baseline(string dir)
{
}

static int 
is_literal(string str) {
       return ('<' != str[0]);
}


void p_info_t::populate_property(const char* longname, const char* property_name)
{
    g->p_info[g->p_count] = this;
    g->str2pid[longname] = g->p_count;
    g->p_count++;
    
    p_name = gstrdup(property_name);
    p_longname = gstrdup(longname);

    buf = calloc(sizeof(vid_t), 1000000);
    count = 0; 

}


/************* Super Bins *****************/

//super bins memory allocation
sgraph_t* pinfo_t::prep_sgraph(sflag_t ori_flag, tid_t flag_count)
{
    sflag_t flag = ori_flag;
    sgraph_t* sgraph  = (sgraph_t*) calloc (sizeof(sgraph_t), flag_count);
    tid_t   pos = 0;

    for(int i = 0; i < flag_count; i++) {
        pos = __builtin_ctz(flag);
        flag ^= (1L << pos);//reset that position
        super_id = g->get_type_scount(pos);
        v_count = TO_VID(super_id);
        sgraph[i].beg_pos = (beg_pos_t*)calloc(sizeof(beg_pos_t), v_count);
        sgraph[i].super_id = super_id;
    } 
}

//estimate edge count
void pinfo_t::calc_edge_count(sgraph_t* sgraph_out, sgraph_t* sgraph_in, 
                        sflag_t flag1, sflag_t flag2, 
                        edge_t* edges, index_t count)
{
    superid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     type1_id, type2_id;
    sflag_t   flag1_mask, flag2_mask;

    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        
        vert1_id = TO_VID(src);
        type1_id = TO_TYPE(src) + 1;
        flag1_mask = flag1 & ( (1L << type1_id) - 1)
        src_index = __builtin_popcountll(flag1_mask);
        sgraph_out[src_index].beg_pos[vert1_id].count += 1;
        
        vert2_id = TO_VID(src);
        type2_id = TO_TYPE(dst) + 1;
        flag2_mask = flag2 & ( (1L << type2_id) - 1)
        dst_index = __builtin_popcountll(flag2_mask);
        sgraph_in[dst_index].beg_pos[vert2_id].count  += 1;
    }
}

//estimate edge count
void pinfo_t::calc_edge_count_out(sgraph_t* sgraph_out, sflag_t flag1, 
                               edge_t* edges, index_t count)
{
    superid_t src, dst;
    vid_t     vert1_id;
    tid_t     type1_id;
    sflag_t   flag1_mask;

    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        
        vert1_id = TO_VID(src);
        type1_id = TO_TYPE(src) + 1;
        flag1_mask = flag1 & ( (1L << type1_id) - 1)
        src_index = __builtin_popcountll(flag1_mask);
        sgraph_out[src_index].beg_pos[vert1_id].count += 1;
        
    }
}
//estimate edge count
void pinfo_t::calc_edge_count_in(sgraph_t* sgraph_in, sflag_t flag2, 
                               edge_t* edges, index_t count)
{
    superid_t src, dst;
    vid_t     vert2_id;
    tid_t     type2_id;
    sflag_t   flag2_mask;

    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        
        vert2_id = TO_VID(src);
        type2_id = TO_TYPE(dst) + 1;
        flag2_mask = flag2 & ( (1L << type2_id) - 1)
        dst_index = __builtin_popcountll(flag2_mask);
        sgraph_in[dst_index].beg_pos[vert2_id].count  += 1;
    }
}

//prefix sum, allocate adj list memory then reset the count
void pinfo_t::prep_sgraph_internal(sgraph_t* sgraph, index_t edge_count, tid_t sgraph_count)
{
    vid* adj_list = (vid_t*) calloc (sizeof(vid_t), edge_count);
    
    index_t     prefix = 0;
    beg_pos_t*  beg_pos = 0;
    vid_t       vcount = 0;
    
    for(int i = 0; i < sgraph_count; i++) {
        beg_pos = sgraph[i];
        v_count = TO_VID(sgraph[i].super_id); 
        for (vid_ j = 0; j < v_count1; ++j) {
            beg_pos[j].adj_list = adj_list_out + prefix_out;
            prefix_out += beg_pos[j].count;
            beg_pos[j].count = 0;
        }
    }
}


void pinfo_t::fill_adj_list(sgraph_t* sgraph_out, sgraph_t* sgraph_in,
                           sflag_t flag1, sflag_t flag2,
                           edge_t* edges, index_t count)
{
    superid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     type1_id, type2_id;
    sflag_t   flag1_mask, flag2_mask;
    beg_pos_t* beg_pos_out = 0, beg_pos_in = 0;
    
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;

        vert1_id = TO_VID(src);
        type1_id = TO_TYPE(src) + 1;
        flag1_mask = flag1 & ( (1L << type1_id) - 1)
        src_index = __builtin_popcountll(flag1_mask);
        
        beg_pos_out = sgraph_out[src_index].beg_pos + vert1_id; 
        beg_pos_out->adj_list[beg_pos_out->count++] = dst;
        
        vert2_id = TO_VID(src);
        type2_id = TO_TYPE(dst) + 1;
        flag2_mask = flag2 & ( (1L << type2_id) - 1)
        dst_index = __builtin_popcountll(flag2_mask);
        
        beg_pos_in = sgraph_in[dst_index].beg_pos + vert2_id; 
        beg_pos_in->adj_list[beg_pos_in->count++] = src;
    }
}

void pinfo_t::fill_adj_list_in(skv_t* skv_out, sgraph_t* sgraph_in, 
                              sflag_t flag1, sflag_t flag2,
                           edge_t* edges, index_t count)
{
    superid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     type2_id;
    sflag_t   flag2_mask;
    beg_pos_t* beg_pos_in = 0;
    
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        
        vert1_id = TO_VID(src);
        type1_id = TO_TYPE(src) + 1;
        flag1_mask = flag1 & ( (1L << type1_id) - 1)
        src_index = __builtin_popcountll(flag1_mask);
        
        skv_out[src_index]->kv[vert1_id] = dst;
        
        vert2_id = TO_VID(src);
        type2_id = TO_TYPE(dst) + 1;
        flag2_mask = flag2 & ( (1L << type2_id) - 1)
        dst_index = __builtin_popcountll(flag2_mask);
        
        beg_pos_in = sgraph_in[dst_index].beg_pos + vert2_id; 
        beg_pos_in->adj_list[beg_pos_in->count++] = src;
    }
}

void pinfo_t::fill_adj_list_out(sgraph_t* sgraph_out, skv_t* skv_in, 
                               sflag_t flag1, sflag_t flag2,
                               edge_t* edges, index_t count)
{
    superid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     type1_id;
    sflag_t   flag1_mask;
    beg_pos_t* beg_pos_out = 0;
    
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        
        vert1_id = TO_VID(src);
        type1_id = TO_TYPE(src) + 1;
        flag1_mask = flag1 & ( (1L << type1_id) - 1)
        src_index = __builtin_popcountll(flag1_mask);
        
        beg_pos_out = sgraph_out[src_index].beg_pos + vert1_id; 
        beg_pos_out->adj_list[beg_pos_out->count++] = dst;
        
        vert2_id = TO_VID(src);
        type2_id = TO_TYPE(dst) + 1;
        flag2_mask = flag2 & ( (1L << type2_id) - 1)
        dst_index = __builtin_popcountll(flag2_mask);
        
        skv_in[dst_index].kv[vert2_id] = src; 
    }
}

void pinfo_t::store_sgraph(sgraph_t* sgraph, sflag_t flag, string dir, string postfix)
{
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
    
    /*
    string file = dir + p_name + ".beg_pos_in";
    FILE* f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(beg_pos_in, sizeof(index_t), vert_count + 1, f);
    fclose(f);
    
    file = dir + p_name + ".adj_list_in";
    f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(adj_list_in, sizeof(vid_t), beg_pos_in[vert_count], f);
    fclose(f);
    
    file = dir + p_name + ".beg_pos_out";
    f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(beg_pos_out, sizeof(index_t), vert_count + 1, f);
    fclose(f);
    
    file = dir + p_name + ".adj_list_out";
    f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(adj_list_out, sizeof(vid_t), beg_pos_out[vert_count], f);
    fclose(f);
    */
}

/******************** super kv *************************/
//super bins memory allocation
skv_t* pinfo_t::prep_skv(sflag_t ori_flag, tid_t flag_count)
{
    sflag_t flag = ori_flag;
    skv_t*  skv  = (skv_t*) calloc (sizeof(skv_t), flag_count);
    tid_t   pos  = 0;

    for(int i = 0; i < flag_count; i++) {
        pos = __builtin_ctz(flag);
        flag ^= (1L << pos);//reset that position
        super_id = g->get_type_scount(pos);
        v_count = TO_VID(super_id);
        skv[i].kv = (kv_t*)calloc(sizeof(kv_t), v_count);
        skv[i].super_id = super_id;
    }
    return skv;
}

void pinfo_t::store_skv(skv_t* skv, sflag_t flag, string dir, string postfix)
{
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
}

void pinfo_t::fill_kv(skv_t* skv_out, skv_t* skv_in, 
                               sflag_t flag1, sflag_t flag2,
                               edge_t* edges, index_t count)
{
    superid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     type1_id;
    sflag_t   flag1_mask;
    beg_pos_t* beg_pos_out = 0;
    
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        
        vert1_id = TO_VID(src);
        type1_id = TO_TYPE(src) + 1;
        flag1_mask = flag1 & ( (1L << type1_id) - 1)
        src_index = __builtin_popcountll(flag1_mask);
        
        skv_out[src_index].kv[vert1_id] = dst; 
        
        vert2_id = TO_VID(src);
        type2_id = TO_TYPE(dst) + 1;
        flag2_mask = flag2 & ( (1L << type2_id) - 1)
        dst_index = __builtin_popcountll(flag2_mask);
        
        skv_in[dst_index].kv[vert2_id] = src; 
    }
}
