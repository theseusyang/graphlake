#pragma once
#include <omp.h>
#include <algorithm>
#include "graph.h"
#include "wtime.h"
#include "mem_iterative_analytics.h"
#include "sgraph.h"

using std::min;

//use direct AIO for BFS to compare against 

segment* seg1 ;
segment* seg2 ;
segment* seg3 ;

char* buf1 = 0;
char* buf2 = 0;

void init_aio(int etf)
{
    seg1 = (segment*)malloc(sizeof(segment));
    seg2 = (segment*)malloc(sizeof(segment));
    seg3 = (segment*)malloc(sizeof(segment));
    
    seg1->ctx_count = 0;
    seg2->ctx_count = 0;
    seg3->ctx_count = 0;
    
    seg1->meta_count = etf;
    seg2->meta_count = etf;
    seg3->meta_count = etf;

    seg1->etf = etf;
    seg2->etf = etf;
    seg3->etf = etf;
    
    seg1->meta = (meta_t*)calloc(sizeof(meta_t), 1024*1024);
    seg2->meta = (meta_t*)calloc(sizeof(meta_t), 1024*1024);
    seg3->meta = (meta_t*)calloc(sizeof(meta_t), 1024*1024);
    
    if (posix_memalign((void**)&buf1, 2097152, BUF_SIZE)) {
        perror("posix memalign batch edge log");
    }
    
    if (posix_memalign((void**)&buf2, 2097152, BUF_SIZE)) {
        perror("posix memalign batch edge log");
    }
}
/*
template<class T>
void
fg_pagerank_push(ext_vunit_t* ext_vunits, int etf, vid_t v_count, int iteration_count)
{
    io_driver io_driver;
    init_aio(etf);

    size_t   size = fsize(etf);
    
    if (size == -1L) {
        assert(0);
    }

    float* rank_array = 0;
	float* prior_rank_array = 0;
    float* dset = 0;
	
    double start = mywtime();
    
    rank_array = (float*)calloc(v_count, sizeof(float));
    prior_rank_array = (float*)calloc(v_count, sizeof(float));
    dset = (float*)calloc(v_count, sizeof(float));
	
	//initialize the rank, and get the degree information
    
    float	inv_count = 1.0f/v_count;

    #pragma omp parallel 
    { 
        degree_t degree = 0;
        float   inv_degree = 0;
        #pragma omp for
        for (vid_t v = 0; v < v_count; ++v) {
            degree = ext_vunits[v].count;
            if (degree != 0) {
                inv_degree = 1.0f/degree;
                dset[v] = inv_degree;
                prior_rank_array[v] = inv_count*inv_degree;
            } else {
                dset[v] = 0;
                prior_rank_array[v] = 0;
            }
        }
    }

    float	inv_v_count = 0.15f/v_count;
   
    vid_t v_count2 = v_count;
    vid_t v_count1 = v_count; 
    vid_t last_read1 = 0;
    vid_t last_read2 = 0;
    vid_t last_read3 = 0;
    char* buf = 0;

    //prep
    io_driver.prep_seq_read_aio<T>(last_read1, v_count, BUF_SIZE, seg1, ext_vunits, v_count1, v_count2);
    cout << "Prep " << seg1->meta[0].vid << "-" 
         << seg1->meta[seg1->meta_count - 1].vid << endl;
    
    //Fetch
    swap(seg2, seg1);
    seg1->buf = 0;
    seg2->buf = buf1;
    io_driver.seq_read_aio(seg2, ext_vunits);
    io_driver.wait_aio_completion();
    cout << "Fetched " << seg2->meta[0].vid << "-" 
         << seg2->meta[seg2->meta_count - 1].vid << endl;

    swap(seg3, seg2);
    last_read3 = last_read2;
    last_read2 = last_read1;

    //prep
    io_driver.prep_seq_read_aio<T>(last_read1, v_count, BUF_SIZE, seg1, ext_vunits, v_count1, v_count2);
    cout << "Prep " << seg1->meta[0].vid << "-" 
         << seg1->meta[seg1->meta_count - 1].vid << endl;
    
    swap(seg2, seg1);
    seg2->buf = buf2;
    
    int iteration_start = 0;
    int iteration = 0;

    assert(seg3->buf != seg2->buf);

	//let's run the pagerank
    while (true) {
        //#pragma omp parallel
        {
            
            //fetch
            if (0 == omp_get_thread_num() && (last_read2 < v_count) && !iteration_start) {
                io_driver.seq_read_aio(seg2, ext_vunits);
                io_driver.wait_aio_completion();
                cout << "Fetched " << seg2->meta[0].vid << "-" 
                     << seg2->meta[seg2->meta_count - 1].vid << endl;
            }
            
            //prep
            #pragma omp master
            {
            last_read3 = last_read2;
            last_read2 = last_read1;
            if (last_read1 < v_count) {
                io_driver.prep_seq_read_aio<T>(last_read1, v_count1, BUF_SIZE, 
                                             seg1, ext_vunits, v_count1, v_count2);
                cout << "Prep " << seg1->meta[0].vid << "-" 
                     << seg1->meta[seg1->meta_count - 1].vid << endl;
            }
            }

            //Process
            cout << "process " << seg3->meta[0].vid << "-" 
                 << seg3->meta[seg3->meta_count - 1].vid << endl;
            sid_t sid;
            vid_t vid;
            degree_t durable_degree = 0;
            durable_adjlist_t<T>* durable_adjlist;
            T* adj_list = 0;
            index_t  offset  = 0;

            ext_vunit_t* v_unit = 0;
            float rank = 0.0f;

            meta_t* meta = seg3->meta;
            int meta_count = seg3->meta_count;
            
            //#pragma omp for
            for (vid_t v = 0; v < meta_count; v++) {
                vid = meta[v].vid;
                offset = meta[v].offset;
                v_unit = ext_vunits + vid;
                durable_degree = v_unit->count;
                if (durable_degree == 0) continue;

                durable_adjlist = (durable_adjlist_t<T>*)(seg3->buf + offset);
                assert(durable_degree == durable_adjlist->get_nebrcount());
                adj_list = durable_adjlist->get_adjlist();

                rank = 0.0f;
                
                //traverse the delta adj list
                for (degree_t i = 0; i < durable_degree; ++i) {
                    sid = get_nebr(adj_list, i);
                    rank = prior_rank_array[sid];
                    qthread_dincr(rank_array + sid, rank);
                }
            }
        }

        if (last_read3 == v_count) {
            float new_rank = 0.0f;
            
            #pragma omp for
            for (vid_t v = 0; v < v_count; v++ ) {
                if (ext_vunits[v].count == 0) continue;
                new_rank = inv_v_count + 0.85*rank_array[v];
                rank_array[v] = new_rank*dset[v];
                prior_rank_array[v] = 0;
            }

            ++iteration;
            if (iteration == iteration_count) break;
            swap(prior_rank_array, rank_array);
            //special handling for first
            iteration_start = true;
            cout << "iteration done " << iteration << endl; 
            last_read1 = 0;
            last_read2 = 0;
            last_read3 = 0;

            v_count1 = seg2->meta[0].vid;
            v_count2 = seg3->meta[seg3->meta_count - 1].vid;

        } else {
            buf = seg3->buf;
            swap(seg3, seg2);
            //last_read3 = last_read2;
            //last_read2 = last_read1;

            swap(seg2, seg1);
            seg2->buf = buf;

            seg1->buf = 0;
            assert(seg3->buf != seg2->buf);
        }
    }	

    #pragma omp for
    for (vid_t v = 0; v < v_count; v++ ) {
        rank_array[v] = rank_array[v]*ext_vunits[v].count;
    }

    double end = mywtime();

    cout << "PR Time = " << end - start << endl;

    free(rank_array);
    free(prior_rank_array);
    free(dset);
	cout << endl;
}
*/

