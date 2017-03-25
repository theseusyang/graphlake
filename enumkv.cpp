#include "graph.h"


typedef struct __label_int8_t {
    vid_t src_id;
    uint8_t dst_id;
} label_int8_t;

void typekv_t::batch_update(const string& src, const string& dst)
{
    vid_t       src_id;
    tid_t       type_id;
    index_t     index = 0;
    vid_t       vert_id = 0;

    label_int8_t* edges = (label_int8_t*) buf;

    map<string, uint64_t>::iterator str2enum_iter = str2enum.find(dst);
    if (str2enum.end() == str2enum_iter) {
        type_id = ecount++;
        vert_id = TO_SUPER(type_id);
        str2enum[dst] = type_id;
        enum_info[type_id].vert_id = vert_id; 
        enum_info[type_id].type_name = gstrdup(dst.c_str());
    } else {
        type_id = str2enum_iter->second;
        vert_id = enum_info[type_id].vert_id;
    }

    //allocate class specific ids.
    map<string, vid_t>::iterator str2vid_iter = str2vid.find(src);
    if (str2vid.end() == str2vid_iter) {
        src_id = vert_id++;
        ++vert_count;
        str2vid[src] = src_id;
        //update the id
        enum_info[dst].vert_id = vert_id;
    } else {
        src_id = str2vid_iter->second;
    }

    index = count++;
    edges[index].src_id = src_id; 
    edges[index].dst_id = type_id;
}

void typekv_t::make_graph_baseline()
{
    if (count == 0) return;

    vid_t src;
    uint8_t dst;
    label_int8_t* edges = (label_int8_t*) buf;
    beg_pos_in = (index_t*)calloc(sizeof(index_t), vert_count);
    adj_list_in = (vid_t*) calloc (sizeof(vid_t), count);
    kv_out = (uint8_t*) calloc(sizeof(uint8_t), vert_count);

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

void typekv_t::store_graph_baseline(string dir)
{
    if (count == 0) return;

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

    //XXX writing enum mapping is pending
}

typekv_t::typekv_t ()
{
    init_enum(256);
}

void typekv_t::init_enum(int enumcount)
{
    max_count = enumcount;
    ecount = 0;
    enum2str = new char*[enumcount];
}
