#include <getopt.h>
#include <iostream>
#include <dirent.h>

#include "all.h"
#include "csv_to_edge.h"
#include "iterative_analytics.h"
#include "ext_iterative_analytics.h"
#include "mem_iterative_analytics.h"
#include "snap_iterative_analytics.h"

using namespace std;

void prep_graph_sync(const string& idirname, const string& odirname);
    
extern index_t residue;
vid_t v_count = 0;


struct estimate_t {
    degree_t durable_degree;
    degree_t delta_degree;
    degree_t degree;
    degree_t space_left;
    //index_t  io_read;
    //index_t  io_write;
    int      chain_count;
    int16_t      type;
};

#define HUB_TYPE 1
#define HUB_COUNT 32768 

#define ALIGN_MASK_32B 0xFFFFFFFFFFFFFFF0
#define ALIGN_MASK_4KB 0xFFFFFFFFFFFFFC00
//#define UPPER_ALIGN_32B(x) (((x) + 16) & ALIGN_MASK_32B)
//16+4-1=19
#define UPPER_ALIGN_32B(x) (((x) + 19) & ALIGN_MASK_32B)
//1024+4-1=1027
#define UPPER_ALIGN_4KB(x) (((x) + 1027) & ALIGN_MASK_4KB)

template <class T>
void estimate_chain(const string& idirname, const string& odirname)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    
    struct dirent *ptr;
    DIR *dir;
    int file_count = 0;
    string filename;
    propid_t cf_id = g->get_cfid("friend");
    pgraph_t<T>* ugraph = (pgraph_t<sid_t>*)g->cf_info[cf_id];
        
    FILE* file = 0;
    index_t size =  0;
    index_t edge_count = 0;
    
    //Read graph files
    double start = mywtime();
    dir = opendir(idirname.c_str());
    blog_t<T>* blog = ugraph->blog;
    edgeT_t<T>* edge = blog->blog_beg;
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        filename = idirname + "/" + string(ptr->d_name);
        file_count++;
        
        file = fopen((idirname + "/" + string(ptr->d_name)).c_str(), "rb");
        assert(file != 0);
        size = fsize(filename);
        edge_count = size/sizeof(edge_t);
        edge = blog->blog_beg + blog->blog_head;
        if (edge_count != fread(edge, sizeof(edgeT_t<T>), edge_count, file)) {
            assert(0);
        }
        blog->blog_head += edge_count;
    }
    closedir(dir);
    double end = mywtime();
    cout << "Reading "  << file_count  << " file time = " << end - start << endl;
    start = mywtime();

    index_t marker = blog->blog_head ;
    cout << "End marker = " << blog->blog_head;
    cout << "make graph marker = " << marker << endl;
    if (marker == 0) return;
    
    edge = blog->blog_beg;
    estimate_t* est = (estimate_t*)calloc(sizeof(estimate_t), v_count);
    index_t last = 0;
    vid_t src = 0;
    vid_t dst = 0;

    index_t total_used_memory = 0;
    index_t total_chain = 0;
    int max_chain = 0;
    vid_t total_hub_vertex = 0;
    //index_t batching_size = 65536;
    index_t batching_size = marker;
    
    for (index_t i = 0; i < marker; i +=batching_size) {
        last = min(i + batching_size, marker);
        //do batching
        #pragma omp parallel for private(src, dst)
        for (index_t j = i; j < last; ++j) {
            src = edge[j].src_id;
            dst = edge[j].dst_id;
            est[src].degree++;
            est[dst].degree++;
        }

        index_t used_memory = 0;
        //Do memory allocation and cleaning
        #pragma omp parallel reduction(+:used_memory, total_chain) reduction(max:max_chain)
        {
        index_t  local_memory = 0;
        degree_t total_degree = 0;
        degree_t new_count = 0;
        #pragma omp for  
        for (vid_t vid = 0; vid < v_count; ++vid) {
            if (est[vid].degree == 0) continue;
            
            local_memory = est[vid].degree*sizeof(T) + 16;
            used_memory += local_memory;
            est[vid].chain_count++;
            max_chain = max(max_chain, est[vid].chain_count);
            total_chain++;
            est[vid].delta_degree += est[vid].degree;
            est[vid].degree = 0;
        }
        }
        total_used_memory += used_memory;
    }

    end = mywtime ();
    cout << "Used Memory = " << total_used_memory << endl;
    cout << "Make graph time = " << end - start << endl;
    cout << "total_hub_vertex =" << total_hub_vertex << endl;
    cout << "total_chain_count =" << total_chain << endl;
    cout << "max_chain =" << max_chain << endl;

    /*
    degree_t* degree = (degree_t*)calloc(sizeof(degree),v_count);
    
    #pragma omp parallel for
    for (vid_t vid = 0; vid < v_count; ++vid) {
        degree[vid] = est[vid].delta_degree;
    }
    sort(degree, degree + v_count);
    
    for (vid_t vid = 0; vid < v_count; ++vid) {
        cerr << vid <<"  " << degree[vid] << endl;
    }
    */

}

