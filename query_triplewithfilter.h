#pragma once

#include "query_triple.h"

class query_triplewithfilter: public query_triple
{
	virtual status_t execute();
};


class filter
{
};
