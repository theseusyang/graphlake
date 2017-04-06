#pragma once

#include "query_triple.h"


class query_triplewithfilter: public query_triple
{
public:
    inline query_triplewithfilter() {
        //filter_info = 0;
    }

	virtual status_t execute();
    inline void set_filterobj(pinfo_t* a_graph, univ_t a_value, filter_fn_t fn) {
        filter_info.rgraph = a_graph;
        filter_info.value = a_value;
        filter_info.filter_fn = fn;
    }

 public:
    filter_info_t filter_info;
};
