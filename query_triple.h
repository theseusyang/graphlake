#pragma once

#include "query_node.h"
#include "typedef.h"

class query_triple: public query_node
{

public:
	query_triple() {sub_id = pred_id = obj_id = flag = -1;};
	virtual status_t execute();
	virtual void to_string();
	inline void set_sub(s_t s_id) { sub_id = s_id;}
	inline void set_obj(s_t o_id) { obj_id = o_id;}
	inline void set_pred(p_t p_id) { pred_id = p_id; }
	inline p_t get_pred() {return pred_id; }

protected:
	//Variables will be assinged an id. Flag will distinguish it.
	s_t sub_id;//Can represent var or actual subject
	p_t pred_id;//Can represent var or actual predicate
	s_t obj_id;//Can represent var or actual object
	flag_t flag; // Will tell you which are variable and which are actual ids.
};


