#include "graph.h"

map <string, vid_t> str2vid;
vid_t vert_count = 0;

map <string, pid_t> str2pid;
p_info_t*       p_info;
pid_t           p_count = 0;

void ugraph_t::populate_property(const char* property)
{
    p_info[p_count] = this;
    ++p_count;
    str2pid[value] = p_count;
    p_name = gstrdup(value);
}

void ugraph_t::batch_update(const string& src, const string& dst)
{
    vid_t src_id, dst_id;
    edge_t index = 0;
    edge_t* edges = (edge_t*) buf;
    map<string, vid_t> str2vid_iter = str2vid.find(src);
    if (str2vid::end() == str2vid_iter) {
        src_id = vert_count++;
        str2vid[src] = src_id;
    } else {
        src_id = str2vid_iter->second;
    }

    str2vid_iter = str2vid.find(dst);
    if (str2vid::end() == str2vid_iter) {
        dst_id = vert_count++;
        str2vid[dst] = dst_id;
    } else {
        dst_id = str2vid_iter->second;
    }
    index = count++;
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
}
    
void p_info_t::make_graph_baseline()
{
    vid_t src;
    vid_t dst;
    edge_t* edges = (edge_t*) buf;
    beg_pos = (index_t*)calloc(sizeof(index_t), vert_count);
    adj_list = (vid_t*) calloc (sizeof(vid_t), count);

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
        adj_list[begpos[src]++] = dst;
        adj_list[begpos[dst]++] = src;
    }
    
    //correcting beg pos
    for (vid_t j = vert_count; j > 0; j--) {
        beg_pos[j] = prev[j - 1];
    }
}

    
void p_info_t::store_graph_baseline(string dir)
{
    string file = dir + p_name + ".beg_pos";
    FILE* f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(beg_pos, sizeof(index_t), vert_counti + 1, f);
    fclose(f);
    
    file = dir + p_name + ".adj_list";
    FILE* f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(adj_list, sizeof(vid_t), _beg_pos[vert_count], f);
    fclose(f);
}

