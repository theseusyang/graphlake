#pragma once

#include "graph.h"

//type class
class typekv_t : public pkv_t {
  public:
    //for each type/class, the count of vertices  
    tinfo_t*       t_info;
    
    //deleted vid list for each class
    lgraph_t* lgraph_in;
    
    //mapping between enum and string
    map<string, tid_t> str2enum;
    char**      enum2str;
    tid_t       t_count;
    tid_t       max_count;

  public:
    typekv_t() {
        init_enum(256);
    };
    inline void init_enum(int enumcount) {
        max_count = enumcount;
        t_count = 0;
        t_info = new tinfo_t [enumcount];
    };
    void populate_enum(const char* e) {
        vid_t id = t_count++;
        str2enum[e] = id;
        t_info[id].type_name = gstrdup(e);
    };
    void batch_update(const string& src, const string& dst);
    inline void make_graph_baseline();
    void store_graph_baseline(string dir) {}

  public:
    status_t filter(sid_t sid, void* value, filter_fn_t fn);
    
};
