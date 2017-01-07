

#include "graph.h"
#include "Sparql11Lexer.h"
#include "Sparql11Parser.h"

using namespace antlr4;

status_t 
graph::run_query(string queryfile)
{
	ANTLRFileStream input(queryfile);
	Sparql11Lexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	Sparql11Parser parser(&tokens);
	tree::ParseTree* tree =  parser.queryUnit();
	std::cout << tree->toStringTree(&parser) << std::endl;
    return 0;
}
