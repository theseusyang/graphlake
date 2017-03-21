#include "graph.h"


map <string, vid_t> str2vid;
vid_t vert_count = 0;

graph::graph()
{
    p_info = 0;
    p_count = 0;
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
