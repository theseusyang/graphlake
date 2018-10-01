#include "typekv.h"
#include "stringkv.h"

sid_t typekv_t::type_update(const string& src, const string& dst)
{
    sid_t       src_id = 0;
    sid_t       super_id = 0;
    vid_t       vid = 0;
    tid_t       type_id;

    map<string, tid_t>::iterator str2enum_iter = str2enum.find(dst);

    //Have not see this type, create one
    if (str2enum.end() == str2enum_iter) {
        type_id = t_count++;
        super_id = TO_SUPER(type_id);
        
        str2enum[dst] = type_id;
        t_info[type_id].vert_id = super_id; 
        t_info[t_count].type_name = strdup(dst.c_str());
        
        t_info[type_id].max_vcount = (1<<20);//guess
        t_info[type_id].vid2name   = (sid_t*)calloc(sizeof(sid_t), 
                                                    t_info[type_id].max_vcount);
        alloc_edgelog(type_id);

    } else { //existing type, get the last vertex id allocated
        type_id = str2enum_iter->second;
        super_id = t_info[type_id].vert_id;
    }

    //allocate class specific ids.
    map<string, vid_t>::iterator str2vid_iter = str2vid.find(src);
    if (str2vid.end() == str2vid_iter) {
        src_id = super_id++;
        t_info[type_id].vert_id = super_id;
        ++g->vert_count;
        str2vid[src] = src_id;

        vid     = TO_VID(super_id); 
        assert(super_id < t_info[type_id].max_vcount);
        //t_info[type_id].vid2name[vid] = gstrdup(src.c_str());
    
        t_info[type_id].vid2name[vid] = t_info[type_id].log_head;
        memcpy(t_info[type_id].log_beg + t_info[type_id].log_head, src.c_str(), 
               strlen(src.c_str()) + 1);
        t_info[type_id].log_head += strlen(src.c_str()) + 1;
        

    } else {
        //dublicate entry 
        //If type mismatch, delete original //XXX
        src_id = str2vid_iter->second;
        tid_t old_tid = TO_TID(src_id);

        if (old_tid != type_id) {
            /*
            //Different types, delete
            str2vid.erase(str2vid_iter);
            cout << "Duplicate unique Id: " << src << " Deleting both. " ;
            cout << "Existing Type: " << (char*)(log_beg + t_info[old_tid].type_name) << "\t";
            cout << "New Type: " << (char*)(log_beg + t_info[type_id].type_name) << endl;
            //assert(0);
            */
            assert(0);
            return INVALID_SID;
        }
    }
    return src_id;
}

