#pragma once

#include "query_triple.h"

class pinfo_t;

class query_triplewithfilter: public query_triple
{
public:
	virtual status_t execute();
    inline void set_filterobj(pinfo_t* a_graph, void* a_value) {
        rgraph = a_graph;
        value = a_value;
    }

 public:
    pinfo_t* rgraph;
    void* value;
};
