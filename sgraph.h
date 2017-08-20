#pragma once
#include "type.h"
#include "graph.h"

template <class T>
class pgraph_t: public cfinfo_t {
    public:
        union {
            onekv_t<T>** skv_out;
            onegraph_t<T>** sgraph_out;
            onegraph_t<T>** sgraph; 
        };
        union {
            onekv_t<T>** skv_in;
            onegraph_t<T>** sgraph_in;
        };
        int ref_count;
        int snapshot_id;

        //edge batching buffer
        edgeT_t<T>* blog_beg;
        index_t     blog_count;
        index_t     blog_head;
        index_t     blog_tail;
        index_t     blog_marker;

        //queue
        index_t*   q_beg;
        index_t    q_count;
        index_t    q_head;
        index_t    q_tail;
 
 public:    
    inline pgraph_t() { 
        MAXX_ECOUNT = MAX_ECOUNT;
        sgraph = 0;
        sgraph_in = 0;
        blog_count = (MAX_ECOUNT << 2);
        if (posix_memalign((void**)&blog_beg, 2097152, blog_count*sizeof(T))) {
            perror("posix memalign batch edge log");
        }
        blog_head = 0;
        blog_tail = 0;
        blog_marker = 0;
        
        q_count = 32;
        q_beg = (index_t*)calloc(q_count, sizeof(index_t));
        if (0 == q_beg) {
            perror("posix memalign batch edge log");
        }
        q_head = 0;
        q_tail = 0;
    }

    status_t batch_update(const string& src, const string& dst, propid_t pid = 0) {
        return eOK;
    }
    status_t batch_edge(edgeT_t<T> edge) {
        index_t incr = 1;
        index_t index = __sync_fetch_and_add(&blog_head, incr);
        index_t index1 = (index % blog_count);
        if (((MAX_ECOUNT<< 1) - 1) == (index - blog_tail)) {
            blog_beg[index1] = edge;
            create_marker(index);
            //blog_marker = index;

            cout << "Will create a snapshot now " << endl;
            return eEndBatch;
        } else if ((index - blog_tail) >= blog_count) {
            //block
            return eOOM;
        }

        blog_beg[index1] = edge;
        return eOK; 
    }
    
    void create_marker(index_t marker) {
        index_t m_index = __sync_fetch_and_add(&q_head, 1L);
        q_beg[m_index % q_count] = marker;
        pthread_mutex_lock(&g->snap_mutex);
        pthread_cond_signal(&g->snap_condition);
        pthread_mutex_unlock(&g->snap_mutex);
    } 
    
    //called from snap thread 
    status_t move_marker() {
        //Need to read marker and set the blog_marker;
        if (q_tail == q_head) {
            return eNoWork;
        }
        
        index_t m_index = __sync_fetch_and_add(&q_tail, 1L);
        index_t marker = q_beg[m_index % q_count];
        blog_marker = marker;
        return eOK;
    }

 public:
    onegraph_t<T>** prep_sgraph(sflag_t ori_flag, onegraph_t<T>** a_sgraph);
    onekv_t<T>** prep_skv(sflag_t ori_flag, onekv_t<T>** a_skv);

    void calc_edge_count(onegraph_t<T>** sgraph_out, onegraph_t<T>** sgraph_in); 
    void calc_edge_count_out(onegraph_t<T>** p_sgraph_out);
    void calc_edge_count_in(onegraph_t<T>** sgraph_in);
    
    void prep_sgraph_internal(onegraph_t<T>** sgraph);
    void update_count(onegraph_t<T>** sgraph);
    
    void store_sgraph(onegraph_t<T>** sgraph, string dir, string postfix);
    void store_skv(onekv_t<T>** skv, string dir, string postfix);
    
    void read_sgraph(onegraph_t<T>** sgraph, string dir, string postfix);
    void read_skv(onekv_t<T>** skv, string dir, string postfix);
    
    void fill_adj_list(onegraph_t<T>** sgraph_out, onegraph_t<T>** sgraph_in);
    void fill_adj_list_in(onekv_t<T>** skv_out, onegraph_t<T>** sgraph_in); 
    void fill_adj_list_out(onegraph_t<T>** sgraph_out, onekv_t<T>** skv_in); 
    void fill_skv(onekv_t<T>** skv_out, onekv_t<T>** skv_in);
    
