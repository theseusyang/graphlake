#pragma once

#include <omp.h>
#include <sys/mman.h>
#include <asm/mman.h>
#include <unistd.h>
#include <fcntl.h>


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

        //edge batching buffer
        blog_t<T>*  blog;
        FILE*       wtf;   //edge log file

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
        
        q_count = 256;
        q_beg = (index_t*)calloc(q_count, sizeof(index_t));
        if (0 == q_beg) {
            perror("posix memalign batch edge log");
        }
        q_head = 0;
        q_tail = 0;
        wtf = 0;
    }


    status_t batch_update(const string& src, const string& dst, propid_t pid = 0) {
        return eOK;
    }
    status_t batch_edge(edgeT_t<T> edge) {
        index_t index = __sync_fetch_and_add(&blog->blog_head, 1L);
        index_t index1 = (index % blog->blog_count);
        index_t size = (index - blog->blog_marker) % BATCH_SIZE;
        if ((0 == size) && (index != 0)) {
            blog->blog_beg[index1] = edge;
            create_marker(index);
            //cout << "Will create a snapshot now " << endl;
            return eEndBatch;
        } else if ((index - blog->blog_tail) == blog->blog_count - 1000) {
            blog->blog_beg[index1] = edge;
            create_marker(index);
            cout << "About OOM" << endl;
            return eOOM;
        } else if ((index - blog->blog_tail) >= blog->blog_count) {
            //block
            assert(0);
            return eOOM;
        }

        blog->blog_beg[index1] = edge;

        //Make the edge log durable
        if(index - blog->blog_wmarker == W_SIZE) {
            create_wmarker(index);
        }
        return eOK; 
    }
    
    //Called from front end thread
    void create_wmarker(index_t marker) {
        pthread_mutex_lock(&g->w_mutex);
        if (marker > blog->blog_wmarker) {
            blog->blog_marker = marker;
        }
        pthread_cond_signal(&g->w_condition);
        pthread_mutex_unlock(&g->w_mutex);
        cout << "WMarker queued." << endl;
    }
    
    //called from w thread 
    status_t write_edgelog() {
        index_t w_marker = 0;
        index_t w_tail = 0;
        index_t w_count = 0;
        pthread_mutex_lock(&g->w_mutex);
        w_marker = blog->blog_wmarker;
        pthread_mutex_unlock(&g->w_mutex);
        w_tail = blog->blog_wtail;
        w_count = w_marker - w_tail;
        if (w_count) {
            //write and update tail
            fwrite(blog->blog_beg + w_tail, sizeof(edgeT_t<T>), w_count, wtf);
            blog->blog_wtail = w_marker;
            return eOK;
        }
        return eNoWork;
    }
    
    void create_marker(index_t marker) {
        pthread_mutex_lock(&g->snap_mutex);
        index_t m_index = __sync_fetch_and_add(&q_head, 1L);
        q_beg[m_index % q_count] = marker;
        pthread_cond_signal(&g->snap_condition);
        pthread_mutex_unlock(&g->snap_mutex);
        cout << "Marker queued. position = " << m_index % q_count << " " << marker << endl;
    } 
    
    //called from snap thread 
    status_t move_marker(index_t& snap_marker) {
        pthread_mutex_lock(&g->snap_mutex);
        index_t head = q_head;
        //Need to read marker and set the blog_marker;
        if (q_tail == head) {
            pthread_mutex_unlock(&g->snap_mutex);
            cout << "Marker NO dequeue. Position = " << head <<  endl;
            return eNoWork;
        }
        
        /*
        index_t m_index = head - 1;
        index_t marker = q_beg[m_index % q_count];
        q_tail = head;
        blog_marker = marker;
        snap_marker = blog_marker;
        */
        
        index_t m_index = __sync_fetch_and_add(&q_tail, 1L);
        index_t marker = q_beg[m_index % q_count];
        blog->blog_marker = marker;
        snap_marker = blog->blog_marker;
        pthread_mutex_unlock(&g->snap_mutex);
        //cout << "working on snapshot" << endl;
        cout << "Marker dequeue. Position = " << m_index % q_count << " " << marker << endl;
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
    
    void store_sgraph(onegraph_t<T>** sgraph);
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
    void store_graph_baseline();
    void read_graph_baseline();
    void file_open(const string& odir,  bool trunc);
    
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
    void store_graph_baseline();
    void read_graph_baseline();
    void file_open(const string& odir,  bool trunc);
    
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
    void store_graph_baseline();
    void read_graph_baseline();
    void file_open(const string& odir,  bool trunc);
    
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
    void store_graph_baseline();
    void read_graph_baseline();
    void file_open(const string& odir,  bool trunc);
    
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
    void store_graph_baseline();
    void read_graph_baseline();
    void file_open(const string& odir,  bool trunc);
    
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
        max_vcount = v_count;// (v_count << 1);
        beg_pos = (vert_table_t<T>*)calloc(sizeof(vert_table_t<T>), max_vcount);
        nebr_count = (nebrcount_t<T>*)calloc(sizeof(nebrcount_t<T>), max_vcount);
        
        //dela adj list
        adjlog_count = (1L << 34);//256*8 MB
        adjlog_beg = (T*)mmap(NULL, sizeof(T)*adjlog_count, PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0 );
        if (MAP_FAILED == adjlog_beg) {
            cout << "Huge page allocation failed for delta adj list" << endl;
            if (posix_memalign((void**)&adjlog_beg, 2097152, adjlog_count*sizeof(T))) {
                perror("posix memalign edge log");
            }
        }
        
        //degree aray realted log, in-memory
        dlog_count = (v_count << 1L);//256 MB
        /*
         * dlog_beg = (snapT_t<T>*)mmap(NULL, sizeof(snapT_t<T>)*dlog_count, PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0 );
        
        if (MAP_FAILED == dlog_beg) {
            cout << "Huge page allocation failed for degree array" << endl;
        }
            */
            if (posix_memalign((void**)&dlog_beg, 2097152, dlog_count*sizeof(snapT_t<T>))) {
                //log_beg = (index_t*)calloc(sizeof(index_t), log_count);
                perror("posix memalign snap log");
            }
        
        //degree array relatd log, for writing to disk
        snap_count = (1L << 16);//256 MB
        if (posix_memalign((void**)&snap_log, 2097152, snap_count*sizeof(disk_snapT_t<T>))) {
            perror("posix memalign snap disk log");
        }
        
        //durable vertex log and adj list log
        dvt_max_count = (v_count);
        log_count = (1L << 22);
        if (posix_memalign((void**) &write_seg[0].dvt, 2097152, 
                           dvt_max_count*sizeof(disk_vtable_t))) {
            perror("posix memalign vertex log");    
        }
        if (posix_memalign((void**) &write_seg[1].dvt, 2097152, 
                           dvt_max_count*sizeof(disk_vtable_t))) {
            perror("posix memalign vertex log");    
        }
        if (posix_memalign((void**)&write_seg[0].log_beg, 2097152, log_count*sizeof(T))) {
            //log_beg = (index_t*)calloc(sizeof(index_t), log_count);
            perror("posix memalign edge log");
        }
        if (posix_memalign((void**)&write_seg[1].log_beg, 2097152, log_count*sizeof(T))) {
            //log_beg = (index_t*)calloc(sizeof(index_t), log_count);
            perror("posix memalign edge log");
        }
        /*
        if (posix_memalign((void**)&log_beg, 2097152, log_count*sizeof(T))) {
            //log_beg = (index_t*)calloc(sizeof(index_t), log_count);
            perror("posix memalign edge log");
        }*/

		//v_unit log
		vunit_count = (v_count << 1L);
        if (posix_memalign((void**)&vunit_beg, 2097152, vunit_count*sizeof(vunit_t<T>))) {
            perror("posix memalign vunit_beg");
        }
		if (posix_memalign((void**)&vunit_ind, 2097152, vunit_count*sizeof(vid_t))) {
            perror("posix memalign vunit_ind");
        }
		
		for (vid_t i = 0; i < vunit_count; ++i) {
			vunit_ind[i] = i; 
		}

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
    snapid_t snap_id = g->get_snapid() + 1;
    
    snapT_t<T>* curr;
	vunit_t<T>* v_unit = 0;
	delta_adjlist_t<T>* delta_adjlist = 0;
	delta_adjlist_t<T>* prev_delta = 0;
    degree_t count, del_count;
    
    #pragma omp for
    for (vid_t vid = 0; vid < v_count; ++vid) {
        del_count = nebr_count[vid].del_count;
        count = nebr_count[vid].add_count;
        
        if (0 != count) {// new nebrs added/deleted
			if (beg_pos[vid].get_vunit()) {
				v_unit = beg_pos[vid].get_vunit();
            } else {
				v_unit = new_vunit();
				beg_pos[vid].set_vunit(v_unit);
			}

            curr = beg_pos[vid].get_snapblob();
            prev_delta = nebr_count[vid].adj_list;
            if (prev_delta) {
                count = nebr_count[vid].add_count - prev_delta->get_nebrcount();
			}	
        
            if (0 == count) {
                continue;
            }
            //delta adj list allocation
			//extra space is for ptr, and count
			delta_adjlist = new_delta_adjlist(count + 4);
            delta_adjlist->set_nebrcount(count);
            delta_adjlist->add_next(0);
			
			//If prev_delta exist, v_unit exists
            if(prev_delta) {
                prev_delta->add_next(delta_adjlist);
            } else {
			    v_unit->delta_adjlist = delta_adjlist;
            }

			nebr_count[vid].adj_list = delta_adjlist;
        
            //allocate new snapshot for degree, and initialize
			snapT_t<T>* next    = new_snapdegree(); 
            next->del_count     = del_count;
            next->snap_id       = snap_id;
            next->next          = 0;
            next->degree        = count;
            if (curr)  next->degree += curr->degree; 
            beg_pos[vid].set_snapblob1(next);
        }
        reset_count(vid);
    }
}

