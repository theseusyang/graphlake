#pragma once

#include "sgraph.h"

#ifndef BULK
template <class T>
void onegraph_t<T>::increment_count_noatomic(vid_t vid) {
	snapid_t snap_id = g->get_snapid() + 1;
	snapT_t<T>* curr = beg_pos[vid].get_snapblob();
	if (curr == 0 || curr->snap_id < snap_id) {
		//allocate new snap blob 
		snapT_t<T>* next = beg_pos[vid].recycle_snapblob(snap_id);
		if (next == 0) {
			next = new_snapdegree_local();
            next->snap_id       = snap_id;
            next->degree        = 0;
            next->del_count     = 0;
            if (curr) {
                next->degree += curr->degree;
                next->del_count += curr->del_count;
            }
            beg_pos[vid].set_snapblob1(next);
        }
		curr = next;
	
		//allocate v-unit
		if (beg_pos[vid].get_vunit() == 0) {
			vunit_t<T>* v_unit = new_vunit_local();
			beg_pos[vid].set_vunit(v_unit);
		}
	}
	curr->degree++;
}
template <class T>
void onegraph_t<T>::decrement_count_noatomic(vid_t vid) {
	snapid_t snap_id = g->get_snapid() + 1;
	snapT_t<T>* curr = beg_pos[vid].get_snapblob();
	if (curr == 0 || curr->snap_id < snap_id) {
		//allocate new snap blob 
		snapT_t<T>* next = beg_pos[vid].recycle_snapblob(snap_id);
		if (next == 0) {
			next = new_snapdegree_local();
            next->snap_id       = snap_id;
            next->degree        = 0;
            next->del_count     = 0;
            if (curr) {
                next->degree += curr->degree;
                next->del_count += curr->del_count;
            }
            beg_pos[vid].set_snapblob1(next);
        }
		curr = next;
	
		//allocate v-unit
		if (beg_pos[vid].get_vunit() == 0) {
			vunit_t<T>* v_unit = new_vunit_local();
			beg_pos[vid].set_vunit(v_unit);
		}
	}
	curr->del_count++;
}
#endif

template <class T>
void pgraph_t<T>::estimate_classify(vid_t* vid_range, vid_t* vid_range_in, vid_t bit_shift) 
{
    sid_t src, dst;
    vid_t vert1_id, vert2_id;
    vid_t range;
    edgeT_t<T>* edges = blog->blog_beg;
    index_t index;

    #pragma omp for
    for (index_t i = blog->blog_tail; i < blog->blog_marker; ++i) {
        index = (i & BLOG_MASK);
        src = edges[index].src_id;
        dst = get_sid(edges[index].dst_id);
        
        vert1_id = TO_VID(src);
        vert2_id = TO_VID(dst);

        //gather high level info for 1
        range = (vert1_id >> bit_shift);
        vid_range[range]++;
        
        //gather high level info for 2
        range = (vert2_id >> bit_shift);
        vid_range_in[range]++;
    }
}


template <class T>
void pgraph_t<T>::prefix_sum(global_range_t<T>* global_range, thd_local_t* thd_local,
                             vid_t range_count, vid_t thd_count, edgeT_t<T>* edge_buf)
{
    index_t total = 0;
    index_t value = 0;
    //index_t alloc_start = 0;

    //#pragma omp master
    #pragma omp for schedule(static) nowait
    for (vid_t i = 0; i < range_count; ++i) {
        total = 0;
        //global_range[i].edges = edge_buf + alloc_start;//good for larger archiving batch
        for (vid_t j = 0; j < thd_count; ++j) {
            value = thd_local[j].vid_range[i];
            thd_local[j].vid_range[i] = total;
            total += value;
        }

        //alloc_start += total;
        global_range[i].count = total;
        if (total != 0)
            global_range[i].edges = (edgeT_t<T>*)malloc(sizeof(edgeT_t<T>)*total);
    }
}

