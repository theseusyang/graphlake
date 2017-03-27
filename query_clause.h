#pragma once
#include "query_node.h"

class query_whereclause : public query_node
{
	public:
	status_t	execute();

	inline virtual 
	void to_string()
	{
		cout << "WHERE (";
		query_node* node = get_child();
		if (node) {
			node->to_string();
		}
		node = get_sibling();
		while (node) {
			node->to_string();
			node = node->get_sibling();
		}
		cout << ")" << endl;
	}
};

class query_clause
{
private:
	query_whereclause* where_clause;
	//More coming soon

public:
	inline void print_where() {where_clause->to_string();};
    status_t execute();


};
