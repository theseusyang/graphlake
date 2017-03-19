#pragma once

typedef uint32_t pid_t;
typedef uint32_t vid_t;
typedef uint64_t index_t;

enum p_type {
    edgraph,
    emany2one,
    eugraph,
    eenum,
    estring,
    efloat,
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

class p_info_t {
 protected:
    char*       p_name;
    void*       buf;
    uint32_t    count;
    uint32_t    flag;

 public:
    virtual void batch_update(const string& src, const string& dst);
    virtual void make_graph_baseline();
    virtual void store_graph_baseline();
};

class ugraph_t: public p_info_t 
{
protected:
    index_t* beg_pos;
    vid_t*   adj_list;

public:
    void batch_update(const string& src, const string& dst);
    void make_graph_baseline();
    void store_graph_baseline();
    
}
