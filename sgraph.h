#pragma once

#include "graph.h"

class pgraph_t: public cfinfo_t {
  
 public:    
    pgraph_t();
 
    status_t batch_update(const string& src, const string& dst, propid_t pid = 0);
    
 
 public:
    template <class T>
    onegraph_t<T>** prep_sgraph(sflag_t ori_flag, onegraph_t<T>** a_sgraph);
    template <class T>
    onekv_t<T>** prep_skv(sflag_t ori_flag, onekv_t<T>** a_skv);

    //void calc_edge_count(lite_sgraph_t** sgraph_out, lite_sgraph_t** sgraph_in); 
    template <class T>
    void calc_edge_count(onegraph_t<T>** sgraph_out, onegraph_t<T>** sgraph_in); 
    template <class T>
    void calc_edge_count_out(onegraph_t<T>** p_sgraph_out);
    template <class T>
    void calc_edge_count_in(onegraph_t<T>** sgraph_in);
    
    template <class T>
    void prep_sgraph_internal(onegraph_t<T>** sgraph);
    template <class T>
    void update_count(onegraph_t<T>** sgraph);
    
    template <class T>
    void store_sgraph(onegraph_t<T>** sgraph, string dir, string postfix);
    template <class T>
    void store_skv(onekv_t<T>** skv, string dir, string postfix);
    
    template <class T>
    void read_sgraph(onegraph_t<T>** sgraph, string dir, string postfix);
    template <class T>
    void read_skv(onekv_t<T>** skv, string dir, string postfix);
    /*
    sgraph_t** prep_sgraph(sflag_t ori_flag, sgraph_t** a_sgraph);
    skv_t** prep_skv(sflag_t ori_flag, skv_t** a_skv);

    void calc_edge_count(sgraph_t** sgraph_out, sgraph_t** sgraph_in); 
    void calc_edge_count_out(sgraph_t** sgraph_out);
    void calc_edge_count_in(sgraph_t** sgraph_in);
    
    void prep_sgraph_internal(sgraph_t** sgraph);
    void update_count(sgraph_t** sgraph);
    void store_sgraph(sgraph_t** sgraph, string dir, string postfix);
    void store_skv(skv_t** skv, string dir, string postfix);
    
    void read_sgraph(sgraph_t** sgraph, string dir, string postfix);
    void read_skv(skv_t** skv, string dir, string postfix);
    */
    
    void fill_adj_list(sgraph_t** sgraph_out, sgraph_t** sgraph_in);
    void fill_adj_list_in(skv_t** skv_out, sgraph_t** sgraph_in); 
    void fill_adj_list_out(sgraph_t** sgraph_out, skv_t** skv_in); 
    void fill_skv(skv_t** skv_out, skv_t** skv_in);
    
    template <class T>
    status_t query_adjlist_td(onegraph_t<T>** sgraph, srset_t* iset, srset_t* oset);
    template <class T>
    status_t query_kv_td(onekv_t<T>** skv, srset_t* iset, srset_t* oset);
    template <class T>
    status_t query_adjlist_bu(onegraph_t<T>** sgraph, srset_t* iset, srset_t* oset);
    template <class T>
    status_t query_kv_bu(onekv_t<T>** skv, srset_t* iset, srset_t* oset);
    
    template <class T> 
    status_t extend_adjlist_td(onegraph_t<T>** skv, srset_t* iset, srset_t* oset);
    template <class T> 
    status_t extend_kv_td(onekv_t<T>** skv, srset_t* iset, srset_t* oset);

};

class ugraph_t: public pgraph_t {
 public:
    sgraph_t** sgraph;

