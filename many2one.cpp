#include "graph.h"

void many2one_t::make_graph_baseline()
{
    
    if (count == 0) return;
    vid_t src;
    vid_t dst;
    edge_t* edges = (edge_t*) buf;
    beg_pos_in = (index_t*)calloc(sizeof(index_t), vert_count);
    adj_list_in = (vid_t*) calloc (sizeof(vid_t), count);
    kv_out = (vid_t*) calloc(sizeof(vid_t), vert_count);

    //estimate 
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        beg_pos_in[dst]++;
    }

    //prefix sum
    index_t prev_in;
    index_t prefix_in = 0;
    for (vid_t j = 0; j < vert_count; ++j) {
        prev_in = beg_pos_in[j];
        beg_pos_in[j] = prefix_in;
        prefix_in += prev_in;
    }
    beg_pos_in[vert_count] = prefix_in;
    
    //populate
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        adj_list_in[beg_pos_in[dst]++] = src;
        kv_out[src] = dst;
    }
    
    //correcting beg pos
    for (vid_t j = vert_count; j > 0; j--) {
        beg_pos_in[j] = beg_pos_in[j - 1];
    }
}

void many2one_t::store_graph_baseline(string dir)
{
    if (count == 0) return ;

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
    
    file = dir + p_name + ".kv_out";
    f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(kv_out, sizeof(vid_t), vert_count, f);
    fclose(f);
}

/*******************************************/
void one2many_t::make_graph_baseline()
{
    vid_t src;
    vid_t dst;
    edge_t* edges = (edge_t*) buf;
    beg_pos_out = (index_t*)calloc(sizeof(index_t), vert_count);
    adj_list_out = (vid_t*) calloc (sizeof(vid_t), count);
    kv_in = (vid_t*) calloc(sizeof(vid_t), vert_count);

    //estimate 
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        beg_pos_out[src]++;
    }

    //prefix sum
    index_t prev_out;
    index_t prefix_out = 0;
    for (vid_t j = 0; j < vert_count; ++j) {
        prev_out = beg_pos_out[j];
        beg_pos_out[j] = prefix_out;
        prefix_out += prev_out;
    }
    beg_pos_out[vert_count] = prefix_out;
    
    //populate
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        adj_list_out[beg_pos_out[src]++] = dst;
        kv_in[dst] = src;
    }
    
    //correcting beg pos
    for (vid_t j = vert_count; j > 0; j--) {
        beg_pos_out[j] = beg_pos_out[j - 1];
    }
}

void one2many_t::store_graph_baseline(string dir)
{
    if (count == 0) return ;

    string file = dir + p_name + ".beg_pos_out";
    FILE* f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(beg_pos_out, sizeof(index_t), vert_count + 1, f);
    fclose(f);
    
    file = dir + p_name + ".adj_list_out";
    f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(adj_list_out, sizeof(vid_t), beg_pos_out[vert_count], f);
    fclose(f);
    
    file = dir + p_name + ".kv_in";
    f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(kv_in, sizeof(vid_t), vert_count, f);
    fclose(f);
}

/************************************************/
void one2one_t::make_graph_baseline()
{
    vid_t src;
    vid_t dst;
    edge_t* edges = (edge_t*) buf;
    kv_in = (vid_t*) calloc(sizeof(vid_t), vert_count);
    kv_out = (vid_t*) calloc(sizeof(vid_t), vert_count);

    //populate
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        kv_in[dst] = src;
        kv_out[src] = dst;
    }
}

void one2one_t::store_graph_baseline(string dir)
{
    if (count == 0) return ;

    string file = dir + p_name + ".kv_in";
    FILE* f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(kv_in, sizeof(vid_t), vert_count, f);
    fclose(f);
    
    file = dir + p_name + ".kv_out";
    f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(kv_out, sizeof(vid_t), vert_count, f3);

    beg_pos_in = (index_t*)calloc(sizeof(index_t), vert_count);
    adj_list_in = (vid_t*) calloc (sizeof(vid_t), count);
    beg_pos_out = (index_t*)calloc(sizeof(index_t), vert_count);
    adj_list_out = (vid_t*) calloc (sizeof(vid_t), count);

    //estimate 
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        beg_pos_out[src]++;
        beg_pos_in[dst]++;
    }

    //prefix sum
    index_t prev_in;
    index_t prefix_in = 0;
    index_t prev_out;
    index_t prefix_out = 0;
    for (vid_t j = 0; j < vert_count; ++j) {
        prev_in = beg_pos_in[j];
        beg_pos_in[j] = prefix_in;
        prefix_in += prev_in;
        prev_out = beg_pos_out[j];
        beg_pos_out[j] = prefix_out;
        prefix_out += prev_out;
    }
    beg_pos_in[vert_count] = prefix_in;
    beg_pos_out[vert_count] = prefix_out;
    
    //populate
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        adj_list_in[beg_pos_in[dst]++] = src;
        adj_list_out[beg_pos_out[src]++] = dst;
    }
    
    //correcting beg pos
    for (vid_t j = vert_count; j > 0; j--) {
        beg_pos_in[j] = beg_pos_in[j - 1];
        beg_pos_out[j] = beg_pos_out[j - 1];
    }
}

    
void dgraph_t::store_graph_baseline(string dir)
{
    if (count == 0) return ;

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
}

/*******************************************/
void ugraph_t::make_graph_baseline()
{
    vid_t src;
    vid_t dst;
    edge_t* edges = (edge_t*) buf;
    beg_pos = (index_t*)calloc(sizeof(index_t), vert_count);
    adj_list = (vid_t*) calloc (sizeof(vid_t), 2*count);

    //estimate 
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        beg_pos[src]++;
        beg_pos[dst]++;
    }

    //prefix sum
    index_t prev;
    index_t prefix = 0;
    for (vid_t j = 0; j < vert_count; ++j) {
        prev = beg_pos[j];
        beg_pos[j] = prefix;
        prefix += prev;
    }
    beg_pos[vert_count] = prefix;
    
    //populate
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        adj_list[beg_pos[src]++] = dst;
        adj_list[beg_pos[dst]++] = src;
    }
    
    //correcting beg pos
    for (vid_t j = vert_count; j > 0; j--) {
        beg_pos[j] = beg_pos[j - 1];
    }
}

void ugraph_t::store_graph_baseline(string dir)
{
    if (count == 0) return ;

    string file = dir + p_name + ".beg_pos";
    FILE* f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(beg_pos, sizeof(index_t), vert_count + 1, f);
    fclose(f);
    
    file = dir + p_name + ".adj_list";
    f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(adj_list, sizeof(vid_t), beg_pos[vert_count], f);
    fclose(f);
}
