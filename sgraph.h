#pragma once

#include <omp.h>
#include <sys/mman.h>
#include <asm/mman.h>
#include <unistd.h>
#include <fcntl.h>


#include "type.h"
#include "graph.h"
#include "wtime.h"

//for each range
template <class T>
class global_range_t {
  public:
      index_t count;
      edgeT_t<T>* edges;
};

//for each thread 
class thd_local_t {
  public:
      //For each thread
      vid_t* vid_range;
      vid_t  range_end;
};

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
        
        edgeT_t<T>* edge_buf_out;
        edgeT_t<T>* edge_buf_in;
        index_t edge_buf_count;

        //edge batching buffer
        blog_t<T>*  blog;
        int       wtf;   //edge log file

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
        edge_buf_out = 0;
        edge_buf_in = 0;
        edge_buf_count = 0;
        
        blog = new blog_t<T>;
        blog->blog_count = BLOG_SIZE;
        blog->blog_beg = (edgeT_t<T>*)mmap(0, sizeof(edgeT_t<T>)*blog->blog_count, PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0);
        if (MAP_FAILED == blog->blog_beg) {
            cout << "Huge page alloc failed for edge log" << endl;
            if (posix_memalign((void**)&blog->blog_beg, 2097152, blog->blog_count*sizeof(edgeT_t<T>))) {
                perror("posix memalign batch edge log");
            }
        }
        
        q_count = 512;
        q_beg = (index_t*)calloc(q_count, sizeof(index_t));
        if (0 == q_beg) {
            perror("posix memalign batch edge log");
        }
        q_head = 0;
        q_tail = 0;
        wtf = 0;
    }
    
    inline void alloc_edge_buf(index_t total) {
        index_t total_edge_count = 0;
        if (0 == sgraph_in) {
            total_edge_count = (total << 1);
            if (0 == edge_buf_count) {
                edge_buf_out = (edgeT_t<T>*)malloc(total_edge_count*sizeof(edgeT_t<T>));
                edge_buf_count = total_edge_count;
            } else if (edge_buf_count < total_edge_count) {
                free(edge_buf_out);
                edge_buf_out = (edgeT_t<T>*)malloc(total_edge_count*sizeof(edgeT_t<T>));
                edge_buf_count = total_edge_count;
            }
        } else {
            total_edge_count = total;
            if (0 == edge_buf_count) {
                edge_buf_out = (edgeT_t<T>*)malloc(total_edge_count*sizeof(edgeT_t<T>));
                edge_buf_in = (edgeT_t<T>*)malloc(total_edge_count*sizeof(edgeT_t<T>));
                edge_buf_count = total_edge_count;
            } else if (edge_buf_count < total_edge_count) {
                free(edge_buf_out);
                free(edge_buf_in);
                edge_buf_out = (edgeT_t<T>*)malloc(total_edge_count*sizeof(edgeT_t<T>));
                edge_buf_in = (edgeT_t<T>*)malloc(total_edge_count*sizeof(edgeT_t<T>));
                edge_buf_count = total_edge_count;
            }
        }
    }

    inline void free_edge_buf() {
        if (edge_buf_out) {    
            free(edge_buf_out);
            edge_buf_out = 0;
        }
        if (edge_buf_in) {
            free(edge_buf_in);
            edge_buf_in = 0;
        }
        edge_buf_count = 0;
    }

    status_t batch_update(const string& src, const string& dst, propid_t pid = 0) {
        return eOK;
    }
    status_t batch_edge(edgeT_t<T> edge) {
        status_t ret = eOK;
        index_t index = __sync_fetch_and_add(&blog->blog_head, 1L);
        index_t index1 = (index & BLOG_MASK);
        index_t size = ((index - blog->blog_marker) & BATCH_MASK);
        if ((0 == size) && (index != blog->blog_marker)) {
            blog->blog_beg[index1] = edge;
            create_marker(index + 1);
            //cout << "Will create a snapshot now " << endl;
            return eEndBatch;
            //ret = eEndBatch;
        } else if ((index - blog->blog_tail) == blog->blog_count - 1000) {
            blog->blog_beg[index1] = edge;
            create_marker(index + 1);
            cout << "About OOM" << endl;
            return eOOM;
        } else if ((index - blog->blog_tail) >= blog->blog_count) {
            //block
            assert(0);
            return eOOM;
        }

        blog->blog_beg[index1] = edge;
        //if (ret != eEndBatch) {
        //    blog->blog_beg[index1] = edge;
        //}
            
        //----
        //Make the edge log durable
        //if ((index != blog->blog_wmarker) && 
        //    ((index - blog->blog_wmarker) % W_SIZE) == 0) {
        //    create_wmarker(index);
        //}
    
        return ret; 
    }
    
    //Called from front end thread
    void create_wmarker(index_t marker) {
        pthread_mutex_lock(&g->w_mutex);
        if (marker > blog->blog_wmarker) {
            blog->blog_wmarker = marker;
        }
        pthread_cond_signal(&g->w_condition);
        pthread_mutex_unlock(&g->w_mutex);
        cout << "WMarker queued." << endl;
    }
    
    //called from w thread 
    status_t write_edgelog() {
        index_t w_marker = blog->blog_head;
        index_t w_tail = blog->blog_wtail;
        index_t w_count = w_marker - w_tail;
        if (w_count == 0) return eNoWork;

        index_t actual_tail = w_tail & BLOG_MASK;
        index_t actual_marker = w_marker & BLOG_MASK;
        
        if (actual_tail < actual_marker) {
            //write and update tail
            //fwrite(blog->blog_beg + w_tail, sizeof(edgeT_t<T>), w_count, wtf);
            write(wtf, blog->blog_beg + actual_tail, sizeof(edgeT_t<T>)*w_count);
        }
        else {
            write(wtf, blog->blog_beg + actual_tail, sizeof(edgeT_t<T>)*(BLOG_SIZE - actual_tail));
            write(wtf, blog->blog_beg, sizeof(edgeT_t<T>)*actual_marker);
        }
        blog->blog_wtail = w_marker;
        //fsync();
        return eOK;
    }
    
   // status_t write_edgelog() {
   //     index_t w_marker = 0;
   //     index_t w_tail = 0;
   //     index_t w_count = 0;
   //     pthread_mutex_lock(&g->w_mutex);
   //     w_marker = blog->blog_wmarker;
   //     pthread_mutex_unlock(&g->w_mutex);
   //     w_tail = blog->blog_wtail;
   //     w_count = w_marker - w_tail;
   //     if (w_count) {
   //         //write and update tail
   //         //fwrite(blog->blog_beg + w_tail, sizeof(edgeT_t<T>), w_count, wtf);
   //         write(wtf, blog->blog_beg + w_tail, sizeof(edgeT_t<T>)*w_count);
   //         blog->blog_wtail = w_marker;
   //         return eOK;
   //     }
   //     return eNoWork;
   // }
    
    void create_marker(index_t marker) {
        pthread_mutex_lock(&g->snap_mutex);
        index_t m_index = __sync_fetch_and_add(&q_head, 1L);
        q_beg[m_index % q_count] = marker;
        pthread_cond_signal(&g->snap_condition);
        pthread_mutex_unlock(&g->snap_mutex);
        //cout << "Marker queued. position = " << m_index % q_count << " " << marker << endl;
    } 
    
    //called from snap thread 
    status_t move_marker(index_t& snap_marker) {
        pthread_mutex_lock(&g->snap_mutex);
        index_t head = q_head;
        //Need to read marker and set the blog_marker;
        if (q_tail == head) {
            pthread_mutex_unlock(&g->snap_mutex);
            //cout << "Marker NO dequeue. Position = " << head <<  endl;
            return eNoWork;
        }
        
        index_t m_index = head - 1;
        index_t marker = q_beg[m_index % q_count];
        q_tail = head;
        blog->blog_marker = marker;
        snap_marker = blog->blog_marker;
        
        /*
        index_t m_index = __sync_fetch_and_add(&q_tail, 1L);
        index_t marker = q_beg[m_index % q_count];
        blog->blog_marker = marker;
        snap_marker = blog->blog_marker;
        */

        pthread_mutex_unlock(&g->snap_mutex);
        //cout << "working on snapshot" << endl;
        //cout << "Marker dequeue. Position = " << m_index % q_count << " " << marker << endl;
        return eOK;
    }

    index_t update_marker() { 
        blog->blog_tail = blog->blog_marker;
        return blog->blog_tail;
    }

 public:
    onegraph_t<T>** prep_sgraph(sflag_t ori_flag, onegraph_t<T>** a_sgraph);
    onekv_t<T>** prep_skv(sflag_t ori_flag, onekv_t<T>** a_skv);
    void make_graph_d(); 
    void make_graph_u();

    void estimate_classify(vid_t* vid_range, vid_t* vid_range_in, vid_t bit_shift);
    void prefix_sum(global_range_t<T>* global_range, thd_local_t* thd_local,
                    vid_t range_count, vid_t thd_count, edgeT_t<T>* edge_buf);
    void work_division(global_range_t<T>* global_range, thd_local_t* thd_local,
                    vid_t range_count, vid_t thd_count, index_t equal_work);
    void classify(vid_t* vid_range, vid_t* vid_range_in, vid_t bit_shift, 
            global_range_t<T>* global_range, global_range_t<T>* global_range_in);
    void calc_degree_noatomic(onegraph_t<T>** sgraph, global_range_t<T>* global_range, 
                      vid_t j_start, vid_t j_end);
    void fill_adjlist_noatomic(onegraph_t<T>** sgraph, global_range_t<T>* global_range, 
                      vid_t j_start, vid_t j_end);

    void calc_edge_count(onegraph_t<T>** sgraph_out, onegraph_t<T>** sgraph_in); 
    void calc_edge_count_out(onegraph_t<T>** p_sgraph_out);
    void calc_edge_count_in(onegraph_t<T>** sgraph_in);
    
    void prep_sgraph_internal(onegraph_t<T>** sgraph);
    void update_count(onegraph_t<T>** sgraph);
    
    void store_sgraph(onegraph_t<T>** sgraph, bool clean = false);
    void store_skv(onekv_t<T>** skv);
    
    void read_sgraph(onegraph_t<T>** sgraph);
    void read_skv(onekv_t<T>** skv);
    
    void file_open_sgraph(onegraph_t<T>** sgraph, const string& odir, const string& postfix, bool trunc);
    void file_open_skv(onekv_t<T>** skv, const string& odir, const string& postfix, bool trunc);
    
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
template <class T>
class ugraph: public pgraph_t<T> {
 public:
    using pgraph_t<T>::sgraph;
    using pgraph_t<T>::flag1;
    using pgraph_t<T>::flag2;
    using pgraph_t<T>::flag1_count;
    using pgraph_t<T>::flag2_count;
    using pgraph_t<T>::blog;

