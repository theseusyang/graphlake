#pragma once

#include <string>
#include "type.h"
using std::string;

typedef struct __econf_t {
    string filename;
    string predicate;
    string src_type;
    string dst_type;
} econf_t; 

typedef struct __vconf_t {
    string filename;
    string predicate;
} vconf_t; 


class csv_manager {
 public:
    static void prep_graph(const string& conf_file, 
                           const string& idir, const string& odir);
    static void prep_vtable(const string& filename, string predicate, const string& odir);
    static void prep_etable(const string& filename, const econf_t& e_conf, const string& odir);
};
