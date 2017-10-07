
#include <algorithm>
#include "cf_info.h"


double bu_factor = 0.07;
int32_t MAX_BCOUNT = 1;
uint64_t MAX_ECOUNT = (1<<9);
uint64_t MAX_PECOUNT = (MAX_ECOUNT << 1)/3;
index_t  BATCH_SIZE = (1L << 17);//edge batching in edge log

//In-memory data structure size
index_t  BLOG_SHIFT = 32;
index_t  BLOG_SIZE = (1L << BLOG_SHIFT); //size of edge log
index_t  BLOG_MASK = (BLOG_SIZE - 1);

index_t  DELTA_SIZE = (1L << 36) ;//(32 + sizeof(T));  //sizeo of delta adj-list
index_t  SNAP_COUNT  = (2);

//durable data structure buffer size
index_t  W_SIZE = (1L << 20); //Edges to write
index_t  DVT_SIZE = (1L <<24);//durable v-unit 
index_t  DURABLE_SIZE = (1L << 30);//Durable adj-list

index_t  OFF_COUNT = 100000;


using std::swap;

void* alloc_buf()
{
    return calloc(sizeof(edge_t), MAX_ECOUNT);
}

void free_buf(void* buf)
{
    free(buf);
    buf = 0;
}
void cfinfo_t::create_columns(propid_t prop_count /* = 1 */)
{
    col_info = new pinfo_t* [prop_count];
    col_count = 0;
    
    /*
    g->cf_info[g->cf_count] = this;
    cf_id = g->cf_count;
    g->cf_count++;
    */
}

void cfinfo_t::add_column(pinfo_t* prop_info)
{
    col_info[col_count] = prop_info;
    ++col_count;
    prop_info->cf_id = cf_id;
}

void cfinfo_t::add_edge_property(const char* longname, prop_encoder_t* prop_encoder)
{
    assert(0);
}

cfinfo_t::cfinfo_t()
{
    /*
    batch_info = (batchinfo_t*)calloc(sizeof(batchinfo_t), MAX_BCOUNT);
    batch_count = 0;
    batch_info1 = (batchinfo_t*)calloc(sizeof(batchinfo_t), MAX_BCOUNT);
    batch_count1 = 0;
    //Only first buffer is allocated.
    //Others are allocated at runtime
    for (int32_t i = 0; i < MAX_BCOUNT; ++i) {
        batch_info[i].buf = calloc(sizeof(edge_t), MAX_ECOUNT);
        batch_info[i].count = 0; 
        batch_info1[i].buf = calloc(sizeof(edge_t), MAX_ECOUNT);
        batch_info1[i].count = 0; 
    }
    */
    flag1 = 0;
    flag2 = 0;
    flag1_count = 0;
    flag2_count = 0;

    col_info = 0;
    col_count = 0;
    
}

void cfinfo_t::swap_log_buffer()
{
    swap(batch_info, batch_info1);
    swap(batch_count, batch_count1);
}

void cfinfo_t::cleanup()
{
    batch_info[0].count = 0;
    for (int i = 1; i <= batch_count; ++i) {
        free_buf(batch_info[i].buf);
        batch_info[i].buf = 0;
        batch_info[i].count = 0;
    }
    batch_count = 0;
}

void cfinfo_t::reset_buffer0()
{
    batch_count = 0;
    for (int32_t i = 0; i < MAX_BCOUNT; ++i) {
        batch_info[i].count = 0;
    }
}

void cfinfo_t::reset_buffer1()
{
    batch_count1 = 0;
    for (int32_t i = 0; i < MAX_BCOUNT; ++i) {
        batch_info1[i].count = 0; 
    }
}

void cfinfo_t::reset()
{
    flag1 = 0;
    flag2 = 0;
    flag1_count = 0;
    flag2_count = 0;
    
    batch_count1 = 0;
    for (int32_t i = 0; i < MAX_BCOUNT; ++i) {
        batch_info1[i].count = 0; 
    }
}

status_t cfinfo_t::batch_update(const string& src, const string& dst, propid_t pid /* = 0*/)
{
    assert(0);
    return  eOK;
}
    
status_t cfinfo_t::batch_update(const string& src, const string& dst, propid_t pid, 
                          propid_t count, prop_pair_t* prop_pair, int del /* = 0 */)
{
    //cout << "ignoring edge properties" << endl;
    batch_update(src, dst, pid);
    return eOK;
}

void cfinfo_t::calc_degree()
{   
    return;
}

void cfinfo_t::prep_graph_baseline()
{   
    return;
}
    
void cfinfo_t::make_graph_baseline()
{
    assert(0);
}
    
status_t cfinfo_t::move_marker(index_t& snap_marker)
{
   return eNoWork;
}

status_t cfinfo_t::write_edgelog()
{
   return eNoWork;
}

void cfinfo_t::store_graph_baseline(bool clean)
{
    assert(0);
}

void cfinfo_t::read_graph_baseline()
{
    assert(0);
}

void cfinfo_t::file_open(const string& filename, bool trunc)
{
    assert(0);
}

/*******label specific **********/
status_t cfinfo_t::filter(sid_t sid, univ_t value, filter_fn_t fn)
{
    assert(0);
    return eOK;
}
    
void cfinfo_t::print_raw_dst(tid_t tid, vid_t vid, propid_t pid /* = 0 */)
{
    assert(0);
}

status_t cfinfo_t::get_encoded_value(const char* value, univ_t* univ)
{
    assert(0);
    return eQueryFail;
}

///****************///
status_t cfinfo_t::transform(srset_t* iset, srset_t* oset, direction_t direction)
{
    assert(0);
    return eOK;
}

status_t cfinfo_t::extend(srset_t* iset, srset_t* oset, direction_t direction)
{
    assert(0);
    return eOK;
}
