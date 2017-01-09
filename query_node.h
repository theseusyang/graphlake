#ifndef __QUERY_NODE_H_
#define __QUERY_NODE_H_

#include <memory>

typedef int32_t status_t;

using std::unique_ptr;
typedef int32_t idata;

class query_node {
private:
	virtual status_t execute()=0;

};
#endif
