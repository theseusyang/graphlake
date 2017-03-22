#include "graph.h"

#define TO_TID(sid) (sid >> 40)
#define TO_VID(sid)  (sid & 0xffffffffff)
#define TO_SUPER(tid) (super_id(tid) << 40)

typedef struct __label_int8_t {
    vid_t src_id;
    uint8_t dst_id;
} label_int8_t;

void typekv_t::batch_update(const string& src, const string& dst)
{
    vid_t       src_id;
    superid_t   super_id;
    tid_t       type_id;
    index_t     index = 0;
    vid_t       vert_id;

    label_int8_t* edges = (label_int8_t*) buf;

    map<string, uint64_t>::iterator str2enum_iter = str2enum.find(dst);
    if (str2enum.end() == str2enum_iter) {
        type_id = ecount++;
        enum2str[type_id] = gstrdup(dst.c_str());
        super_id = TO_SUPER(type_id);
        str2enum[dst] = super_id;
    } else {
        super_id = str2enum_iter->second;
        type_id = TO_TYPE(super_id);
        vert_id = TO_VID(super_id);
    }

    //allocate class specific ids.
    map<string, vid_t>::iterator str2vid_iter = str2vid.find(src);
    if (str2vid.end() == str2vid_iter) {
        src_id = super_id++;
        str2vid[src] = src_id;

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



enum8kv_t::enum8kv_t ()
{
    init_enum(256);
}


void enum8kv_t::batch_update(const string& src, const string& dst)
{
    vid_t src_id;
    uint8_t dst_id;
    index_t index = 0;
    label_int8_t* edges = (label_int8_t*) buf;

    map<string, vid_t>::iterator str2vid_iter = str2vid.find(src);
    if (str2vid.end() == str2vid_iter) {
        src_id = vert_count++;
        str2vid[src] = src_id;
    } else {
        src_id = str2vid_iter->second;
    }

    map<string, uint8_t>::iterator str2enum_iter = str2enum.find(dst);
    if (str2enum.end() == str2enum_iter) {
        dst_id = ecount++;
        str2enum[dst] = dst_id;
        enum2str[dst_id] = gstrdup(dst.c_str());
    } else {
        dst_id = str2enum_iter->second;
    }

    index = count++;
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
}
    
void enum8kv_t::make_graph_baseline()
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

void enum8kv_t::store_graph_baseline(string dir)
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

void enum8kv_t::init_enum(int enumcount)
{
    max_count = enumcount;
    ecount = 0;
    enum2str = new char*[enumcount];
}

void enum8kv_t::populate_enum(const char* e)
{
    vid_t id = ecount++;
    str2enum[e] = id;
    enum2str[id] = gstrdup(e);
}
