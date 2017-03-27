#pragma once

#include "query_node.h"

extern char* gstrdup(const char* str);

class query_triple: public query_node
{

public:
	query_triple() {src = dst = pred = 0;};
	virtual status_t execute();
	virtual void to_string();
	
    inline void set_src(const char* a_src) { 
        src = gstrdup(a_src);
    }
	
    inline void set_dst(const char* a_dst) { 
        dst = gstrdup(a_dst);
    }
	
    inline void set_pred(const char* a_pred) { 
        pred = gstrdup(a_pred); 
    }

protected:
	//Variables will be assinged an id. Flag will distinguish it.
	char* src;//Can represent var or actual subject
	char* pred;//Can represent var or actual predicate
	char* dst ;//Can represent var or actual object
	//uint8_t flag; // Will tell you which are variable and which are actual ids.
};