//estimate the IO read and Write amount and number of chains
template <class T>
void estimate_chain_new(const string& idirname, const string& odirname)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    
    struct dirent *ptr;
    DIR *dir;
    int file_count = 0;
    string filename;
    propid_t cf_id = g->get_cfid("friend");
    pgraph_t<T>* ugraph = (pgraph_t<sid_t>*)g->cf_info[cf_id];
        
    FILE* file = 0;
    index_t size =  0;
    index_t edge_count = 0;
    
    //Read graph files
    double start = mywtime();
    dir = opendir(idirname.c_str());
    blog_t<T>* blog = ugraph->blog;
    edgeT_t<T>* edge = blog->blog_beg;
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        filename = idirname + "/" + string(ptr->d_name);
        file_count++;
        
        file = fopen((idirname + "/" + string(ptr->d_name)).c_str(), "rb");
        assert(file != 0);
        size = fsize(filename);
        edge_count = size/sizeof(edge_t);
        edge = blog->blog_beg + blog->blog_head;
        if (edge_count != fread(edge, sizeof(edgeT_t<T>), edge_count, file)) {
            assert(0);
        }
        blog->blog_head += edge_count;
    }
    closedir(dir);
    double end = mywtime();
    cout << "Reading "  << file_count  << " file time = " << end - start << endl;
    start = mywtime();

    index_t marker = blog->blog_head ;
    cout << "End marker = " << blog->blog_head;
    cout << "make graph marker = " << marker << endl;
    if (marker == 0) return;
    
    edge = blog->blog_beg;
    estimate_t* est = (estimate_t*)calloc(sizeof(estimate_t), v_count);
    index_t last = 0;
    vid_t src = 0;
    vid_t dst = 0;

    index_t total_used_memory = 0;
    index_t total_chain = 0;
    int max_chain = 0;
    vid_t total_hub_vertex = 0;

    
    for (index_t i = 0; i < marker; i +=65536) {
        last = min(i + 65536, marker);
        //do batching
        #pragma omp parallel for private(src, dst)
        for (index_t j = i; j < last; ++j) {
            src = edge[j].src_id;
            dst = edge[j].dst_id;
            est[src].degree++;
            est[dst].degree++;
        }
        index_t used_memory = 0;

        //Do memory allocation and cleaning
        #pragma omp parallel reduction(+:used_memory, total_chain) reduction(max:max_chain)
        {
        index_t  local_memory = 0;
        degree_t total_degree = 0;
        degree_t new_count = 0;
        #pragma omp for  
        for (vid_t vid = 0; vid < v_count; ++vid) {
            if (est[vid].degree == 0) continue;
            
            //---------------
            total_degree = est[vid].delta_degree + est[vid].degree;
            //Embedded case only
            //if (false)
            if (total_degree <= 5) {
                est[vid].delta_degree += est[vid].degree;
                est[vid].degree = 0;
                continue;
            } else if (est[vid].delta_degree <= 5) {//total > 5
                local_memory = UPPER_ALIGN_32B(total_degree);
                
                est[vid].chain_count = 1;
                total_chain++;
                est[vid].space_left = local_memory - total_degree - 4;
                est[vid].delta_degree += est[vid].degree;
                used_memory += local_memory*sizeof(T);
                est[vid].degree = 0;
                continue;
            }
            //----embedded case ends

            //At least 0th chain exists or will be created
            if (est[vid].degree <= est[vid].space_left) {
                est[vid].space_left -= est[vid].degree; 
                est[vid].delta_degree += est[vid].degree;
                est[vid].degree = 0;
            //------hub vertices case
            } else if (total_degree >= 8192) {
                new_count = est[vid].degree - est[vid].space_left;
                local_memory = UPPER_ALIGN_4KB(new_count);
                
                est[vid].chain_count++;
                max_chain = max(max_chain, est[vid].chain_count);
                total_chain++;
                est[vid].space_left = local_memory - new_count - 4;
                est[vid].delta_degree += est[vid].degree;
                used_memory += local_memory*sizeof(T);
                est[vid].degree = 0;
            //------
            } else {
                new_count = est[vid].degree - est[vid].space_left;
                local_memory = UPPER_ALIGN_32B(new_count) ;
                
                est[vid].chain_count++;
                max_chain = max(max_chain, est[vid].chain_count);
                total_chain++;
                est[vid].space_left = local_memory - new_count - 4;
                est[vid].delta_degree += est[vid].degree;
                used_memory += local_memory*sizeof(T);
                est[vid].degree = 0;     
            }
        }
        }
        total_used_memory += used_memory;
    }

    end = mywtime ();
    cout << "Used Memory = " << total_used_memory << endl;
    cout << "Make graph time = " << end - start << endl;
    cout << "total_hub_vertex =" << total_hub_vertex << endl;
    cout << "total_chain_count =" << total_chain << endl;
    cout << "max_chain =" << max_chain << endl;
}

