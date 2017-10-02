#include "typekv.h"
#include "stringkv.h"

sid_t typekv_t::type_update(const string& src, const string& dst)
{
    sid_t       src_id = 0;
    sid_t       vert_id = 0;
    tid_t       type_id;

    map<string, tid_t>::iterator str2enum_iter = str2enum.find(dst);
    if (str2enum.end() == str2enum_iter) {
        type_id = t_count++;
        vert_id = TO_SUPER(type_id);
        str2enum[dst] = type_id;
        t_info[type_id].vert_id = vert_id; 
        t_info[type_id].type_name = log_head; //gstrdup(dst.c_str());
        memcpy(log_beg + log_head, dst.c_str(), strlen(dst.c_str()) + 1);
        log_head += strlen(dst.c_str()) + 1;
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
        //dublicate entry 
        //If type mismatch, delete original //XXX
        src_id = str2vid_iter->second;
        tid_t old_tid = TO_TID(src_id);

        if (old_tid != type_id) {
            /*
            //Different types, delete
            g->str2vid.erase(str2vid_iter);
            cout << "Duplicate unique Id: " << src << " Deleting both. " ;
            cout << "Existing Type: " << (char*)(log_beg + t_info[old_tid].type_name) << "\t";
            cout << "New Type: " << (char*)(log_beg + t_info[type_id].type_name) << endl;
            //assert(0);
            */
            
            return INVALID_SID;
        }
    }

    return src_id;
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

void typekv_t::file_open(const string& dir, bool trunc) 
{
    string vtfile, etfile;
    vtfile = dir + "typekv.vtable";
    etfile = dir + "typekv.etable";

    if(trunc) {
		etf = open(etfile.c_str(), O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
		vtf = open(vtfile.c_str(), O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
		//vtf = fopen(vtfile.c_str(), "wb");
        //etf = fopen(etfile.c_str(), "wb");
		assert(vtf != -1); 
		assert(etf != -1); 
    } else {
		etf = open(etfile.c_str(), O_RDWR|O_CREAT, S_IRWXU);
		vtf = open(vtfile.c_str(), O_RDWR|O_CREAT, S_IRWXU);
		//vtf = fopen(vtfile.c_str(), "r+b");
        //etf = fopen(etfile.c_str(), "r+b");
		assert(vtf != -1); 
		assert(etf != -1); 
    }
}

void typekv_t::store_graph_baseline(bool clean)
{
    //write down the type info, t_info
    write(vtf, t_info, sizeof(tinfo_t)*t_count);

    //Make a copy
    sid_t wpos = log_wpos;

    //Update the mark
    log_wpos = log_head;
    
    write(etf, log_beg + wpos, sizeof(char)*(log_head-wpos));

    //str2enum: No need to write. We make it from disk during initial read.
    //XXX: write down the deleted id list
    
}

void typekv_t::read_graph_baseline()
{
    off_t size = fsize(etf);
    if (size == -1L) {
        assert(0);
    }
    
    sid_t edge_count = size/sizeof(char);
    read(etf, log_beg, sizeof(char)*edge_count);

    log_head = edge_count;
    log_wpos = log_head;

    //read vtable
    size = fsize(vtf);
    if (size == -1L) {
        assert(0);
    }
    t_count = size/sizeof(tinfo_t);
    read(vtf, t_info, sizeof(tinfo_t)*t_count);

    //Populate str2enum now.
    string dst;
    for (tid_t t = 0; t < t_count; ++t) {
        dst = log_beg + t_info[t].type_name;
        str2enum[dst] = TO_TID(t_info[t].vert_id);
    }
}

typekv_t::typekv_t()
{
    init_enum(256);
    //XXX everything is in memory
    log_count = (1L << 9);//32*8 MB
    if (posix_memalign((void**)&log_beg, 2097152, log_count*sizeof(char))) {
        //log_beg = (sid_t*)calloc(sizeof(sid_t), log_count);
        perror("posix memalign edge log");
    }
    log_head = 0;
    log_tail = 0;
    log_wpos = 0;
    
    dvt_count = 0;
    dvt_max_count = (1L << 9);
    if (posix_memalign((void**) &dvt, 2097152, 
                       dvt_max_count*sizeof(disk_typekv_t*))) {
        perror("posix memalign vertex log");    
    }
    vtf = -1;
    etf = -1;
}

void typekv_t::manual_setup(sid_t  vert_count)
{
    t_count = 1;
    t_info[0].vert_id = vert_count;
}

cfinfo_t*
typekv_t::create_instance()
{
    return new typekv_t;
}
