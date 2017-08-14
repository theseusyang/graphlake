
#include <algorithm>
#include "cf_info.h"


double bu_factor = 0.07;
uint32_t MAX_BCOUNT = 256;
uint64_t MAX_ECOUNT = 1000000;
uint64_t MAX_PECOUNT = 666666;
uint64_t BUF_SCOUNT = 2000000;
uint64_t BUF_SIZE = 16000000;

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
    batch_info = (batchinfo_t*)calloc(sizeof(batchinfo_t), MAX_BCOUNT);
    batch_count = 0;
    batch_info1 = (batchinfo_t*)calloc(sizeof(batchinfo_t), MAX_BCOUNT);
    batch_count1 = 0;
    //Only first buffer is allocated.
    //Others are allocated at runtime
    for (uint32_t i = 0; i < MAX_BCOUNT; ++i) {
        batch_info[i].buf = calloc(sizeof(edge_t), MAX_ECOUNT);
        batch_info[i].count = 0; 
        batch_info1[i].buf = calloc(sizeof(edge_t), MAX_ECOUNT);
        batch_info1[i].count = 0; 
    }

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
    for (uint32_t i = 1; i <= batch_count; ++i) {
        free_buf(batch_info[i].buf);
        batch_info[i].buf = 0;
        batch_info[i].count = 0;
    }
    batch_count = 0;
}

void cfinfo_t::reset_buffer0()
{
    batch_count = 0;
    for (uint32_t i = 0; i < MAX_BCOUNT; ++i) {
        batch_info[i].count = 0;
    }
}

void cfinfo_t::reset_buffer1()
{
    batch_count1 = 0;
    for (uint32_t i = 0; i < MAX_BCOUNT; ++i) {
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
    for (uint32_t i = 0; i < MAX_BCOUNT; ++i) {
        batch_info1[i].count = 0; 
    }
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