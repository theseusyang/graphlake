#include "graph.h"

void dgraph_t::batch_update(const string& src, const string& dst)
{
    vid_t src_id, dst_id;
    index_t index = 0;
    edge_t* edges = (edge_t*) buf;

    map<string, vid_t>::iterator str2vid_iter = str2vid.find(src);
    if (str2vid.end() == str2vid_iter) {
        src_id = vert_count++;
        str2vid[src] = src_id;
    } else {
        src_id = str2vid_iter->second;
    }

    str2vid_iter = str2vid.find(dst);
    if (str2vid.end() == str2vid_iter) {
        dst_id = vert_count++;
        str2vid[dst] = dst_id;
    } else {
        dst_id = str2vid_iter->second;
    }

    index = count++;
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
}
    
void dgraph_t::make_graph_baseline()
{
    vid_t src;
    vid_t dst;
    edge_t* edges = (edge_t*) buf;
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
