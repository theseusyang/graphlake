CC=g++
CFLAGS=-g -Wall  -std=gnu++11  -march=native -fopenmp
SRC=main.cpp \
	util.cpp\
	run_query.cpp\
	query_union.cpp\
	query_intersection.cpp\
	query_stagefilter.cpp\
	query_trianglejoin.cpp\
	query_transform.cpp\
	query_triplewithfilter.cpp\
	query_triple.cpp\
	antlr4/Sparql11BaseListener.cpp\
	antlr4/Sparql11BaseVisitor.cpp\
	antlr4/Sparql11Lexer.cpp\
	antlr4/Sparql11Listener.cpp\
	antlr4/Sparql11Parser.cpp\
	antlr4/Sparql11Visitor.cpp\

HEADER=graph.h \
	btree.h\
	query_union.h\
	query_intersection.h\
	query_stagefilter.h\
	query_trianglejoin.h\
	query_transform.h\
	query_triplewithfilter.h\
	query_triple.h\

INCLUDES= -Iantlr4/include -Iantlr4
LIBDIRS= -Lantlr4/lib

DEPS=$(SRC) $(HEADER)

grdf: $(DEPS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBDIRS) $(SRC) -lantlr4-runtime -o grdf

clean:
	rm grdf *.o 
