#pragma once

#include "graph.h"



//generic enum class
template <class T>
class enumkv_t : public pinfo_t 
{
  protected:
    lkv_t<T>* lkv_out; 
    lgraph_t* lgraph_in;
    
    //mapping between enum and string
    map<string, T> str2enum;
    char**      enum2str;
    T           ecount;
    T           max_count;

  public:
    void batch_update(const string& src, const string& dst);
    void make_graph_baseline();
    void store_graph_baseline(string dir);
};

template<class T>
void enumkv_t<T>::batch_update(const string& src, const string& dst)
{
    vid_t src_id;
    T     dst_id;
    index_t index = 0;
    edgeT_t<T>* edges = (edgeT_t<T>*) buf;

    map<string, vid_t>::iterator str2vid_iter = str2vid.find(src);
    if (str2vid.end() == str2vid_iter) {
        assert(0);
    } else {
        src_id = str2vid_iter->second;
    }
    
    tid_t type_id = TO_TYPE(src_id);
    flag1 |= (1L << type_id);

    map<string, T>::iterator str2enum_iter = str2enum.find(dst);
    if (str2enum.end() == str2enum_iter) {
        dst_id = ecount++;
        str2enum[dst] = dst_id;
        enum2str[dst_id] = gstrdup(dst.c_str());
    } else {
        dst_id = str2enum_iter->second;
    }

    index = count++;
    edges[index].src_id = src_id; 
    edges[index].dst_id = dst_id;
}

template<class T>
void enumkv_t<T>::make_graph_baseline()
{
    if (count == 0) return;

    vid_t src;
    T dst;
    edgeT_t<T>* edges = (edgeT_t<T>*) buf;
   
    flag1_count = __builtin_popcountll(flag1);
    
    //super bins memory allocation
    lkv_out  = prep_lkv(flag1, flag1_count);
    lgraph_in = prep_lgraph();    

    //estimate edge count
    calc_edge_count_kv(lgraph_in, edges, count);
    
    //prefix sum then reset the count
    prep_lgraph_internal(lgraph_in, count);
    
    //populate and get the original count back
    //handle kv_out as well.
    fill_adj_list_kv(skv_out, sgraph_in, flag1, flag2, buf, count);
}

//super bins memory allocation
template<class T>
lkv_t<T>* enumkv_t<T>::prep_lkv(sflag_t ori_flag, tid_t flag_count)
{
    sflag_t flag = ori_flag;
    lkv_t<T>*  lkv  = (lkv_t<T>*) calloc (sizeof(lkv_t<T>), flag_count);
    tid_t      pos  = 0;

    for(tid_t i = 0; i < flag_count; i++) {
        pos = __builtin_ctz(flag);
        flag ^= (1L << pos);//reset that position
        super_id = g->get_type_scount(pos);
        v_count = TO_VID(super_id);
        lkv[i].kv = (T*)calloc(sizeof(T), v_count);
        lkv[i].super_id = super_id;
    }
    return lkv;
}

template<class T>
beg_pos_t* enumkv_t<T>::prep_lgraph()
{
    beg_pos_t* lgraph  = (beg_pos_t*) calloc (sizeof(beg_pos_t), ecount);
    return lgraph;
}

template<class T>
void enumkv_t<T>::calc_edge_count_kv(beg_pos_t* lgraph_in, 
                            edgeT_t<T>* edges, index_t count)
{
    superid_t src;
    T  dst;
    
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        lgraph_in[dst].count  += 1;
    }
}

template<class T>
void enumkv_t<T>::prep_lgraph_internal(beg_pos_t* lgraph_in, 
                                            index_t edge_count)
{
    vid* adj_list = (vid_t*) calloc (sizeof(vid_t), edge_count);
    
    index_t     prefix = 0;
    beg_pos_t*  beg_pos = lgraph_in;
    vid_t       vcount = 0;
    
    for (vid_t j = 0; j < ecount1; ++j) {
        beg_pos[j].adj_list = adj_list + prefix;
        prefix += beg_pos[j].count;
        beg_pos[j].count = 0;
    }
}