template <class T>
void pgraph_t<T>::work_division(global_range_t<T>* global_range, thd_local_t* thd_local,
                        vid_t range_count, vid_t thd_count, index_t equal_work)
{
    index_t my_portion = global_range[0].count;
    index_t value;
    vid_t j = 0;
    
    for (vid_t i = 1; i < range_count && j < thd_count; ++i) {
        value = global_range[i].count;
        if (my_portion + value > equal_work && my_portion != 0) {
            //cout << j << " " << my_portion << endl;
            thd_local[j++].range_end = i;
            my_portion = 0;
        }
        my_portion += value;
    }

    if (j == thd_count)
        thd_local[j -1].range_end = range_count;
    else 
        thd_local[j++].range_end = range_count;
    
    /*
    my_portion = 0;
    vid_t i1 = thd_local[j - 2].range_end;
    for (vid_t i = i1; i < range_count; i++) {
        my_portion += global_range[i1].count;
    }
    cout << j - 1 << " " << my_portion << endl;
    */
}


template <class T>
void pgraph_t<T>::classify(vid_t* vid_range, vid_t* vid_range_in, vid_t bit_shift, 
            global_range_t<T>* global_range, global_range_t<T>* global_range_in)
{
    sid_t src, dst;
    vid_t vert1_id, vert2_id;
    vid_t range = 0;
    edgeT_t<T>* edge;
    edgeT_t<T>* edges = blog->blog_beg;
    index_t index;

    #pragma omp for
    for (index_t i = blog->blog_tail; i < blog->blog_marker; ++i) {
        index = (i & BLOG_MASK);
        src = edges[index].src_id;
        dst = get_sid(edges[index].dst_id);
        
        vert1_id = TO_VID(src);
        vert2_id = TO_VID(dst);
        
        range = (vert1_id >> bit_shift);
        edge = global_range[range].edges + vid_range[range]++;
        edge->src_id = src;
        edge->dst_id = edges[index].dst_id;
        
        range = (vert2_id >> bit_shift);
        edge = global_range_in[range].edges + vid_range_in[range]++;
        edge->src_id = dst;
        set_dst(edge, src);
        set_weight(edge, edges[index].dst_id);
    }
}

template <class T>
void pgraph_t<T>::calc_degree_noatomic(onegraph_t<T>** sgraph, global_range_t<T>* global_range, vid_t j_start, vid_t j_end) 
{
    index_t total = 0;
    edgeT_t<T>* edges = 0;
    tid_t src_index;
    sid_t src;
    vid_t vert1_id;

    for (vid_t j = j_start; j < j_end; ++j) {
        total = global_range[j].count;
        edges = global_range[j].edges;
        
        for (index_t i = 0; i < total; ++ i) {
            src = edges[i].src_id;
            src_index = TO_TID(src);
            vert1_id = TO_VID(src);

            if (!IS_DEL(src)) { 
                sgraph[src_index]->increment_count_noatomic(vert1_id);
            } else { 
                sgraph[src_index]->decrement_count_noatomic(vert1_id);
            }
        }
    }
}

template <class T>
void pgraph_t<T>::fill_adjlist_noatomic(onegraph_t<T>** sgraph, global_range_t<T>* global_range, vid_t j_start, vid_t j_end) 
{
    index_t total = 0;
    edgeT_t<T>* edges = 0;
    tid_t src_index;
    sid_t src;
    T dst;
    vid_t vert1_id;

    for (vid_t j = j_start; j < j_end; ++j) {
        total = global_range[j].count;
        edges = global_range[j].edges;
        
        for (index_t i = 0; i < total; ++ i) {
            src = edges[i].src_id;
            dst = edges[i].dst_id;
            src_index = TO_TID(src);
            vert1_id = TO_VID(src);

            sgraph[src_index]->add_nebr_noatomic(vert1_id, dst);
        }
    }
}