    using pgraph_t<T>::read_sgraph;
    using pgraph_t<T>::prep_sgraph;
    using pgraph_t<T>::file_open_sgraph;
    using pgraph_t<T>::calc_edge_count;
    using pgraph_t<T>::prep_sgraph_internal;
    using pgraph_t<T>::fill_adj_list;
    using pgraph_t<T>::store_sgraph;
    using pgraph_t<T>::extend_adjlist_td;
    using pgraph_t<T>::query_adjlist_td;
    using pgraph_t<T>::query_adjlist_bu;


 public:
    static cfinfo_t* create_instance();
    
    void incr_count(sid_t src, sid_t dst, int del = 0);
    void add_nebr(sid_t src, sid_t dst, int del = 0);
    void prep_graph_baseline();
    void calc_degree();
    void make_graph_baseline();
    void create_snapshot();
    void store_graph_baseline(bool clean = false);
    void read_graph_baseline();
    void file_open(const string& odir,  bool trunc);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

template <class T>
class dgraph: public pgraph_t<T> {
 public:
    //count is hidden in type count
    //sgraph_t** sgraph_out;
    //sgraph_t** sgraph_in; 
    using pgraph_t<T>::sgraph_in;
    using pgraph_t<T>::sgraph_out;
    using pgraph_t<T>::flag1;
    using pgraph_t<T>::flag2;
    using pgraph_t<T>::flag1_count;
    using pgraph_t<T>::flag2_count;
    using pgraph_t<T>::blog;
    
    using pgraph_t<T>::prep_sgraph;
    using pgraph_t<T>::read_sgraph;
    using pgraph_t<T>::file_open_sgraph;
    using pgraph_t<T>::calc_edge_count;
    using pgraph_t<T>::prep_sgraph_internal;
    using pgraph_t<T>::fill_adj_list;
    using pgraph_t<T>::store_sgraph;
    using pgraph_t<T>::extend_adjlist_td;
    using pgraph_t<T>::query_adjlist_td;
    using pgraph_t<T>::query_adjlist_bu;

 public:
    static cfinfo_t* create_instance();
    
    void incr_count(sid_t src, sid_t dst, int del = 0);
    void add_nebr(sid_t src, sid_t dst, int del = 0);
    void prep_graph_baseline();
    void calc_degree();
    void make_graph_baseline();
    void create_snapshot();
    void store_graph_baseline(bool clean = false);
    void read_graph_baseline();
    void file_open(const string& odir,  bool trunc);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

template <class T>
class many2one: public pgraph_t<T> {
 public:
    //skv_t**     skv_out;
    //sgraph_t**  sgraph_in;
    using pgraph_t<T>::sgraph_in;
    using pgraph_t<T>::skv_out;
    using pgraph_t<T>::flag1;
    using pgraph_t<T>::flag2;
    using pgraph_t<T>::flag1_count;
    using pgraph_t<T>::flag2_count;
    using pgraph_t<T>::blog;
    
    using pgraph_t<T>::read_sgraph;
    using pgraph_t<T>::read_skv;
    using pgraph_t<T>::prep_sgraph;
    using pgraph_t<T>::prep_skv;
    using pgraph_t<T>::file_open_sgraph;
    using pgraph_t<T>::file_open_skv;
    using pgraph_t<T>::calc_edge_count_in;
    using pgraph_t<T>::prep_sgraph_internal;
    using pgraph_t<T>::fill_adj_list_in;
    using pgraph_t<T>::store_sgraph;
    using pgraph_t<T>::store_skv;
    using pgraph_t<T>::extend_adjlist_td;
    using pgraph_t<T>::extend_kv_td;
    using pgraph_t<T>::query_adjlist_td;
    using pgraph_t<T>::query_adjlist_bu;
    using pgraph_t<T>::query_kv_td;
    using pgraph_t<T>::query_kv_bu;

 public:
    static cfinfo_t* create_instance();
    
    void incr_count(sid_t src, sid_t dst, int del = 0);
    void add_nebr(sid_t src, sid_t dst, int del = 0);
    void prep_graph_baseline();
    void calc_degree();
    void make_graph_baseline();
    void create_snapshot();
    void store_graph_baseline(bool clean = false);
    void read_graph_baseline();
    void file_open(const string& odir,  bool trunc);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

template <class T>
class one2one: public pgraph_t<T> {
 public:
    //skv_t**   skv_in;
    //skv_t**   skv_out;
    using pgraph_t<T>::skv_in;
    using pgraph_t<T>::skv_out;
    using pgraph_t<T>::flag1;
    using pgraph_t<T>::flag2;
    using pgraph_t<T>::flag1_count;
    using pgraph_t<T>::flag2_count;
    using pgraph_t<T>::blog;
    
    using pgraph_t<T>::read_skv;
    using pgraph_t<T>::prep_skv;
    using pgraph_t<T>::file_open_skv;
    using pgraph_t<T>::store_skv;
    using pgraph_t<T>::fill_skv;
    using pgraph_t<T>::extend_kv_td;
    using pgraph_t<T>::query_kv_td;
    using pgraph_t<T>::query_kv_bu;

 public:
    static cfinfo_t* create_instance();
    
    void incr_count(sid_t src, sid_t dst, int del = 0);
    void add_nebr(sid_t src, sid_t dst, int del = 0);
    void prep_graph_baseline();
    void calc_degree();
    void make_graph_baseline();
    void create_snapshot();
    void store_graph_baseline(bool clean = false);
    void read_graph_baseline();
    void file_open(const string& odir,  bool trunc);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};

template <class T>
class one2many: public pgraph_t<T> {
 public:
    //sgraph_t**   sgraph_out;
    //skv_t**      skv_in;
    using pgraph_t<T>::skv_in;
    using pgraph_t<T>::sgraph_out;
    using pgraph_t<T>::flag1;
    using pgraph_t<T>::flag2;
    using pgraph_t<T>::flag1_count;
    using pgraph_t<T>::flag2_count;
    using pgraph_t<T>::blog;
    
    using pgraph_t<T>::read_sgraph;
    using pgraph_t<T>::read_skv;
    using pgraph_t<T>::prep_sgraph;
    using pgraph_t<T>::prep_skv;
    using pgraph_t<T>::file_open_sgraph;
    using pgraph_t<T>::file_open_skv;
    using pgraph_t<T>::calc_edge_count_out;
    using pgraph_t<T>::prep_sgraph_internal;
    using pgraph_t<T>::fill_adj_list_out;
    using pgraph_t<T>::store_sgraph;
    using pgraph_t<T>::store_skv;
    using pgraph_t<T>::extend_adjlist_td;
    using pgraph_t<T>::extend_kv_td;
    using pgraph_t<T>::query_adjlist_td;
    using pgraph_t<T>::query_adjlist_bu;
    using pgraph_t<T>::query_kv_td;
    using pgraph_t<T>::query_kv_bu;

 public:
    static cfinfo_t* create_instance();
    
    void incr_count(sid_t src, sid_t dst, int del = 0);
    void add_nebr(sid_t src, sid_t dst, int del = 0);
    void prep_graph_baseline();
    void calc_degree();
    void make_graph_baseline();
    void create_snapshot();
    void store_graph_baseline(bool clean = false);
    void read_graph_baseline();
    void file_open(const string& odir,  bool trunc);
    
