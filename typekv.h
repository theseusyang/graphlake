#pragma once

#include "graph.h"

class tinfo_t {
 public:
    sid_t   vert_id;
    sid_t   type_name;
};

class inference_tinfo_t {
 public:
    char* type_name;
    tid_t count;
    tid_t* tlist;
};

class disk_typekv_t {
    public:
    sid_t sid;
    sid_t offset;
};

//type class
class typekv_t : public cfinfo_t {
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

    //edgetable file related log
    char*    log_beg;  //memory log pointer
    sid_t    log_count;//size of memory log
    sid_t    log_head; // current log write position
    sid_t    log_tail; //current log cleaning position
    sid_t    log_wpos; //Write this pointer for write persistency

    //vertex table file related log
    disk_typekv_t* dvt;
    vid_t    dvt_count; 
    vid_t    dvt_max_count;

    FILE*    vtf;   //vertex table file
    FILE*    etf;   //edge table file

  public:

    typekv_t();

    //used by plain graph
    void manual_setup(sid_t vert_count);
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
    inline const char* get_type_name(tid_t type) {
        return log_beg + t_info[type].type_name;
    }
    inline tid_t get_total_types() {
        return t_count;
    }
    
    sid_t type_update(const string& src, const string& dst);
    void make_graph_baseline();
    void store_graph_baseline(string dir); 
    void read_graph_baseline(const string& dir); 

  public:
    virtual status_t filter(sid_t sid, univ_t value, filter_fn_t fn);
    virtual status_t get_encoded_value(const char* value, univ_t* univ);
    virtual status_t get_encoded_values(const char* value, tid_t** tids, qid_t* counts);

    static cfinfo_t* create_instance();
};
