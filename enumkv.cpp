#include "graph.h"

typedef struct __label_int8_t {
    vid_t src_id;
    int8_t dst_id;
} label_int8_t;

void enum8kv_t::batch_update(const string& src, const string& dst)
{
    vid_t src_id;
    int8_t dst_id;
    index_t index = 0;
    label_int8_t* edges = (label_int64_t*) buf;

    map<string, vid_t> str2vid_iter = str2vid.find(src);
    if (str2vid.end() == str2vid_iter) {
        src_id = vert_count++;
        str2vid[src] = src_id;
    } else {
        src_id = str2vid_iter->second;
    }

    map<string, int8_t>::iterator str2enum_iter = str2enum.find(dst);
    if (str2enum.end() == str2enum_iter) {
        dst_id = ecount++;
        str2enum[dst] = dst_id;
        enum2str[dst_id] = gstrdup(dst.c_str());
    } else {
        dst_id = str2vid_iter->second;
    }

    index = count++;
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
}
    
void enum8kv_t::make_graph_baseline()
{
    vid_t src;
    int8_t dst;
    label_int8_t* edges = (label_int8_t*) buf;
    beg_pos_in = (index_t*)calloc(sizeof(index_t), vert_count);
    adj_list_in = (vid_t*) calloc (sizeof(vid_t), count);
    kv_out = (int8_t*) calloc(sizeof(int8_t), vert_count);

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
        beg_pos_in[j] = prefix;
        prefix_in += prev_in;
    }
    beg_pos_in[vert_count] = prefix_in;
    
    //populate
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        adj_list_in[begpos_in[dst]++] = src;
        kv_out[src] = dst;
    }
    
    //correcting beg pos
    for (vid_t j = vert_count; j > 0; j--) {
        beg_pos_in[j] = beg_pos_in[j - 1];
    }
}

void many2one_t::store_graph_baseline(string dir)
{
    string file = dir + p_name + ".beg_pos_in";
    FILE* f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(beg_pos_in, sizeof(index_t), vert_count + 1, f);
    fclose(f);
    
    file = dir + p_name + ".adj_list_in";
    FILE* f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(adj_list_in, sizeof(vid_t), beg_pos_in[vert_count], f);
    fclose(f);
    
    file = dir + p_name + ".kv_out";
    FILE* f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(kv_out, sizeof(vertex_t), vert_count, f);
    fclose(f);

    //XXX writing enum mapping is pending
}

void enumkv_t::init_enum(int enumcount)
{
    max_count = enumcount;
    ecount = 0;
    enum2str = new char*[enumcount];
}

void enumkv_t::populate_enum(const char* e)
{
    vid_t id = ecount++;
    str2enum[e] = id;
    enum2str[id] = gstrdup(e);
}
