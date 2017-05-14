#include "typekv.h"

status_t typekv_t::batch_update(const string& src, const string& dst)
{
    vid_t       src_id;
    tid_t       type_id;
    vid_t       vert_id = 0;

    map<string, tid_t>::iterator str2enum_iter = str2enum.find(dst);
    if (str2enum.end() == str2enum_iter) {
        type_id = t_count++;
        vert_id = TO_SUPER(type_id);
        str2enum[dst] = type_id;
        t_info[type_id].vert_id = vert_id; 
        t_info[type_id].type_name = gstrdup(dst.c_str());
    } else {
        type_id = str2enum_iter->second;
        vert_id = t_info[type_id].vert_id;
    }

    //allocate class specific ids.
    map<string, vid_t>::iterator str2vid_iter = g->str2vid.find(src);
    if (g->str2vid.end() == str2vid_iter) {
        src_id = vert_id++;
        ++g->vert_count;
        g->str2vid[src] = src_id;
        //update the id
        t_info[type_id].vert_id = vert_id;
        g->v_graph->id2name(src_id, src);
    } else {
        //dublicate entry XXX
        src_id = str2vid_iter->second;
    }

    return eOK;
}


status_t typekv_t::filter(sid_t src, univ_t a_value, filter_fn_t fn)
{
    //value is already encoded, so typecast it
    tid_t  dst = (tid_t) a_value.value_tid;
  
    assert(fn == fn_out); 
    
    tid_t type1_id = TO_TID(src);
    if (type1_id == dst) return eOK;
    return eQueryFail;
}


status_t typekv_t::get_encoded_value(const char* value, univ_t* univ) 
{
    map<string, tid_t>::iterator str2enum_iter = str2enum.find(value);
    if (str2enum.end() == str2enum_iter) {
        return eQueryFail;
    }

    univ->value_tid = str2enum_iter->second;
    return eOK;
    
}
    
status_t typekv_t::get_encoded_values(const char* value, tid_t** tids, qid_t* counts)
{
    tid_t tid;
    map<string, tid_t>::iterator str2enum_iter = str2enum.find(value);
    if (str2enum.end() == str2enum_iter) {
        return eQueryFail;
    }

    tid = str2enum_iter->second;
    assert(tid < t_count + it_count);
    
    if (tid < t_count) {
        *counts = 1;
        tids[0] = new tid_t;
        tids[0][0] = tid;
    } else {
        *counts = it_info[tid - t_count].count;
        tids[0] = it_info[tid - t_count].tlist; 
    }

    return eOK;
}

void typekv_t::make_graph_baseline() 
{
    
}