 public:
    static cfinfo_t* create_instance();
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    //status_t calc_deletededge_count(pedge_t* edge);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class dgraph_t: public pgraph_t {
 public:
    //count is hidden in type count
    sgraph_t** sgraph_out;
    sgraph_t** sgraph_in; 
 public:
    static cfinfo_t* create_instance();
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class many2one_t: public pgraph_t {
 public:
    skv_t**     skv_out;
    sgraph_t**  sgraph_in;

 public:
    static cfinfo_t* create_instance();
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class one2one_t: public pgraph_t {
 public:
    skv_t**   skv_in;
    skv_t**   skv_out;

 public:
    static cfinfo_t* create_instance();
    void make_graph_baseline();
    void store_graph_baseline(string dir);
    void read_graph_baseline(const string& dir);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

class one2many_t: public pgraph_t {
 public:
    sgraph_t**   sgraph_out;
    skv_t**      skv_in;

 public:
    static cfinfo_t* create_instance();
    void make_graph_baseline();
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
onegraph_t<T>** pgraph_t::prep_sgraph(sflag_t ori_flag, onegraph_t<T>** sgraph)
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
void pgraph_t::calc_edge_count(onegraph_t<T>** sgraph_out, onegraph_t<T>** sgraph_in) 
{
    sid_t     src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    edgeT_t<T>*   edges;
    index_t   count;
    
    for (int j = 0; j <= batch_count; ++j) { 
        edges = (edgeT_t<T>*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            src = edges[i].src_id;
            dst = get_sid(edges[i].dst_id);
            
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
}

//estimate edge count
template <class T>
void pgraph_t::calc_edge_count_out(onegraph_t<T>** sgraph_out)
{
    sid_t     src;
    vid_t     vert1_id;
    tid_t     src_index;
    edgeT_t<T>*   edges;
    index_t   count;

    for (int j = 0; j <= batch_count; ++j) { 
        edges = (edgeT_t<T>*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            src = edges[i].src_id;
            src_index = TO_TID(src);
            vert1_id = TO_VID(src);
            if (!IS_DEL(src)) {
                sgraph_out[src_index]->increment_count(vert1_id);
            } else {
                sgraph_out[src_index]->decrement_count(vert1_id);
            }
        }
    }
}
//estimate edge count
template <class T>
void pgraph_t::calc_edge_count_in(onegraph_t<T>** sgraph_in)
{
    sid_t     src, dst;
    vid_t     vert2_id;
    tid_t     dst_index;
    edgeT_t<T>*  edges;
    index_t   count;
    
    for (int j = 0; j <= batch_count; ++j) { 
        edges = (edgeT_t<T>*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            src = edges[i].src_id;
            dst = get_sid(edges[i].dst_id);
            dst_index = TO_TID(dst);
            vert2_id = TO_VID(dst);
            if (!IS_DEL(src)) {//XXX
                sgraph_in[dst_index]->increment_count(vert2_id);
            } else {
                sgraph_in[dst_index]->decrement_count(vert2_id);
            }
        }
    }
}

//prefix sum, allocate adj list memory then reset the count
template <class T>
void pgraph_t::prep_sgraph_internal(onegraph_t<T>** sgraph)
{
    tid_t       t_count = g->get_total_types();
    
    for(tid_t i = 0; i < t_count; i++) {
        if (0 == sgraph[i]) continue;
        sgraph[i]->setup_adjlist();
    }
}

template <class T>
void pgraph_t::update_count(onegraph_t<T>** sgraph)
{
    vid_t       v_count = 0;
    tid_t       t_count = g->get_total_types();
    
    for(tid_t i = 0; i < t_count; i++) {
        if (0 == sgraph[i]) continue;
        v_count = sgraph[i]->get_vcount();
        for (vid_t j = 0; j < v_count; ++j) {
            sgraph[i]->update_count(j);
        }
    }
}

template <class T>
void pgraph_t::store_sgraph(onegraph_t<T>** sgraph, string dir, string postfix)
{
    if (sgraph == 0) return;
    
    string   vtfile, etfile;
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
         
        sgraph[i]->persist_elog(etfile);
        sgraph[i]->persist_vlog(vtfile);
    }
}

template <class T>
void pgraph_t::read_sgraph(onegraph_t<T>** sgraph, string dir, string postfix)
{
    if (sgraph == 0) return;
    
    string   vtfile, etfile;
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
        
        FILE* vtf = fopen(vtfile.c_str(), "r+b");
        if (vtf == 0)  continue;
        fclose(vtf); 
        
        sgraph[i] = new onegraph_t<T>;
        sgraph[i]->setup(i);
        sgraph[i]->read_vtable(vtfile);
        sgraph[i]->read_etable(etfile);
    }
}
/******************** super kv *************************/
template <class T>
void pgraph_t::read_skv(onekv_t<T>** skv, string dir, string postfix)
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
void pgraph_t::store_skv(onekv_t<T>** skv, string dir, string postfix)
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
onekv_t<T>** pgraph_t::prep_skv(sflag_t ori_flag, onekv_t<T>** skv)
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
status_t pgraph_t::query_adjlist_td(onegraph_t<T>** sgraph, srset_t* iset, srset_t* oset)
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
status_t pgraph_t::query_kv_td(onekv_t<T>** skv, srset_t* iset, srset_t* oset)
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
status_t pgraph_t::query_adjlist_bu(onegraph_t<T>** sgraph, srset_t* iset, srset_t* oset)
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
status_t pgraph_t::query_kv_bu(onekv_t<T>** skv, srset_t* iset, srset_t* oset) 
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
status_t pgraph_t::extend_adjlist_td(onegraph_t<T>** sgraph, srset_t* iset, srset_t* oset)
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
status_t pgraph_t::extend_kv_td(onekv_t<T>** skv, srset_t* iset, srset_t* oset)
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
