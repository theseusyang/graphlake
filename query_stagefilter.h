#pragma once

#include "query_node.h"

class query_stagefilter: public query_node
{
	status_t execute();
};
