#include <assert.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <omp.h>
#include "type.h"
#include "graph.h"
#include "graph_base.h"

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



size_t io_driver::seq_read_aio(segment* seg, ext_vunit_t* ext_vunits)
{
    index_t ctx_count = seg->ctx_count;
    if (0 == ctx_count) return 0;
    
    uint32_t tid = omp_get_thread_num();
    index_t sz_to_read = BUF_SIZE;
    
    index_t disk_offset =  ext_vunits[seg->meta[0].vid].offset - (seg->meta[0].offset);
    cout << "Offset = " << disk_offset << endl;

    io_prep_pread(aio_meta[tid].cb_list[0], seg->etf,seg->buf, sz_to_read, disk_offset);
    int ret = io_submit(aio_meta[tid].ctx, 1, aio_meta[tid].cb_list);

    if (ret  != 1) {
        cout << ret << endl;
        perror("io_submit");
        assert(0);
    }
    aio_meta[tid].busy += 1;
    return 0;
}

int io_driver::wait_aio_completion()
{
    uint32_t tid = omp_get_thread_num();
    int ret = 0;
    if (aio_meta[tid].busy) {
        ret = io_getevents(aio_meta[tid].ctx, aio_meta[tid].busy, 
                           aio_meta[tid].busy, aio_meta[tid].events, 0);

        if (ret != aio_meta[tid].busy) {
            cout << aio_meta[tid].busy << " " << ret << endl;
            perror(" io_getevents");
        }
    }

    aio_meta[tid].busy = 0;
    return 0;
}

io_driver::io_driver()
{
    aio_meta = new aio_meta_t[IO_THDS];
    
    for (int j = 0; j < IO_THDS; ++j) {
        aio_meta[j].events = new struct io_event [AIO_MAXIO];
        aio_meta[j].cb_list = new struct iocb*[AIO_MAXIO];
        aio_meta[j].ctx = 0;
        for(index_t i = 0; i < AIO_MAXIO; ++i) {	
            aio_meta[j].cb_list[i] = new struct iocb;
        }
        if(io_setup(AIO_MAXIO, &aio_meta[j].ctx) < 0) {
            cout << AIO_MAXIO << endl;
            perror("io_setup");
            assert(0);
        }
        aio_meta[j].busy = 0;
    }
}

