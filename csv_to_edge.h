#pragma once

#include <string>
#include "type.h"
using std::string;


class csv_manager {
 public:
    static void prep_graph(const string& conf_file, 
                           const string& idir, const string& odir);
    static void prep_vtable(const string& filename, string predicate, const string& odir);
    static void prep_etable(const string& filename, const econf_t& e_conf, const string& odir);
};

class plaingraph_manager {
    public:
    static void schema_plaingraph();
    static void setup_graph(vid_t v_count);
    static void prep_graph(const string& idirname, const string& odirname);
    static void prep_graph_sync(const string& idirname, const string& odirname);
    static void prep_graph_paper_num(const string& idirname, const string& odirname);
};