    status_t transform(srset_t* iset, srset_t* oset, direction_t direction);
    virtual status_t extend(srset_t* iset, srset_t* oset, direction_t direction);
};


typedef ugraph<sid_t> ugraph_t;
typedef dgraph<sid_t> dgraph_t;
typedef one2many<sid_t> one2many_t;
typedef many2one<sid_t> many2one_t;
typedef one2one<sid_t> one2one_t;

typedef ugraph<lite_edge_t> p_ugraph_t;
typedef dgraph<lite_edge_t> p_dgraph_t;
typedef one2many<lite_edge_t> p_one2many_t;
typedef many2one<lite_edge_t> p_many2one_t;
typedef one2one<lite_edge_t> p_one2one_t;

/*****************************/

template <class T>
void onegraph_t<T>::setup(tid_t tid)
{
    if(0 == super_id) {
        super_id = g->get_type_scount(tid);
        vid_t v_count = TO_VID(super_id);
        max_vcount = v_count;// (v_count << 1);
        beg_pos = (vert_table_t<T>*)calloc(sizeof(vert_table_t<T>), max_vcount);

#ifdef BULK
        nebr_count = (nebrcount_t<T>*)calloc(sizeof(nebrcount_t<T>), max_vcount);

        index_t total_memory = 0;
        total_memory += max_vcount*(sizeof(vert_table_t<T>) + sizeof(nebrcount_t<T>));
        cout << "Total Memory 1 = " << total_memory << endl;
        
        //dela adj list
        adjlog_count = DELTA_SIZE + (v_count*sizeof(delta_adjlist_t<T>)); //8GB
        adjlog_beg = (char*)mmap(NULL, adjlog_count, PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0);
        if (MAP_FAILED == adjlog_beg) {
            cout << "Huge page allocation failed for delta adj list" << endl;
            if (posix_memalign((void**)&adjlog_beg, 2097152, adjlog_count)) {
                perror("posix memalign delta adj list");
            }
        }
        
        total_memory += adjlog_count;
        cout << "Total Memory 2 = " << total_memory << endl;
        
        //degree aray realted log, in-memory
        dlog_count = (((index_t)v_count)*SNAP_COUNT);//256 MB
        /*
         * dlog_beg = (snapT_t<T>*)mmap(NULL, sizeof(snapT_t<T>)*dlog_count, PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0 );
        
        if (MAP_FAILED == dlog_beg) {
            cout << "Huge page allocation failed for degree array" << endl;
        }
            */
            if (posix_memalign((void**)&dlog_beg, 2097152, dlog_count*sizeof(snapT_t<T>))) {
                perror("posix memalign snap log");
            }
        /*
        //degree array relatd log, for writing to disk
        snap_count = (1L << 16);//256 MB
        if (posix_memalign((void**)&snap_log, 2097152, snap_count*sizeof(disk_snapT_t<T>))) {
            perror("posix memalign snap disk log");
        }
        */
        
        total_memory += dlog_count*sizeof(snapT_t<T>);
        cout << "Total Memory 2 = " << total_memory << endl;
        
        //durable vertex log and adj list log
        dvt_max_count = DVT_SIZE;
        log_count = DURABLE_SIZE;
        if (posix_memalign((void**) &write_seg[0].dvt, 2097152, 
                           dvt_max_count*sizeof(disk_vtable_t))) {
            perror("posix memalign vertex log");    
        }
        if (posix_memalign((void**) &write_seg[1].dvt, 2097152, 
                           dvt_max_count*sizeof(disk_vtable_t))) {
            perror("posix memalign vertex log");    
        }
        if (posix_memalign((void**) &write_seg[2].dvt, 2097152, 
                           dvt_max_count*sizeof(disk_vtable_t))) {
            perror("posix memalign vertex log");    
        }
        if (posix_memalign((void**)&write_seg[0].log_beg, 2097152, log_count)) {
            //log_beg = (index_t*)calloc(sizeof(index_t), log_count);
            perror("posix memalign edge log");
        }
        if (posix_memalign((void**)&write_seg[1].log_beg, 2097152, log_count)) {
            //log_beg = (index_t*)calloc(sizeof(index_t), log_count);
            perror("posix memalign edge log");
        }

        total_memory += dvt_max_count*sizeof(disk_vtable_t)*3 + log_count*2;
        cout << "Total Memory 2 = " << total_memory << endl;
        
        /*
        if (posix_memalign((void**)&log_beg, 2097152, log_count*sizeof(T))) {
            //log_beg = (index_t*)calloc(sizeof(index_t), log_count);
            perror("posix memalign edge log");
        }*/

		//v_unit log
		vunit_count = (v_count << 1L);
        if (posix_memalign((void**)&vunit_beg, 2097152, 3L*v_count*sizeof(vunit_t<T>))) {
            perror("posix memalign vunit_beg");
        }
		if (posix_memalign((void**)&vunit_ind, 2097152, 2L*v_count*sizeof(vid_t))) {
            perror("posix memalign vunit_ind");
        }
        
        total_memory += 3L*vunit_count*sizeof(vunit_t<T>) + 2L*sizeof(vid_t);
        cout << "Total Memory 2 = " << total_memory << endl;
		
        vid_t i_end = 3L*v_count; 
		for (vid_t i = v_count; i < i_end; ++i) {
			vunit_ind[i-v_count] = i; 
		}
#endif

    } else {
        super_id = g->get_type_scount(tid);
        vid_t v_count = TO_VID(super_id);
        if (max_vcount < v_count) {
            assert(0);
        }
    }
}

//returns the location of the found value
template <class T>
degree_t onegraph_t<T>::find_nebr(vid_t vid, sid_t sid) 
{
    //Find the location of deleted one
    vunit_t<T>* v_unit = beg_pos[vid].get_vunit();
    if (0 == v_unit) return INVALID_DEGREE;

    degree_t  durable_degree = v_unit->count;
    degree_t    local_degree = 0;
    degree_t          degree = 0;
    sid_t               nebr = 0;
    T*         local_adjlist = 0;
    delta_adjlist_t<T>* delta_adjlist = v_unit->delta_adjlist;
    delta_adjlist_t<T>* next = delta_adjlist->get_next();
    
    while (next != 0) {
        local_adjlist = delta_adjlist->get_adjlist();
        local_degree  = delta_adjlist->get_nebrcount();
        for (degree_t i = 0; i < local_degree; ++i) {
            nebr = get_nebr(local_adjlist, i);
            if (nebr == sid) {
                return i + degree + durable_degree;
            }
        }
        degree += local_degree;
        delta_adjlist = next;
        next = next->get_next();
    }

    local_adjlist = delta_adjlist->get_adjlist();
    local_degree = nebr_count[vid].add_count;
    for (degree_t i = 0; i < local_degree; ++i) {
        nebr = get_nebr(local_adjlist, i);
        if (nebr == sid) {
            return i + degree + durable_degree;
        }
    }
    //Durable adj list 
    if (durable_degree == 0) return INVALID_DEGREE;

    index_t   offset = v_unit->offset;
    index_t sz_to_read = offset*sizeof(T) + sizeof(durable_adjlist_t<T>);
    durable_adjlist_t<T>* durable_adjlist = (durable_adjlist_t<T>*)malloc(sz_to_read);
    pread(etf, durable_adjlist, sz_to_read, offset);
    T* adj_list = delta_adjlist->get_adjlist();
    for (degree_t i = 0; i < durable_degree; ++i) {
        nebr = get_nebr(adj_list, i);
        if (nebr == sid) {
            return i;
        }
    }
    return INVALID_DEGREE;
}
/*
template <class T>
void onegraph_t<T>::setup_adjlist(vid_t vid_start, vid_t vid_end)
{
    //vid_t    v_count = TO_VID(super_id);
    degree_t count, del_count, total_count;
	vunit_t<T>* v_unit = 0;
    snapT_t<T>* curr;
    index_t my_vunit_count = 0;
    index_t my_dsnap_count = 0;
    index_t my_delta_size = 0;

    //#pragma omp for schedule(static) nowait
    for (vid_t vid = vid_start; vid < vid_end; ++vid) {
        del_count = nebr_count[vid].del_count;
        count = nebr_count[vid].add_count;
        
        if (0 != count || 0 != del_count) {// new nebrs added/deleted

            total_count = count + del_count;
        
            if (0 == total_count) {
                continue;
            }
            v_unit = beg_pos[vid].get_vunit();
            my_vunit_count += (v_unit == 0);
            curr = beg_pos[vid].get_snapblob();
            ++my_dsnap_count;
            //my_dsnap_count += (curr == 0);
            my_delta_size += total_count;
        }            
    }

    //Allocate bulk memory
    vunit_t<T>* my_vunit_beg = new_vunit_bulk(my_vunit_count);
    snapT_t<T>* my_dlog_beg = new_snapdegree_bulk(my_dsnap_count);
    assert(dlog_head <= dlog_count);

    index_t new_count = my_delta_size*sizeof(T) 
						+ my_dsnap_count*sizeof(delta_adjlist_t<T>);
    char*  my_adjlog_beg = new_delta_adjlist_bulk(new_count);

    //Do the smaller allocations without needing any atomic instrcutions
    // and regular work
    snapid_t snap_id = g->get_snapid() + 1;
	delta_adjlist_t<T>* prev_delta = 0;
	delta_adjlist_t<T>* delta_adjlist = 0;
    index_t delta_size = 0;
    index_t delta_metasize = sizeof(delta_adjlist_t<T>);

    //#pragma omp for schedule(static) 
    //for (vid_t vid = 0; vid < v_count; ++vid) 
    for (vid_t vid = vid_start; vid < vid_end; ++vid) {
        del_count = nebr_count[vid].del_count;
        count = nebr_count[vid].add_count;
        
        if (0 != count || 0 != del_count) {// new nebrs added/deleted
            total_count = count + del_count;
            if (0 == total_count) {
                continue;
            }
            
            //delta adj list allocation
            delta_adjlist = (delta_adjlist_t<T>*)(my_adjlog_beg);
            delta_size = total_count*sizeof(T) + delta_metasize;
			my_adjlog_beg += delta_size;
            
            if (my_adjlog_beg > adjlog_beg + adjlog_count) { //rewind happened
                my_adjlog_beg -=  adjlog_count;
                
                //Last allocation is wasted due to rewind
                delta_adjlist = (delta_adjlist_t<T>*)new_delta_adjlist_bulk(delta_size);
            }
            
            //delta_adjlist->set_nebrcount(total_count);
            delta_adjlist->set_nebrcount(0);
            delta_adjlist->add_next(0);
			
            v_unit = beg_pos[vid].get_vunit();
            if (v_unit) {
                prev_delta = v_unit->adj_list;
			    if (prev_delta) {
                    prev_delta->add_next(delta_adjlist);
                } else {
			        v_unit->delta_adjlist = delta_adjlist;
                }
			} else {
				v_unit = my_vunit_beg;
                my_vunit_beg += 1;
			    v_unit->delta_adjlist = delta_adjlist;
				beg_pos[vid].set_vunit(v_unit);
            }

			v_unit->adj_list = delta_adjlist;
            
            ////allocate new snapshot for degree, and initialize
			//snapT_t<T>* next    = my_dlog_beg; 
            //my_dlog_beg        += 1;
            //next->del_count     = del_count;
            //next->snap_id       = snap_id;
            ////next->next          = 0;
            //next->degree        = count;

            curr = beg_pos[vid].get_snapblob();
            if (curr) {
                curr->degree += count;
                curr->del_count += del_count;
            } else {
                //allocate new snapshot for degree, and initialize
                snapT_t<T>* next    = my_dlog_beg; 
                my_dlog_beg        += 1;
                next->del_count     = del_count;
                next->snap_id       = snap_id;
                //next->next          = 0;
                next->degree        = count;
                
                if (curr) {
                    next->degree    += curr->degree;
                    next->del_count += curr->del_count;
                }
                beg_pos[vid].set_snapblob1(next);
            }
        }
        reset_count(vid);
    }
}
*/

template <class T>
void onegraph_t<T>::setup_adjlist()
{
    vid_t    v_count = TO_VID(super_id);
    snapid_t snap_id = g->get_snapid() + 1;
    
    snapT_t<T>* curr;
	vunit_t<T>* v_unit = 0;
	delta_adjlist_t<T>* delta_adjlist = 0;
	delta_adjlist_t<T>* prev_delta = 0;
    degree_t count, del_count, total_count;
    
    #pragma omp for
    for (vid_t vid = 0; vid < v_count; ++vid) {
        del_count = nebr_count[vid].del_count;
        count = nebr_count[vid].add_count;
        total_count = count + del_count;
    
        if (0 == total_count) {
            continue;
        }

        
        //delta adj list allocation
        delta_adjlist = new_delta_adjlist(total_count);
        delta_adjlist->set_nebrcount(0);
        delta_adjlist->add_next(0);
        
        v_unit = beg_pos[vid].get_vunit();
        if(v_unit) {
            prev_delta = v_unit->adj_list;
            if (prev_delta) {
                prev_delta->add_next(delta_adjlist);
            } else {
                v_unit->delta_adjlist = delta_adjlist;
            }
        } else {
            v_unit = new_vunit();
            v_unit->delta_adjlist = delta_adjlist;
            beg_pos[vid].set_vunit(v_unit);
        }

        v_unit->adj_list = delta_adjlist;
    
        //allocate new snapshot for degree, and initialize
        snapT_t<T>* next    = new_snapdegree(); 
        next->del_count     = del_count;
        next->snap_id       = snap_id;
        //next->next          = 0;
        next->degree        = count;
        
        curr = beg_pos[vid].get_snapblob();
        if (curr) {
            next->degree    += curr->degree;
            next->del_count += curr->del_count;
        }

        beg_pos[vid].set_snapblob1(next);
        reset_count(vid);
    }
}


template <class T>
void onegraph_t<T>::file_open(const string& filename, bool trunc)
{
    file = filename; 
    string  vtfile = filename + ".vtable";
    string  etfile = filename + ".etable";
    //string  stfile = filename + ".stable";

    if (trunc) {
		etf = open(etfile.c_str(), O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
		vtf = open(vtfile.c_str(), O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
        //vtf = fopen(vtfile.c_str(), "wb");
    } else {
		etf = open(etfile.c_str(), O_RDWR|O_CREAT, S_IRWXU);
		vtf = open(vtfile.c_str(), O_RDWR|O_CREAT, S_IRWXU);
        //vtf = fopen(vtfile.c_str(), "r+b");
    }
}

#include <stdio.h>
template <class T>
void onegraph_t<T>::handle_write(bool clean /* = false */)
{
    vid_t   v_count = TO_VID(super_id);
    vid_t last_vid1 = 0;
    vid_t last_vid2 = 0;
    
    string etfile = file + ".etable";
    string vtfile = file + ".vtable";
    string etfile_new = file + ".etable_new";
    string vtfile_new = file + ".vtable_new";
    
    int etf_new = etf;
    int vtf_new = vtf;
    
    if (clean) {
		vtf_new = open(vtfile_new.c_str(), O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
		etf_new = open(etfile_new.c_str(), O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
        log_tail = 0;
    }
     
    write_seg_t* seg1 = new write_seg_t(write_seg[0]);
    write_seg_t* seg2 = new write_seg_t(write_seg[1]); 
    write_seg_t* seg3 = new write_seg_t(write_seg[2]); 
    
	prepare_dvt(seg1, last_vid1, clean);
    
    do {
        last_vid2 = last_vid1;
        swap(seg1, seg2);
        #pragma omp parallel num_threads(THD_COUNT)
        {
            #pragma omp master
            {
                prepare_dvt(seg1, last_vid1,clean);
            }
            if (1 == omp_get_thread_num())
            {
                //Write the dvt log
                if (seg2->dvt_count) {
                    off_t size = sizeof(disk_vtable_t)*seg2->dvt_count;
					if (size != write(vtf_new, seg2->dvt, size)) {
						perror("write issue in dvt");
						assert(0);
					}
                }
			}
            if (2 == omp_get_thread_num())
            {
				//Write new adj list
				if (seg3->log_head != 0) {
					off_t size = seg3->log_head;
					if(size != write(etf_new, seg3->log_beg, size)) {
						perror("pwrite issue in adj list");
						assert(0);
					}
				}
            }

			adj_update(seg3);
            adj_prep(seg2);
        }

		swap(seg2, seg3);
		seg2->log_head = 0;
		seg2->dvt_count = 0;
		seg2->log_tail = seg3->log_tail;
		seg2->log_beg = seg3->log_beg;
		
    } while(last_vid2 < v_count);

	//The last write and adj update	
	#pragma omp parallel num_threads(THD_COUNT)
	{
		//Write new adj list
		#pragma omp master
		{
            if (seg3->log_head != 0) {
                off_t size = seg3->log_head;
                if (size != write(etf_new, seg3->log_beg, seg3->log_head)) {
                    perror("pwrite issue");
                    assert(0);
                }
            }
		}
	    adj_update(seg3);
	}

    //Rename the files
    if (clean) {
        swap(vtf, vtf_new);
        close(vtf_new);
        remove(vtfile.c_str());
        rename(vtfile_new.c_str(), vtfile.c_str());
        
        
        swap(etf, etf_new);
        //XXX Should be closed only when no one is using it. 
        close(etf_new);
        remove(etfile.c_str());
        rename(etfile_new.c_str(), etfile.c_str());
    }

    adjlog_tail = adjlog_head;
	//adjlog_head = 0;
}

template <class T>
void onegraph_t<T>::prepare_dvt (write_seg_t* seg, vid_t& last_vid, bool clean /* = false */)
{
    vid_t    v_count = TO_VID(super_id);
    durable_adjlist_t<T>* adj_list2 = 0;
    snapT_t<T>* curr = 0;
	disk_vtable_t* dvt1 = 0;
	//Note the initial offset
	seg->log_tail = log_tail;
	seg->log_head = 0;
	seg->dvt_count = 0;
	
    for (vid_t vid = last_vid; vid < v_count ; ++vid) {
        if (0 == beg_pos[vid].v_unit || (0 == beg_pos[vid].v_unit->adj_list  && !clean)) continue;
		
        curr		= beg_pos[vid].get_snapblob();
		if ((seg->log_head + curr->degree*sizeof(T) + sizeof(durable_adjlist_t<T>)  > log_count) ||
            (seg->dvt_count >= dvt_max_count)) {
            last_vid = vid;
            log_tail += seg->log_head;
			seg->my_vunit_head = new_vunit_bulk2(seg->dvt_count);
            return;
		}
        
        //durable adj list allocation
		adj_list2   = new_adjlist(seg, curr->degree);
        
		//v_unit log for disk write
        dvt1              = new_dvt(seg);
		dvt1->vid         = vid;
		dvt1->count	     = curr->degree;
        dvt1->del_count  = curr->del_count;
        dvt1->file_offset = ((char*)adj_list2) - seg->log_beg;
        dvt1->file_offset += seg->log_tail;
    }

    last_vid = v_count;
    log_tail += seg->log_head;
	seg->my_vunit_head = new_vunit_bulk2(seg->dvt_count);
    return;
}
/*
template <class T>
void onegraph_t<T>::adj_write(write_seg_t* seg)
{
	vid_t vid;
	disk_vtable_t* dvt1 = 0;
	vunit_t<T>* v_unit = 0;
	vunit_t<T>* prev_v_unit = 0;
	index_t  prev_offset;
    degree_t total_count = 0;
    degree_t prev_total_count;

	delta_adjlist_t<T>* delta_adjlist = 0;
	durable_adjlist_t<T>* durable_adjlist = 0;
    T* adj_list1 = 0;

    #pragma omp for schedule(dynamic, 256) nowait
	for (vid_t v = 0; v < seg->dvt_count; ++v) {
		dvt1 = seg->dvt + v;
		vid = dvt1->vid;
		if (0 == nebr_count[vid].adj_list) continue;
		prev_v_unit       = beg_pos[vid].get_vunit();
		prev_total_count  = prev_v_unit->count;
		prev_offset       = prev_v_unit->offset;
        total_count       = dvt1->count + dvt1->del_count;
		
		//Find the allocated durable adj list
		durable_adjlist = (durable_adjlist_t<T>*)(seg->log_beg + dvt1->file_offset - log_tail);
        adj_list1 = durable_adjlist->get_adjlist();
	   
        //Copy the Old durable adj list
		if (prev_total_count) {
			//Read the old adj list from disk
            index_t sz_to_read = sizeof(durable_adjlist_t<T>) + prev_total_count*sizeof(T);
			pread(etf, durable_adjlist , sz_to_read, prev_offset);
			adj_list1 += prev_total_count;
        }
        
        durable_adjlist->set_nebrcount(total_count);

        //Copy the new in-memory adj-list
		delta_adjlist = prev_v_unit->delta_adjlist;
        while(delta_adjlist) {
			memcpy(adj_list1, delta_adjlist->get_adjlist(),
				   delta_adjlist->get_nebrcount()*sizeof(T));
			adj_list1 += delta_adjlist->get_nebrcount();
			delta_adjlist = delta_adjlist->get_next();
		}

		v_unit = new_vunit();
		v_unit->count = total_count;
		v_unit->offset = dvt1->file_offset;// + log_tail;
		v_unit->delta_adjlist = 0;
		//beg_pos[vid].set_vunit(v_unit);
		nebr_count[vid].v_unit = v_unit;
            
		nebr_count[vid].add_count = 0;
        nebr_count[vid].del_count = 0;
        //nebr_count[vid].adj_list = 0;
    }
}
*/

template <class T>
void onegraph_t<T>::adj_update(write_seg_t* seg)
{
	vid_t vid;
	disk_vtable_t* dvt1 = 0;
	vunit_t<T>* v_unit = 0;
	vunit_t<T>* v_unit1 = 0;

    #pragma omp for nowait 
	for (vid_t v = 0; v < seg->dvt_count; ++v) {
		dvt1 = seg->dvt + v;
		vid = dvt1->vid;
		v_unit =   new_vunit(seg, v);
		v_unit1 = beg_pos[vid].set_vunit(v_unit);
        vunit_ind[(seg->my_vunit_head + v) % vunit_count] = v_unit1 - vunit_beg;
	}

}
template <class T>
void onegraph_t<T>::adj_prep(write_seg_t* seg)
{
	vid_t vid;
	disk_vtable_t* dvt1 = 0;
	vunit_t<T>* v_unit = 0;
	vunit_t<T>* prev_v_unit = 0;
	index_t  prev_offset;
    degree_t total_count = 0;
    degree_t prev_total_count;

	delta_adjlist_t<T>* delta_adjlist = 0;
	durable_adjlist_t<T>* durable_adjlist = 0;
    T* adj_list1 = 0;

    #pragma omp for nowait 
	for (vid_t v = 0; v < seg->dvt_count; ++v) {
		dvt1 = seg->dvt + v;
		vid = dvt1->vid;

		prev_v_unit       = beg_pos[vid].get_vunit();
		prev_total_count  = prev_v_unit->count;
		prev_offset       = prev_v_unit->offset;
        total_count       = dvt1->count + dvt1->del_count;
		
		//Find the allocated durable adj list
		durable_adjlist = (durable_adjlist_t<T>*)(seg->log_beg + dvt1->file_offset 
												  - seg->log_tail);
        adj_list1 = durable_adjlist->get_adjlist();
	   
        //Copy the Old durable adj list
		if (prev_total_count) {
			//Read the old adj list from disk
            index_t sz_to_read = sizeof(durable_adjlist_t<T>) + prev_total_count*sizeof(T);
			pread(etf, durable_adjlist , sz_to_read, prev_offset);
			adj_list1 += prev_total_count;
        }
        
        durable_adjlist->set_nebrcount(total_count);

        //Copy the new in-memory adj-list
		delta_adjlist = prev_v_unit->delta_adjlist;
        while(delta_adjlist) {
			memcpy(adj_list1, delta_adjlist->get_adjlist(),
				   delta_adjlist->get_nebrcount()*sizeof(T));
			adj_list1 += delta_adjlist->get_nebrcount();
			delta_adjlist = delta_adjlist->get_next();
		}

		//Write new adj list
        //index_t sz_to_write = total_count*sizeof(T) + sizeof(durable_adjlist_t<T>);
		//pwrite (etf, durable_adjlist, sz_to_write, dvt1->file_offset);

		v_unit =   new_vunit(seg, v);
		v_unit->reset();
		v_unit->count = total_count;
		v_unit->offset = dvt1->file_offset;// + log_tail;
		v_unit->delta_adjlist = 0;
        v_unit->adj_list = 0;
		//beg_pos[vid].set_vunit(v_unit);
            
		nebr_count[vid].add_count = 0;
        nebr_count[vid].del_count = 0;
        //nebr_count[vid].adj_list = 0;
    }
		
	//Write new adj list
    //fwrite (log_beg, sizeof(T), log_head, etf);
    
    //if (seg->log_head != 0) {
	//    index_t size = pwrite(etf, seg->log_beg, seg->log_head*sizeof(T), 
    //                          log_tail*sizeof(T));
    //    if (size != seg->log_head*sizeof(T)) {
    //        perror("pwrite issue");
    //        assert(0);
    //    }
    //}
    
	//Write the dvt log
	//fwrite(seg->dvt, sizeof(disk_vtable_t), seg->dvt_count, vtf);
}



template <class T>
void onegraph_t<T>::read_vtable()
{
    off_t size = fsize(vtf);
    if (size == -1L) {
        assert(0);
    }
    vid_t count = (size/sizeof(disk_vtable_t));
	vid_t vid = 0;
	vunit_t<T>* v_unit = 0;
    disk_vtable_t* dvt = write_seg[0].dvt;
	snapT_t<T>* next ; 
    snapid_t snap_id = 1;

    //read in batches
    while (count != 0 ) {
        //vid_t read_count = read(dvt, sizeof(disk_vtable_t), dvt_max_count, vtf);
        vid_t read_count = read(vtf, dvt, sizeof(disk_vtable_t)*dvt_max_count);
        read_count /= sizeof(disk_vtable_t); 

        for (vid_t v = 0; v < read_count; ++v) {
			vid = dvt[v].vid;
			v_unit = beg_pos[vid].get_vunit();
			if (v_unit) {
				v_unit->offset = dvt[v].file_offset;
				v_unit->count = dvt[v].count + dvt[v].del_count;
			} else {
				v_unit = new_vunit();
				v_unit->offset = dvt[v].file_offset;
				v_unit->count = dvt[v].count + dvt->del_count;
				beg_pos[vid].set_vunit(v_unit);
			}
            //allocate new snapshot for degree, and initialize
			next                = new_snapdegree(); 
            next->del_count     = dvt[v].del_count;
            next->snap_id       = snap_id;
            //next->next          = 0;
            next->degree        = dvt[v].count;
            beg_pos[vid].set_snapblob1(next);
        }
        count -= read_count;
    }
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
void onekv_t<T>::file_open(const string& vtfile, bool trunc)
{
    if(trunc) {
        //vtf = fopen(vtfile.c_str(), "wb");
		vtf = open(vtfile.c_str(), O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
        assert(vtf != 0);
    } else {
        //vtf = fopen(vtfile.c_str(), "r+b");
		vtf = open(vtfile.c_str(), O_RDWR|O_CREAT, S_IRWXU);
        assert(vtf != 0);
    }
}

template <class T>
void onekv_t<T>::persist_kvlog()
{
    //Make a copy
    sid_t count =  dvt_count;

    //update the mark
    dvt_count = 0;

    //Write the file
    //fwrite(dvt, sizeof(disk_kvT_t<T>), count, vtf);
    write(vtf, dvt, sizeof(disk_kvT_t<T>)*count);
}

template <class T>
void onekv_t<T>::read_kv()
{
    off_t size = fsize(vtf);
    if (size == -1L) {
        assert(0);
    }
    vid_t count = (size/sizeof(disk_kvT_t<T>));

    //read in batches
    while (count !=0) {
        //vid_t read_count = fread(dvt, sizeof(disk_kvT_t<T>), dvt_max_count, vtf);
        vid_t read_count = read(vtf, dvt, sizeof(disk_kvT_t<T>)*dvt_max_count);
        read_count /= sizeof(disk_kvT_t<T>);
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
    edgeT_t<T>* edges = blog->blog_beg;
    index_t index = 0;
   
    #pragma omp for
    for (index_t i = blog->blog_tail; i < blog->blog_marker; ++i) {
        index = (i & BLOG_MASK);
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
    edgeT_t<T>* edges = blog->blog_beg;
    
    index_t index = 0;
    for (index_t i = blog->blog_tail; i < blog->blog_marker; ++i) {
        index = (i & BLOG_MASK);
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
    edgeT_t<T>* edges = blog->blog_beg;
    
    /*
    edgeT_t<T>*  edges;
    index_t   count;
    for (int j = 0; j <= batch_count; ++j) { 
        edges = (edgeT_t<T>*)batch_info[j].buf;
        count = batch_info[j].count;
    }*/
    
    index_t index = 0;
    for (index_t i = blog->blog_tail; i < blog->blog_marker; ++i) {
        index = (i & BLOG_MASK);
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


//prefix sum, allocate adj list memory then reset the count
template <class T>
void pgraph_t<T>::prep_sgraph_internal(onegraph_t<T>** sgraph)
{
    tid_t  t_count   = g->get_total_types();
    
    vid_t  v_count   = 0;
    vid_t  portion   = 0;
    vid_t  vid_start = 0;
    vid_t  vid_end   = 0;
    vid_t  total_thds  = omp_get_num_threads();
    vid_t         tid  = omp_get_thread_num();  
    
    for(tid_t i = 0; i < t_count; i++) {
        if (0 == sgraph[i]) continue;
        //sgraph[i]->setup_adjlist();
        
        v_count = sgraph[i]->get_vcount();
        portion = v_count/total_thds;
        vid_start = portion*tid;
        vid_end   = portion*(tid + 1);
        if (tid == total_thds - 1) {
            vid_end = v_count;
        }

        sgraph[i]->setup_adjlist_noatomic(vid_start, vid_end);
        #pragma omp barrier
        
    }
}


template <class T>
void pgraph_t<T>::store_sgraph(onegraph_t<T>** sgraph, bool clean /*= false*/)
{
    if (sgraph == 0) return;
    
    tid_t    t_count = g->get_total_types();
    
    // For each file.
    for (tid_t i = 0; i < t_count; ++i) {
        if (sgraph[i] == 0) continue;
		sgraph[i]->handle_write(clean);
        /*
		sgraph[i]->persist_elog(etfile);
        sgraph[i]->persist_slog(stfile);
        sgraph[i]->persist_vlog(vtfile);
		*/
    }
}

template <class T>
void pgraph_t<T>::file_open_sgraph(onegraph_t<T>** sgraph, const string& dir, const string& postfix, bool trunc)
{
    if (sgraph == 0) return;
    
    char name[8];
    string  basefile = dir + col_info[0]->p_name;
    string  filename;
    string  wtfile; 

    // For each file.
    tid_t    t_count = g->get_total_types();
    for (tid_t i = 0; i < t_count; ++i) {
        if (0 == sgraph[i]) continue;

        sprintf(name, "%d", i);
        filename = basefile + name + postfix ; 
        sgraph[i]->file_open(filename, trunc);
        
        wtfile = filename + ".elog";
		if (trunc) {
            wtf = open(wtfile.c_str(), O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
        } else {
		    wtf = open(wtfile.c_str(), O_RDWR|O_CREAT, S_IRWXU);
        }
    }
}

template <class T>
void pgraph_t<T>::read_sgraph(onegraph_t<T>** sgraph)
{
    if (sgraph == 0) return;
    
    tid_t    t_count = g->get_total_types();
    
    // For each file.
    for (tid_t i = 0; i < t_count; ++i) {
        if (sgraph[i] == 0) continue;
        sgraph[i]->read_vtable();
        //sgraph[i]->read_stable(stfile);
        //sgraph[i]->read_etable(etfile);
    }
}


template <class T>
void pgraph_t<T>::fill_adj_list(onegraph_t<T>** sgraph_out, onegraph_t<T>** sgraph_in)
{
    sid_t     src, dst2; 
    T         src2, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    
    edgeT_t<T>*   edges = blog->blog_beg;

    index_t index = 0;
    #pragma omp for
    for (index_t i = blog->blog_tail; i < blog->blog_marker; ++i) {
        index = (i & BLOG_MASK);
        src = edges[index].src_id;
        dst = edges[index].dst_id;
        
        src_index = TO_TID(src);
        vert1_id = TO_VID(src);
        sgraph_out[src_index]->add_nebr(vert1_id, dst);
        
        dst2 = get_sid(dst);
        set_sid(src2, src);
        set_weight(src2, dst);

        dst_index = TO_TID(dst2);
        vert2_id = TO_VID(dst2);
        sgraph_in[dst_index]->add_nebr(vert2_id, src2);
    }
}

template <class T>
void pgraph_t<T>::fill_adj_list_in(onekv_t<T>** skv_out, onegraph_t<T>** sgraph_in) 
{
    sid_t src, dst2;
    T     src2, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    edgeT_t<T>*   edges = blog->blog_beg;
    
    index_t index = 0;
    for (index_t i = blog->blog_tail; i < blog->blog_marker; ++i) {
        index = (i & BLOG_MASK);
        src = edges[index].src_id;
        dst = edges[index].dst_id;
        
        src_index = TO_TID(src);
        vert1_id = TO_VID(src);
        skv_out[src_index]->set_value(vert1_id, dst);
        
        dst2 = get_sid(dst);
        set_sid(src2, src);
        set_weight(src2, dst);
        
        dst_index = TO_TID(dst2);
        vert2_id = TO_VID(dst2);
        sgraph_in[dst_index]->add_nebr(vert2_id, src2);
    }
}

template <class T>
void pgraph_t<T>::fill_adj_list_out(onegraph_t<T>** sgraph_out, onekv_t<T>** skv_in) 
{
    sid_t   src, dst2;
    T       src2, dst;
    vid_t   vert1_id, vert2_id;
    tid_t   src_index, dst_index; 
    edgeT_t<T>*   edges = blog->blog_beg;
    
    index_t index = 0;
    for (index_t i = blog->blog_tail; i < blog->blog_marker; ++i) {
        index = (i & BLOG_MASK);
        src = edges[index].src_id;
        dst = edges[index].dst_id;
        
        src_index = TO_TID(src);
        vert1_id = TO_VID(src);
        sgraph_out[src_index]->add_nebr(vert1_id, dst);
        
        dst2 = get_sid(dst);
        set_sid(src2, src);
        set_weight(src2, dst);
        
        dst_index = TO_TID(dst2);
        vert2_id = TO_VID(dst2);
        skv_in[dst_index]->set_value(vert2_id, src2); 
    }
}

template <class T>
void pgraph_t<T>::fill_skv(onekv_t<T>** skv_out, onekv_t<T>** skv_in)
{
    sid_t src, dst2;
    T     src2, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    edge_t*   edges = blog->blog_beg;
    
    index_t index = 0;
    for (index_t i = blog->blog_tail; i < blog->blog_marker; ++i) {
        index = (i & BLOG_MASK);
        src = edges[index].src_id;
        dst = edges[index].dst_id;
        
        src_index = TO_TID(src);
        vert1_id = TO_VID(src);
        skv_out[src_index]->set_value(vert1_id, dst); 
        
        dst2 = get_sid(dst);
        set_sid(src2, src);
        set_weight(src2, dst);
        
        dst_index = TO_TID(dst2);
        vert2_id = TO_VID(dst2);
        skv_in[dst_index]->set_value(vert2_id, src2); 
    }
}


/******************** super kv *************************/
template <class T>
void pgraph_t<T>::read_skv(onekv_t<T>** skv)
{
    if (skv == 0) return;

    tid_t       t_count = g->get_total_types();
    
    // For each file.
    for (tid_t i = 0; i < t_count; ++i) {
        if (skv[i] == 0) continue;
        skv[i]->read_kv();
    }
}

template <class T>
void pgraph_t<T>::file_open_skv(onekv_t<T>** skv, const string& dir, const string& postfix, bool trunc)
{
    if (skv == 0) return;

    char name[8];
    tid_t       t_count = g->get_total_types();
    
    //base name using relationship type
    string basefile = dir + col_info[0]->p_name;
    string vtfile;

    // For each file.
    for (tid_t i = 0; i < t_count; ++i) {
        if (skv[i] == 0) continue;
        sprintf(name, "%d", i);
        vtfile = basefile + name + postfix;
        skv[i] = new onekv_t<T>;
        skv[i]->setup(i);

        skv[i]->file_open(vtfile, trunc);
    }
}

template <class T>
void pgraph_t<T>::store_skv(onekv_t<T>** skv)
{
    if (skv == 0) return;

    tid_t       t_count = g->get_total_types();

    // For each file.
    for (tid_t i = 0; i < t_count; ++i) {
        if (skv[i] == 0) continue;

        skv[i]->persist_kvlog();
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

/************* Semantic graphs  *****************/
template <class T> 
void dgraph<T>::prep_graph_baseline()
{
    flag1_count = __builtin_popcountll(flag1);
    flag2_count = __builtin_popcountll(flag2);

    //super bins memory allocation
    tid_t   t_count = g->get_total_types();
    
    if (0 == sgraph_out) {
        sgraph_out  = (onegraph_t<T>**) calloc (sizeof(onegraph_t<T>*), t_count);
    }
    prep_sgraph(flag1, sgraph_out);    
    
    if (0 == sgraph_in) {
        sgraph_in  = (onegraph_t<T>**) calloc (sizeof(onegraph_t<T>*), t_count);
    }
    prep_sgraph(flag2, sgraph_in);
}

template <class T> 
void dgraph<T>::calc_degree()
{
    //estimate edge count
    calc_edge_count(sgraph_out, sgraph_in);
}

//We assume that no new vertex type is defined
template <class T> 
void dgraph<T>::make_graph_baseline()
{
    this->make_graph_d();
    
    /*
    if (blog->blog_tail >= blog->blog_marker) return;
    double start, end;
    start = mywtime(); 
    #pragma omp parallel num_threads(THD_COUNT)
    {
    calc_edge_count(sgraph_out, sgraph_in);
    }
    end = mywtime();
    cout << "degree time = " << end-start << endl;
    
    //prefix sum then reset the count
    start = mywtime(); 
    #pragma omp parallel num_threads(THD_COUNT)
    {
    prep_sgraph_internal(sgraph_out);
    prep_sgraph_internal(sgraph_in);
    }
    end = mywtime();
    cout << "prep time = " << end-start << endl;
    
    //populate and get the original count back
    start = mywtime(); 
    #pragma omp parallel num_threads(THD_COUNT)
    {
    fill_adj_list(sgraph_out, sgraph_in);
    }
    end = mywtime();
    cout << "fill  time = " << end-start << endl;
    
    //blog->blog_tail = blog->blog_marker;
    */
}

template <class T> 
void dgraph<T>::store_graph_baseline(bool clean)
{
    //#pragma omp parallel num_threads(THD_COUNT)
    {
    store_sgraph(sgraph_out, clean);
    store_sgraph(sgraph_in, clean);
    }
}

template <class T> 
void dgraph<T>::file_open(const string& odir, bool trunc)
{
    string postfix = "out";
    file_open_sgraph(sgraph_out, odir, postfix, trunc);
    postfix = "in";
    file_open_sgraph(sgraph_in, odir, postfix, trunc);
}

template <class T> 
void dgraph<T>::read_graph_baseline()
{
    tid_t   t_count    = g->get_total_types();
    
    if (0 == sgraph_out) {
        sgraph_out  = (onegraph_t<T>**) calloc (sizeof(onegraph_t<T>*), t_count);
    }
    read_sgraph(sgraph_out);
    
    if (0 == sgraph_in) {
        sgraph_in  = (onegraph_t<T>**) calloc (sizeof(onegraph_t<T>*), t_count);
    }
    read_sgraph(sgraph_in);
}

/*******************************************/
template <class T> 
void ugraph<T>::prep_graph_baseline()
{
    flag1 = flag1 | flag2;
    flag2 = flag1;

    flag1_count = __builtin_popcountll(flag1);
    flag2_count = flag1_count;

    //super bins memory allocation
    tid_t   t_count = g->get_total_types();
    
    if (0 == sgraph) {
        sgraph  = (onegraph_t<T>**) calloc (sizeof(onegraph_t<T>*), t_count);
    }
    prep_sgraph(flag1, sgraph); 
}

template <class T> 
void ugraph<T>::calc_degree()
{
    //estimate edge count
    calc_edge_count(sgraph, sgraph);
}

template <class T> 
void ugraph<T>::make_graph_baseline()
{
    this->make_graph_u();
    
    /*
    if (blog->blog_tail >= blog->blog_marker) return;
   
    double start, end;
    start = mywtime(); 
    
    #pragma omp parallel   num_threads(THD_COUNT)  
    {
        calc_edge_count(sgraph, sgraph);
        #pragma omp master 
        {
            end = mywtime();
            cout << " calc degree time = " << end - start << endl;
        }
        prep_sgraph_internal(sgraph);
        #pragma omp master 
        {
            end = mywtime();
            cout << " prep time = " << end - start << endl;
        }
        fill_adj_list(sgraph, sgraph);
        #pragma omp master 
        {
            end = mywtime();
            cout << " fill adj time = " << end - start << endl;
        }
    }
    end = mywtime();
    cout << "Make graph time = " << end - start << endl;
    //blog->blog_tail = blog->blog_marker;  
   */ 
}

template <class T> 
void ugraph<T>::store_graph_baseline(bool clean)
{
    double start, end;
    start = mywtime(); 
    store_sgraph(sgraph, clean);
    end = mywtime();
    cout << "store graph time = " << end - start << endl;
}

template <class T> 
void ugraph<T>::file_open(const string& odir, bool trunc)
{
    string postfix = "";
    file_open_sgraph(sgraph, odir, postfix, trunc);
}

template <class T> 
void ugraph<T>::read_graph_baseline()
{
    tid_t   t_count = g->get_total_types();
    
    if (0 == sgraph) {
        sgraph  = (onegraph_t<T>**) calloc (sizeof(onegraph_t<T>*), t_count);
    }
    read_sgraph(sgraph);
}

/***************************************/
template <class T> 
void many2one<T>::prep_graph_baseline()
{
    flag1_count = __builtin_popcountll(flag1);
    flag2_count = __builtin_popcountll(flag2);

    //super bins memory allocation
    tid_t   t_count = g->get_total_types();
    
    if (0 == sgraph_in) {
        sgraph_in  = (onegraph_t<T>**) calloc (sizeof(onegraph_t<T>*), t_count);
    }
    prep_sgraph(flag2, sgraph_in);
    
    if (0 == skv_out) {
        skv_out  = (onekv_t<T>**) calloc (sizeof(onekv_t<T>*), t_count);
    }

    skv_out  = prep_skv(flag1, skv_out);
}

template <class T> 
void many2one<T>::calc_degree()
{
    //estimate edge count
    calc_edge_count_in(sgraph_in);
}

template <class T> 
void many2one<T>::make_graph_baseline()
{
    if (blog->blog_tail >= blog->blog_marker) return;
    
    calc_edge_count_in(sgraph_in);
    
    //prefix sum then reset the count
    prep_sgraph_internal(sgraph_in);

    //populate and get the original count back
    //handle kv_out as well.
    fill_adj_list_in(skv_out, sgraph_in);
    //update_count(sgraph_in);
    blog->blog_tail = blog->blog_marker;  
}

template <class T> 
void many2one<T>::store_graph_baseline(bool clean)
{
    store_skv(skv_out);
    store_sgraph(sgraph_in);
}

template <class T> 
void many2one<T>::file_open(const string& odir, bool trunc)
{
    string postfix = "in";
    file_open_sgraph(sgraph_in, odir, postfix, trunc);
    postfix = "out";
    file_open_skv(skv_out, odir, postfix, trunc);
}

template <class T> 
void many2one<T>::read_graph_baseline()
{
    tid_t   t_count = g->get_total_types();
    
    if (0 == skv_out) {
        skv_out  = (onekv_t<T>**) calloc (sizeof(onekv_t<T>*), t_count);
    }
    read_skv(skv_out);
    
    if (0 == sgraph_in) {
        sgraph_in  = (onegraph_t<T>**) calloc (sizeof(onegraph_t<T>*), t_count);
    }
    read_sgraph(sgraph_in);
}

/*******************************************/
template <class T> 
void one2many<T>::prep_graph_baseline()
{
    flag1_count = __builtin_popcountll(flag1);
    flag2_count = __builtin_popcountll(flag2);

    //super bins memory allocation
    tid_t   t_count = g->get_total_types();
    
    if (0 == sgraph_out) {
        sgraph_out  = (onegraph_t<T>**) calloc (sizeof(onegraph_t<T>*), t_count);
    }
    prep_sgraph(flag1, sgraph_out);
    
    if (0 == skv_in) {
        skv_in  = (onekv_t<T>**) calloc (sizeof(onekv_t<T>*), t_count);
    }
    
    skv_in   = prep_skv(flag2, skv_in);
}
    
template <class T> 
void one2many<T>::calc_degree()
{
    //estimate edge count
    calc_edge_count_out(sgraph_out);
}
    
template <class T> 
void one2many<T>::make_graph_baseline()
{
    if (blog->blog_tail >= blog->blog_marker) return;
    
    calc_edge_count_out(sgraph_out);
    
    //prefix sum then reset the count
    prep_sgraph_internal(sgraph_out);

    //populate and get the original count back
    //handle kv_in as well.
    fill_adj_list_out(sgraph_out, skv_in);
    //update_count(sgraph_out);
    blog->blog_tail = blog->blog_marker;  
    
}

template <class T> 
void one2many<T>::store_graph_baseline(bool clean)
{
    store_sgraph(sgraph_out);
    store_skv(skv_in);
}

template <class T> 
void one2many<T>::file_open(const string& odir, bool trunc)
{
    string postfix = "out";
    file_open_sgraph(sgraph_out, odir, postfix, trunc);
    postfix = "in";
    file_open_skv(skv_in, odir, postfix, trunc);
}

template <class T> 
void one2many<T>::read_graph_baseline()
{
    tid_t   t_count = g->get_total_types();
    
    if (0 == sgraph_out) {
        sgraph_out  = (onegraph_t<T>**) calloc (sizeof(onegraph_t<T>*), t_count);
    }
    read_sgraph(sgraph_out);
    
    if (0 == skv_in) {
        skv_in  = (onekv_t<T>**) calloc (sizeof(onekv_t<T>*), t_count);
    }
    read_skv(skv_in);
}

/************************************************/
template <class T> 
void one2one<T>::prep_graph_baseline()
{
    flag1_count = __builtin_popcountll(flag1);
    flag2_count = __builtin_popcountll(flag2);
    tid_t   t_count    = g->get_total_types();

    //super bins memory allocation
    
    if (0 == skv_in) {
        skv_in  = (onekv_t<T>**) calloc (sizeof(onekv_t<T>*), t_count);
    }
    skv_in  = prep_skv(flag2, skv_in);
    
    if (0 == skv_out) {
        skv_out  = (onekv_t<T>**) calloc (sizeof(onekv_t<T>*), t_count);
    }
    skv_out = prep_skv(flag1, skv_out);
}

template <class T> 
void one2one<T>::calc_degree()
{
}

template <class T> 
void one2one<T>::make_graph_baseline()
{
    if (blog->blog_tail >= blog->blog_marker) return;

    //handle kv_out as well as kv_in.
    fill_skv(skv_out, skv_in);
    
}

template <class T> 
void one2one<T>::store_graph_baseline(bool clean)
{
    store_skv(skv_out);
    store_skv(skv_in);
}

template <class T> 
void one2one<T>::file_open(const string& odir, bool trunc)
{
    string postfix = "out";
    file_open_skv(skv_out, odir, postfix, trunc);
    postfix = "in";
    file_open_skv(skv_in, odir, postfix, trunc);
}

template <class T> 
void one2one<T>::read_graph_baseline()
{
    tid_t   t_count    = g->get_total_types();
    
    if (0 == skv_out) {
        skv_out  = (onekv_t<T>**) calloc (sizeof(onekv_t<T>*), t_count);
    }
    read_skv(skv_out);
    
    if (0 == skv_in) {
        skv_in  = (onekv_t<T>**) calloc (sizeof(onekv_t<T>*), t_count);
    }
    read_skv(skv_in);
}

template <class T> 
cfinfo_t* ugraph<T>::create_instance()
{
    return new ugraph_t;
}

template <class T> 
cfinfo_t* dgraph<T>::create_instance()
{
    return new dgraph_t;
}

template <class T> 
cfinfo_t* one2one<T>::create_instance()
{
    return new one2one_t;
}

template <class T> 
cfinfo_t* one2many<T>::create_instance()
{
    return new one2many_t;
}

template <class T> 
cfinfo_t* many2one<T>::create_instance()
{
    return new many2one_t;
}
//////
template <class T> 
void ugraph<T>::incr_count(sid_t src, sid_t dst, int del /*= 0*/)
{
    vid_t vert1_id = TO_VID(src);
    vid_t vert2_id = TO_VID(dst);
    
    tid_t src_index = TO_TID(src);
    tid_t dst_index = TO_TID(dst);
    
    if (!del) { 
        sgraph[src_index]->increment_count(vert1_id);
        sgraph[dst_index]->increment_count(vert2_id);
    } else { 
        sgraph[src_index]->decrement_count(vert1_id);
        sgraph[dst_index]->decrement_count(vert2_id);
    }
}

template <class T> 
void dgraph<T>::incr_count(sid_t src, sid_t dst, int del /*= 0*/)
{
    tid_t src_index = TO_TID(src);
    tid_t dst_index = TO_TID(dst);
    
    vid_t vert1_id = TO_VID(src);
    vid_t vert2_id = TO_VID(dst);
    
    if (!del) { 
        sgraph_out[src_index]->increment_count(vert1_id);
        sgraph_in[dst_index]->increment_count(vert2_id);
    } else { 
        sgraph_out[src_index]->decrement_count(vert1_id);
        sgraph_in[dst_index]->decrement_count(vert2_id);
    }
}

template <class T> 
void one2one<T>::incr_count(sid_t src, sid_t dst, int del /*= 0*/)
{
}

template <class T> 
void one2many<T>::incr_count(sid_t src, sid_t dst, int del /*= 0*/)
{
    tid_t dst_index = TO_TID(dst);
    
    vid_t vert2_id = TO_VID(dst);
    
    if (!del) { 
        sgraph_out[dst_index]->increment_count(vert2_id);
    } else { 
        skv_in[dst_index]->decrement_count(vert2_id);
    }
}

template <class T> 
void many2one<T>::incr_count(sid_t src, sid_t dst, int del /*= 0*/)
{
    tid_t src_index = TO_TID(src);
    
    vid_t vert1_id = TO_VID(src);
    
    if (!del) { 
        skv_out[src_index]->increment_count(vert1_id);
    } else { 
        sgraph_in[src_index]->decrement_count(vert1_id);
    }
}

template <class T> 
void ugraph<T>::add_nebr(sid_t src, sid_t dst, int del /*= 0*/)
{
    vid_t vert1_id = TO_VID(src);
    vid_t vert2_id = TO_VID(dst);
    
    tid_t src_index = TO_TID(src);
    tid_t dst_index = TO_TID(dst);
    
    if (!del) { 
        sgraph[src_index]->add_nebr(vert1_id, dst);
        sgraph[dst_index]->add_nebr(vert2_id, src);
    } else { 
        sgraph[src_index]->del_nebr(vert1_id, dst);
        sgraph[dst_index]->del_nebr(vert2_id, src);
    }
}

template <class T> 
void dgraph<T>::add_nebr(sid_t src, sid_t dst, int del /*= 0*/)
{
    tid_t src_index = TO_TID(src);
    tid_t dst_index = TO_TID(dst);
    
    vid_t vert1_id = TO_VID(src);
    vid_t vert2_id = TO_VID(dst);
    
    if (!del) { 
        sgraph_out[src_index]->add_nebr(vert1_id, dst);
        sgraph_in[dst_index]->add_nebr(vert2_id, src);
    } else { 
        sgraph_out[src_index]->del_nebr(vert1_id, dst);
        sgraph_in[dst_index]->del_nebr(vert2_id, src);
    }
}

template <class T> 
void one2one<T>::add_nebr(sid_t src, sid_t dst, int del /*= 0*/)
{
    tid_t src_index = TO_TID(src);
    tid_t dst_index = TO_TID(dst);
    
    vid_t vert1_id = TO_VID(src);
    vid_t vert2_id = TO_VID(dst);
    
    if (!del) { 
        skv_out[src_index]->set_value(vert1_id, dst);
        skv_in[dst_index]->set_value(vert2_id, src);
    } else { 
        skv_out[src_index]->set_value(vert1_id, dst);
        skv_in[dst_index]->set_value(vert2_id, src);
    }
}

template <class T> 
void many2one<T>::add_nebr(sid_t src, sid_t dst, int del /*= 0*/)
{
    tid_t src_index = TO_TID(src);
    tid_t dst_index = TO_TID(dst);
    
    vid_t vert1_id = TO_VID(src);
    vid_t vert2_id = TO_VID(dst);
    
    if (!del) { 
        sgraph_in[dst_index]->add_nebr(vert2_id, src);
        skv_out[src_index]->set_value(vert1_id, dst);
    } else { 
        sgraph_in[dst_index]->del_nebr(vert2_id, src);
        skv_out[src_index]->set_value(vert1_id, dst);
    }
}

template <class T> 
void one2many<T>::add_nebr(sid_t src, sid_t dst, int del /*= 0*/)
{
    tid_t src_index = TO_TID(src);
    tid_t dst_index = TO_TID(dst);
    
    vid_t vert1_id = TO_VID(src);
    vid_t vert2_id = TO_VID(dst);
    
    if (!del) { 
        sgraph_out[src_index]->add_nebr(vert1_id, dst);
        skv_in[dst_index]->set_value(vert2_id, src);
    } else { 
        sgraph_out[src_index]->del_nebr(vert1_id, dst);
        skv_in[dst_index]->set_value(vert2_id, src);
    }
}
/////
template <class T> 
void ugraph<T>::create_snapshot()
{
    update_count(sgraph);
}

template <class T> 
void dgraph<T>::create_snapshot()
{
    update_count(sgraph_out);
    update_count(sgraph_in);
}

template <class T> 
void one2one<T>::create_snapshot()
{
    return;
}

template <class T> 
void one2many<T>::create_snapshot()
{
    update_count(sgraph_out);
}

template <class T> 
void many2one<T>::create_snapshot()
{
    update_count(sgraph_in);
}

template <class T>
status_t ugraph<T>::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    return extend_adjlist_td(sgraph, iset, oset);
}

//due to many2one structure, we give preference to bottom up approach
template <class T>
status_t many2one<T>::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    if (direction == eout) {
        return extend_kv_td(skv_out,  iset, oset);
    } else {
        assert(direction == ein);
        return extend_adjlist_td(sgraph_in, iset, oset);
    }
    return eOK;
}

template <class T>
status_t dgraph<T>::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    if (direction == eout) {
        return extend_adjlist_td(sgraph_out, iset, oset);
    } else {
        assert(direction == ein);
        return extend_adjlist_td(sgraph_in, iset, oset);
    }
    return eOK;
}

template <class T>
status_t one2one<T>::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    if (direction == eout) {
        return extend_kv_td(skv_out, iset, oset);
    } else {
        assert(direction == ein);
        return extend_kv_td(skv_in, iset, oset);
    }
    return eOK;
}

template <class T>
status_t one2many<T>::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    if (direction == eout) {
        return extend_adjlist_td(sgraph_out, iset, oset);
    } else {
        assert(direction == ein);
        return extend_kv_td(skv_in, iset, oset);
    }
    return eOK;
}

////////
template <class T>
status_t ugraph<T>::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    //prepare the output 1,2;
    oset->full_setup(sgraph);
    int total_count = 0;
    
    if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
        return query_adjlist_td(sgraph, iset, oset);
    } else { //bottom up approach
        return query_adjlist_bu(sgraph, iset, oset);
    }
    return eOK;
}

//due to many2one structure, we give preference to bottom up approach
template <class T>
status_t many2one<T>::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    int total_count = 0;

    if (direction == eout) {
        oset->full_setup(sgraph_in);
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td(skv_out, iset, oset);
        } else { //bottom up approach
            return query_adjlist_bu(sgraph_in, iset, oset);
        }
    } else {
        assert(direction == ein);
        oset->full_setup(skv_out);
        total_count = 0;
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td(sgraph_in, iset, oset);
        } else { //bottom up approach 
            return query_kv_bu(skv_out, iset, oset);
        }
    }
    return eOK;
}

template <class T>
status_t dgraph<T>::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    int total_count = 0;
    if (direction == eout) {
        total_count = 0;
        oset->full_setup(sgraph_in);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td(sgraph_out, iset, oset);
        } else { //bottom up approach
            return query_adjlist_bu(sgraph_in, iset, oset);
        }
    } else {
        assert(direction == ein);
        total_count = 0;
        oset->full_setup(sgraph_out);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td(sgraph_in, iset, oset);
        } else { //bottom up approach 
            return query_adjlist_bu(sgraph_out, iset, oset);
        }
    }
    return eOK;
}

template <class T>
status_t one2one<T>::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    int total_count = 0;
    if (direction == eout) {
        total_count = 0;
        oset->full_setup(skv_in);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td(skv_out, iset, oset);
        } else { //bottom up approach
            return query_kv_bu(skv_in, iset, oset);
        }
    } else {
        assert(direction == ein);
        total_count = 0;
        oset->full_setup(skv_out);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td(skv_in, iset, oset);
        } else { //bottom up approach 
            return query_kv_bu(skv_out, iset, oset);
        }
    }
    return eOK;
}

template <class T>
status_t one2many<T>::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    int total_count = 0;
    if (direction == eout) {
        total_count = 0;
        oset->full_setup(skv_in);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_adjlist_td(sgraph_out, iset, oset);
        } else { //bottom up approach
            return query_kv_bu(skv_in, iset, oset);
        }
    } else {
        assert(direction == ein);
        total_count = 0;
        oset->full_setup(sgraph_out);
        if (iset->get_total_vcount() <= bu_factor*total_count) { //top down approach
            return query_kv_td(skv_in, iset, oset);
        } else { //bottom up approach 
            return query_adjlist_bu(sgraph_out, iset, oset);
        }
    }
    return eOK;
}

    /*
template <class T>
void onegraph_t<T>::update_count() 
{
    vid_t    v_count = TO_VID(super_id);
    disk_snapT_t<T>* slog = (disk_snapT_t<T>*)snap_log;
    T* adj_list1 = 0;
    T* adj_list2 = 0;
    T* prev_adjlist = 0;
	vunit_t<T>* v_unit = 0;
	vunit_t<T>* prev_v_unit = 0;
	delta_adjlist_t<T>* delta_adjlist = 0;
    index_t j = 0;
    snapT_t<T>* curr = 0;
    index_t count;
    snapid_t snap_id = g->get_snapid() + 1;
    
    #pragma omp for
    for (vid_t vid = 0; vid < v_count ; ++vid) {
        if (0 == nebr_count[vid].adj_list) continue;
		
		prev_v_unit = beg_pos[vid].get_vunit();
        prev_adjlist = prev_v_unit->adj_list;
        
        //durable adj list allocation
        curr		= beg_pos[vid].get_snapblob();
        adj_list1   = new_adjlist(curr->degree + 1);
        adj_list2   = adj_list1;
        
        //Copy the Old durable adj list
        set_nebrcount1(adj_list1, curr->degree);
        adj_list1 += 1;
        if (0 != prev_adjlist) {
            count = get_nebrcount1(prev_adjlist);
            memcpy(adj_list1, prev_adjlist, count*sizeof(T));
            adj_list1 += count;
        }

        //Copy the new in-memory adj-list
		delta_adjlist = prev_v_unit->delta_adjlist;
        while(delta_adjlist) {
			memcpy(adj_list1, delta_adjlist->get_adjlist(),
				   delta_adjlist->get_nebrcount()*sizeof(T));
			adj_list1 += delta_adjlist->get_nebrcount();
			delta_adjlist = delta_adjlist->get_next();
		}


		v_unit = new_vunit();
		v_unit->count = curr->degree;
		v_unit->adj_list = adj_list2;
		v_unit->delta_adjlist = 0;
		beg_pos[vid].set_vunit(v_unit);
            
		//snap log for disk write
		j = __sync_fetch_and_add(&snap_whead, 1L); 
		slog[j].vid       = vid;
		slog[j].snap_id   = snap_id;
		//slog[j].del_count = del_count;
		slog[j].degree    = curr->degree;
		if (curr) { slog[j].degree += curr->degree; }

		//v_unit log for disk write
        j = __sync_fetch_and_add(&dvt_count, 1L); 
        dvt[j].vid         = vid;
		dvt[j].count	   = curr->degree;
        dvt[j].file_offset = adj_list2 - log_beg;
        dvt[j].old_offset  =  prev_adjlist - log_beg;
        
		nebr_count[vid].add_count = 0;
        nebr_count[vid].del_count = 0;
        nebr_count[vid].adj_list = 0;
    }
    log_whead = log_head;
    adjlog_head = 0;
}
    */

