#pragma once

#include "query_node.h"

class query_union: public query_node
{
	status_t execute();
};