//estimate the IO read and Write amount and number of chains
template <class T>
void estimate_IO(const string& idirname, const string& odirname)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    
    struct dirent *ptr;
    DIR *dir;
    int file_count = 0;
    string filename;
    propid_t cf_id = g->get_cfid("friend");
    pgraph_t<T>* ugraph = (pgraph_t<sid_t>*)g->cf_info[cf_id];
        
    FILE* file = 0;
    index_t size =  0;
    index_t edge_count = 0;
    
    
    //Read graph files
    double start = mywtime();
    dir = opendir(idirname.c_str());
    blog_t<T>* blog = ugraph->blog;
    edgeT_t<T>* edge = blog->blog_beg;
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        filename = idirname + "/" + string(ptr->d_name);
        file_count++;
        
        file = fopen((idirname + "/" + string(ptr->d_name)).c_str(), "rb");
        assert(file != 0);
        size = fsize(filename);
        edge_count = size/sizeof(edge_t);
        edge = blog->blog_beg + blog->blog_head;
        if (edge_count != fread(edge, sizeof(edgeT_t<T>), edge_count, file)) {
            assert(0);
        }
        blog->blog_head += edge_count;
    }
    closedir(dir);
    double end = mywtime();
    cout << "Reading "  << file_count  << " file time = " << end - start << endl;
    start = mywtime();

    index_t marker = blog->blog_head ;
    cout << "End marker = " << blog->blog_head;
    cout << "make graph marker = " << marker << endl;
    if (marker == 0) return;
    
    edge = blog->blog_beg;
    estimate_t* est = (estimate_t*)calloc(sizeof(estimate_t), v_count);
    index_t last = 0;
    vid_t src = 0;
    vid_t dst = 0;

    index_t total_memory = (1L<<30L);//4GB
    index_t free_memory = 0;
    index_t cut_off = (4 << 20); //16MB
    index_t cut_off2 = (64 << 20); //256MB
    index_t wbuf_count = (21); //32MB
    index_t total_used_memory = 0;

    cout << "allocating " << total_memory << endl;
    
    index_t total_io_read = 0;
    index_t total_io_write = 0;
    index_t total_io_write_count = 0;
    index_t total_io_read_count = 0;

    vid_t total_hub_vertex = 0;

    
    for (index_t i = 0; i < marker; i +=65536) {
        last = min(i + 65536, marker);
        //do batching
        for (index_t j = i; j < last; ++j) {
            src = edge[j].src_id;
            dst = edge[j].dst_id;
            est[src].degree++;
            est[dst].degree++;
        }
        index_t used_memory = 0;

        //Do memory allocation and cleaning
        #pragma omp parallel reduction(+:used_memory) 
        {
        index_t  local_memory = 0;
        degree_t total_degree = 0;
        degree_t new_count = 0;
        #pragma omp for  
        for (vid_t vid = 0; vid < v_count; ++vid) {
            if (est[vid].degree == 0) continue;
            total_degree = est[vid].delta_degree + est[vid].degree;
            //---------------
            
            if (est[vid].durable_degree == 0) {
              if (total_degree <=7) {
                est[vid].delta_degree += est[vid].degree;
                est[vid].degree = 0;
                continue;
              } else if (est[vid].delta_degree <= 7){
                  local_memory += est[vid].delta_degree;
              }
            }
            local_memory = est[vid].degree + 1;
            used_memory += local_memory;
            est[vid].chain_count++;
            est[vid].delta_degree += est[vid].degree;
            est[vid].degree = 0;
            
            //---------------
            /*
            //Embedded case only
            //if (false)
            if (est[vid].durable_degree == 0) 
            {
                if (total_degree <= 7) {
                    est[vid].delta_degree += est[vid].degree;
                    est[vid].degree = 0;
                    continue;
                } else if (est[vid].delta_degree <= 7) {//total > 7
                    local_memory = UPPER_ALIGN_32B(total_degree + 1);
                    used_memory += local_memory;
                    
                    est[vid].chain_count = 1;
                    est[vid].space_left = local_memory - total_degree - 1;
                    est[vid].delta_degree += est[vid].degree;
                    est[vid].degree = 0;
                    continue;
                }
            }
            

            //At least 0th chain exists or will be created
            if (est[vid].degree <= est[vid].space_left) {
                est[vid].space_left -= est[vid].degree; 
                est[vid].delta_degree += est[vid].degree;
                est[vid].degree = 0;
            } else {
                new_count = est[vid].degree - est[vid].space_left;
                local_memory = UPPER_ALIGN_32B(new_count + 1) ;
                used_memory += local_memory;
                
                est[vid].chain_count++;
                est[vid].space_left = local_memory - new_count - 1;
                est[vid].delta_degree += est[vid].degree;
                est[vid].degree = 0;     
            }
            */
        }
        }
        total_used_memory += used_memory;
        free_memory = total_memory - total_used_memory; //edge count not bytes
        
        //Do durable phase
        if (free_memory > cut_off) {
            continue;
        }

        end = mywtime ();
        cout << "Total used Memory = " << total_used_memory << endl;
        cout << "time = " << end - start << endl;
        
        index_t total_chain_count = 0; 
        int max_chain = 0;
        const int chain = 64;
        index_t total_free_i[chain];
        memset(total_free_i, 0, sizeof(index_t)*chain);
        
        #pragma omp parallel 
        {
            index_t free_i[chain];
            int chain_count = 0;
            memset(free_i, 0, sizeof(index_t)*chain);

            #pragma omp for reduction(+:total_chain_count) reduction(max:max_chain)
            for (vid_t vid = 0; vid < v_count; ++vid) {
                chain_count = est[vid].chain_count;
                max_chain = std::max(chain_count, max_chain);
                total_chain_count += chain_count; 
                if (chain_count < chain) {
                    free_i[chain_count] += est[vid].delta_degree + est[vid].space_left
                                         + chain_count;
                } else {
                    free_i[chain - 1] += est[vid].delta_degree + est[vid].space_left
                                         + chain_count;
                }
            }
            for (int i = 0; i < chain; ++i) {
                __sync_fetch_and_add(total_free_i + i, free_i[i]);
            }
        }
        int freed_memory = 0;
        int freed_chain = 0;
        //----------
        freed_memory= total_used_memory;
        //----------
        /*
        for (int i = chain - 1; i >= freed_chain; --i) {
            freed_memory += total_free_i[i];
        }
        */
        //----------
        /*
        for (int i = chain - 1; i >= 0; --i) {
            freed_memory += total_free_i[i];
            if (freed_memory + free_memory >= cut_off2) {
                freed_chain = i;
                break;
            }
        }*/
        
        cout << "i = " << i;
        cout << " total chain count = " << total_chain_count 
             << " max_chain = " << max_chain << endl;
        cout << "available free = " << free_memory;
        cout << " freeing memory = " << freed_chain << " " << freed_memory << endl;
        
        total_used_memory -= freed_memory;
        
        index_t io_read = 0;
        index_t io_write = 0;
        index_t io_write_count = 0;
        index_t io_read_count = 0;
        vid_t hub_vertex = 0;

        #pragma omp parallel for reduction(+:io_read,io_read_count,io_write,hub_vertex)
        for (vid_t vid = 0; vid < v_count; ++vid) {
            if (est[vid].chain_count < freed_chain) continue;
            
            if (est[vid].durable_degree !=0 && est[vid].type != HUB_TYPE) {
                io_read += est[vid].durable_degree + 2;
                io_read_count++;
                /*
                if (est[vid].durable_degree + est[vid].delta_degree >= HUB_COUNT) {
                    est[vid].type = HUB_TYPE;
                    io_write += est[vid].durable_degree;
                    ++hub_vertex;
                }*/
            }
            if (est[vid].type == HUB_TYPE) {
                io_write += est[vid].delta_degree; 
            } else {
                io_write += est[vid].delta_degree + est[vid].durable_degree + 2; 
            }

            est[vid].durable_degree += est[vid].delta_degree;
            est[vid].space_left = 0;
            est[vid].delta_degree = 0;
            est[vid].chain_count = 0;
        }
        io_write_count = (io_write >> wbuf_count);
        if (io_write_count == 0) io_write_count = 1;
        
        total_io_read += io_read;
        total_io_read_count += io_read_count;
        total_io_write += io_write;
        total_io_write_count += io_write_count; 
        
        total_hub_vertex += hub_vertex;
        hub_vertex = 0;
        
        end = mywtime ();
        cout << "total_io_read =" << total_io_read << endl; 
        cout << "total_io_read_count =" << total_io_read_count << endl; 
        cout << "total_io_write =" << total_io_write << endl; 
        cout << "total_io_write_count =" << total_io_write_count << endl; 
        cout << "Make graph time = " << end - start << endl;
    }

    end = mywtime ();
    cout << "Used Memory = " << total_used_memory << endl;
    cout << "Make graph time = " << end - start << endl;
    cout << "total_io_read =" << total_io_read << endl; 
    cout << "total_io_read_count =" << total_io_read_count << endl; 
    cout << "total_io_write =" << total_io_write << endl; 
    cout << "total_io_write_count =" << total_io_write_count << endl; 
    cout << "total_hub_vertex =" << total_hub_vertex << endl;
}


