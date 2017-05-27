#include "mlabel.h"


void mkv_t::setup(tid_t tid)
{
    if ( 0 == super_id ) {
        super_id = g->get_type_scount(tid);
        vid_t v_count = TO_VID(super_id);
        max_vcount = (v_count << 1);
        kv = (kv_t*)calloc(sizeof(kv_t), max_vcount);
        nebr_count = (vid_t*)calloc(sizeof(vid_t), max_vcount);
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
    for (vid_t vid = 0; vid < v_count; ++vid) {
        kv[vid].setup(nebr_count[vid]);
        reset_count(vid);
    }
}

/*****************/
mkv_t** manykv_t::prep_mkv()
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
        if (0 == lkv_out[pos]) {
            mkv_out[pos] = new mkv_t;
        }
        mkv_out[pos]->setup(pos);
    }
    return mkv_out;
}

void manykv_t::make_graph_baseline()
{
}

status_t manykv_t::batch_update(const string& src, const string& dst, propid_t pid /*=0*/)
{
    return eOK;
}
