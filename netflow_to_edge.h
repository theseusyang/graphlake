#pragma once

#include <string>
#include "type.h"

struct netflow_weight_t {
    uint32_t time;
    uint32_t duration;
    uint32_t protocol;
    uint16_t src_port;
    uint16_t dst_port;
    uint32_t src_packet;
    uint32_t dst_packet;
    uint32_t src_bytes;
    uint32_t dst_bytes;
};

struct netflow_dst_t {
    vid_t     dst_id;
    netflow_weight_t netflow;
};

typedef edgeT_t<netflow_dst_t> netflow_edge_t;

class netflow_manager_t {
    
    cfinfo_t* netflow_graph;

    public:
     netflow_manager_t() {
        netflow_graph = 0;
     }
     void get_netlow_graph();
     void set_netflow_graph();
     
     void prep_graph(const string& idirname, const string& odirname);
     index_t netflow_text_to_bin_idir(const string& idirname, const string& odirname);

};

extern netflow_manager_t netflow_manager;


