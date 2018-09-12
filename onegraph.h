#pragma once

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

template <class T>
void onegraph_t<T>::setup(tid_t tid)
{
    if(0 == super_id) {
        super_id = g->get_type_scount(tid);
        vid_t v_count = TO_VID(super_id);
        max_vcount = v_count;// (v_count << 1);
        beg_pos = (vert_table_t<T>*)calloc(sizeof(vert_table_t<T>), max_vcount);
        
        if(posix_memalign((void**)&thd_mem, 64 , THD_COUNT*sizeof(thd_mem_t<T>))) {
            cout << "posix_memalign failed()" << endl;
		    thd_mem = (thd_mem_t<T>*)calloc(sizeof(thd_mem_t<T>), THD_COUNT);
        } else {
            memset(thd_mem, 0, THD_COUNT*sizeof(thd_mem_t<T>));
        } 

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
