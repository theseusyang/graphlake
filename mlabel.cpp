#include "graph.h"
#include "mlabel.h"


void mkv_t::setup(tid_t tid)
{
    if ( 0 == super_id ) {
        super_id = g->get_type_scount(tid);
        vid_t v_count = TO_VID(super_id);
        max_vcount = (v_count << 1);
        kv_array = (kvarray_t*)calloc(sizeof(kvarray_t), max_vcount);
        nebr_count = (kv_t*)calloc(sizeof(kv_t), max_vcount);
    } else {
        super_id = g->get_type_scount(tid);
        vid_t v_count = TO_VID(super_id);
        if (max_vcount < v_count) {
            assert(0);
        }
    }
}

void mkv_t::setup_adjlist()
{
    vid_t v_count = TO_VID(super_id);
    propid_t size = 0;
    propid_t degree = 0;
    kv_t* adj_list = 0;
    vid_t v = 0;

    for (vid_t vid = 0; vid < v_count; ++vid) {
        adj_list = kv_array[vid].adj_list;
        //XXX align it
        size = nebr_count[vid].offset + sizeof(propid_t);

        if (adj_list && adj_list[0] ! = size) {
            adj_list = log_beg + log_head;
            memcpy(adj_list, kv_array[vid].adj_list, kv_array[vid].adj_list[0]);
            kv_array[v].adj_list = adj_list;
            
            dvt[v].vid = vid;
            dvt[v].degree = nebr_count[vid].pid;
            dvt[v].size = size;
            dvt[v].file_offset = log head;
            
            log_head += size;
            ++v;

        } else {
            kv_array[vid].adj_list = log_beg + log_head;

            dvt[v].vid = vid;
            dvt[v].degree = nebr_count[vid].pid;
            dvt[v].size = size;
            dvt[v].file_offset = log head;
            
            log_head += size;
            ++v;
        }
        nebr_count[vid].size = kv_array[vid].get_size();
        nebr_count[vid].degree = kv_array[vid].get_nebr_count();
    }
    dvt_count = v;
}
    
void manykv_t::add_nebr(vid_t vid, propid_t pid, char* dst) 
{
    kv_t* kv = (kv_t*)(kv_array[vid] + 2);
    kv[nebr_count[vid]].pid = pid;
    kv[nebr_count[vid]].offset = log_beg; 
  
    kv_array[vid].add_nebr(nebr_count[vid], pid, dst);
    ++nebr_count[vid].pid;
}

/*****************/
status_t manykv_t::batch_update(const string& src, const string& dst, propid_t pid /*=0*/)
{
    vid_t src_id;
    char* dst_id;
    index_t index = 0;
    pedge_t* edges;
    
    if (batch_info1[batch_count1].count == MAX_PECOUNT) {
        void* mem = alloc_buf();
        if (mem == 0) return eEndBatch;
        ++batch_count1;
        batch_info1[batch_count1].count = 0;
        batch_info1[batch_count1].buf = mem; 
    }

    map<string, vid_t>::iterator str2vid_iter = g->str2vid.find(src);
    if (g->str2vid.end() == str2vid_iter) {
        assert(0);
    } else {
        src_id = str2vid_iter->second;
    }
    
    tid_t type_id = TO_TID(src_id);
    flag1 |= (1L << type_id);
    
    dst_id = gstrdup(dst.c_str());

    index = batch_info1[batch_count1].count++;
    edges = (pedge_t*) batch_info1[batch_count1].buf;
    edges[index].pid = pid;
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
    return eOK;
}

void manykv_t::make_graph_baseline()
{
    if (batch_info[0].count == 0) return;
    flag1_count = __builtin_popcountll(flag1);

    //super bins memory allocation
    prep_mkv();
    
    //estimate edge count
    calc_edge_count();
    
    //prefix sum then reset the count
    prep_mkv_internal();

    //populate and get the original count back
    fill_mkv_out();
    update_count();
    
    //clean up
    cleanup();
}

void manykv_t::prep_mkv()
{
    sflag_t    flag = flag1;
    tid_t      pos  = 0;
    tid_t   t_count = g->get_total_types();
    
    if (0 == mkv_out) {
        mkv_out = (mkv_t**) calloc (sizeof(mkv_t*), t_count);
    }

    for(tid_t i = 0; i < flag1_count; i++) {
        pos = __builtin_ctz(flag);
        flag ^= (1L << pos);//reset that position
        if (0 == mkv_out[pos]) {
            mkv_out[pos] = new mkv_t;
        }
        mkv_out[pos]->setup(pos);
    }
}

void manykv_t::calc_edge_count()
{
    sid_t     src;
    vid_t     vert1_id;
    tid_t     src_index;
    pedge_t*  edges;
    index_t   count;

    for (int j = 0; j <= batch_count; ++j) { 
        edges = (pedge_t*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            src = edges[i].src_id;
            src_index = TO_TID(src);
            vert1_id = TO_VID(src);
            mkv_out[src_index]->increment_count(vert1_id, strlen(edges[i].dst_id) + 1);
        }
    }
}

void manykv_t::prep_mkv_internal()
{
    tid_t       t_count = g->get_total_types();
    
    for(tid_t i = 0; i < t_count; i++) {
        if (0 == mkv_out[i]) continue;
        mkv_out[i]->setup_adjlist();
    }
}

void manykv_t::fill_mkv_out()
{
    sid_t src;
    char* dst;
    propid_t pid;
    vid_t     vert1_id;
    tid_t     src_index;
    
    pedge_t*  edges;
    index_t   count;

    for (int j = 0; j <= batch_count; ++j) { 
        edges = (pedge_t*)batch_info[j].buf;
        count = batch_info[j].count;
        for (index_t i = 0; i < count; ++i) {
            pid = edges[i].pid;
            src = edges[i].src_id;
            dst = edges[i].dst_id;
            src_index = TO_TID(src);
            vert1_id = TO_VID(src);
            
            mkv_out[src_index]->add_nebr(vert1_id, pid, dst);
        }
    }
}

void manykv_t::update_count()
{
    vid_t       v_count = 0;
    tid_t       t_count = g->get_total_types();
    
    for(tid_t i = 0; i < t_count; i++) {
        if (0 == mkv_out[i]) continue;
        v_count = mkv_out[i]->get_vcount();
        for (vid_t j = 0; j < v_count; ++j) {
            mkv_out[i]->update_count(j);
        }
    }
}

void manykv_t::print_raw_dst(tid_t tid, vid_t vid, propid_t pid)
{
    kvarray_t* kv = mkv_out[tid]->get_nebrlist(vid);
    propid_t count = kv->get_nebrcount();
    for (propid_t i = 1; i <= count; ++i) {
        if (pid == kv->get_pid(i)) {
            cout << kv->get_value(i);
            break;
        }
    }
}

void manykv_t::store_graph_baseline(string dir)
{
}
