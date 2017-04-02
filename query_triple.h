#pragma once

#include "query_node.h"



extern char* gstrdup(const char* str);

class query_triple: public query_node
{

public:
	inline query_triple() {
        src = dst = pred = 0;
        src_qid = dst_qid = NO_QID;
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
   

protected:
    query_clause* q;
	char* src;//Can represent var or actual subject
	char* pred;//Can represent var or actual predicate
	char* dst ;//Can represent var or actual object
	qid_t src_qid;
    //uint8_t pred_qid;//Not supported yet.
    qid_t dst_qid;
};
