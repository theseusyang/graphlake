#include <iostream>
#include <string>
#include "antlr4-runtime.h"
#include "Sparql11Lexer.h"
#include "Sparql11Parser.h"


using namespace antlr4;
using std::string;

int main(int argc, char* argv[])
{
	string fName = argv[1];
	ANTLRFileStream input(fName);
	Sparql11Lexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	Sparql11Parser parser(&tokens);

	tree::ParseTree* tree =  parser.queryUnit();
	std::cout << tree->toStringTree(&parser) << std::endl;

	return 0;
}	