template<class T>
void
fg_pagerank_push(ext_vunit_t* ext_vunits, int etf, vid_t v_count, int iteration_count)
{
    io_driver io_driver;
    init_aio(etf);

    size_t   size = fsize(etf);
    
    if (size == -1L) {
        assert(0);
    }

    float* rank_array = 0;
	float* prior_rank_array = 0;
    float* dset = 0;
	
    double start = mywtime();
    
    rank_array = (float*)calloc(v_count, sizeof(float));
    prior_rank_array = (float*)calloc(v_count, sizeof(float));
    dset = (float*)calloc(v_count, sizeof(float));
	
	//initialize the rank, and get the degree information
    
    float	inv_count = 1.0f/v_count;

    #pragma omp parallel 
    { 
        degree_t degree = 0;
        float   inv_degree = 0;
        #pragma omp for
        for (vid_t v = 0; v < v_count; ++v) {
            degree = ext_vunits[v].count;
            if (degree != 0) {
                inv_degree = 1.0f/degree;
                dset[v] = inv_degree;
                prior_rank_array[v] = inv_count*inv_degree;
            } else {
                dset[v] = 0;
                prior_rank_array[v] = 0;
            }
        }
    }

    float	inv_v_count = 0.15f/v_count;
   
    vid_t v_count2 = v_count;
    vid_t v_count1 = v_count; 
    vid_t last_read1 = 0;
    vid_t last_read2 = 0;
    vid_t last_read3 = 0;
    char* buf = 0;

    //prep
    io_driver.prep_seq_read_aio<T>(last_read1, v_count, BUF_SIZE, seg1, ext_vunits, v_count1, v_count2);
    cout << "Prep " << seg1->meta[0].vid << "-" 
         << seg1->meta[seg1->meta_count - 1].vid << endl;
    
    //Fetch
    swap(seg2, seg1);
    seg1->buf = 0;
    seg2->buf = buf1;
    io_driver.seq_read_aio(seg2, ext_vunits);
    io_driver.wait_aio_completion();
    cout << "Fetched " << seg2->meta[0].vid << "-" 
         << seg2->meta[seg2->meta_count - 1].vid << endl;

    swap(seg3, seg2);
    last_read3 = last_read2;
    last_read2 = last_read1;

    //prep
    io_driver.prep_seq_read_aio<T>(last_read1, v_count, BUF_SIZE, seg1, ext_vunits, v_count1, v_count2);
    cout << "Prep " << seg1->meta[0].vid << "-" 
         << seg1->meta[seg1->meta_count - 1].vid << endl;
    
    swap(seg2, seg1);
    seg2->buf = buf2;

    assert(seg3->buf != seg2->buf);

    int iteration_start = 0;
    int iteration = 0;

	//let's run the pagerank
    while (true) {
        //#pragma omp parallel
        {
            
            //fetch
            if (0 == omp_get_thread_num() && (last_read2 < v_count) && !iteration_start) {
                io_driver.seq_read_aio(seg2, ext_vunits);
                io_driver.wait_aio_completion();
                cout << "Fetched " << seg2->meta[0].vid << "-" 
                     << seg2->meta[seg2->meta_count - 1].vid << endl;
            }
            
            //prep
            #pragma omp master
            {
            last_read3 = last_read2;
            last_read2 = last_read1;
            if (last_read1 < v_count) {
                io_driver.prep_seq_read_aio<T>(last_read1, v_count1, BUF_SIZE, 
                                             seg1, ext_vunits, v_count1, v_count2);
                cout << "Prep " << seg1->meta[0].vid << "-" 
                     << seg1->meta[seg1->meta_count - 1].vid << endl;
            }
            }

            //Process
            cout << "process " << seg3->meta[0].vid << "-" 
                 << seg3->meta[seg3->meta_count - 1].vid << endl;
            sid_t sid;
            vid_t vid;
            degree_t durable_degree = 0;
            durable_adjlist_t<T>* durable_adjlist;
            T* adj_list = 0;
            index_t  offset  = 0;

            ext_vunit_t* v_unit = 0;
            float rank = 0.0f;

            meta_t* meta = seg3->meta;
            int meta_count = seg3->meta_count;
            
            //#pragma omp for
            for (vid_t v = 0; v < meta_count; v++) {
                vid = meta[v].vid;
                offset = meta[v].offset;
                v_unit = ext_vunits + vid;
                durable_degree = v_unit->count;
                if (durable_degree == 0) continue;

                durable_adjlist = (durable_adjlist_t<T>*)(seg3->buf + offset);
                assert(durable_degree == durable_adjlist->get_nebrcount());
                adj_list = durable_adjlist->get_adjlist();

                rank = 0.0f;
                
                //traverse the delta adj list
                for (degree_t i = 0; i < durable_degree; ++i) {
                    sid = get_nebr(adj_list, i);
                    rank = prior_rank_array[sid];
                    qthread_dincr(rank_array + sid, rank);
                }
            }
        }

        if (last_read3 == v_count) {
            float new_rank = 0.0f;
            
            #pragma omp for
            for (vid_t v = 0; v < v_count; v++ ) {
                if (ext_vunits[v].count == 0) continue;
                new_rank = inv_v_count + 0.85*rank_array[v];
                rank_array[v] = new_rank*dset[v];
                prior_rank_array[v] = 0;
            }

            ++iteration;
            if (iteration == iteration_count) break;

            swap(prior_rank_array, rank_array);
            //special handling for first
            iteration_start = 0;
            cout << "iteration done " << iteration << endl; 
            last_read1 = 0;
            last_read2 = 0;
            last_read3 = 0;

            //new iteration
            
            //prep
            io_driver.prep_seq_read_aio<T>(last_read1, v_count, BUF_SIZE, 
                                           seg1, ext_vunits, v_count1, v_count2);
            cout << "Prep " << seg1->meta[0].vid << "-" 
                 << seg1->meta[seg1->meta_count - 1].vid << endl;
            
            //Fetch
            swap(seg2, seg1);
            seg1->buf = 0;
            seg2->buf = buf1;
            io_driver.seq_read_aio(seg2, ext_vunits);
            io_driver.wait_aio_completion();
            cout << "Fetched " << seg2->meta[0].vid << "-" 
                 << seg2->meta[seg2->meta_count - 1].vid << endl;

            swap(seg3, seg2);
            last_read3 = last_read2;
            last_read2 = last_read1;

            //prep
            io_driver.prep_seq_read_aio<T>(last_read1, v_count, BUF_SIZE, seg1, ext_vunits, v_count1, v_count2);
            cout << "Prep " << seg1->meta[0].vid << "-" 
                 << seg1->meta[seg1->meta_count - 1].vid << endl;
            
            swap(seg2, seg1);
            seg2->buf = buf2;

            assert(seg3->buf != seg2->buf);

        } else {
            buf = seg3->buf;
            swap(seg3, seg2);
            //last_read3 = last_read2;
            //last_read2 = last_read1;

            swap(seg2, seg1);
            seg2->buf = buf;

            seg1->buf = 0;
            assert(seg3->buf != seg2->buf);
        }
    }	

    #pragma omp for
    for (vid_t v = 0; v < v_count; v++ ) {
        rank_array[v] = rank_array[v]*ext_vunits[v].count;
    }

    double end = mywtime();

    cout << "PR Time = " << end - start << endl;

    free(rank_array);
    free(prior_rank_array);
    free(dset);
	cout << endl;
}

