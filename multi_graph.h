#pragma once

#include <string>
#include <dirent.h>
#include <assert.h>
#include <string>
#include <unistd.h>

#include "type.h"
#include "graph.h"
#include "typekv.h"
#include "sgraph.h"
#include "util.h"

using namespace std;

class multi_graph_t {

 public:
     multi_graph_t();
     void schema();
     void setup_graph();     
     void prep_graph_fromtext(const string& idirname, const string& odirname, 
                              typename callback<wls_dst_t>::parse_fn_t);



};