sid_t typekv_t::type_update(const string& src, tid_t type_id)
{
    sid_t       src_id = 0;
    sid_t       super_id = 0;
    vid_t       vid = 0;

    assert(type_id < t_count);

    super_id = t_info[type_id].vert_id;

    //allocate class specific ids.
    map<string, vid_t>::iterator str2vid_iter = str2vid.find(src);
    if (str2vid.end() == str2vid_iter) {
        src_id = super_id++;
        t_info[type_id].vert_id = super_id;
        ++g->vert_count;
        str2vid[src] = src_id;

        vid     = TO_VID(src_id); 
        assert(super_id < t_info[type_id].max_vcount);
        //t_info[type_id].vid2name[vid] = gstrdup(src.c_str());
        
        t_info[type_id].vid2name[vid] = t_info[type_id].log_head;
        memcpy(t_info[type_id].log_beg + t_info[type_id].log_head, src.c_str(), 
               strlen(src.c_str()) + 1);
        t_info[type_id].log_head += strlen(src.c_str()) + 1;

    } else {
        //dublicate entry 
        //If type mismatch, delete original //XXX
        src_id = str2vid_iter->second;
        tid_t old_tid = TO_TID(src_id);

        if (old_tid != type_id) {
            /*
            //Different types, delete
            str2vid.erase(str2vid_iter);
            cout << "Duplicate unique Id: " << src << " Deleting both. " ;
            cout << "Existing Type: " << (char*)(log_beg + t_info[old_tid].type_name) << "\t";
            cout << "New Type: " << (char*)(log_beg + t_info[type_id].type_name) << endl;
            //assert(0);
            */
            assert(0);
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
    string vtfile;
    vtfile = dir + "typekv.vtable";
    //string etfile = dir + "typekv.etable";

    if(trunc) {
		//etf = open(etfile.c_str(), O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
        //etf = fopen(etfile.c_str(), "wb");
		//assert(etf != -1); 
		//vtf = open(vtfile.c_str(), O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
		vtf = fopen(vtfile.c_str(), "wb");
		assert(vtf != 0); 
    } else {
		//etf = open(etfile.c_str(), O_RDWR|O_CREAT, S_IRWXU);
        //etf = fopen(etfile.c_str(), "r+b");
		//assert(etf != -1); 
		//vtf = open(vtfile.c_str(), O_RDWR|O_CREAT, S_IRWXU);
		vtf = fopen(vtfile.c_str(), "r+b");
		assert(vtf != 0); 
    }
}

void typekv_t::store_graph_baseline(bool clean)
{
    index_t total_size = 0;

    for (tid_t t = 0; t < t_count; ++t) {
        total_size += 8 + 8 + strlen(t_info[t].type_name) + 4; 
        //sprintf(type_text, "%ld %ld %s\n", max_vcount, vert_id, type_name);
    }
    
    //write down the type info, t_info
    char* type_text = (char*)calloc(sizeof(char), total_size);
    for (tid_t t = 0; t < t_count; ++t) {
#ifdef B32
        sprintf(type_text, "%u %u %s\n", t_info[t].max_vcount, t_info[t].vert_id, 
                t_info[t].type_name);
#elif B64
        sprintf(type_text, "%lu %lu %s\n", t_info[t].max_vcount, t_info[t].vert_id, 
                t_info[t].type_name);
#endif        
        //Make a copy
        sid_t wpos = t_info[t].log_wpos;
        //Update the mark
        t_info[t].log_wpos = t_info[t].log_head;
        write(t_info[t].etf, t_info[t].log_beg + wpos, t_info[t].log_head-wpos);
    }

    fwrite(type_text, sizeof(char), total_size, vtf);
    //str2enum: No need to write. We make it from disk during initial read.
    //XXX: write down the deleted id list
}

void typekv_t::read_graph_baseline()
{
    //read vtable
    /*
    index_t size = fsize(vtf);
    if (size == -1L) {
        assert(0);
    }*/
    char  line[1024];
    char* token = 0;
    tid_t t = 0;
    char* saveptr = 0;
    char  file_ext[16];

    while (fgets(line, sizeof(line), vtf)) {
        token = strtok_r(line, " \n", &saveptr);
        t_info[t].max_vcount = strtol(token, NULL, 0);
        token = strtok_r(line, " \n", &saveptr);
        t_info[t].vert_id = strtol(token, NULL, 0);
        token = strtok_r(line, " \n", &saveptr);
        t_info[t].type_name = strdup(token);

        //read etf
        sprintf(file_ext,"%u",t);
        string etfile = g->odirname + "typekv.etable" + file_ext;
		t_info[t].etf = open(etfile.c_str(), O_RDWR|O_CREAT, S_IRWXU);
        off_t size = fsize(t_info[t].etf);
        if (size == -1L) {
            assert(0);
        }
        
        sid_t edge_count = size/sizeof(char);

        read(t_info[t].etf, t_info[t].log_beg, sizeof(char)*edge_count);

        t_info[t].log_head = edge_count;
        t_info[t].log_wpos = t_info[t].log_head;
        ++t;
    }

    //Populate str2enum now.
    /*string dst;
    for (tid_t t = 0; t < t_count; ++t) {
        dst = log_beg + t_info[t].type_name;
        str2enum[dst] = TO_TID(t_info[t].vert_id);
    }*/
}

void typekv_t::alloc_edgelog(tid_t t) 
{
    //XXX everything is in memory
    t_info[t].log_count = (1L << 9);//32*8 MB
    if (posix_memalign((void**)&t_info[t].log_beg, 2097152, t_info[t].log_count)) {
        //log_beg = (sid_t*)calloc(sizeof(sid_t), log_count);
        perror("posix memalign type edge log");
    }
    t_info[t].log_head = 0;
    t_info[t].log_tail = 0;
    t_info[t].log_wpos = 0;
    //t_info[t].etf = -1;
    char  file_ext[16];
    sprintf(file_ext,"%u",t);
    string etfile = g->odirname + "typekv.etable" + file_ext;
	t_info[t].etf = open(etfile.c_str(), O_RDWR|O_CREAT, S_IRWXU);
	t_info[t].etf = open(etfile.c_str(), O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
}

typekv_t::typekv_t()
{
    init_enum(256);
    vtf = 0;
}

//Required to be called as we need to have a guess for max v_count
tid_t typekv_t::manual_setup(sid_t vert_count, const string& type_name/*="gtype"*/)
{
    str2enum[type_name.c_str()] = t_count;
    t_info[t_count].type_name = strdup(type_name.c_str());


    t_info[t_count].vert_id = TO_SUPER(t_count);
    //t_info[0].vert_id = vert_count;
    t_info[t_count].max_vcount = TO_SUPER(t_count) + vert_count;
    t_info[t_count].vid2name = (sid_t*)calloc(sizeof(sid_t), vert_count);
    alloc_edgelog(t_count);
    return t_count++;//return the tid of this type
}

cfinfo_t*
typekv_t::create_instance()
{
    return new typekv_t;
}
