#include "query_union.h"

status_t
query_union::execute()
{
	return 0;
}
void
query_union::to_string()
{
	cout << "UNION (";
	query_node* node = get_child();
	if (node) {
		node->to_string();
	}
	cout << ")";
	node = get_sibling();
	while (node) {
		node->to_string();
		node = node->get_sibling();
	}

}