    status_t query_adjlist_td(onegraph_t<T>** sgraph, srset_t* iset, srset_t* oset);
    status_t query_kv_td(onekv_t<T>** skv, srset_t* iset, srset_t* oset);
    status_t query_adjlist_bu(onegraph_t<T>** sgraph, srset_t* iset, srset_t* oset);
    status_t query_kv_bu(onekv_t<T>** skv, srset_t* iset, srset_t* oset);
    
    status_t extend_adjlist_td(onegraph_t<T>** skv, srset_t* iset, srset_t* oset);
    status_t extend_kv_td(onekv_t<T>** skv, srset_t* iset, srset_t* oset);

};

class ugraph_t: public pgraph_t<sid_t> {
 public:
    //sgraph_t** sgraph;

 public:
    static cfinfo_t* create_instance();
    
    void incr_count(sid_t src, sid_t dst, int del = 0);
    void add_nebr(sid_t src, sid_t dst, int del = 0);
    void prep_graph_baseline();
    void calc_degree();
    void make_graph_baseline();
    void create_snapshot();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class dgraph_t: public pgraph_t<sid_t> {
 public:
    //count is hidden in type count
    //sgraph_t** sgraph_out;
    //sgraph_t** sgraph_in; 
 public:
    static cfinfo_t* create_instance();
    
    void incr_count(sid_t src, sid_t dst, int del = 0);
    void add_nebr(sid_t src, sid_t dst, int del = 0);
    void prep_graph_baseline();
    void calc_degree();
    void make_graph_baseline();
    void create_snapshot();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class many2one_t: public pgraph_t<sid_t> {
 public:
    //skv_t**     skv_out;
    //sgraph_t**  sgraph_in;

 public:
    static cfinfo_t* create_instance();
    
    void incr_count(sid_t src, sid_t dst, int del = 0);
    void add_nebr(sid_t src, sid_t dst, int del = 0);
    void prep_graph_baseline();
    void calc_degree();
    void make_graph_baseline();
    void create_snapshot();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class one2one_t: public pgraph_t<sid_t> {
 public:
    //skv_t**   skv_in;
    //skv_t**   skv_out;

 public:
    static cfinfo_t* create_instance();
    
    void incr_count(sid_t src, sid_t dst, int del = 0);
    void add_nebr(sid_t src, sid_t dst, int del = 0);
    void prep_graph_baseline();
    void calc_degree();
    void make_graph_baseline();
    void create_snapshot();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class one2many_t: public pgraph_t<sid_t> {
 public:
    //sgraph_t**   sgraph_out;
    //skv_t**      skv_in;

 public:
    static cfinfo_t* create_instance();
    
    void incr_count(sid_t src, sid_t dst, int del = 0);
    void add_nebr(sid_t src, sid_t dst, int del = 0);
    void prep_graph_baseline();
    void calc_degree();
    void make_graph_baseline();
    void create_snapshot();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};



/*****************************/

template <class T>
void onegraph_t<T>::setup(tid_t tid)
{
    if(0 == super_id) {
        super_id = g->get_type_scount(tid);
        vid_t v_count = TO_VID(super_id);
        max_vcount = (v_count << 1);
        beg_pos = (vert_table_t<T>*)calloc(sizeof(vert_table_t<T>), max_vcount);
        nebr_count = (nebrcount_t<T>*)calloc(sizeof(nebrcount_t<T>), max_vcount);
    } else {
        super_id = g->get_type_scount(tid);
        vid_t v_count = TO_VID(super_id);
        if (max_vcount < v_count) {
            assert(0);
        }
    }
}

template <class T>
void onegraph_t<T>::setup_adjlist()
{
    vid_t    v_count = TO_VID(super_id);
    vid_t          v = 0;
    vid_t          u = 0;
    degree_t count, del_count;
    
    //snapT_t<T>* snap_blob;
    snapT_t<T>* curr;

    for (vid_t vid = 0; vid < v_count; ++vid) {
        del_count = nebr_count[vid].del_count;
        count = nebr_count[vid].add_count;
        curr = beg_pos[vid].get_snapblob();
            
        if (0 != count || del_count != 0) {// new nebrs added/deleted
            //for added edges
            //even if none are added, only deleted
            nebr_count[vid].adj_list = (T*)calloc(count, sizeof(T));
            u =__sync_fetch_and_add(&v, 1L);
            dvt[u].vid = vid;
            dvt[u].degree = count;
            if (curr) { dvt[u].degree += curr->degree; }
        }
        reset_count(vid);
    }
    
    dvt_count = v;
}

template <class T>
void onegraph_t<T>::update_count() 
{
    vid_t vid = 0;
    T* adj_list1 = 0;
    T* adj_list2 = 0;
    snapid_t snap_id = g->get_snapid() + 1;

    for (sid_t i = 0; i < dvt_count; ++i) {
        vid = dvt[i].vid;
        
        snapT_t<T>* snap_blob = beg_pos[vid].get_snapblob();
        index_t index_dlog = __sync_fetch_and_add(&dlog_head, 1L);
        snapT_t<T>* curr = (snapT_t<T>*)(dlog_beg + index_dlog);
        assert(index_dlog < dlog_count);
           
        curr->del_count = nebr_count[vid].del_count;
        curr->snap_id   = snap_id;
        curr->next      = 0;
        curr->degree    = nebr_count[vid].add_count;
        if (0 != snap_blob)  curr->degree += snap_blob->degree; 
        
        index_t index_log = __sync_fetch_and_add(&log_head, curr->degree + 1);
        assert(index_log < log_count); 
        adj_list1       = log_beg + index_log;
        adj_list2       = adj_list1;
        
        if (0 != snap_blob) {
            //Old copy
            memcpy(adj_list1, beg_pos[vid].get_adjlist(),
                   (snap_blob->degree + 1)*sizeof(T));
            adj_list1 += snap_blob->degree + 1;
            //dvt[i].old_offset = adj_list - log_beg;
        } else {
            //dvt[i].old_offset = 0;
            adj_list1 += 1;
        }

        //New copy
        memcpy(adj_list1, nebr_count[vid].adj_list, nebr_count[vid].add_count*sizeof(T));
        set_nebrcount1(adj_list2, curr->degree);
        
        beg_pos[vid].set_adjlist(adj_list2);
        beg_pos[vid].set_snapblob1(curr);
        dvt[i].file_offset = index_log;
        
        nebr_count[vid].add_count = 0;
        nebr_count[vid].del_count = 0;
        free(nebr_count[vid].adj_list);
    }
}

template <class T>
void onegraph_t<T>::persist_elog(const string& etfile)
{
    if (log_wpos == log_head) return;
    
    //Make a copy
    sid_t wpos = log_wpos;
    
    //Update the mark
    log_wpos = log_head;
        
    //Write the file.
    if (etf == 0) {
        etf = fopen(etfile.c_str(), "wb");//append/write + binary
        assert(etf != 0);
    }
    fwrite(log_beg+wpos, sizeof(T), log_head-wpos, etf);
}

template <class T>
void onegraph_t<T>::persist_vlog(const string& vtfile)
{
    if (dvt_count == 0) return;
    
    //Make a copy
    sid_t count =  dvt_count;

    //update the mark
    dvt_count = 0;

    //Write the file
    if(vtf == 0) {
        vtf = fopen(vtfile.c_str(), "wb");
        assert(vtf != 0);
    }
    fwrite(dvt, sizeof(disk_vtable_t), count, vtf);
}

template <class T>
void onegraph_t<T>::persist_slog(const string& stfile)
{   
    if (dvt_count == 0) return;

    snapT_t<T>* snap_blob;
    disk_snapT_t<T>* dlog = (disk_snapT_t<T>*)snap_log;
    
    if(stf == 0) {
        stf = fopen(stfile.c_str(), "wb");
        assert(stf != 0);
    }
    
    //Lets write the snapshot log
    for (sid_t i = 0; i < dvt_count; ++i) {
        snap_blob = beg_pos[dvt[i].vid].get_snapblob();
        dlog[i].vid       = dvt[i].vid;
        dlog[i].snap_id   = snap_blob->snap_id;
        dlog[i].del_count = snap_blob->del_count;
        dlog[i].degree   = snap_blob->degree;
    }

    fwrite(snap_log, sizeof(disk_snapT_t<T>), dvt_count, stf);
}

template <class T>
void onegraph_t<T>::read_stable(const string& stfile)
{
    snapT_t<T>*      snap_blob;
    disk_snapT_t<T>* dlog;
    
    //read the file
    if(stf == 0) {
        stf = fopen(stfile.c_str(), "r+b");
        assert(stf != 0);
    }

    off_t size = fsize(stfile.c_str());
    if (size == -1L) {
        assert(0);
    }

    //read in batches. XXX
    assert(snap_size >= size);
    uint64_t read_count = fread(snap_log, sizeof(disk_snapT_t<T>), size, stf);
    snap_blob = (snapT_t<T>*)dlog_beg;
    dlog = (disk_snapT_t<T>*)snap_log; 
    
    for (int i  = 0; i < read_count; ++i)  {
        snap_blob[i].del_count = dlog[i].del_count;
        snap_blob[i].snap_id = dlog[i].snap_id;
        snap_blob[i].degree = dlog[i].degree;

        beg_pos[dlog[i].vid].set_snapblob1(snap_blob + i);
    }
    dlog_head = read_count;
}

template <class T>
void onegraph_t<T>::read_etable(const string& etfile)
{
    if (etf == 0) {
        etf = fopen(etfile.c_str(), "r+b");//append/write + binary
        assert(etf != 0);
    }

    off_t size = fsize(etfile.c_str());
    if (size == -1L) {
        assert(0);
    }
    sid_t edge_count = size/sizeof(T);
    fread(log_beg, sizeof(T), edge_count, etf);

    log_head = edge_count;
    log_wpos = log_head;
}

template <class T>
void onegraph_t<T>::read_vtable(const string& vtfile)
{
    //Write the file
    if(vtf == 0) {
        vtf = fopen(vtfile.c_str(), "r+b");
        assert(vtf != 0);
    }

    off_t size = fsize(vtfile.c_str());
    if (size == -1L) {
        assert(0);
    }
    vid_t count = (size/sizeof(disk_vtable_t));
    //snapT_t<T>* curr = 0;
    //read in batches
    while (count != 0 ) {
        vid_t read_count = fread(dvt, sizeof(disk_vtable_t), dvt_max_count, vtf);
        for (vid_t v = 0; v < read_count; ++v) {
            //curr = (snapT_t<T>*) malloc(sizeof(snapT_t<T>));
            //curr->degree = dvt[v].degree;
            //curr->del_count = 0;
            //curr->adj_list = log_beg + dvt[v].file_offset;
            //curr->snap_id = 0; 
            //nebr_count[dvt[v].vid].add_count = 0;
            
            //beg_pos[dvt[v].vid].set_snapblob1(curr);
            beg_pos[dvt[v].vid].set_adjlist(log_beg + dvt[v].file_offset);
            //beg_pos[dvt[v].vid].degree = dvt[v].degree;
        }
        count -= read_count;
    }
    dvt_count = 0;
}

/**************** SKV ******************/
template <class T>
void onekv_t<T>::setup(tid_t tid)
{
    if (0 == super_id) {
        super_id = g->get_type_scount(tid);
        vid_t v_count = TO_VID(super_id);
        max_vcount = (v_count << 2);
        kv = (T*)calloc(sizeof(T), max_vcount);
    } else {
        super_id = g->get_type_scount(tid);
        vid_t v_count = TO_VID(super_id);
        if (max_vcount < v_count) {
            assert(0);
        }
    }
}

template <class T>
void onekv_t<T>::persist_kvlog(const string& vtfile)
{
    //Make a copy
    sid_t count =  dvt_count;

    //update the mark
    dvt_count = 0;

    //Write the file
    if(vtf == 0) {
        vtf = fopen(vtfile.c_str(), "a+b");
        assert(vtf != 0);
    }
    fwrite(dvt, sizeof(disk_kvT_t<T>), count, vtf);
}

template <class T>
void onekv_t<T>::read_kv(const string& vtfile)
{
    //Write the file
    if(vtf == 0) {
        vtf = fopen(vtfile.c_str(), "r+b");
        assert(vtf != 0);
    }

    off_t size = fsize(vtfile.c_str());
    if (size == -1L) {
        assert(0);
    }
    vid_t count = (size/sizeof(disk_kvT_t<T>));

    //read in batches
    while (count !=0) {
        vid_t read_count = fread(dvt, sizeof(disk_kvT_t<T>), dvt_max_count, vtf);
        for (vid_t v = 0; v < read_count; ++v) {
            kv[dvt[v].vid] = dvt[v].dst;
        }
        count -= read_count;
    }
    dvt_count = 0;
}

/*****************************/

template <class T>
onegraph_t<T>** pgraph_t<T>::prep_sgraph(sflag_t ori_flag, onegraph_t<T>** sgraph)
{
    tid_t   pos = 0;//it is tid
    
    sflag_t      flag = ori_flag;
    tid_t  flag_count = __builtin_popcountll(flag);
    
    for(tid_t i = 0; i < flag_count; i++) {
        pos = __builtin_ctzll(flag);
        flag ^= (1L << pos);//reset that position
        if (0 == sgraph[pos]) {
            sgraph[pos] = new onegraph_t<T>;
        }
        sgraph[pos]->setup(pos);
    }
    return sgraph;
}

//estimate edge count
template <class T>
void pgraph_t<T>::calc_edge_count(onegraph_t<T>** sgraph_out, onegraph_t<T>** sgraph_in) 
{
    sid_t     src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    edgeT_t<T>* edges = blog_beg;
    index_t index = 0;
    
    for (index_t i = blog_tail; i < blog_marker; ++i) {
        index = (i % blog_count);
        src = edges[index].src_id;
        dst = get_sid(edges[index].dst_id);
        
        src_index = TO_TID(src);
        dst_index = TO_TID(dst);
        vert1_id = TO_VID(src);
        vert2_id = TO_VID(dst);
        
        if (!IS_DEL(src)) { 
            sgraph_out[src_index]->increment_count(vert1_id);
            sgraph_in[dst_index]->increment_count(vert2_id);
        } else { 
            sgraph_out[src_index]->decrement_count(vert1_id);
            sgraph_in[dst_index]->decrement_count(vert2_id);
        }
    }
}

//estimate edge count
template <class T>
void pgraph_t<T>::calc_edge_count_out(onegraph_t<T>** sgraph_out)
{
    sid_t     src;
    vid_t     vert1_id;
    tid_t     src_index;
    edgeT_t<T>* edges = blog_beg;
    
    index_t index = 0;
    for (index_t i = blog_tail; i < blog_marker; ++i) {
        index = (i % blog_count);
        src = edges[index].src_id;
        src_index = TO_TID(src);
        vert1_id = TO_VID(src);
        if (!IS_DEL(src)) {
            sgraph_out[src_index]->increment_count(vert1_id);
        } else {
            sgraph_out[src_index]->decrement_count(vert1_id);
        }
    }
}
//estimate edge count
template <class T>
void pgraph_t<T>::calc_edge_count_in(onegraph_t<T>** sgraph_in)
{
    sid_t     src, dst;
    vid_t     vert2_id;
    tid_t     dst_index;
    edgeT_t<T>* edges = blog_beg;
    
    /*
    edgeT_t<T>*  edges;
    index_t   count;
    for (int j = 0; j <= batch_count; ++j) { 
        edges = (edgeT_t<T>*)batch_info[j].buf;
        count = batch_info[j].count;
    }*/
    
    index_t index = 0;
    for (index_t i = blog_tail; i < blog_marker; ++i) {
        index = (i % blog_count);
        src = edges[index].src_id;
        dst = get_sid(edges[index].dst_id);
        dst_index = TO_TID(dst);
        vert2_id = TO_VID(dst);
        if (!IS_DEL(src)) {
            sgraph_in[dst_index]->increment_count(vert2_id);
        } else {
            sgraph_in[dst_index]->decrement_count(vert2_id);
        }
    }
}

template <class T>
void pgraph_t<T>::fill_adj_list(onegraph_t<T>** sgraph_out, onegraph_t<T>** sgraph_in)
{
    sid_t     src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    
    edge_t*   edges = blog_beg;

    index_t index = 0;
    for (index_t i = blog_tail; i < blog_marker; ++i) {
        index = (i % blog_count);
        src = edges[index].src_id;
        dst = edges[index].dst_id;
        src_index = TO_TID(src);
        dst_index = TO_TID(dst);
        vert1_id = TO_VID(src);
        vert2_id = TO_VID(dst);
       
        if (!IS_DEL(src)) { 
            sgraph_out[src_index]->add_nebr(vert1_id, dst);
            sgraph_in[dst_index]->add_nebr(vert2_id, src);
        } else {
            assert(0);
            //sgraph_out[src_index]->del_nebr(vert1_id, dst);
            //sgraph_in[dst_index]->del_nebr(vert2_id, TO_SID(src));
        }
    }
}

template <class T>
void pgraph_t<T>::fill_adj_list_in(onekv_t<T>** skv_out, onegraph_t<T>** sgraph_in) 
{
    sid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    edge_t*   edges = blog_beg;
    
    index_t index = 0;
    for (index_t i = blog_tail; i < blog_marker; ++i) {
        index = (i % blog_count);
        src = edges[index].src_id;
        dst = edges[index].dst_id;
        src_index = TO_TID(src);
        dst_index = TO_TID(dst);
        
        vert1_id = TO_VID(src);
        vert2_id = TO_VID(dst);
        
        if (!IS_DEL(src)) { 
            skv_out[src_index]->set_value(vert1_id, dst);
            sgraph_in[dst_index]->add_nebr(vert2_id, src);
        } else {
            //skv_out[src_index]->del_value(vert1_id, dst);
            //sgraph_in[dst_index]->del_nebr(vert2_id, TO_SID(src));
        }
    }
}

template <class T>
void pgraph_t<T>::fill_adj_list_out(onegraph_t<T>** sgraph_out, onekv_t<T>** skv_in) 
{
    sid_t   src, dst;
    vid_t   vert1_id, vert2_id;
    tid_t   src_index, dst_index; 
    edge_t*   edges = blog_beg;
    
    index_t index = 0;
    for (index_t i = blog_tail; i < blog_marker; ++i) {
        index = (i % blog_count);
        src = edges[index].src_id;
        dst = edges[index].dst_id;
        src_index = TO_TID(src);
        dst_index = TO_TID(dst);
        
        vert1_id = TO_VID(src);
        vert2_id = TO_VID(dst);
        if (!IS_DEL(src)) {
            sgraph_out[src_index]->add_nebr(vert1_id, dst);
            skv_in[dst_index]->set_value(vert2_id, src); 
        } else {
            //sgraph_out[src_index]->del_nebr(vert1_id, dst);
            //skv_in[dst_index]->del_value(vert2_id, TO_SID(src));
        }
    }
}

template <class T>
void pgraph_t<T>::fill_skv(onekv_t<T>** skv_out, onekv_t<T>** skv_in)
{
    sid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    edge_t*   edges = blog_beg;
    
    index_t index = 0;
    for (index_t i = blog_tail; i < blog_marker; ++i) {
        index = (i % blog_count);
        src = edges[index].src_id;
        dst = edges[index].dst_id;
        src_index = TO_TID(src);
        dst_index = TO_TID(dst);
        
        vert1_id = TO_VID(src);
        vert2_id = TO_VID(dst);
        
        if (!IS_DEL(src)) {
            skv_out[src_index]->set_value(vert1_id, dst); 
            skv_in[dst_index]->set_value(vert2_id, src); 
        } else {
            skv_out[src_index]->del_value(vert1_id, dst); 
            skv_in[dst_index]->del_value(vert2_id, TO_SID(src)); 
        }
    }
}

//prefix sum, allocate adj list memory then reset the count
template <class T>
void pgraph_t<T>::prep_sgraph_internal(onegraph_t<T>** sgraph)
{
    tid_t       t_count = g->get_total_types();
    
    for(tid_t i = 0; i < t_count; i++) {
        if (0 == sgraph[i]) continue;
        sgraph[i]->setup_adjlist();
    }
}

template <class T>
void pgraph_t<T>::update_count(onegraph_t<T>** sgraph)
{
    tid_t       t_count = g->get_total_types();
    
    for(tid_t i = 0; i < t_count; i++) {
        if (0 == sgraph[i]) continue;
        sgraph[i]->update_count();
    }

    blog_tail = blog_marker;  
}

template <class T>
void pgraph_t<T>::store_sgraph(onegraph_t<T>** sgraph, string dir, string postfix)
{
    if (sgraph == 0) return;
    
    string   vtfile, etfile, stfile;
    tid_t    t_count = g->get_total_types();
    
    //base name using relationship type
    //const char* name = 0;
    //typekv_t* typekv = g->get_typekv();
    char name[8];
    string  basefile = dir + col_info[0]->p_name;

    
    // For each file.
    for (tid_t i = 0; i < t_count; ++i) {
        if (sgraph[i] == 0) continue;

        //name = typekv->get_type_name(i);
        sprintf(name, "%d.", i);
        vtfile = basefile + name + "vtable" + postfix;
        etfile = basefile + name + "etable" + postfix;
        stfile = basefile + name + "stable" + postfix;
         
        sgraph[i]->persist_elog(etfile);
        sgraph[i]->persist_slog(stfile);
        sgraph[i]->persist_vlog(vtfile);
    }
}

template <class T>
void pgraph_t<T>::read_sgraph(onegraph_t<T>** sgraph, string dir, string postfix)
{
    if (sgraph == 0) return;
    
    string   vtfile, etfile, stfile;
    tid_t    t_count = g->get_total_types();
    
    //base name using relationship type
    //const char* name = 0;
    //typekv_t* typekv = g->get_typekv();
    char name[8];
    string  basefile = dir + col_info[0]->p_name;

    
    // For each file.
    for (tid_t i = 0; i < t_count; ++i) {

        //name = typekv->get_type_name(i);
        sprintf(name, "%d.", i);
        vtfile = basefile + name + "vtable" + postfix;
        etfile = basefile + name + "etable" + postfix;
        stfile = basefile + name + "stable" + postfix;
        
        FILE* vtf = fopen(vtfile.c_str(), "r+b");
        if (vtf == 0)  continue;
        fclose(vtf); 
        
        sgraph[i] = new onegraph_t<T>;
        sgraph[i]->setup(i);
        sgraph[i]->read_stable(stfile);
        sgraph[i]->read_vtable(vtfile);
        sgraph[i]->read_etable(etfile);
    }
}
/******************** super kv *************************/
template <class T>
void pgraph_t<T>::read_skv(onekv_t<T>** skv, string dir, string postfix)
{
    if (skv == 0) return;

    //const char* name = 0;
    //typekv_t*   typekv = g->get_typekv();
    char name[8];
    tid_t       t_count = g->get_total_types();
    
    //base name using relationship type
    string basefile = dir + col_info[0]->p_name;
    string vtfile;

    // For each file.
    for (tid_t i = 0; i < t_count; ++i) {
        
        //name = typekv->get_type_name(i);
        sprintf(name, "%d.", i);
        vtfile = basefile + name + "kv" + postfix;
        
        FILE* vtf = fopen(vtfile.c_str(), "r+b");
        if (vtf == 0)  continue; 
        fclose(vtf); 

        skv[i] = new onekv_t<T>;
        skv[i]->setup(i);
        skv[i]->read_kv(vtfile);
    }
}

template <class T>
void pgraph_t<T>::store_skv(onekv_t<T>** skv, string dir, string postfix)
{
    if (skv == 0) return;

    //const char* name = 0;
    //typekv_t*   typekv = g->get_typekv();
    char name[8];
    tid_t       t_count = g->get_total_types();
    
    //base name using relationship type
    string basefile = dir + col_info[0]->p_name;
    string vtfile;

    // For each file.
    for (tid_t i = 0; i < t_count; ++i) {
        if (skv[i] == 0) continue;
        //name = typekv->get_type_name(i);
        sprintf(name, "%d.", i);
        vtfile = basefile + name + "kv" + postfix;

        skv[i]->persist_kvlog(vtfile);
    }
}

//super bins memory allocation
template <class T>
onekv_t<T>** pgraph_t<T>::prep_skv(sflag_t ori_flag, onekv_t<T>** skv)
{
    tid_t   pos  = 0;
    sflag_t flag       = ori_flag;
    tid_t   flag_count = __builtin_popcountll(flag);

    for(tid_t i = 0; i < flag_count; i++) {
        pos = __builtin_ctz(flag);
        flag ^= (1L << pos);//reset that position
        if (0 == skv[pos]) {
            skv[pos] = new onekv_t<T>;
        }
        skv[pos]->setup(pos);
    }
    return skv;
}

template <class T>
status_t pgraph_t<T>::query_adjlist_td(onegraph_t<T>** sgraph, srset_t* iset, srset_t* oset)
{
    tid_t    iset_count = iset->get_rset_count();
    rset_t*        rset = 0;

    for (tid_t i = 0; i < iset_count; ++i) {
        rset = iset->rset + i;
        vid_t v_count = rset->get_vcount();
        vid_t* vlist = rset->get_vlist();
        
        //get the graph where we will traverse
        tid_t        tid = rset->get_tid();
        if (0 == sgraph[tid]) continue;
        vert_table_t<T>* graph = sgraph[tid]->get_begpos();

        
        //Get the frontiers
        vid_t     frontier;
        for (vid_t v = 0; v < v_count; v++) {
            frontier = vlist[v];
            T* adj_list = graph[frontier].get_adjlist();
            vid_t nebr_count = get_nebrcount1(adj_list);
            ++adj_list;
            
            //traverse the adj list
            for (vid_t k = 0; k < nebr_count; ++k) {
                oset->set_status(get_nebr(adj_list, k));
            }
        }
    }
    return eOK;
}

template <class T>
status_t pgraph_t<T>::query_kv_td(onekv_t<T>** skv, srset_t* iset, srset_t* oset)
{
    tid_t    iset_count = iset->get_rset_count();
    rset_t*        rset = 0;

    for (tid_t i = 0; i < iset_count; ++i) {
        rset = iset->rset + i;
        vid_t v_count = rset->get_vcount();
        vid_t* vlist = rset->get_vlist();
        
        //get the graph where we will traverse
        tid_t        tid = rset->get_tid();
        if (0 == skv[tid]) continue;
        T* kv = skv[tid]->get_kv(); 

        //Get the frontiers
        vid_t     frontier;
        for (vid_t v = 0; v < v_count; v++) {
            frontier = vlist[v];
            oset->set_status(get_nebr(kv, frontier));
        }
    }
    return eOK;
}

//sgraph_in and oset share the same flag.
template <class T>
status_t pgraph_t<T>::query_adjlist_bu(onegraph_t<T>** sgraph, srset_t* iset, srset_t* oset)
{
    rset_t* rset = 0;
    tid_t   tid  = 0;
    tid_t oset_count = oset->get_rset_count();

    for (tid_t i = 0; i < oset_count; ++i) {
        
        //get the graph where we will traverse
        rset = oset->rset + i;
        tid  = rset->get_tid();
        if (0 == sgraph[tid]) continue; 

        vert_table_t<T>* graph = sgraph[tid]->get_begpos(); 
        vid_t    v_count = sgraph[tid]->get_vcount();
        
        
        for (vid_t v = 0; v < v_count; v++) {
            //traverse the adj list
            T* adj_list = graph[v].get_adjlist();
            vid_t nebr_count = get_nebrcount1(adj_list);
            ++adj_list;
            for (vid_t k = 0; k < nebr_count; ++k) {
                if (iset->get_status(get_nebr(adj_list, k))) {
                    rset->set_status(v);
                    break;
                }
            }
        }
    }
    return eOK;
}

template <class T>
status_t pgraph_t<T>::query_kv_bu(onekv_t<T>** skv, srset_t* iset, srset_t* oset) 
{
    rset_t*  rset = 0;
    tid_t    tid  = 0;
    tid_t    oset_count = oset->get_rset_count();
    for (tid_t i = 0; i < oset_count; ++i) {

        //get the graph where we will traverse
        rset = oset->rset + i;
        tid  = rset->get_tid(); 
        if (0 == skv[tid]) continue;

        T* kv = skv[tid]->get_kv(); 
        sid_t   v_count = skv[tid]->get_vcount();
        
        for (vid_t v = 0; v < v_count; ++v) {
            if (iset->get_status(get_nebr(kv, v))) {
                rset->set_status(v);
                break;
            }
        }
    }
    return eOK;
}

template <class T> 
status_t pgraph_t<T>::extend_adjlist_td(onegraph_t<T>** sgraph, srset_t* iset, srset_t* oset)
{
    tid_t    iset_count = iset->get_rset_count();
    rset_t*        rset = 0;
    rset_t*        rset2 = 0;

    iset->bitwise2vlist();
    //prepare the output 1,2;
    oset->copy_setup(iset, eAdjlist);

    for (tid_t i = 0; i < iset_count; ++i) {
        rset = iset->rset + i;
        rset2 = oset->rset + i;
        vid_t v_count = rset->get_vcount();
        sid_t* varray = rset->get_vlist();
        
        //get the graph where we will traverse
        tid_t        tid = rset->get_tid();
        if (0 == sgraph[tid]) continue;
        vert_table_t<T>* graph = sgraph[tid]->get_begpos(); 
        
        for (vid_t v = 0; v < v_count; v++) {
            rset2->add_adjlist_ro(v, graph+varray[v]);
        }
    }
    return eOK;
}

template <class T>
status_t pgraph_t<T>::extend_kv_td(onekv_t<T>** skv, srset_t* iset, srset_t* oset)
{
    tid_t    iset_count = iset->get_rset_count();
    rset_t*        rset = 0;
    rset_t*       rset2 = 0;

    iset->bitwise2vlist();
    //prepare the output 1,2;
    oset->copy_setup(iset, eKV);

    for (tid_t i = 0; i < iset_count; ++i) {
        rset = iset->rset + i;
        rset2 = oset->rset + i;
        vid_t v_count = rset->get_vcount();
        sid_t* varray = rset->get_vlist();
        
        //get the graph where we will traverse
        tid_t     tid = rset->get_tid();
        if (0 == skv[tid]) continue;
        T*  graph = skv[tid]->get_kv(); 
        
        for (vid_t v = 0; v < v_count; v++) {
            rset2->add_kv(v, get_nebr(graph, varray[v]));
        }
    }
    return eOK;
}