template <class T>
void onegraph_t<T>::setup_adjlist_noatomic(vid_t vid_start, vid_t vid_end)
{
    degree_t count, del_count, total_count;
	vunit_t<T>* v_unit = 0;
    snapT_t<T>* curr;
	snapT_t<T>* next;
    snapid_t snap_id = g->get_snapid() + 1;
	int tid = omp_get_thread_num();
	thd_mem_t<T>* my_thd_mem = thd_mem + tid;
	memset(my_thd_mem, 0, sizeof(thd_mem_t<T>));

	//Memory estimation
    for (vid_t vid = vid_start; vid < vid_end; ++vid) {
        del_count = nebr_count[vid].del_count;
        count = nebr_count[vid].add_count;
        total_count = count + del_count;
        
        if (0 == total_count) { continue; }
        
        next = beg_pos[vid].recycle_snapblob(snap_id);
        if (next != 0) {
            next->del_count += del_count;
            next->degree    += count;
        }
        my_thd_mem->degree_count += (0 == next);
        ++my_thd_mem->dsnap_count;
    
        v_unit = beg_pos[vid].get_vunit();
        my_thd_mem->vunit_count += (v_unit == 0);
        my_thd_mem->delta_size += total_count;
    }

	//Bulk memory allocation
    my_thd_mem->vunit_beg = new_vunit_bulk(my_thd_mem->vunit_count);
    my_thd_mem->dlog_beg = new_snapdegree_bulk(my_thd_mem->degree_count);
    assert(dlog_head <= dlog_count);

	index_t new_count = my_thd_mem->delta_size*sizeof(T) 
						+ my_thd_mem->dsnap_count*sizeof(delta_adjlist_t<T>);
    my_thd_mem->adjlog_beg = new_delta_adjlist_bulk(new_count);
    assert(adjlog_head <= adjlog_count);

	delta_adjlist_t<T>* prev_delta = 0;
	delta_adjlist_t<T>* delta_adjlist = 0;
    index_t delta_size = 0;
    index_t delta_metasize = sizeof(delta_adjlist_t<T>);

	//individual allocation
    for (vid_t vid = vid_start; vid < vid_end; ++vid) {
        del_count = nebr_count[vid].del_count;
        count = nebr_count[vid].add_count;
        total_count = count + del_count;
        
        if (0 == total_count) { continue; }

        //delta adj list allocation
        delta_adjlist = (delta_adjlist_t<T>*)(my_thd_mem->adjlog_beg); 
        delta_size = total_count*sizeof(T) + delta_metasize;
        my_thd_mem->adjlog_beg += delta_size;
        
        if (my_thd_mem->adjlog_beg > adjlog_beg + adjlog_count) { //rewind happened
            my_thd_mem->adjlog_beg -=  adjlog_count;
            
            //Last allocation is wasted due to rewind
            delta_adjlist = (delta_adjlist_t<T>*)new_delta_adjlist_bulk(delta_size);
        }
        
        delta_adjlist->set_nebrcount(0);
        delta_adjlist->add_next(0);
        
        curr = beg_pos[vid].get_snapblob();
        if (0 == curr || curr->snap_id < snap_id) {
			next                = my_thd_mem->dlog_beg; 
            my_thd_mem->dlog_beg        += 1;
            next->del_count     = del_count;
            next->snap_id       = snap_id;
            next->degree        = count;
            if (curr) {
                next->degree += curr->degree;
                next->del_count += curr->del_count;
            }
            beg_pos[vid].set_snapblob1(next);
        }
        
        v_unit = beg_pos[vid].get_vunit();
        if (v_unit) {
            prev_delta = v_unit->adj_list;
            if (prev_delta) {
                prev_delta->add_next(delta_adjlist);
            } else {
                v_unit->delta_adjlist = delta_adjlist;
            }
        } else {
            v_unit = my_thd_mem->vunit_beg;
            my_thd_mem->vunit_beg += 1;
            v_unit->delta_adjlist = delta_adjlist;
            beg_pos[vid].set_vunit(v_unit);
        }

        v_unit->adj_list = delta_adjlist;
        reset_count(vid);
    }
}


inline void print(const char* str, double start_time) 
{
	//#pragma omp master
	//{
	//	double end = mywtime();
	//	cout << str << end - start_time << endl;
	//}
}

