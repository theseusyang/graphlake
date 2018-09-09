#pragma once
#include <omp.h>
#include <algorithm>

#include "graph.h"
#include "wtime.h"

#include "sgraph.h"
//#include "p_sgraph.h"

typedef int cid_t;
class wcc_t {
  public:
    cid_t*  v_cid;
    cid_t*  c_cid;
    cid_t   c_count;
  public:
    wcc_t() {
        v_cid = 0;
        c_cid = 0;
        c_count = 0;
    }
};
const cid_t invalid_cid = -1;

template <class T>
void wcc_post_reg(sstream_t<T>* sstreamh, vid_t v_count) {
    wcc_t* wcc = new wcc_t();
    wcc->v_cid =  (cid_t*)calloc(v_count, sizeof(cid_t));
    wcc->c_cid =  (cid_t*)calloc(v_count, sizeof(cid_t));
    memset(wcc->v_cid, invalid_cid, sizeof(cid_t)*v_count);
    memset(wcc->c_cid, invalid_cid, sizeof(cid_t)*v_count);
    sstreamh->set_algometa(wcc);
} 

inline void map_cid(vid_t c1, vid_t c, cid_t* c_cid)
{
    c_cid[c1] = c;
}

template <class T>
void wcc_edge(vid_t v0, vid_t v1, wcc_t* wcc)
{
    cid_t c00, c11;
    cid_t c0 = wcc->v_cid[v0];
    cid_t c1 = wcc->v_cid[v1];
    int sw = (c0 != invalid_cid) + ((c1 != invalid_cid) << 1);
    cid_t m = 0;

    switch(sw) {
    case 0: //if ((c0 == invalid_cid) && (c1 == invalid_cid)) {
        m = __sync_fetch_and_add(&wcc->c_count, 1);
        wcc->v_cid[v1] = m;
        wcc->v_cid[v0] = m;
        map_cid(m, m, wcc->c_cid);
        //++t_front_count;
        break;
    case 1: //} else if(c1 == invalid_cid) {
        wcc->v_cid[v1] = c0;
        //++t_front_count;
        break;
    case 2: // } else if (c0 == invalid_cid) {
        wcc->v_cid[v0] = c1;
        //++t_front_count;
        break;
    case 3: // } else if (c0 != c1) {
        c00 = wcc->c_cid[wcc->v_cid[v0]];
        c11 = wcc->c_cid[wcc->v_cid[v1]];
        if (c00 < c11) {
            //if (cid[c1] == c1)
            wcc->v_cid[v1] = c00;
            map_cid(c1, c00, wcc->c_cid);
            //++t_front_count;
        } else if (c00 > c11) {
            //if (cid[c0] == c0)
            wcc->v_cid[v0] = c11;
            map_cid(c0, c11, wcc->c_cid);
            //++t_front_count;
        }
        break;
    default:
        assert(0);
    }
}

template <class T>
void wcc_finalize(sstream_t<T>* sstreamh)
{
    wcc_t* wcc = (wcc_t*)sstreamh->get_algometa();
    std::sort(wcc->c_cid, wcc->c_cid + wcc->c_count);
    
    cid_t tt;
    cid_t count = 0;
    
    #pragma omp parallel for reduction(+:count) private(tt)
    for(cid_t i = 1; i < wcc->c_count; ++i) {
        tt = wcc->c_cid[i- 1];
        count += (tt != wcc->c_cid[i]);
    }
    ++count;
    cout << "WCC count = " << count << endl;
    cout << "wcc_group used <debug> =" << wcc->c_count << endl;
}

template <class T>
void do_stream_wcc(sstream_t<T>* sstreamh)
{
    edgeT_t<sid_t>* edges = sstreamh->get_edges();
    index_t edge_count = sstreamh->get_edgecount();
    vid_t src, dst;
    
    wcc_t* wcc = (wcc_t*)sstreamh->get_algometa();

    for (index_t i = 0; i < edge_count; ++i) {
        src = edges[i].src_id;
        dst = get_dst(edges+i);
        wcc_edge<T>(src, dst, wcc);
    }
}
