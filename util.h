#pragma once
#include "type.h"

inline index_t upper_power_of_two(index_t v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v |= v >> 32;
    v++;
    return v;

}

template <class T>
index_t read_idir(const string& idirname, edgeT_t<T>** pedges, bool alloc)
{
    struct dirent *ptr;
    DIR *dir;
    int file_count = 0;
    string filename;
        
    FILE* file = 0;
    index_t size = 0;
    index_t edge_count = 0;
    index_t total_edge_count = 0;
    
    edgeT_t<T>* edges = 0;

    //allocate accuately
    dir = opendir(idirname.c_str());
    if (alloc) {
        while (NULL != (ptr = readdir(dir))) {
            if (ptr->d_name[0] == '.') continue;
            filename = idirname + "/" + string(ptr->d_name);
            size = fsize(filename);
            edge_count = size/sizeof(edgeT_t<T>);
            total_edge_count += edge_count;
        }
        closedir(dir);

        edges =  (edgeT_t<T>*)calloc(sizeof(edgeT_t<T>),total_edge_count);
        *pedges = edges;
    } else {
        //edges = *pedges;
        //
        while (NULL != (ptr = readdir(dir))) {
            if (ptr->d_name[0] == '.') continue;
            filename = idirname + "/" + string(ptr->d_name);
            size = fsize(filename);
            edge_count = size/sizeof(edgeT_t<T>);
            total_edge_count += edge_count;
        }
        closedir(dir);
        //upper align the memory allocation
        index_t new_count =  upper_power_of_two(total_edge_count);
        edges =  (edgeT_t<T>*)calloc(sizeof(edgeT_t<T>), new_count);
        *pedges = edges;
    }
    
    //Read graph files
    total_edge_count = 0;
    double start = mywtime();
    dir = opendir(idirname.c_str());
    edgeT_t<T>* edge = edges;
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        filename = idirname + "/" + string(ptr->d_name);
        file_count++;
        
        file = fopen((idirname + "/" + string(ptr->d_name)).c_str(), "rb");
        assert(file != 0);
        size = fsize(filename);
        edge_count = size/sizeof(edgeT_t<T>);
        edge = edges + total_edge_count;
        if (edge_count != fread(edge, sizeof(edgeT_t<T>), edge_count, file)) {
            assert(0);
        }
        total_edge_count += edge_count;
    }
    closedir(dir);
    double end = mywtime();
    cout << "Reading "  << file_count  << " file time = " << end - start << endl;
    cout << "End marker = " << total_edge_count << endl;
    return total_edge_count;
}