template <class T>
void pgraph_t<T>::make_graph_d() 
{
    if (blog->blog_tail >= blog->blog_marker) return;
    
    vid_t v_count = sgraph_out[0]->get_vcount();
    vid_t range_count = 1024;
    vid_t thd_count = THD_COUNT;
    vid_t  base_vid = ((v_count -1)/range_count);
    
    //find the number of bits to do shift to find the range
#if B32    
    vid_t bit_shift = __builtin_clz(base_vid);
    bit_shift = 32 - bit_shift; 
#else
    vid_t bit_shift = __builtin_clzl(base_vid);
    bit_shift = 64 - bit_shift; 
#endif

    global_range_t<T>* global_range = (global_range_t<T>*)calloc(
                            sizeof(global_range_t<T>), range_count);
    
    global_range_t<T>* global_range_in = (global_range_t<T>*)calloc(
                            sizeof(global_range_t<T>), range_count);
    
    thd_local_t* thd_local = (thd_local_t*) calloc(sizeof(thd_local_t), thd_count);  
    thd_local_t* thd_local_in = (thd_local_t*) calloc(sizeof(thd_local_t), thd_count);  
   
    index_t total_edge_count = blog->blog_marker - blog->blog_tail;
    //alloc_edge_buf(total_edge_count);
    
    index_t edge_count = (total_edge_count*1.15)/(thd_count);
    

    #pragma omp parallel num_threads (thd_count) 
    {
        vid_t tid = omp_get_thread_num();
        vid_t* vid_range = (vid_t*)calloc(sizeof(vid_t), range_count); 
        vid_t* vid_range_in = (vid_t*)calloc(sizeof(vid_t), range_count); 
        thd_local[tid].vid_range = vid_range;
        thd_local_in[tid].vid_range = vid_range_in;

        double start = mywtime();

        //Get the count for classification
        this->estimate_classify(vid_range, vid_range_in, bit_shift);
        
        this->prefix_sum(global_range, thd_local, range_count, thd_count, edge_buf_out);
        this->prefix_sum(global_range_in, thd_local_in, range_count, thd_count, edge_buf_in);
        #pragma omp barrier 
        
        //Classify
        this->classify(vid_range, vid_range_in, bit_shift, global_range, global_range_in);
        
        #pragma omp master 
        {
            //double end = mywtime();
            //cout << " classify " << end - start << endl;
            this->work_division(global_range, thd_local, range_count, thd_count, edge_count);
            //this->work_division(global_range_in, thd_local_in, range_count, thd_count, edge_count);
        }
        
        if (tid == 1) {
            this->work_division(global_range_in, thd_local_in, range_count, thd_count, edge_count);
        }
        #pragma omp barrier 
        
        //Now get the division of work
        vid_t     j_start, j_start_in;
        vid_t     j_end, j_end_in;
        
        if (tid == 0) { 
            j_start = 0; 
        } else { 
            j_start = thd_local[tid - 1].range_end;
        }
        j_end = thd_local[tid].range_end;
        
        if (tid == thd_count - 1) j_start_in = 0;
        else {
            j_start_in = thd_local_in[thd_count - 2 - tid].range_end;
        }
        j_end_in = thd_local_in[thd_count - 1 - tid].range_end;

        //degree count
        this->calc_degree_noatomic(sgraph_out, global_range, j_start, j_end);
        this->calc_degree_noatomic(sgraph_in, global_range_in, j_start_in, j_end_in);
		print(" Degree = ", start);
        
        #ifdef BULK
        vid_t vid_start = (j_start << bit_shift);
        vid_t vid_end = (j_end << bit_shift);
        if (vid_end > v_count) vid_end = v_count;
        sgraph_out[0]->setup_adjlist_noatomic(vid_start, vid_end);

        vid_t vid_start_in = (j_start_in << bit_shift);
        vid_t vid_end_in = (j_end_in << bit_shift);
        if (vid_end_in > v_count) vid_end_in = v_count;
        sgraph_in[0]->setup_adjlist_noatomic(vid_start_in, vid_end_in);
		print(" adj-list setup =", start);
        #endif
        
        //fill adj-list
        this->fill_adjlist_noatomic(sgraph_out, global_range, j_start, j_end);
        print(" adj-list filled = ", start);
        this->fill_adjlist_noatomic(sgraph_in, global_range_in, j_start_in, j_end_in);
        print(" adj-list in filled = ", start);
        
        free(vid_range);
        free(vid_range_in);
        #pragma omp barrier 
        
        //free the memory
        #pragma omp for schedule (static)
        for (vid_t i = 0; i < range_count; ++i) {
            if (global_range[i].edges)
                free(global_range[i].edges);
            
            if (global_range_in[i].edges)
                free(global_range_in[i].edges);
        }
    }

    free(global_range);
    free(thd_local);
    
    free(global_range_in);
    free(thd_local_in);
    //blog->blog_tail = blog->blog_marker;  
}

