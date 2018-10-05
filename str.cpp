#include <string.h>
#include "graph.h"
#include "str.h"


strkv_t::strkv_t()
{
    kv = 0;
    tid = 0;
    //super_id = 0;
    log_head = 0;
    log_tail = 0;
    log_wpos = 0;
    vtf = -1;
    etf = -1;
}

void strkv_t::set_value(vid_t vid, const char* value)
{
    //Check if values are same;
    if (0 != strncmp(log_beg + kv[vid], value, strlen(value))) {
        kv[vid] = log_head;
        char* ptr = log_beg + log_head;
        log_head += strlen(value) + 1;
        assert(log_head < log_count);
        memcpy(ptr, value, strlen(value) + 1);
    }

    /*
    kv[vid] = ptr;
    dvt[dvt_count].vid = vid;
    dvt[dvt_count].offset = ptr - log_beg; 
    ++dvt_count;
    */
}

const char* strkv_t::get_value(vid_t vid)
{
    return log_beg + kv[vid];
}

void strkv_t::setup(tid_t t) 
{
    tid = t;
    vid_t v_count = g->get_type_scount(tid);
    
    kv = (sid_t*)calloc(sizeof(sid_t), v_count);
    
    //everything is in memory
    log_count = (1L << 28);//256*8 MB
    if (posix_memalign((void**)&log_beg, 2097152, log_count*sizeof(char))) {
        //log_beg = (sid_t*)calloc(sizeof(sid_t), log_count);
        perror("posix memalign edge log");
    }
    log_head = 0;
    log_tail = 0;
    log_wpos = 0;
    
    /*
    if (posix_memalign((void**) &dvt, 2097152, dvt_max_count*sizeof(disk_strkv_t*))) {
        perror("posix memalign vertex log");
    }*/
}

void strkv_t::persist_elog()
{
    //Make a copy
    sid_t wpos = log_wpos;
    //Update the mark
    log_wpos = log_head;
    write(etf, log_beg + wpos, log_head-wpos);
    //fwrite(log_beg+wpos, sizeof(char), log_head-wpos, etf);
}

void strkv_t::persist_vlog()
{
    /*
    //Make a copy
    sid_t count =  dvt_count;

    //update the mark
    dvt_count = 0;

    fwrite(dvt, sizeof(disk_strkv_t), count, vtf);*/
    vid_t v_count = g->get_type_vcount(tid);
    if (v_count != 0) {
        pwrite(vtf, kv, v_count*sizeof(sid_t), 0);
    }
}

void strkv_t::file_open(const string& filename, bool trunc)
{
    char  file_ext[16];
    sprintf(file_ext,"%u",tid);
    
    string vtfile = filename + file_ext + ".vtable";
    string etfile = filename + file_ext + ".etable";
    if (trunc) {
		etf = open(etfile.c_str(), O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
        //etf = fopen(etfile.c_str(), "wb");//append/write + binary
        //vtf = fopen(vtfile.c_str(), "wb");
		vtf = open(vtfile.c_str(), O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);

    } else {
	    etf = open(etfile.c_str(), O_RDWR|O_CREAT, S_IRWXU);
        //etf = fopen(etfile.c_str(), "r+b");//append/write + binary
	    vtf = open(vtfile.c_str(), O_RDWR|O_CREAT, S_IRWXU);
        //vtf = fopen(vtfile.c_str(), "r+b");
    }
        
    assert(etf != -1);
    assert(vtf != -1);
}

void strkv_t::read_etable()
{
    /*
    off_t size = 0; //XXX fsize(etfile.c_str());
    if (size == -1L) {
        assert(0);
    }
    sid_t edge_count = size/sizeof(char);
    fread(log_beg, sizeof(char), edge_count, etf);

    log_head = edge_count;
    log_wpos = log_head;
    */
}

void strkv_t::read_vtable()
{
    //read etf
    off_t size = fsize(etf);
    if (size == -1L) { assert(0); }
    
    if (size != 0) {
        sid_t edge_count = size/sizeof(char);
        read(etf, log_beg, sizeof(char)*edge_count);

        log_head = edge_count;
        log_wpos = log_head;
    }
    
    //read vtf 
    size = fsize(vtf);
    if (size == -1L) { assert(0); }
    
    if (size != 0) {
        vid_t vcount = size/sizeof(sid_t);
        assert(vcount == g->get_type_vcount(tid));
        vid_t max_vcount = g->get_type_scount(tid);
        kv = (sid_t*)calloc(sizeof(sid_t), max_vcount);
        read(vtf, kv, sizeof(sid_t)*vcount);
    }

    /*
    off_t size = 0; //XXX fsize(vtfile.c_str());
    if (size == -1L) {
        assert(0);
    }
    vid_t count = (size/sizeof(disk_strkv_t));

    //read in batches
    while (count !=0) {
        vid_t read_count = fread(dvt, sizeof(disk_strkv_t), dvt_max_count, vtf);
        for (vid_t v = 0; v < read_count; ++v) {
            kv[dvt[v].vid] = log_beg + dvt[v].offset;
        }
        count -= read_count;
    }
    dvt_count = 0;
    */
}

void strkv_t::prep_str2sid(map<string, sid_t>& str2sid)
{
    
    char* type_name = 0;
    sid_t super_id = TO_SUPER(tid);
    vid_t v_count = g->get_type_vcount(tid);
    
    //create the str2vid now
    for (vid_t vid = 0; vid < v_count; ++vid) {
        type_name = log_beg + kv[vid];
        str2sid[type_name] = super_id + vid;
    }

    /*
    if (log_head == 0) return;
    string dst;
    sid_t sid = TO_THIGH(super_id);
    for(sid_t v = sid; v < super_id; ++v) {
        dst = kv[v - sid];
        str2sid[dst] = v;
    } */
}
