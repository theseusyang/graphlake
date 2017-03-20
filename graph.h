#pragma once

typedef uint32_t pid_t;
typedef uint32_t vid_t;
typedef uint64_t index_t;

enum p_type {
    edgraph, //directed graph
    emany2one, // directed graph many to one such as "advisor"
    eugraph, // undirected graph
    // All the label properties now
    eenum,   // value is an enum, such as "type" property
    estring, // value is a string, such as "name"
    efloat,  // 
    edouble,
    eint32,
    euint32,
    eint64,
    euint64,
    edate,
    elast
}

class edge_t {
    vid_t src_id;
    vid_t dst_id;
};

map <string, vid_t> str2vid;
vid_t vert_count = 0;

map <string, pid_t> str2pid;
p_info_t*       p_info;
pid_t           p_count = 0;

class p_info_t {
 protected:
    char*       p_name;
    void*       buf;
    uint32_t    count;
    uint32_t    flag;

 public:
    void populate_property(const char* property);
    virtual void batch_update(const string& src, const string& dst);
    virtual void make_graph_baseline();
    virtual void store_graph_baseline();
};

class ugraph_t: public p_info_t {
 protected:
    index_t* beg_pos;
    vid_t*   adj_list;

 public:
    void batch_update(const string& src, const string& dst);
    void make_graph_baseline();
    void store_graph_baseline();
}

class dgraph_t: public p_info_t {
 protected:
    index_t* beg_pos_in;
    vid_t*   adj_list_in;
    index_t* beg_pos_out;
    vid_t*   adj_list_out;

 public:
    void batch_update(const string& src, const string& dst);
    void make_graph_baseline();
    void store_graph_baseline();
}

class many2one_t: public p_info_t {
 protected:
    index_t* beg_pos_in;
    vid_t*   adj_list_in;
    vid_t*   kv_out;

 public:
    void batch_update(const string& src, const string& dst);
    void make_graph_baseline();
    void store_graph_baseline();
};


} 

class enumgraph_t: public many2one_t {
protected:
    //mapping between enum and string
    map<string, vid_t> str2enum;
    char** enum2str;
    int     ecount;
    int     max_count;

 public:
    void init_enum(int enumcount);
    void populate_enum(const char* e); 
    void batch_update(const string& src, const string& dst);
    //void make_graph_baseline();
    //void store_graph_baseline();

};

class int64kv: public p_info_t {
 protected:
    index_t* beg_pos;
    vid_t*   adj_list;

 public:
    void batch_update(const string& src, const string& dst);
    void make_graph_baseline();
    void store_graph_baseline();
}
