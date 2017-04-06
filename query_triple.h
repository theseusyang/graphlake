#pragma once

#include "query_node.h"



extern char* gstrdup(const char* str);

class query_triple: public query_node
{

public:
	inline query_triple() {
        src = dst = pred = 0;
        src_qid = dst_qid = NO_QID;
        query_plan = eDefault;
    }
	virtual status_t execute();
	virtual void to_string();
	
    inline void set_src(const char* a_src) { 
        src = gstrdup(a_src);
    }
    
    inline void set_src(const char* a_src, qid_t qid) { 
        src = gstrdup(a_src);
        src_qid = qid;
    }
	
    inline void set_dst(const char* a_dst) { 
        dst = gstrdup(a_dst);
    }
	
    inline void set_dst(const char* a_dst, qid_t qid) { 
        dst = gstrdup(a_dst);
        dst_qid = qid;
    }
	
    inline void set_pred(const char* a_pred) { 
        pred = gstrdup(a_pred); 
    }
    
    inline void set_query(query_clause* a_q ) {
        q = a_q;
    }
    inline void set_qplan(queryplan_t qplan) {
        query_plan = qplan;
    } 

protected:
	char* src;//Can represent var or actual subject
	char* pred;//Can represent var or actual predicate
	char* dst ;//Can represent var or actual object
	qid_t src_qid;
    //uint8_t pred_qid;//Not supported yet.
    qid_t dst_qid;
    queryplan_t query_plan;
};