template<class T>
void enumkv_t<T>::fill_adj_list_kv(lkv_t* lkv_out, beg_pos_t* lgraph_in, 
                             sflag_t flag1, edgeT_t<T>* edges, index_t count)
{
    superid_t src;
    T         dst;
    vid_t     vert1_id;
    tid_t     type1_id;
    sflag_t   flag1_mask;
    tid_t     src_index;
    beg_pos_t* beg_pos_in = lgraph_in;
    
    for (index_t i = 0; i < count; ++i) {
        src = edges[i].src_id;
        dst = edges[i].dst_id;
        
        vert1_id = TO_VID(src);
        type1_id = TO_TYPE(src) + 1;
        flag1_mask = flag1 & ( (1L << type1_id) - 1)
        src_index = __builtin_popcountll(flag1_mask);
        
        skv_out[src_index]->kv[vert1_id] = dst;
        
        beg_pos_in[dst]->adj_list[beg_pos_in->count++] = src;
    }
}

template<class T>
void enumkv_t<T>::store_lgraph(beg_pos_t* lgraph_in, 
                                    string dir, string postfix)
{
    //base name using relationship type
    string basefile = dir + p_name;
    string file = baseline + "beg_pos";
    FILE* f;
    
    /*
    string file = dir + p_name + ".beg_pos_in";
    FILE* f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(beg_pos_in, sizeof(index_t), vert_count + 1, f);
    fclose(f);
    
    file = dir + p_name + ".adj_list_in";
    f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(adj_list_in, sizeof(vid_t), beg_pos_in[vert_count], f);
    fclose(f);
    
    file = dir + p_name + ".kv_out";
    f = fopen(file.c_str(), "wb");
    assert(f != 0);
    fwrite(kv_out, sizeof(vid_t), vert_count, f);
    fclose(f);
    */
}

template<class T>
void enumkv_t<T>::store_lgraph(beg_pos_t* lgraph_in, 
                                    string dir, string postfix)
{
}

template<class T>
void enumkv_t<T>::store_graph_baseline(string dir)
{
    if (count == 0) return;
    store_lgraph(lgraph_in, dir, "in");
    
    store_lkv(lkv_out, dir, "out");
    
    //XXX writing enum mapping is pending
}

template <class T>
void enumkv_t<T>::init_enum(int enumcount)
{
    max_count = enumcount;
    ecount = 0;
    enum2str = new char*[enumcount];
}

template<class T>
void enumkv_t<T>::populate_enum(const char* e)
{
    vid_t id = ecount++;
    str2enum[e] = id;
    enum2str[id] = gstrdup(e);
}

template<class T>
enumkv_t<T>::enumkv_t()
{
    init_enum(256);
}

template <class T>
void typekv_t<T>::batch_update(const string& src, const string& dst)
{
    vid_t       src_id;
    tid_t       type_id;
    index_t     index = 0;
    vid_t       vert_id = 0;

    edgeT_t<T>* edges = (edgeT_t<T>*) buf;

    map<string, T>::iterator str2enum_iter = str2enum.find(dst);
    if (str2enum.end() == str2enum_iter) {
        type_id = ecount++;
        vert_id = TO_SUPER(type_id);
        str2enum[dst] = type_id;
        enum_info[type_id].vert_id = vert_id; 
        enum_info[type_id].type_name = gstrdup(dst.c_str());
    } else {
        type_id = str2enum_iter->second;
        vert_id = enum_info[type_id].vert_id;
    }

    //allocate class specific ids.
    map<string, vid_t>::iterator str2vid_iter = str2vid.find(src);
    if (str2vid.end() == str2vid_iter) {
        src_id = vert_id++;
        ++vert_count;
        str2vid[src] = src_id;
        //update the id
        enum_info[dst].vert_id = vert_id;
    } else {
        src_id = str2vid_iter->second;
    }

    index = count++;
    edges[index].src_id = src_id; 
    edges[index].dst_id = type_id;
}
