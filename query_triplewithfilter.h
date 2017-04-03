#pragma once

#include "query_triple.h"

class pkv_t;

class query_triplewithfilter: public query_triple
{
	virtual status_t execute();
    inline void set_filterobj(pkv_t* a_graph) {
        rgraph = a_graph;
    }

 public:
    pkv_t* rgraph;
};
