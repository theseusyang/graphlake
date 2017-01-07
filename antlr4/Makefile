CC=g++
CFLAGS= -std=gnu++11

SRC= main.cpp \
	Sparql11BaseListener.cpp\
	Sparql11BaseVisitor.cpp\
	Sparql11Lexer.cpp\
	Sparql11Listener.cpp\
	Sparql11Parser.cpp\
	Sparql11Visitor.cpp\

INCLUDES= include
LIBDIRS= ./lib

all:
	$(CC) $(CFLAGS) -I$(INCLUDES) -L$(LIBDIRS) $(SRC) -lantlr4-runtime -o demo
