

#include "graph.h"
#include "Sparql11Lexer.h"
#include "Sparql11Parser.h"
#include "query_visitor.h"

using namespace antlr4;

status_t 
graph::run_query(string queryfile)
{
	ANTLRFileStream input(queryfile);
	//input.setUcaseLA(input, ANTLR4_FALSE);
	Sparql11Lexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	Sparql11Parser parser(&tokens);
	tree::ParseTree* tree =  parser.queryUnit();
	query_visitor visitor;
	visitor.visit(tree);
	visitor.print_whereclause();
	std::cout << tree->toStringTree(&parser) << std::endl;
	//std::cout << tree->getText() << std::endl;

    return 0;
}