template<class T>
void
fg_bfs(ext_vunit_t* ext_vunits, int etf, vid_t v_count, uint8_t* status, vid_t root)
{
    io_driver io_driver;
    init_aio(etf);
	
    int		level      = 1;
	sid_t	frontier   = 0;

    size_t   size = fsize(etf);
    if (size == -1L) {
        assert(0);
    }

    double start = mywtime();
    
    vid_t last_read1 = 0;
    vid_t last_read2 = 0;
    vid_t last_read3 = 0;
    char* buf = 0;
    vid_t v_count1 = v_count;
    vid_t v_count2 = v_count;
	
    status[root] = level;

    //prep
    io_driver.prep_seq_read_aio<T>(last_read1, v_count, BUF_SIZE, seg1, ext_vunits, v_count1, v_count2);
    cout << "Prep " << seg1->meta[0].vid << "-" 
         << seg1->meta[seg1->meta_count - 1].vid << endl;
    
    //Fetch
    swap(seg2, seg1);
    seg1->buf = 0;
    seg2->buf = buf1;
    io_driver.seq_read_aio(seg2, ext_vunits);
    io_driver.wait_aio_completion();
    cout << "Fetched " << seg2->meta[0].vid << "-" 
         << seg2->meta[seg2->meta_count - 1].vid << endl;

    swap(seg3, seg2);
    last_read3 = last_read2;
    last_read2 = last_read1;

    //prep
    io_driver.prep_seq_read_aio<T>(last_read1, v_count, BUF_SIZE, seg1, ext_vunits, v_count1, v_count2);
    cout << "Prep " << seg1->meta[0].vid << "-" 
         << seg1->meta[seg1->meta_count - 1].vid << endl;
    
    swap(seg2, seg1);
    seg2->buf = buf2;

    assert(seg3->buf != seg2->buf);

	//let's run the pagerank
    while (true) {
        //#pragma omp parallel
        {
            
            //fetch
            if (0 == omp_get_thread_num() && (last_read2 < v_count)) {
                io_driver.seq_read_aio(seg2, ext_vunits);
                io_driver.wait_aio_completion();
                cout << "Fetched " << seg2->meta[0].vid << "-" 
                     << seg2->meta[seg2->meta_count - 1].vid << endl;
            }
            
            //prep
            #pragma omp master
            {
            last_read3 = last_read2;
            last_read2 = last_read1;
            if (last_read1 < v_count) {
                io_driver.prep_seq_read_aio<T>(last_read1, v_count1, BUF_SIZE, 
                                             seg1, ext_vunits, v_count1, v_count2);
                cout << "Prep " << seg1->meta[0].vid << "-" 
                     << seg1->meta[seg1->meta_count - 1].vid << endl;
            }
            }

            //Process
            cout << "process " << seg3->meta[0].vid << "-" 
                 << seg3->meta[seg3->meta_count - 1].vid << endl;
            sid_t sid;
            vid_t vid;
            degree_t durable_degree = 0;
            durable_adjlist_t<T>* durable_adjlist;
            T* adj_list = 0;
            index_t  offset  = 0;

            ext_vunit_t* v_unit = 0;
            meta_t* meta = seg3->meta;
            int meta_count = seg3->meta_count;
            
            //#pragma omp for
            for (vid_t v = 0; v < meta_count; v++) {
                vid = meta[v].vid;
                if (status[vid] != level) continue;
                v_unit = ext_vunits + vid;
                durable_degree = v_unit->count;
                if (durable_degree == 0) continue;

                offset = meta[v].offset;
                durable_adjlist = (durable_adjlist_t<T>*)(seg3->buf + offset);
                assert(durable_degree == durable_adjlist->get_nebrcount());
                adj_list = durable_adjlist->get_adjlist();

                //traverse the adj list
                for (degree_t k = 0; k < durable_degree; ++k) {
                    sid = get_nebr(adj_list, k);
                    if (status[sid] == 0) {
                        status[sid] = level + 1;
                        ++frontier;
                    }
                }
            }
            //end process
        }

        if (last_read3 == v_count) {
            if (frontier == 0) break;

            last_read1 = 0;
            last_read2 = 0;
            last_read3 = 0;
		
            cout << " Level = " << level
                 << " Frontier Count = " << frontier
		         //<< " Time = " << end - start
		         << endl;
	
		    ++level;
            frontier = 0;

            //new iteration
            
            //prep
            io_driver.prep_seq_read_aio<T>(last_read1, v_count, BUF_SIZE, 
                                           seg1, ext_vunits, v_count1, v_count2);
            cout << "Prep " << seg1->meta[0].vid << "-" 
                 << seg1->meta[seg1->meta_count - 1].vid << endl;
            
            //Fetch
            swap(seg2, seg1);
            seg1->buf = 0;
            seg2->buf = buf1;
            io_driver.seq_read_aio(seg2, ext_vunits);
            io_driver.wait_aio_completion();
            cout << "Fetched " << seg2->meta[0].vid << "-" 
                 << seg2->meta[seg2->meta_count - 1].vid << endl;

            swap(seg3, seg2);
            last_read3 = last_read2;
            last_read2 = last_read1;

            //prep
            io_driver.prep_seq_read_aio<T>(last_read1, v_count, BUF_SIZE, seg1, ext_vunits, v_count1, v_count2);
            cout << "Prep " << seg1->meta[0].vid << "-" 
                 << seg1->meta[seg1->meta_count - 1].vid << endl;
            
            swap(seg2, seg1);
            seg2->buf = buf2;

            assert(seg3->buf != seg2->buf);

        } else {
            buf = seg3->buf;
            swap(seg3, seg2);
            //last_read3 = last_read2;
            //last_read2 = last_read1;

            swap(seg2, seg1);
            seg2->buf = buf;

            seg1->buf = 0;
            assert(seg3->buf != seg2->buf);
        }
    }	

    double end = mywtime();
	
    for (int l = 1; l < level; ++l) {
        vid_t vid_count = 0;
        #pragma omp parallel for reduction (+:vid_count) 
        for (vid_t v = 0; v < v_count; ++v) {
            if (status[v] == l) ++vid_count;
        }
        cout << " Level = " << l << " count = " << vid_count << endl;
    }

    cout << "PR Time = " << end - start << endl;
}