template <class T>
void split_graph(const string& idirname, const string& odirname)
{
    
    struct dirent *ptr;
    DIR *dir;
    int file_count = 0;
    string filename;
        
    FILE* file = 0;
    index_t size =  0;
    index_t edge_count = 0;

    blog_t<T> my_blog; 
    blog_t<T>* blog = &my_blog;
    memset(blog, 0, sizeof(my_blog));
    blog->blog_beg = (edgeT_t<T>*) calloc((1L<<33), sizeof(edgeT_t<T>)); 
    
    //Read graph files
    double start = mywtime();
    dir = opendir(idirname.c_str());
    edgeT_t<T>* edge = blog->blog_beg;
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        filename = idirname + "/" + string(ptr->d_name);
        file_count++;
        
        file = fopen((idirname + "/" + string(ptr->d_name)).c_str(), "rb");
        assert(file != 0);
        size = fsize(filename);
        edge_count = size/sizeof(edgeT_t<T>);
        edge = blog->blog_beg + blog->blog_head;
        if (edge_count != fread(edge, sizeof(edgeT_t<T>), edge_count, file)) {
            assert(0);
        }
        blog->blog_head += edge_count;
        fclose(file);
    }
    closedir(dir);
    double end = mywtime();
    cout << "Reading "  << file_count  << " file time = " << end - start << endl;
    cout << "Creating " << residue << " graphs of equal size" << endl;

    start = mywtime();

    index_t marker = blog->blog_head/residue;
    index_t old_marker = 0;
    index_t new_marker = 0;
    char  suffix[8];
    for (index_t i = 1; i <= residue; ++i) {
        sprintf(suffix, "%ld",i);
          
        new_marker = marker*i;
        cout << "graph marker = " << new_marker << endl;
        filename = odirname + "part" + suffix + ".dat";
        cout << "Filename = " << filename << endl;
        file = fopen(filename.c_str(), "wb");
        assert(file  != 0);
        edge_count = new_marker - old_marker;
        if (edge_count != fwrite(blog->blog_beg + old_marker, 
                                 sizeof(edgeT_t<T>), edge_count, file)) {
            assert(0);
        }
        fclose(file);
        old_marker = new_marker;
    }

    end = mywtime ();
    cout << "Make graph time = " << end - start << endl;
}

void plain_test0(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    prep_graph_sync(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    onegraph_t<sid_t>*   sgraph = ugraph->sgraph[0];
    vert_table_t<sid_t>* graph = sgraph->get_begpos();
    blog_t<sid_t>* blog = ugraph->blog;
   
    uint8_t* level_array = (uint8_t*)mmap(NULL, sizeof(uint8_t)*v_count, 
                            PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0 );
    
    if (MAP_FAILED == level_array) {
        cout << "Huge page alloc failed for level array" << endl;
        level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    }
    
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array = 0;
        
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));

    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    ext_bfs<sid_t>(sgraph, degree_array, sgraph, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    
    return;
}