/*
template <class T>
void onegraph_t<T>::persist_elog(const string& etfile)
{
    index_t wpos = log_whead;

    if (log_wtail == wpos) return;
    
    //Write the file.
    if (etf == 0) {
        etf = fopen(etfile.c_str(), "wb");//append/write + binary
        assert(etf != 0);
    }
    
    fwrite (log_beg + log_wtail, sizeof(T), wpos - log_wtail, etf);
    //Update the mark
    log_wtail = wpos;
}

template <class T>
void onegraph_t<T>::persist_vlog(const string& vtfile)
{
    if (dvt_count == 0) return;
   
    //Make a copy
    sid_t count =  dvt_count;


    //Write the file
    if(vtf == 0) {
        vtf = fopen(vtfile.c_str(), "wb");
        assert(vtf != 0);
    }
    fwrite(dvt, sizeof(disk_vtable_t), count, vtf);
    
    //update the mark
    dvt_count = 0;
}
	*/

/*
template <class T>
void onegraph_t<T>::prepare_vlog()
{
    vid_t v_count = get_vcount();
    snapid_t snap_id = g->get_snapid();
    snapT_t<T>* snap_blob;
    vid_t j = 0;
    
    #pragma omp for 
    for (sid_t i = 0; i < v_count; ++i) {
        snap_blob = beg_pos[i].get_snapblob();
        if (0 == snap_blob || snap_blob->snap_id <= snap_id) continue;
        
        j = __sync_fetch_and_add(&dvt_count, 1L); 
        dvt[j].vid       = i;
        dvt[j].file_offset   = beg_pos[i].get_adjlist() - log_beg;
    }
}
template <class T>
void onegraph_t<T>::prepare_slog()
{
    vid_t v_count = get_vcount();
    snapid_t snap_id = g->get_snapid();
    vid_t j = 0;
    disk_snapT_t<T>* dlog = (disk_snapT_t<T>*)snap_log;
    snapT_t<T>* snap_blob;
    #pragma omp for 
    for (sid_t i = 0; i < v_count; ++i) {
        snap_blob = beg_pos[i].get_snapblob();
        if (0 == snap_blob || snap_blob->snap_id <= snap_id) continue;
        
        j = __sync_fetch_and_add(&snap_whead, 1L); 
        dlog[j].vid       = i;
        dlog[j].snap_id   = snap_blob->snap_id;
        dlog[j].del_count = snap_blob->del_count;
        dlog[j].degree    = snap_blob->degree;
    }
}

template <class T>
void onegraph_t<T>::persist_slog(const string& stfile)
{   
    index_t wpos = snap_whead;
    if (snap_wtail == wpos) return;

    //prepare_slog();
    if(stf == 0) {
        stf = fopen(stfile.c_str(), "wb");
        assert(stf != 0);
    }
    
    fwrite(snap_log + snap_wtail, sizeof(disk_snapT_t<T>), wpos - snap_wtail, stf);
    snap_wtail = 0;
    snap_whead = 0;
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
    assert(snap_count >= size);
    index_t read_count = fread(snap_log, sizeof(disk_snapT_t<T>), size, stf);
    dlog = (disk_snapT_t<T>*)snap_log; 
    snap_blob = (snapT_t<T>*)dlog_beg;
    
    for (index_t i  = 0; i < read_count; ++i)  {
        snap_blob[i].del_count = dlog[i].del_count;
        snap_blob[i].snap_id = dlog[i].snap_id;
        snap_blob[i].degree = dlog[i].degree;

        beg_pos[dlog[i].vid].set_snapblob1(snap_blob + i);
    }
    dlog_head = read_count;
}
*/

