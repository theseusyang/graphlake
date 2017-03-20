#include "graph.h"


typedef struct __label_string_t {
    vid_t src_id;
    char* dst_id;
} label_string_t;

void stringkv_t::batch_update(const string& src, const string& dst)
{
    vid_t src_id;
    char* dst_id;
    index_t index = 0;
    label_string_t* edges = (label_string_t*) buf;
    map<string, vid_t>::iterator str2vid_iter = str2vid.find(src);
    if (str2vid.end() == str2vid_iter) {
        src_id = vert_count++;
        str2vid[src] = src_id;
    } else {
        src_id = str2vid_iter->second;
    }
    
    dst_id = gstrdup(dst.c_str());
    index = count++;
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
}
    
void stringkv_t::make_graph_baseline()
{
    vid_t src;
    char* dst;
    label_string_t* edges = (label_string_t*) buf;
    kv_out = (char**) calloc(sizeof(char*), vert_count);

    //populate
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        kv_out[src] = dst;
    }
}

    
void stringkv_t::store_graph_baseline(string dir)
{
    //XXX it is wrong, we are writing the char*, not the string
    string file = dir + p_name + ".kv_out";
    FILE* f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(kv_out, sizeof(int64_t), vert_count, f);
    fclose(f);
}