void plaind_test0(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraphd();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    prep_graph_sync(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    pgraph_t<sid_t>* pgraph = (pgraph_t<sid_t>*)g->cf_info[cf_id];
    onegraph_t<sid_t>* sgraph_out = pgraph->sgraph_out[0];
    onegraph_t<sid_t>* sgraph_in  = pgraph->sgraph_in[0];
    blog_t<sid_t>* blog = pgraph->blog;
   
    uint8_t* level_array = (uint8_t*)mmap(NULL, sizeof(uint8_t)*v_count,
                            PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0 );
    
    if (MAP_FAILED == level_array) {
        cout << "Huge page alloc failed for level array" << endl;
        level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    }
    
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_out = 0;
    degree_t* degree_in = 0;

    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnapd (sgraph_out, sgraph_in, snapshot, marker, blog->blog_beg,
                            degree_out, degree_in);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;


    ext_bfs<sid_t>(sgraph_out, degree_out, sgraph_in, degree_in, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    return ;
}
            
void weight_dtest0(const string& idir, const string& odir)
{
    plaingraph_manager::schema_weightedgraphd();
    plaingraph_manager::setup_weightedgraph(v_count);    
}

void weight_dtest1(const string& odir)
{
    plaingraph_manager::schema_weightedgraphu();
    plaingraph_manager::setup_weightedgraph(v_count);    
}

//template <class T>
void weighted_dtest0(const string& idir, const string& odir)
{
    
    plaingraph_manager::schema_weightedgraphu();
    
    //Is called from below function
    //plaingraph_manager::setup_weightedgraph(v_count);    
    
    //string graph_file = idir + "g.bin";
    //string action_file = idir + "a.bin"; 
    string graph_file = idir + "small_basegraph";
    string action_file = idir + "small_action"; 
    //plaingraph_manager::prep_weighted_rmat(graph_file, action_file);
    
    int fd = open(graph_file.c_str(), O_RDONLY);
    assert(fd != -1);
    index_t size = fsize(fd);
    int64_t* buf = (int64_t*)malloc(size);
    pread(fd, buf, size, 0);
    int64_t little_endian = buf[0];
    assert(little_endian == 0x1234ABCD);

    int64_t nv = buf[1]; 
    int64_t ne = buf[2];
    int64_t* v_offset = buf + 3;
    int64_t* index = v_offset + nv + 1; //+1 for offset in CSR 
    int64_t* weight = index + ne;
    lite_edge_t* nebrs = (lite_edge_t*)malloc(ne*sizeof(lite_edge_t));

    for (int64_t i = 0; i < ne; i++) {
        nebrs[i].first = index[i];
        nebrs[i].second.value = weight[i];  
    }

    //Create number of vertex
    v_count = nv;
    plaingraph_manager::setup_weightedgraph(v_count);
    
    //Do ingestion
    /*
     * We are doing something to be compliant with stinger test
     * 1. the graph file is CSR file, we don't expect that
     * 2. The graph already stores the reverse edge, we don't expect that
     * 3. Stinger does something directly with the memory that is allocated 
     *      for graph read, for initial graph building.
     */
    propid_t cf_id = g->get_cfid("friend");
    pgraph_t<lite_edge_t>*    graph = (pgraph_t<lite_edge_t>*)g->cf_info[cf_id];
    blog_t<lite_edge_t>*       blog = graph->blog;
    onegraph_t<lite_edge_t>* sgraph = graph->sgraph[0];
    nebrcount_t<lite_edge_t>* degree_array = sgraph->nebr_count;
    
    double start = mywtime();
    
    #pragma omp parallel
    {
        index_t   nebr_count = 0;
        
        #pragma omp for
        for (int64_t v = 0; v < nv; ++v) {
            nebr_count = v_offset[v+1] - v_offset[v];
            degree_array[v].add_count = nebr_count;
        }
        sgraph->setup_adjlist();
        /*
        //-------------
        vid_t  total_thds  = omp_get_num_threads();
        vid_t         tid  = omp_get_thread_num();  
        
        vid_t portion = nv/total_thds;
        vid_t vid_start = portion*tid;
        vid_t vid_end   = portion*(tid + 1);
        if (tid == total_thds - 1) {
            vid_end = v_count;
        }
        
        sgraph->setup_adjlist_noatomic(vid_start, vid_end);
        */
        #pragma omp barrier
        //--------------
        
        #pragma omp for
        for (int64_t v = 0; v < nv; ++v) {
            nebr_count = v_offset[v+1] - v_offset[v];
            if (nebr_count) {
                sgraph->add_nebr_bulk(v, nebrs + v_offset[v], nebr_count);
            }
        }
    }
    
    double end = mywtime();
    
    blog->blog_head += ne;
    index_t marker = blog->blog_head;
    index_t snap_marker = 0;
    if (marker == 0) return;

    graph->create_marker(marker);
    if (eOK == graph->move_marker(snap_marker)) {
        blog->blog_tail = marker;
        //graph->make_graph_baseline();
        //graph->store_graph_baseline();
        g->incr_snapid(snap_marker, snap_marker);
    }
    cout << "Batch time = " << end - start << endl;
    end = mywtime();
    cout << "make graph marker = " << marker << endl;
    cout << "Make graph time = " << end - start << endl;

    free(buf);
    free(nebrs);

    //-------Run bfs and PR------
    uint8_t* level_array = 0;
    level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    
    /*
    level_array = (uint8_t*)mmap(NULL, sizeof(uint8_t)*v_count, 
                            PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0 );
    
    if (MAP_FAILED == level_array) {
        cout << "Huge page alloc failed for level array" << endl;
        level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    }*/
    
    
    vert_table_t<lite_edge_t>* beg_pos = sgraph->get_begpos();
    degree_t* degree_snap = 0;
    degree_snap = (degree_t*) calloc(v_count, sizeof(degree_t));

    index_t old_marker = 0;
    snapshot_t* snapshot = g->get_snapshot();
    marker = blog->blog_head;
    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnap(beg_pos, v_count, snapshot, marker, blog->blog_beg, degree_snap);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;
    
    mem_bfs<lite_edge_t>(beg_pos, degree_snap, beg_pos, degree_snap, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 0);
  
    mem_pagerank_epsilon<lite_edge_t>(beg_pos, degree_snap, degree_snap, 
                   snapshot, marker, blog->blog_beg,
                   v_count, 1e-8);

    free(degree_snap);
    free(level_array);
    
    //----
    //graph->store_graph_baseline();
    //----


    //-------Graph Updates-------
    g->create_snapthread();
    g->create_wthread();

    usleep(1000);
    int fd1 = open(action_file.c_str(), O_RDONLY);
    assert(fd1 != -1);
    index_t size1 = fsize(fd1);
    int64_t* buf1 = (int64_t*)malloc(size1);
    pread(fd1, buf1, size1, 0);
    int64_t little_endian1 = buf1[0];
    assert(little_endian1 == 0x1234ABCD);

    int64_t na = buf1[1];
    edge_t* edges = (edge_t*)(buf1 + 2);

    //Do ingestion
    start = mywtime();
    int64_t del_count = 0;
    
    //#pragma omp parallel 
    { 
    int64_t src, dst;
    edgeT_t<lite_edge_t> edge;

    //#pragma omp for reduction(+:del_count)
    for (int64_t i = 0; i < na; i++) {
        src = edges[i].src_id;
        edge.dst_id.second.value = 1;
        dst = edges[i].dst_id;
        if (src >= 0) {
            edge.src_id = src;
            edge.dst_id.first = dst;
            graph->batch_edge(edge);
        } else {
            edge.src_id = DEL_SID(-src);
            edge.dst_id.first = DEL_SID(-dst);
            graph->batch_edge(edge);
            ++del_count;
        }
    }
    }
    
    end = mywtime();
    
    marker = blog->blog_head;
    if (marker != blog->blog_marker) {
        graph->create_marker(marker);
    }
    
    //if (eOK == graph->move_marker(snap_marker)) {
        //graph->make_graph_baseline();
        //graph->store_graph_baseline();
        //g->incr_snapid(snap_marker, snap_marker);
    //}
    cout << "batch Edge time = " << end - start << endl;
    cout << "no of actions " << na << endl;
    cout << "del_count "<<del_count << endl;
    while (blog->blog_tail != blog->blog_head) {
        usleep(10);
    }
    usleep(100000);
    //----
    //graph->store_graph_baseline();
    //----
    end = mywtime();
    cout << "Make graph time = " << end - start << endl;
    

    //-------Run bfs and PR------
    /*
    level_array = (uint8_t*)mmap(NULL, sizeof(uint8_t)*v_count, 
                            PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0 );
    
    if (MAP_FAILED == level_array) {
        cout << "Huge page alloc failed for level array" << endl;
        level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    }
    
    degree_snap = (degree_t*) calloc(v_count, sizeof(degree_t));

    snapshot = g->get_snapshot();
    marker = blog->blog_head;
    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnap(beg_pos, v_count, snapshot, marker, blog->blog_beg, degree_snap);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;
    
    mem_bfs<lite_edge_t>(beg_pos, degree_snap, beg_pos, degree_snap, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 0);
    
    mem_pagerank_epsilon<lite_edge_t>(beg_pos, degree_snap, degree_snap, 
                   snapshot, marker, blog->blog_beg,
                   v_count, 1e-8);

    free(degree_snap);
*/

    return ;
}

void plain_test1(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    blog_t<sid_t>* blog = ugraph->blog;
    cout << "snapshot id = " << g->get_snapid() << endl;
    snapshot_t* snapshot = g->get_snapshot();
    //bfs<sid_t>(ugraph->sgraph, ugraph->sgraph, 1); 
    
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    
    string idir1 = "/mnt/disk_huge_1/pradeepk/pradeep_graph/kron_21_16_incr/"; 
    //string idir1 = "../data/kron_21_16_incr/"; 
    plaingraph_manager::prep_graph(idir1, odir);
    
    snapid_t snap_id = g->get_snapid(); 
    uint8_t* level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    /*
    cout << "BFS on whole graph" << endl; 
    bfs<sid_t>(ugraph->sgraph, ugraph->sgraph, 1); 
    
    
    //memset(level_array, 0, v_count*sizeof(uint8_t));
    cout << "BFS on snap id = " << snap_id << endl; 
    snap_bfs<sid_t>(graph, graph, v_count, edge_count, level_array, snap_id - 1, 1);
    

    cout << "multi-snap BFS" << endl;
    multisnap_bfs<sid_t>(graph, graph, v_count, edge_count, snap_id - 1, snap_id , 1);
    */
    memset(level_array, 0, v_count*sizeof(uint8_t));
    snapshot_t* old_snapshot = snapshot;
    snapshot = g->get_snapshot();
    index_t marker = snapshot->marker;
    
    snap_id = old_snapshot->snap_id;
    degree_t* degree_array = 0; 
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));
    create_degreesnap(graph, v_count, old_snapshot, old_snapshot->marker, blog->blog_beg, degree_array);
    
    cout << "BFS on snap id = " << snap_id << endl; 
    cout << "old marker = " << old_snapshot->marker << " New marker = " << marker << endl;
    mem_bfs<sid_t>(graph, degree_array, graph, degree_array, 
                   old_snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    
    /*
    memset(level_array, 0, v_count*sizeof(uint8_t));
    
    old_snapshot = snapshot;
    snapshot = g->get_snapshot();
    marker = snapshot->marker;
    snap_id = old_snapshot->snap_id;
    degree_array = create_degreesnap(graph, v_count, snap_id);
    cout << "BFS on snap id = " << snap_id << endl; 
    cout << "old marker = " << old_snapshot->marker << " New marker = " << marker << endl;
    mem_bfs<sid_t>(graph, degree_array, graph, degree_array, 
                   old_snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    
    memset(level_array, 0, v_count*sizeof(uint8_t));
    old_snapshot = snapshot;
    marker = snapshot->marker;
    snap_id = old_snapshot->snap_id;
    degree_array = create_degreesnap(graph, v_count, snap_id);
    cout << "BFS on snap id = " << snap_id << endl; 
    cout << "old marker = " << old_snapshot->marker << " New marker = " << marker << endl;
    mem_bfs<sid_t>(graph, degree_array, graph, degree_array, 
                   old_snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    
    */
    /*
    memset(level_array, 0, v_count*sizeof(uint8_t));
    cout << "BFS on first snapshot" << endl; 
    snap_bfs<sid_t>(graph, graph, v_count, edge_count, level_array, snap_id, 1);
    */
    return ;
}

void plaind_test1(const string& odir)
{
    plaingraph_manager::schema_plaingraphd();
    //do some setup for plain graphs
    //plaingraph_manager::setup_graph(v_count);    
    propid_t cf_id = g->get_cfid("friend");
    pgraph_t<sid_t>* pgraph = (pgraph_t<sid_t>*)g->cf_info[cf_id];
    pgraph->flag1 = 1;
    pgraph->flag2 = 1;
    
    g->read_graph_baseline();
   
    onegraph_t<sid_t>* sgraph_out = pgraph->sgraph_out[0];
    onegraph_t<sid_t>* sgraph_in  = pgraph->sgraph_in[0];
    blog_t<sid_t>* blog = pgraph->blog;
   
    uint8_t* level_array = (uint8_t*)mmap(NULL, sizeof(uint8_t)*v_count, 
                            PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0 );
    if (MAP_FAILED == level_array) {
        cout << "Huge page alloc failed for level array" << endl;
        level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    }

    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_out = 0;
    degree_t* degree_in  = 0;

    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnapd(sgraph_out, sgraph_in, snapshot, marker, blog->blog_beg,
                           degree_out, degree_in);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    ext_bfs<sid_t>(sgraph_out, degree_out, sgraph_in, degree_in, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    
    return ;
}

void plain_test2(const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    //plaingraph_manager::setup_graph(v_count);    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    ugraph->flag1 = 1;
    ugraph->flag2 = 1;
    
    g->read_graph_baseline();
   
/*
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];*/
    onegraph_t<sid_t>* sgraph = ugraph->sgraph[0];
    vert_table_t<sid_t>* graph = sgraph->get_begpos();
    blog_t<sid_t>* blog = ugraph->blog;
   
    uint8_t* level_array = (uint8_t*)mmap(NULL, sizeof(uint8_t)*v_count, 
                            PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0 );
    if (MAP_FAILED == level_array) {
        cout << "Huge page alloc failed for level array" << endl;
        level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    }

    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array = 0;
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));

    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    ext_bfs<sid_t>(sgraph, degree_array, sgraph, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    
/*
    index_t edge_count = (v_count << 5);
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    bfs<sid_t>(ugraph->sgraph, ugraph->sgraph, 1); 
    
    snapid_t snap_id = g->get_snapid();
    cout << "multi-snap BFS" << endl;
    cout << "snap id = " << snap_id << endl;
    cout << "durable marker = " <<g->get_snapshot()->durable_marker << endl;
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    multisnap_bfs<sid_t>(graph, graph, v_count, edge_count, snap_id - 1, snap_id , 1);
    
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = snapshot->marker;
    snapshot = snapshot->next;
    snap_id = snapshot->snap_id;
    uint8_t* level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    cout << "BFS on snap id = " << snap_id << endl; 
    cout << "old marker = " << snapshot->marker << " New marker = " << marker << endl;
    degree_t* degree_array = create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg);
    mem_bfs<sid_t>(graph, degree_array, graph, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
*/
    return ;
}

void plain_test3(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph_paper_chain(idir, odir);
    //plaingraph_manager::prep_graph(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    verification<sid_t>(ugraph->sgraph, ugraph->sgraph, 1); 
    return ;
}

void plain_test4(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    
    plaingraph_manager::prep_graph(idir, odir);
    
    string idir1 = "/mnt/disk_huge_1/pradeepk/pradeep_graph/kron_21_16_incr/"; 
    plaingraph_manager::prep_graph(idir1, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    verification<sid_t>(ugraph->sgraph, ugraph->sgraph, 1); 
    return ;
}

void plain_test5(const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    //plaingraph_manager::setup_graph(v_count);    
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    
    ugraph->flag1 = 1;
    ugraph->flag2 = 1;
    g->read_graph_baseline();
    
    verification<sid_t>(ugraph->sgraph, ugraph->sgraph, 1); 
    return ;
}

void plain_test6(const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    
    g->read_graph_baseline();
    
    //call mem_bfs
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    index_t edge_count = (v_count << 5);
    uint8_t* level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    
    snap_bfs<sid_t>(graph, graph, v_count, edge_count, level_array, 1, 1);
    return ;
}

void paper_test0(vid_t v_count, const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph_paper_num(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    blog_t<sid_t>* blog = ugraph->blog;
   
    uint8_t* level_array = (uint8_t*)mmap(NULL, sizeof(uint8_t)*v_count, PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0 );
    if (MAP_FAILED == level_array) {
        cout << "Huge page alloc failed for level array" << endl;
        level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    }
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array = 0;
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));

    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    mem_bfs<sid_t>(graph, degree_array, graph, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);

}

void paper_test_chain_bfs(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph_paper_chain(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    blog_t<sid_t>* blog = ugraph->blog;
   
    uint8_t* level_array = (uint8_t*)mmap(NULL, sizeof(uint8_t)*v_count, PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0 );
    if (MAP_FAILED == level_array) {
        cout << "Huge page alloc failed for level array" << endl;
        level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    }
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array = 0;
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));

    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;
   
    for (int i = 0; i < 10; i++) {
        memset(level_array, 0, v_count*sizeof(uint8_t));
        mem_bfs<sid_t>(graph, degree_array, graph, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    }
    
    /*
	ext_bfs<sid_t>(ugraph->sgraph[0], degree_array, ugraph->sgraph[0], degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
	*/
}
void paper_test_pr_chain(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph_paper_chain(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    blog_t<sid_t>* blog = ugraph->blog;
   
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array = 0;
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));
    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    for (int i = 0; i < 10; i++) {
        mem_pagerank<sid_t>(graph, degree_array, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, 5);
    }

}

