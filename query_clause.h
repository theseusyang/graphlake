#pragma once


class query_whereclause : public query_node
{
	public:
	inline status_t	execute() {return 0;}

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
		cout << ")";
	}
};

class query_clause
{
private:
	query_whereclause* where_clause;
	//More coming soon

public:
	inline void print_where() {where_clause->to_string();};


};
