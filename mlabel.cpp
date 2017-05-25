#include "mlabel.h"

mkv_t** prep_mkv()
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
            mkv_out[pos]->setup(pos);
        }
    }
    return mkv_out;
}

