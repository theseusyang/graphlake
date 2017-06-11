#pragma once

template <class T>
void onegraph_t<T>::setup(tid_t tid)
{
    if(0 == super_id) {
        super_id = g->get_type_scount(tid);
        vid_t v_count = TO_VID(super_id);
        max_vcount = (v_count << 1);
        beg_pos = (vert_table_t<T>*)calloc(sizeof(vert_table_t<T>), max_vcount);
        nebr_count = (vid_t*)calloc(sizeof(vid_t), max_vcount);
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
    vid_t v_count = TO_VID(super_id);
    sid_t count;
    T* adj_list = 0;
    T* adj_list1 = 0;
    vid_t v = 0;

    for (vid_t vid = 0; vid < v_count; ++vid) {
        adj_list = beg_pos[vid].get_adjlist();
        count = nebr_count[vid];

        if (adj_list && beg_pos[vid].get_nebrcount() != count) {// new nebrs added
            adj_list = log_beg + log_head;
            adj_list1 = beg_pos[vid].get_adjlist();

            memcpy(adj_list, adj_list1, 
                   beg_pos[vid].get_nebrcount()*sizeof(T));
            beg_pos[vid].set_adjlist(adj_list);
            
            dvt[v].vid = vid;
            dvt[v].degree = count;
            dvt[v].file_offset = log_head;
            
            log_head += count + 1;
            ++v;
        } else if (!adj_list) {//first time
            beg_pos[vid].set_adjlist(log_beg + log_head); 
            
            dvt[v].vid = vid;
            dvt[v].degree = count;
            dvt[v].file_offset = log_head;
            
            log_head += count + 1; 
            ++v;
        }
        nebr_count[vid] = beg_pos[vid].get_nebrcount();
    }
    dvt_count = v;
}

template <class T>
void onegraph_t<T>::persist_elog(const string& etfile)
{
    //Make a copy
    sid_t wpos = log_wpos;
    
    //Update the mark
    log_wpos = log_head;
        
    //Write the file.
    if (etf == 0) {
        etf = fopen(etfile.c_str(), "a+b");//append/write + binary
        assert(etf != 0);
    }
    fwrite(log_beg+wpos, sizeof(T), log_head-wpos, etf);
}

template <class T>
void onegraph_t<T>::persist_vlog(const string& vtfile)
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
    fwrite(dvt, sizeof(disk_vtable_t), count, vtf);
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

    //read in batches
    while (count !=0 ) {
        vid_t read_count = fread(dvt, sizeof(disk_vtable_t), dvt_max_count, vtf);
        for (vid_t v = 0; v < read_count; ++v) {
            nebr_count[dvt[v].vid] = dvt[v].degree;
            beg_pos[dvt[v].vid].set_adjlist(log_beg + dvt[v].file_offset);
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
        kv = (vid_t*)calloc(sizeof(T), max_vcount);
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
    fwrite(dvt, sizeof(disk_kv_t), count, vtf);
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
    vid_t count = (size/sizeof(disk_kv_t));

    //read in batches
    while (count !=0) {
        vid_t read_count = fread(dvt, sizeof(disk_kv_t), dvt_max_count, vtf);
        for (vid_t v = 0; v < read_count; ++v) {
            kv[dvt[v].vid] = dvt[v].dst;
        }
        count -= read_count;
    }
    dvt_count = 0;
}

/******** graphs **************/
class pgraph_t: public cfinfo_t {
  public:    
 
    //graph specific functions 
    status_t batch_update(const string& src, const string& dst, propid_t pid = 0);
 
 public:
    pgraph_t();
 public:
    sgraph_t** prep_sgraph(sflag_t ori_flag, sgraph_t** a_sgraph);
    skv_t** prep_skv(sflag_t ori_flag, skv_t** a_skv);
    
    void calc_edge_count(sgraph_t** sgraph_out, sgraph_t** sgraph_in); 
    void calc_edge_count_out(sgraph_t** sgraph_out);
    void calc_edge_count_in(sgraph_t** sgraph_in);
    
    //void calc_deletededge_count(sgraph_t** sgraph_out, sgraph_t** sgraph_in); 
    void calc_deletededge_count_out(sgraph_t** sgraph_out);
    void calc_deletededge_count_in(sgraph_t** sgraph_in);
    
    void prep_sgraph_internal(sgraph_t** sgraph);
    void update_count(sgraph_t** sgraph);
    
    void fill_adj_list(sgraph_t** sgraph_out, sgraph_t** sgraph_in);
    void fill_adj_list_in(skv_t** skv_out, sgraph_t** sgraph_in); 
    void fill_adj_list_out(sgraph_t** sgraph_out, skv_t** skv_in); 
    void fill_skv(skv_t** skv_out, skv_t** skv_in);
    
    void store_sgraph(sgraph_t** sgraph, string dir, string postfix);
    void store_skv(skv_t** skv, string dir, string postfix);
    
    void read_sgraph(sgraph_t** sgraph, string dir, string postfix);
    void read_skv(skv_t** skv, string dir, string postfix);

    status_t query_adjlist_td(sgraph_t** sgraph, srset_t* iset, srset_t* oset);
    status_t query_kv_td(skv_t** skv, srset_t* iset, srset_t* oset);
    status_t query_adjlist_bu(sgraph_t** sgraph, srset_t* iset, srset_t* oset);
    status_t query_kv_bu(skv_t** skv, srset_t* iset, srset_t* oset);
  
    
    status_t extend_adjlist_td(sgraph_t** skv, srset_t* iset, srset_t* oset);
    status_t extend_kv_td(skv_t** skv, srset_t* iset, srset_t* oset);
};


class ugraph_t: public pgraph_t {
 protected:
    sgraph_t** sgraph;

 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    //status_t calc_deletededge_count(pedge_t* edge);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class dgraph_t: public pgraph_t {
 protected:
    //count is hidden in type count
    sgraph_t** sgraph_out;
    sgraph_t** sgraph_in; 
 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class many2one_t: public pgraph_t {
 protected:
    skv_t**     skv_out;
    sgraph_t**  sgraph_in;

 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class one2one_t: public pgraph_t {
 protected:
    skv_t**   skv_in;
    skv_t**   skv_out;

 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class one2many_t: public pgraph_t {
 protected:
    sgraph_t**   sgraph_out;
    skv_t**      skv_in;

 public:
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};