void paper_test_pr(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph_paper_num(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    blog_t<sid_t>* blog = ugraph->blog;
   
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array = 0;
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));
    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    mem_pagerank<sid_t>(graph, degree_array, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, 5);

}

void paper_test_hop1_chain(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph_paper_chain(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    blog_t<sid_t>* blog = ugraph->blog;
   
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array = 0;
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t)); 
    if (snapshot) {
        old_marker = snapshot->marker;
    }
    create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    for (int i = 0; i < 10; i++) {
        mem_hop1<sid_t>(graph, degree_array, snapshot, marker, blog->blog_beg, v_count);
    }

}

void paper_test_hop1(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph_paper_num(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    blog_t<sid_t>* blog = ugraph->blog;
   
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array = 0;
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));
    if (snapshot) {
        old_marker = snapshot->marker;
    }
    create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    mem_hop1<sid_t>(graph, degree_array, snapshot, marker, blog->blog_beg, v_count);

}

void paper_test_hop2_chain(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph_paper_chain(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    blog_t<sid_t>* blog = ugraph->blog;
   
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array = 0;
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t)); 
    if (snapshot) {
        old_marker = snapshot->marker;
    }
    degree_array = create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    mem_hop2<sid_t>(graph, degree_array, snapshot, marker, blog->blog_beg, v_count);

}