template <class T>
void pgraph_t<T>::make_graph_u() 
{
    if (blog->blog_tail >= blog->blog_marker) return;
    
    vid_t v_count = sgraph[0]->get_vcount();
    vid_t range_count = 1024;
    vid_t thd_count = THD_COUNT;
    vid_t  base_vid = ((v_count -1)/range_count);
    
    //find the number of bits to do shift to find the range
#if B32    
    vid_t bit_shift = __builtin_clz(base_vid);
    bit_shift = 32 - bit_shift; 
#else
    vid_t bit_shift = __builtin_clzl(base_vid);
    bit_shift = 64 - bit_shift; 
#endif

    global_range_t<T>* global_range = (global_range_t<T>*)calloc(
                            sizeof(global_range_t<T>), range_count);
    
    thd_local_t* thd_local = (thd_local_t*) calloc(sizeof(thd_local_t), thd_count);  
    index_t total_edge_count = blog->blog_marker - blog->blog_tail ;
    index_t edge_count = ((total_edge_count << 1)*1.15)/(thd_count);
    
    //alloc_edge_buf(total_edge_count);
    double start = mywtime();

    #pragma omp parallel num_threads(thd_count)
    {
        int tid = omp_get_thread_num();
        vid_t* vid_range = (vid_t*)calloc(sizeof(vid_t), range_count); 
        thd_local[tid].vid_range = vid_range;

        //Get the count for classification
        this->estimate_classify(vid_range, vid_range, bit_shift);
        
        this->prefix_sum(global_range, thd_local, range_count, thd_count, edge_buf_out);
        #pragma omp barrier 
        
        //Classify
        this->classify(vid_range, vid_range, bit_shift, global_range, global_range);
        #pragma omp master 
        {
            print(" classify = ", start);
            //double end = mywtime();
            //cout << " classify " << end - start << endl;
            this->work_division(global_range, thd_local, range_count, thd_count, edge_count);
        }
        #pragma omp barrier 
        
        //Now get the division of work
        vid_t     j_start;
        vid_t     j_end; 
        
        if (tid == 0) { 
            j_start = 0; 
        } else { 
            j_start = thd_local[tid - 1].range_end;
        }
        j_end = thd_local[tid].range_end;
        
        //degree count
        this->calc_degree_noatomic(sgraph, global_range, j_start, j_end);
		print(" Degree = ", start);

        //Adj list
		#ifdef BULK 
        vid_t vid_start = (j_start << bit_shift);
        vid_t vid_end = (j_end << bit_shift);
        if (vid_end > v_count) vid_end = v_count;
		sgraph[0]->setup_adjlist_noatomic(vid_start, vid_end);
		print(" adj-list setup =", start);
		#endif
        
        //fill adj-list
        this->fill_adjlist_noatomic(sgraph, global_range, j_start, j_end);
        free(vid_range);
        #pragma omp barrier 
        print(" adj-list filled = ", start);
        
        //free the memory
        #pragma omp for schedule (static)
        for (vid_t i = 0; i < range_count; ++i) {
            if (global_range[i].edges)
                free(global_range[i].edges);
        }
    }
    //free_edge_buf();
    free(global_range);
    free(thd_local);
    blog->blog_tail = blog->blog_marker;  
    //cout << "setting the tail to" << blog->blog_tail << endl;
}
