#pragma once

#include "query_node.h"

class query_union: public query_node
{
public:
	virtual status_t execute();
	virtual void to_string();

};