/*
template <class T>
void onegraph_t<T>::read_etable(const string& etfile)
{
    if (etf == -1) {
		etf = open(etfile.c_str(), O_RDWR);
        //etf = fopen(etfile.c_str(), "r+b");//append/write + binary
        assert(etf != 0);
    }

    index_t size = fsize(etfile.c_str());
    if (size == -1L) {
        assert(0);
    }
    sid_t edge_count = size/sizeof(T);
    //fread(log_beg, sizeof(T), edge_count, etf);
    //read(etf, log_beg, size, 0);//offset as 0

    log_head = edge_count;
    log_wtail = log_head;
    log_whead = log_head;
}
*/
/*
template <class T>
void pgraph_t<T>::update_count(onegraph_t<T>** sgraph)
{
    tid_t       t_count = g->get_total_types();
    
    for(tid_t i = 0; i < t_count; i++) {
        if (0 == sgraph[i]) continue;
        sgraph[i]->update_count();
    }

}
*/
/////////// QUERIES ///////////////////////////
/*
status_t pgraph_t::query_adjlist_td(sgraph_t** sgraph, srset_t* iset, srset_t* oset)
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
        beg_pos_t* graph = sgraph[tid]->get_begpos();

        
        //Get the frontiers
        vid_t     frontier;
        for (vid_t v = 0; v < v_count; v++) {
            frontier = vlist[v];
            sid_t* adj_list = graph[frontier].get_adjlist();
            vid_t nebr_count = adj_list[0];
            ++adj_list;
            
            //traverse the adj list
            for (vid_t k = 0; k < nebr_count; ++k) {
                oset->set_status(adj_list[k]);
            }
        }
    }
    return eOK;
}
status_t pgraph_t::query_kv_td(skv_t** skv, srset_t* iset, srset_t* oset)
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
        sid_t* kv = skv[tid]->get_kv(); 

        //Get the frontiers
        vid_t     frontier;
        for (vid_t v = 0; v < v_count; v++) {
            frontier = vlist[v];
            oset->set_status(kv[frontier]);
        }
    }
    return eOK;
}

//sgraph_in and oset share the same flag.
status_t pgraph_t::query_adjlist_bu(sgraph_t** sgraph, srset_t* iset, srset_t* oset)
{
    rset_t* rset = 0;
    tid_t   tid  = 0;
    tid_t oset_count = oset->get_rset_count();

    for (tid_t i = 0; i < oset_count; ++i) {
        
        //get the graph where we will traverse
        rset = oset->rset + i;
        tid  = rset->get_tid();
        if (0 == sgraph[tid]) continue; 

        beg_pos_t* graph = sgraph[tid]->get_begpos(); 
        vid_t    v_count = sgraph[tid]->get_vcount();
        
        
        for (vid_t v = 0; v < v_count; v++) {
            //traverse the adj list
            sid_t* adj_list = graph[v].get_adjlist();
            vid_t nebr_count = adj_list[0];
            ++adj_list;
            for (vid_t k = 0; k < nebr_count; ++k) {
                if (iset->get_status(adj_list[k])) {
                    rset->set_status(v);
                    break;
                }
            }
        }
    }
    return eOK;
}

status_t pgraph_t::query_kv_bu(skv_t** skv, srset_t* iset, srset_t* oset) 
{
    rset_t*  rset = 0;
    tid_t    tid  = 0;
    tid_t    oset_count = oset->get_rset_count();
    for (tid_t i = 0; i < oset_count; ++i) {

        //get the graph where we will traverse
        rset = oset->rset + i;
        tid  = rset->get_tid(); 
        if (0 == skv[tid]) continue;

        vid_t*       kv = skv[tid]->get_kv(); 
        sid_t   v_count = skv[tid]->get_vcount();
        
        for (vid_t v = 0; v < v_count; ++v) {
            if (iset->get_status(kv[v])) {
                rset->set_status(v);
                break;
            }
        }
    }
    return eOK;
}

//////extend functions ------------------------
status_t 
pgraph_t::extend_adjlist_td(sgraph_t** sgraph, srset_t* iset, srset_t* oset)
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
        beg_pos_t* graph = sgraph[tid]->get_begpos(); 
        
        for (vid_t v = 0; v < v_count; v++) {
            rset2->add_adjlist_ro(v, graph+varray[v]);
        }
    }
    return eOK;
}

status_t 
pgraph_t::extend_kv_td(skv_t** skv, srset_t* iset, srset_t* oset)
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
        sid_t*  graph = skv[tid]->get_kv(); 
        
        for (vid_t v = 0; v < v_count; v++) {
            rset2->add_kv(v, graph[varray[v]]);
        }
    }
    return eOK;
}
*/
#include "sgraph2.h"
