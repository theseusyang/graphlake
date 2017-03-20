#include "graph.h"


void enumgraph_t::batch_update(const string& src, const string& dst)
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

    str2vid_iter = str2enum.find(dst);
    if (str2enum::end() == str2vid_iter) {
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

void enumgraph_t::init_enum(int enumcount)
{
    max_count = enumcount;
    ecount = 0;
    enum2str = new char*[enumcount];
}

void enumgraph_t::populate_enum(const char* e)
{
    vid_t id = ecount++;
    str2enum[e] = id;
    enum2str[id] = gstrdup(e);
}
