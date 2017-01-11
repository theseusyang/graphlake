#pragma once

#include <vector>
#include <map>
#include <string>

#include "Sparql11BaseVisitor.h"
#include "query_node.h"

using std::string;
using std::vector;
using std::map;

class query_visitor : public Sparql11BaseVisitor
{
public:
	query_visitor();

	virtual antlrcpp::Any 
	visitWhereClause(Sparql11Parser::WhereClauseContext *ctx); 
	
	virtual antlrcpp::Any 
	visitGroupOrUnionGraphPattern(Sparql11Parser::GroupOrUnionGraphPatternContext *ctx);
  
	virtual antlrcpp::Any 
	visitTriplesSameSubjectPath(Sparql11Parser::TriplesSameSubjectPathContext *ctx);
  
	virtual antlrcpp::Any 
	visitVarOrTerm(Sparql11Parser::VarOrTermContext *ctx); 
  
	virtual antlrcpp::Any 
	visitVerbPathOrSimple(Sparql11Parser::VerbPathOrSimpleContext *ctx);
  
	virtual antlrcpp::Any 
	visitObjectList(Sparql11Parser::ObjectListContext *ctx); 
 
public:
	void print_whereclause();	
private:
	query_node* where_clause;
	query_node* last_node;
	map<string, int32_t> var2id;
	map<string, int32_t>::iterator var2id_iter;
	vector<string> id2var;
	int32_t varid;

};
