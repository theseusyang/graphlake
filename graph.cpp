#include "graph.h"
#include <algorithm>

using std::swap;

graph::graph()
{
    cf_info  = 0;
    cf_count = 0;
    p_info   = 0;
    p_count  = 0;
    vert_count = 0;
    v_graph =  new vgraph_t;
    //v_graph->create_columnfamily();
    //pinfo_t *info = new pinfo_t;
    //v_graph->add_column(info);
}

void* alloc_buf()
{
    return calloc(sizeof(edge_t), MAX_ECOUNT);
}

void free_buf(void* buf)
{
    free(buf);
    buf = 0;
}

sid_t graph::get_type_scount(tid_t type)
{
    typekv_t* typekv = dynamic_cast<typekv_t*>(cf_info[0]);
    return typekv->get_type_scount(type);
}

tid_t graph::get_total_types()
{
    typekv_t* typekv = dynamic_cast<typekv_t*>(cf_info[0]);
    return typekv->get_total_types();
}

status_t graph::type_update(const string& src, const string& dst)
{
    return cf_info[0]->batch_update(src, dst);
}

void graph::type_done()
{
    v_graph->make_graph_baseline();
}

void graph::type_store(const string& odir)
{
    v_graph->store_graph_baseline(odir);
}

propid_t graph::get_cfid(propid_t pid)
{
    return p_info[pid].cf_id;
}

propid_t graph::get_cfid(const char* predicate)
{
    propid_t pid = get_pid(predicate);
    return p_info[pid].cf_id;
}

propid_t graph::get_pid(const char* predicate)
{
    map<string, propid_t>::iterator str2pid_iter = str2pid.find(predicate);
    if (str2pid_iter == str2pid.end()) {
        return INVALID_PID;
    }
    return str2pid_iter->second;
}

sid_t graph::get_sid(const char* src)
{
    map<string, sid_t>::iterator str2vid_iter = str2vid.find(src);
    if (str2vid_iter == str2vid.end()) {
        return INVALID_SID;
    }
    return str2vid_iter->second;
}

status_t graph::add_property(const char* longname)
{
    map<string, propid_t>::iterator iter;
    iter = str2pid.find(longname);
    if (str2pid.end() == iter) {
        str2pid[longname] = p_count;
        p_count++;
        return eOK;
    }
    //XXX
    return eOK;
}
    
status_t graph::batch_update(const string& src, const string& dst, const string& predicate)
{
    map<string, propid_t>::iterator str2pid_iter;
    str2pid_iter = str2pid.find(predicate);
    if (str2pid_iter == g->str2pid.end()) {
        assert(0);
    }
    propid_t pid = str2pid_iter->second;
    propid_t cf_id = g->get_cfid(pid);
    if (pid != 0) { //non-type
      return  cf_info[cf_id]->batch_update(src, dst, pid);
    //} else { //Is already handled above
    }
    return eOK;
}
    
status_t graph::batch_update(const string& src, const string& dst, propid_t pid, 
                          propid_t count, prop_pair_t* prop_pair)
{
    propid_t cf_id = g->get_cfid(pid);
    if (pid != 0) { //non-type
      return  cf_info[cf_id]->batch_update(src, dst, pid, count, prop_pair);
    //} else { //Is already handled above
    }
    return eOK;
}

void graph::make_graph_baseline()
{
    /*
    propid_t  cf_id;
    pedge_t*  edges;
    index_t   count;

    for (int j = 0; j <= batch_count; ++j) { 
        edges = (pedge_t*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            cf_id = 0;//XXX
            if (eOK != cf_info[cf_id]->calc_deletededge_count(edges+i)) {
                //delete this one,
            }
        }
    }
    */
    //swap 
    for (int i = 0; i < cf_count; i++) {
        cf_info[i]->swap_log_buffer();
    }
    
    //make graph
    for (int i = 0; i < cf_count; i++) {
        cf_info[i]->make_graph_baseline();
    }
}

void graph::store_graph_baseline(const string& odir)
{
    //Store graph
    for (int i = 0; i < cf_count; i++) {
        cf_info[i]->store_graph_baseline(odir);
    }
}

void graph::read_graph_baseline(const string& odir)
{
    for (int i = 0; i < cf_count; i++) {
        cf_info[i]->read_graph_baseline(odir);
    }
    v_graph->read_graph_baseline(odir);
    v_graph->prep_str2sid(str2vid);
}

/////////////////////////////////////////
void pinfo_t::populate_property(const char* longname, const char* property_name)
{

    p_name  = gstrdup(property_name);
    p_longname = gstrdup(longname);
    cf_id = 0;//will be corrected later
}

status_t cfinfo_t::batch_update(const string& src, const string& dst, propid_t pid /* = 0*/)
{
    assert(0);
    return  eOK;
}
    
status_t cfinfo_t::batch_update(const string& src, const string& dst, propid_t pid, 
                          propid_t count, prop_pair_t* prop_pair)
{
    //cout << "ignoring edge properties" << endl;
    batch_update(src, dst, pid);
    return eOK;
}
    
void cfinfo_t::make_graph_baseline()
{
    assert(0);
}

void cfinfo_t::store_graph_baseline(string dir)
{
    assert(0);
}

void cfinfo_t::read_graph_baseline(const string& dir)
{
    assert(0);
}

/*
static int 
is_literal(string str) {
       return ('<' != str[0]);
}
*/

void graph::add_columnfamily(cfinfo_t* cf) 
{
    cf_info[cf_count] = cf;
    cf->cf_id = cf_count;
    cf_count++;
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

cfinfo_t::cfinfo_t()
{
    batch_info = (batchinfo_t*)calloc(sizeof(batchinfo_t), MAX_BCOUNT);
    batch_count = 0;
    batch_info1 = (batchinfo_t*)calloc(sizeof(batchinfo_t), MAX_BCOUNT);
    batch_count1 = 0;
    //Only first buffer is allocated.
    //Others are allocated at runtime
    for (int i = 0; i < MAX_BCOUNT; ++i) {
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
