CC=g++
CFLAGS=-g -Wall  -std=gnu++11  -march=native -fopenmp
SRC=main.cpp \
	graph.cpp\
	ugraph.cpp\
	dgraph.cpp\
	many2one.cpp\
	enumkv.cpp\
	stringkv.cpp\
	intkv.cpp\
	nt_to_edge.cpp\
	intersection.cpp\
	run_query.cpp\
	query_union.cpp\
	query_intersection.cpp\
	query_stagefilter.cpp\
	query_trianglejoin.cpp\
	query_transform.cpp\
	query_triplewithfilter.cpp\
	query_triple.cpp\
	query_visitor.cpp\
	antlr4/Sparql11BaseVisitor.cpp\
	antlr4/Sparql11Lexer.cpp\
	antlr4/Sparql11Parser.cpp\
	antlr4/Sparql11Visitor.cpp\

HEADER=rdf.h \
	btree.h\
	kbtree.h\
	edges.h\
	query_union.h\
	query_intersection.h\
	query_stagefilter.h\
	query_trianglejoin.h\
	query_transform.h\
	query_triplewithfilter.h\
	query_triple.h\
	query_visitor.h\

INCLUDES= -Iantlr4/include -Iantlr4
LIBDIRS= -Lantlr4/lib

DEPS=$(SRC) $(HEADER)

grdf: $(DEPS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBDIRS) $(SRC) -lantlr4-runtime -o grdf

clean:
	rm grdf *.o 
