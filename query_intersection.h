#pragma once

#include "query_node.h"

class query_intersection: public query_node
{
	status_t execute();
};
