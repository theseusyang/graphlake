
#pragma once
/**************** SKV ******************/
template <class T>
void onekv_t<T>::setup(tid_t tid)
{
    if (0 == super_id) {
        super_id = g->get_type_scount(tid);
        vid_t v_count = TO_VID(super_id);
        max_vcount = (v_count << 2);
        kv = (T*)calloc(sizeof(T), max_vcount);
    } else {
        super_id = g->get_type_scount(tid);
        vid_t v_count = TO_VID(super_id);
        if (max_vcount < v_count) {
            assert(0);
        }
    }
}

template <class T>
void onekv_t<T>::file_open(const string& vtfile, bool trunc)
{
    if(trunc) {
        //vtf = fopen(vtfile.c_str(), "wb");
		vtf = open(vtfile.c_str(), O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
        assert(vtf != 0);
    } else {
        //vtf = fopen(vtfile.c_str(), "r+b");
		vtf = open(vtfile.c_str(), O_RDWR|O_CREAT, S_IRWXU);
        assert(vtf != 0);
    }
}

template <class T>
void onekv_t<T>::persist_kvlog()
{
    //Make a copy
    sid_t count =  dvt_count;

    //update the mark
    dvt_count = 0;

    //Write the file
    //fwrite(dvt, sizeof(disk_kvT_t<T>), count, vtf);
    write(vtf, dvt, sizeof(disk_kvT_t<T>)*count);
}

template <class T>
void onekv_t<T>::read_kv()
{
    off_t size = fsize(vtf);
    if (size == -1L) {
        assert(0);
    }
    vid_t count = (size/sizeof(disk_kvT_t<T>));

    //read in batches
    while (count !=0) {
        //vid_t read_count = fread(dvt, sizeof(disk_kvT_t<T>), dvt_max_count, vtf);
        vid_t read_count = read(vtf, dvt, sizeof(disk_kvT_t<T>)*dvt_max_count);
        read_count /= sizeof(disk_kvT_t<T>);
        for (vid_t v = 0; v < read_count; ++v) {
            kv[dvt[v].vid] = dvt[v].dst;
        }
        count -= read_count;
    }
    dvt_count = 0;
}
