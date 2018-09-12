#pragma once

#include <string>

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


