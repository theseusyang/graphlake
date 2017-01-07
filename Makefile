CC=g++
CFLAGS=-g -Wall  -std=gnu++11  -march=native -fopenmp
SRC=main.cpp \
	util.cpp\
	run_query.cpp\
	antlr4/Sparql11BaseListener.cpp\
	antlr4/Sparql11BaseVisitor.cpp\
	antlr4/Sparql11Lexer.cpp\
	antlr4/Sparql11Listener.cpp\
	antlr4/Sparql11Parser.cpp\
	antlr4/Sparql11Visitor.cpp\

HEADER=graph.h btree.h

INCLUDES= -Iantlr4/include -Iantlr4
LIBDIRS= -Lantlr4/lib

DEPS=$(SRC) $(HEADER)

grdf: $(DEPS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBDIRS) $(SRC) -lantlr4-runtime -o grdf

clean:
	rm grdf *.o 
