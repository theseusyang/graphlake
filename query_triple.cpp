#include "query_triple.h"
#include "query_clause.h"
#include "graph.h"


status_t
query_triple::execute()
{
    //get the property id
    propid_t pid = g->get_pid(pred); 
	//sid_t superid = g->to_sid(src);

    srset_t iset;
    srset_t oset;
    g->p_info[pid]->transform(&iset, &oset, eout);
    return 0;
}

void
query_triple::to_string()
{
	cout << "(";
	query_node* node = get_child();
	if (node) {
		node->to_string();
	}
	cout << src << " " << pred << " " << dst << ")" << endl;
    
	node = get_sibling();
	while (node) {
		node->to_string();
		node = node->get_sibling();
	}
}