void paper_test_hop2(const string& idir, const string& odir)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    plaingraph_manager::prep_graph_paper_num(idir, odir);
    
    propid_t cf_id = g->get_cfid("friend");
    ugraph_t* ugraph = (ugraph_t*)g->cf_info[cf_id];
    vert_table_t<sid_t>* graph = ugraph->sgraph[0]->get_begpos();
    blog_t<sid_t>* blog = ugraph->blog;
   
    snapshot_t* snapshot = g->get_snapshot();
    index_t marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array = 0;
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t)); 
    if (snapshot) {
        old_marker = snapshot->marker;
    }
    create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg,degree_array);

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;

    mem_hop2<sid_t>(graph, degree_array, snapshot, marker, blog->blog_beg, v_count);

}

void update_test0(const string& idirname, const string& odirname)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    
    struct dirent *ptr;
    DIR *dir;
    int file_count = 0;
    string filename;
    propid_t cf_id = g->get_cfid("friend");
    pgraph_t<sid_t>* ugraph = (pgraph_t<sid_t>*)g->cf_info[cf_id];
        
    FILE* file = 0;
    index_t size =  0;
    index_t edge_count = 0;
    
    
    //Read graph files
    double start = mywtime();
    dir = opendir(idirname.c_str());
    blog_t<sid_t>* blog = ugraph->blog;
    edge_t* edge = blog->blog_beg;
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        filename = idirname + "/" + string(ptr->d_name);
        file_count++;
        
        file = fopen((idirname + "/" + string(ptr->d_name)).c_str(), "rb");
        assert(file != 0);
        size = fsize(filename);
        edge_count = size/sizeof(edge_t);
        edge = blog->blog_beg + blog->blog_head;
        if (edge_count != fread(edge, sizeof(edge_t), edge_count, file)) {
            assert(0);
        }
        blog->blog_head += edge_count;
    }
    closedir(dir);
    double end = mywtime();
    cout << "Reading "  << file_count  << " file time = " << end - start << endl;
    start = mywtime();

    cout << "End marker = " << blog->blog_head << endl;
    
    //Make Graph
    index_t total_edge_count = blog->blog_head;
    index_t marker = 0;
    index_t snap_marker = 0;
    index_t batch_size = (total_edge_count >> residue);
    cout << "batch _size = " << batch_size << endl;

    while (marker < blog->blog_head) {
        marker = min(blog->blog_head, marker+batch_size);
        ugraph->create_marker(marker);
        if (eOK != ugraph->move_marker(snap_marker)) {
            assert(0);
        }
        //blog->marker = marker;
        ugraph->make_graph_baseline();
        //ugraph->store_graph_baseline();
        g->incr_snapid(snap_marker, snap_marker);
        //cout << marker << endl;
    }
    end = mywtime ();
    cout << "Make graph time = " << end - start << endl;
    
    /*
    //Run BFS
    for (int i = 0; i < 8; i++){
        uint8_t* level_array = 0;
        
        / *
        level_array = (uint8_t*)mmap(NULL, sizeof(uint8_t)*v_count, 
                                PROT_READ|PROT_WRITE,
                                MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0 );
        
        if (MAP_FAILED == level_array) {
            cout << "Huge page alloc failed for level array" << endl;
            level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
        }* /
        
        level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
        
        onegraph_t<sid_t>*   sgraph = ugraph->sgraph[0];
        vert_table_t<sid_t>* graph = sgraph->get_begpos();
        
        snapshot_t* snapshot = g->get_snapshot();
        marker = blog->blog_head;
        index_t old_marker = 0;
        degree_t* degree_array = 0;
            
        degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));

        if (snapshot) {
            old_marker = snapshot->marker;
            create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);
        }

        cout << "old marker = " << old_marker << " New marker = " << marker << endl;
        / *
        ext_bfs<sid_t>(sgraph, degree_array, sgraph, degree_array, 
                       snapshot, marker, blog->blog_beg,
                       v_count, level_array, 1);
        * /
        mem_bfs<sid_t>(graph, degree_array, graph, degree_array, 
                       snapshot, marker, blog->blog_beg,
                       v_count, level_array, 1);
        free(level_array);
        free(degree_array);
    }
    
    //Run PageRank
    for (int i = 0; i < 8; i++){
        onegraph_t<sid_t>*   sgraph = ugraph->sgraph[0];
        vert_table_t<sid_t>* graph = sgraph->get_begpos();
        
        snapshot_t* snapshot = g->get_snapshot();
        marker = blog->blog_head;
        index_t old_marker = 0;
        degree_t* degree_array = 0;
            
        degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));

        if (snapshot) {
            old_marker = snapshot->marker;
            create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);
        }

        cout << "old marker = " << old_marker << " New marker = " << marker << endl;
        mem_pagerank<sid_t>(graph, degree_array, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, 5);
        free(degree_array);
    }
    
    //Run 1-HOP query
    for (int i = 0; i < 8; i++){
        onegraph_t<sid_t>*   sgraph = ugraph->sgraph[0];
        vert_table_t<sid_t>* graph = sgraph->get_begpos();
        
        snapshot_t* snapshot = g->get_snapshot();
        marker = blog->blog_head;
        index_t old_marker = 0;
        degree_t* degree_array = 0;
            
        degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));

        if (snapshot) {
            old_marker = snapshot->marker;
            create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);
        }

        cout << "old marker = " << old_marker << " New marker = " << marker << endl;
        mem_hop1<sid_t>(graph, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count);
        free(degree_array);
    }
    */
}

