#pragma once

#include "graph.h"

class tinfo_t {
 public:
    char*   type_name;
    sid_t vert_id;
};

class inference_tinfo_t {
 public:
    char* type_name;
    tid_t count;
    tid_t* tlist;
};

//type class
class typekv_t : public pinfo_t {
  private:
    
    //deleted vid list for each class
    lgraph_t* lgraph_in;
    
    //mapping between enum and string
    map<string, tid_t> str2enum;
    
    //for each type/class, the count of vertices  
    tinfo_t*    t_info;
    tid_t       t_count;

    inference_tinfo_t* it_info;
    tid_t       it_count;

    tid_t       max_count;


  public:
    typekv_t() {
        init_enum(256);
    };
    inline void init_enum(int enumcount) {
        max_count = enumcount;
        t_count = 0;
        it_count = 0;
        t_info = new tinfo_t [enumcount];
        it_info = new inference_tinfo_t[enumcount];
    };
    
    inline void populate_inference_type(const char* e, tid_t count, tid_t* tlist) {
        vid_t id = it_count++;
        str2enum[e] = id + t_count;
        it_info[id].type_name = gstrdup(e);
        it_info[id].tlist = tlist;
        it_info[id].count = count;
    };

    inline  sid_t get_type_scount(tid_t type) {
        return t_info[type].vert_id;
    }
    inline tid_t get_total_types() {
        return t_count;
    }
    
    status_t batch_update(const string& src, const string& dst);
    inline void make_graph_baseline();
    void store_graph_baseline(string dir) {}

  public:
    virtual status_t filter(sid_t sid, univ_t value, filter_fn_t fn);
    virtual status_t get_encoded_value(const char* value, univ_t* univ);
    virtual status_t get_encoded_values(const char* value, tid_t** tids, qid_t* counts);
    
};
