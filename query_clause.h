#pragma once


class query_whereclause : public query_node
{
	public:
	inline status_t	execute() {return 0;}
};

class query_clause
{
private:
	query_whereclause* where_clause;
	//More coming soon


};
