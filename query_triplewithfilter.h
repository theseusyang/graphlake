#pragma once

#include "query_triple.h"

class pinfo_t;

class query_triplewithfilter: public query_triple
{
public:
	virtual status_t execute();
    inline void set_filterobj(pinfo_t* a_graph, void* a_value, filter_fn_t fn) {
        rgraph = a_graph;
        value = a_value;
        filter_fn = fn;
    }

 public:
    pinfo_t* rgraph;
    void* value;
    filter_fn_t filter_fn;
};