void update_test1(const string& idirname, const string& odirname)
{
    plaingraph_manager::schema_plaingraph();
    //do some setup for plain graphs
    plaingraph_manager::setup_graph(v_count);    
    g->create_snapthread();
    //usleep(1000);
    
    struct dirent *ptr;
    DIR *dir;
    int file_count = 0;
    string filename;
    propid_t cf_id = g->get_cfid("friend");
    pgraph_t<sid_t>* ugraph = (pgraph_t<sid_t>*)g->cf_info[cf_id];
        
    FILE* file = 0;
    index_t size =  0;
    index_t edge_count = 0;
    index_t total_edge_count = 0;
    
    
    //Read graph files
    double start = mywtime();
    dir = opendir(idirname.c_str());
    edge_t* edges =  (edge_t*)calloc(sizeof(edge_t),(1L<<32));
    edge_t* edge = edges;
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        filename = idirname + "/" + string(ptr->d_name);
        file_count++;
        
        file = fopen((idirname + "/" + string(ptr->d_name)).c_str(), "rb");
        assert(file != 0);
        size = fsize(filename);
        edge_count = size/sizeof(edge_t);
        edge = edges + total_edge_count;
        if (edge_count != fread(edge, sizeof(edge_t), edge_count, file)) {
            assert(0);
        }
        total_edge_count += edge_count;
    }
    closedir(dir);
    double end = mywtime();
    cout << "Reading "  << file_count  << " file time = " << end - start << endl;
    start = mywtime();
    cout << "End marker = " << total_edge_count << endl;
    
    
    //Batch and Make Graph
    for (index_t i = 0; i < total_edge_count; ++i) {
        ugraph->batch_edge(edges[i]);
    }

    //----------
    end = mywtime ();
    cout << "Batch Update Time = " << end - start << endl;
    
    blog_t<sid_t>* blog = ugraph->blog;
    index_t marker = blog->blog_head;
    if (marker != blog->blog_marker) {
        ugraph->create_marker(marker);
    }

    //Wait for make graph
    while (blog->blog_tail != blog->blog_head) {
        usleep(10);
    }
    //---------
    end = mywtime();
    cout << "Make graph time = " << end - start << endl;
    
    //Run BFS
    //blog_t<sid_t>* blog = ugraph->blog;
    marker = blog->blog_head;
    uint8_t* level_array = (uint8_t*)mmap(NULL, sizeof(uint8_t)*v_count, 
                            PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0 );
    
    if (MAP_FAILED == level_array) {
        cout << "Huge page alloc failed for level array" << endl;
        level_array = (uint8_t*) calloc(v_count, sizeof(uint8_t));
    }
    
    onegraph_t<sid_t>*   sgraph = ugraph->sgraph[0];
    vert_table_t<sid_t>* graph = sgraph->get_begpos();
    
    snapshot_t* snapshot = g->get_snapshot();
    marker = blog->blog_head;
    index_t old_marker = 0;
    degree_t* degree_array = 0;
        
    degree_array = (degree_t*) calloc(v_count, sizeof(degree_t));

    if (snapshot) {
        old_marker = snapshot->marker;
        create_degreesnap(graph, v_count, snapshot, marker, blog->blog_beg, degree_array);
    }

    cout << "old marker = " << old_marker << " New marker = " << marker << endl;
    ext_bfs<sid_t>(sgraph, degree_array, sgraph, degree_array, 
                   snapshot, marker, blog->blog_beg,
                   v_count, level_array, 1);
    
}

void llama_test_bfs(const string& odir);
void llama_test_pr(const string& odir);
void llama_test_pr_push(const string& odir);

void plain_test(vid_t v_count1, const string& idir, const string& odir, int job)
{
    v_count = v_count1; 
    switch (job) {
        case 0:
            plain_test0(idir, odir);
            break;
        case 1:
            plain_test1(idir, odir);
            break;
        case 2:
            plain_test2(odir);
            break;
        case 3:
            split_graph<sid_t>(idir, odir);
            break;
        case 4:
            split_graph<lite_edge_t>(idir, odir);
            break;
        case 5:
            weight_dtest0(idir, odir);
            break;
        case 6:
            weight_dtest1(odir);
            break;
        case 7:
            plaind_test0(idir, odir);
            break;
        case 8:
            plaind_test1(odir);
            break;
        case 9:
            //stinger test
            weighted_dtest0(idir, odir);
            break;
        case 10:
            paper_test0(v_count1, idir, odir);
            break;
        case 11:
            paper_test_pr(idir, odir);
            break;
        case 12:
            paper_test_hop1(idir, odir);
            break;
        case 13:
            paper_test_hop2(idir, odir);
            break;
        case 14:
            paper_test_chain_bfs(idir, odir);
            break;
        case 15:
            paper_test_pr_chain(idir, odir);
            break;
        case 16:
            paper_test_hop1_chain(idir, odir);
            break;
        case 17:
            paper_test_hop2_chain(idir, odir);
            break;
        case 18:
            llama_test_bfs(odir);
            break;
        case 19:
            llama_test_pr(odir);
            break;
        case 20:
            llama_test_pr_push(odir);
            break;
        case 21: 
            update_test0(idir, odir);
            break;
        case 22: 
            update_test1(idir, odir);
            break;
        case 97:
            estimate_chain_new<sid_t>(idir, odir);
            break; 
        case 98:
            estimate_chain<sid_t>(idir, odir);
            break; 
        case 99:
            estimate_IO<sid_t>(idir, odir);
            break; 
        case 100:
            plain_test3(idir, odir);
            //plain_test4(odir);
            //plain_test6(odir);
            break;
        case 101:
            plain_test5(odir);
            break;
        default:
            break;
    }
}