template <class T>
void onegraph_t<T>::file_open(const string& filename, bool trunc)
{
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

template <class T>
void onegraph_t<T>::handle_write()
{
    vid_t   v_count = TO_VID(super_id);
    vid_t last_vid1 = 0;
    vid_t last_vid2 = 0;
    write_seg_t<T>* seg1 = write_seg + 0;
    write_seg_t<T>* seg2 = write_seg + 1; 
    index_t       offset = log_tail;
    
    prepare_dvt(seg1, last_vid1, offset);
    
    do {
        last_vid2 = last_vid1;
        swap(seg1, seg2);
        #pragma omp parallel
        {
            #pragma omp master
            {
                prepare_dvt(seg1, last_vid1, offset);
            }
            if (1 == omp_get_thread_num())
            {
                //Write the dvt log
                if (seg2->dvt_count) {
                    //fwrite(seg2->dvt, sizeof(disk_vtable_t), seg2->dvt_count, vtf);
                    write(vtf, seg2->dvt, sizeof(disk_vtable_t)*seg2->dvt_count);
                }
            }

            adj_write(seg2);
        }
        if (seg2->log_head != 0) { 
            log_tail += seg2->log_head;
        }
        seg2->log_head = 0;
        seg2->dvt_count = 0;
        
    } while(last_vid2 < v_count);
    adjlog_head = 0;
}

template <class T>
void onegraph_t<T>::prepare_dvt(write_seg_t<T>* seg, vid_t& last_vid, index_t& offset)
{
    vid_t    v_count = TO_VID(super_id);
    T* adj_list2 = 0;
    snapT_t<T>* curr = 0;
	disk_vtable_t* dvt1 = 0;
	
    for (vid_t vid = last_vid; vid < v_count ; ++vid) {
        if (0 == nebr_count[vid].adj_list) continue;
		
        curr		= beg_pos[vid].get_snapblob();
		if ((seg->log_head + curr->degree + 1 > log_count) ||
            (seg->dvt_count >= dvt_max_count)) {
            last_vid = vid;
            offset += seg->log_head;
            return;
		}
        
        //durable adj list allocation
		adj_list2   = new_adjlist(seg, curr->degree + 1);
        
		//v_unit log for disk write
        dvt1              = new_dvt(seg);
		dvt1->vid         = vid;
		dvt1->count	     = curr->degree;
        dvt1->file_offset = adj_list2 - seg->log_beg;
        dvt1->file_offset += offset;
    }

    last_vid = v_count;
    offset += seg->log_head;
    return;
}

template <class T>
void onegraph_t<T>::adj_write(write_seg_t<T>* seg)
{
	vid_t vid;
	disk_vtable_t* dvt1 = 0;
	vunit_t<T>* v_unit = 0;
	vunit_t<T>* prev_v_unit = 0;
	degree_t prev_count;
	index_t  prev_offset;
	delta_adjlist_t<T>* delta_adjlist = 0;
    T* adj_list1 = 0;
    T* adj_list2 = 0;

    #pragma omp for  
	for (vid_t v = 0; v < seg->dvt_count; ++v) {
		dvt1 = seg->dvt + v;
		vid = dvt1->vid;
		if (0 == nebr_count[vid].adj_list) continue;
		prev_v_unit  = beg_pos[vid].get_vunit();
		prev_count   = prev_v_unit->count;
		prev_offset  = prev_v_unit->offset;
		
		//durable adj list allocated
		adj_list1   = seg->log_beg + dvt1->file_offset - log_tail;//XXX
		adj_list2   = adj_list1;
	   
        //Copy the Old durable adj list
		if (prev_count) {
			//Read the old adj list from disk
			pread(etf, adj_list1 , (prev_count+1)*sizeof(T), prev_offset*sizeof(T));
            set_nebrcount1(adj_list1, dvt1->count);
			adj_list1 += prev_count + 1;
		} else {
            set_nebrcount1(adj_list1, dvt1->count);
		    ++adj_list1;
        }
	    assert(vid == dvt1->vid);	

        //Copy the new in-memory adj-list
		delta_adjlist = prev_v_unit->delta_adjlist;
        while(delta_adjlist) {
			memcpy(adj_list1, delta_adjlist->get_adjlist(),
				   delta_adjlist->get_nebrcount()*sizeof(T));
			adj_list1 += delta_adjlist->get_nebrcount();
			delta_adjlist = delta_adjlist->get_next();
		}

		//Write new adj list
		pwrite(etf, adj_list2, (dvt1->count + 1)*sizeof(T), 
               (dvt1->file_offset)*sizeof(T));

		v_unit = new_vunit();
		v_unit->count = dvt1->count;
		v_unit->offset = dvt1->file_offset;// + log_tail;
		v_unit->delta_adjlist = 0;
		beg_pos[vid].set_vunit(v_unit);
            
		nebr_count[vid].add_count = 0;
        nebr_count[vid].del_count = 0;
        nebr_count[vid].adj_list = 0;
    }
		
	//Write new adj list
    //fwrite (log_beg, sizeof(T), log_head, etf);
    /*
    if (seg->log_head != 0) {
	    index_t size = pwrite(etf, seg->log_beg, seg->log_head*sizeof(T), 
                              log_tail*sizeof(T));
        if (size != seg->log_head*sizeof(T)) {
            perror("pwrite issue");
            assert(0);
        }
    }*/
    
	//Write the dvt log
	//fwrite(seg->dvt, sizeof(disk_vtable_t), seg->dvt_count, vtf);
}

template <class T>
void onegraph_t<T>::update_count() 
{
    /*
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
    */
}

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
				v_unit->count = dvt[v].count;
			} else {
				v_unit = new_vunit();
				v_unit->offset = dvt[v].file_offset;
				v_unit->count = dvt[v].count;
				beg_pos[vid].set_vunit(v_unit);
			}
            //allocate new snapshot for degree, and initialize
			next                = new_snapdegree(); 
            next->del_count     = 0;
            next->snap_id       = snap_id;
            next->next          = 0;
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
        index = (i % blog->blog_count);
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
        index = (i % blog->blog_count);
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
        index = (i % blog->blog_count);
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
    
    edge_t*   edges = blog->blog_beg;

    index_t index = 0;
    #pragma omp for
    for (index_t i = blog->blog_tail; i < blog->blog_marker; ++i) {
        index = (i % blog->blog_count);
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
    blog->blog_tail = blog->blog_marker;  
}

