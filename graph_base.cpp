#include <assert.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "type.h"
#include "graph.h"

#ifdef B64
propid_t INVALID_PID = 0xFFFF;
tid_t    INVALID_TID  = 0xFFFFFFFF;
sid_t    INVALID_SID  = 0xFFFFFFFFFFFFFFFF;
#else 
propid_t INVALID_PID = 0xFF;
tid_t    INVALID_TID  = 0xFF;
sid_t    INVALID_SID  = 0xFFFFFFFF;
#endif

degree_t INVALID_DEGREE = 0xFFFFFFFF;

/*
void lite_skv_t::setup(tid_t tid)
{
    if (0 == super_id) {
        super_id = g->get_type_scount(tid);
        vid_t v_count = TO_VID(super_id);
        max_vcount = (v_count << 2);
        kv = (lite_edge_t*)calloc(sizeof(lite_edge_t), max_vcount);
    } else {
        super_id = g->get_type_scount(tid);
        vid_t v_count = TO_VID(super_id);
        if (max_vcount < v_count) {
            assert(0);
        }
    }
}

void lite_skv_t::persist_kvlog(const string& vtfile)
{
    //Make a copy
    sid_t count =  dvt_count;

    //update the mark
    dvt_count = 0;

    //Write the file
    if(vtf == 0) {
        vtf = fopen(vtfile.c_str(), "a+b");
        assert(vtf != 0);
    }
    fwrite(dvt, sizeof(disk_kvlite_t), count, vtf);
}

void lite_skv_t::read_kv(const string& vtfile)
{
    //Write the file
    if(vtf == 0) {
        vtf = fopen(vtfile.c_str(), "r+b");
        assert(vtf != 0);
    }

    off_t size = fsize(vtfile.c_str());
    if (size == -1L) {
        assert(0);
    }
    vid_t count = (size/sizeof(disk_kvlite_t));

    //read in batches
    while (count !=0) {
        vid_t read_count = fread(dvt, sizeof(disk_kvlite_t), dvt_max_count, vtf);
        for (vid_t v = 0; v < read_count; ++v) {
            kv[dvt[v].vid].first = dvt[v].dst;
            kv[dvt[v].vid].second = dvt[v].univ;
        }
        count -= read_count;
    }
    dvt_count = 0;
}
*/
