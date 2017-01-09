#pragma once

#include "query_node.h"

class query_triple: public query_node
{
	virtual status_t execute();
};


