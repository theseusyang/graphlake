#include "query_visitor.h"
#include "query_triple.h"
#include "query_clause.h"
#include "query_union.h"
#include "graph.h"

extern graph* g;

query_visitor::query_visitor()
{
	where_clause = 0;
	last_node = 0;
	varid = 0;
}
antlrcpp::Any 
query_visitor::visitWhereClause(Sparql11Parser::WhereClauseContext *ctx) {
	where_clause = new query_whereclause;
	last_node = where_clause;
	visitChildren(ctx);
	return 0;
	
}
antlrcpp::Any 
query_visitor::visitGroupOrUnionGraphPattern(Sparql11Parser::GroupOrUnionGraphPatternContext *ctx)
{
	query_node* node_union = new query_union;
	query_node* prev_node = last_node;
	assert(last_node);

	//add sibling to last one
	last_node->add_child(node_union);
	last_node = node_union;
	visitChildren(ctx);
	last_node = prev_node;
	return 0;
}

antlrcpp::Any 
query_visitor::visitTriplesSameSubjectPath(Sparql11Parser::TriplesSameSubjectPathContext *ctx)
{
	query_triple* triple = new query_triple;
	query_node* prev_node = last_node;
	assert(last_node);
	last_node = triple;
	last_node->add_child(triple);
	visitChildren(ctx);
	last_node = prev_node;
	return 0;
}
	
antlrcpp::Any 
query_visitor::visitVarOrTerm(Sparql11Parser::VarOrTermContext *ctx) 
{
	//last_node must be a triple
	query_triple* triple = dynamic_cast<query_triple*>(last_node);

	//Get the text
	string sub = ctx->getText();
	//If it is a literal, IRI ref or variable.
	char first_char = sub[0];
	if ('?' == first_char || '$' == first_char) { //variable
		var2id_iter = var2id.find(sub);
		if (var2id_iter == var2id.end()) {
			var2id[sub] = varid;
			id2var.push_back(sub);
			triple->set_sub(varid);
			++varid;
		} else {
			triple->set_sub(var2id_iter->second);

		}
	} else if ('<' == first_char) {//IRI
		s_t s_id = g->find_str2sid(sub);
		assert(s_id != -1);
		triple->set_sub(s_id);
	} else {
		assert(0);
	}

	return 0;//let's not visit children
}