template <class T>
void pgraph_t<T>::fill_adj_list_in(onekv_t<T>** skv_out, onegraph_t<T>** sgraph_in) 
{
    sid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    edge_t*   edges = blog->blog_beg;
    
    index_t index = 0;
    for (index_t i = blog->blog_tail; i < blog->blog_marker; ++i) {
        index = (i % blog->blog_count);
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
    blog->blog_tail = blog->blog_marker;  
}

template <class T>
void pgraph_t<T>::fill_adj_list_out(onegraph_t<T>** sgraph_out, onekv_t<T>** skv_in) 
{
    sid_t   src, dst;
    vid_t   vert1_id, vert2_id;
    tid_t   src_index, dst_index; 
    edge_t*   edges = blog->blog_beg;
    
    index_t index = 0;
    for (index_t i = blog->blog_tail; i < blog->blog_marker; ++i) {
        index = (i % blog->blog_count);
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
    blog->blog_tail = blog->blog_marker;  
}

template <class T>
void pgraph_t<T>::fill_skv(onekv_t<T>** skv_out, onekv_t<T>** skv_in)
{
    sid_t src, dst;
    vid_t     vert1_id, vert2_id;
    tid_t     src_index, dst_index;
    edge_t*   edges = blog->blog_beg;
    
    index_t index = 0;
    for (index_t i = blog->blog_tail; i < blog->blog_marker; ++i) {
        index = (i % blog->blog_count);
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
    blog->blog_tail = blog->blog_marker;  
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

}

template <class T>
void pgraph_t<T>::store_sgraph(onegraph_t<T>** sgraph)
{
    if (sgraph == 0) return;
    
    tid_t    t_count = g->get_total_types();
    
    // For each file.
    for (tid_t i = 0; i < t_count; ++i) {
        if (sgraph[i] == 0) continue;
		sgraph[i]->handle_write();
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
    string  vtfile, filename; 
    FILE*   vtf = 0;

    // For each file.
    tid_t    t_count = g->get_total_types();
    for (tid_t i = 0; i < t_count; ++i) {

        //name = typekv->get_type_name(i);
        sprintf(name, "%d", i);
        filename = basefile + name + postfix ; 
        if (trunc) {
            if (sgraph[i]) {
                sgraph[i]->file_open(filename, trunc);
                continue;
            }
        } 

        vtfile = filename + ".vtable";
        vtf = fopen(vtfile.c_str(), "rb");
        if(vtf == 0) continue;
        fclose(vtf);

        sgraph[i] = new onegraph_t<T>;
        sgraph[i]->setup(i);
        
        sgraph[i]->file_open(filename, trunc);
        sgraph[i]->read_vtable();
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
        //sgraph[i] = new onegraph_t<T>;
        //sgraph[i]->setup(i);
        sgraph[i]->read_vtable();
        //sgraph[i]->read_stable(stfile);
        //sgraph[i]->read_etable(etfile);
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
        
        skv[i] = new onekv_t<T>;
        skv[i]->setup(i);
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
