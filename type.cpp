#include <assert.h>
#include "type.h"

void srset_t::bitwise2vlist()
{
    tid_t    iset_count = get_rset_count();
    for (tid_t i = 0; i < iset_count; ++i) {
        rset[i].bitwise2vlist();
    }
}

void rset_t::bitwise2vlist()
{
    uint64_t* barray  = get_barray();
    vid_t     w_count = get_wcount();

    vid_t   list_count = get_vcount();
    vid_t*  vid_list = (vid_t*)calloc(sizeof(vid_t), list_count);
    list_count = 0; 
        
    vid_t     word, base, frontier;
    tid_t     pos, count;
    
    //Get the frontiers
    for (vid_t w = 0; w < w_count; w++) {
        if ( 0 == barray[w]) continue;
        
        word  = barray[w];
        count = __builtin_popcountll(word);
        base  = (w << 6);

        for (tid_t j = 0; j < count; ++j) {
            pos = __builtin_ctzll(word);
            word  ^= (1L << pos);//reset that position
            frontier = pos + base;
            vid_list[list_count] = frontier;
            ++list_count;
        }
    }
    free(barray);
    vlist = vid_list;
    scount = TO_TID(scount) + list_count;
}

void rset_t::copy_setup(rset_t* iset, int union_type) 
{
    assert(eStatusarray != TO_TID(iset->count2));
    vid_t v_count = iset->get_vcount();
    scount = TO_TID(iset->scount) + v_count;
    count2 = TO_SUPER(union_type) + v_count;
    switch(union_type) {
    case eFrontiers:
        vlist = (vid_t*)calloc(sizeof(vid_t), v_count);
        break;
    case eAdjlist:
        adjlist = (beg_pos_t*)calloc(sizeof(beg_pos_t), v_count);
        break;
    case eKV:
        kv = (sid_t*)calloc(sizeof(sid_t), v_count);
        break;
    default:
    assert(0);
    }
}
