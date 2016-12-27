CC=g++
CFLAGS=-g -Wall -march=native -fopenmp
SRC=main.cpp
HEADER=graph.h btree.h

DEPS=$(SRC) $(HEADER)

grdf: $(DEPS)
	$(CC) $(CFLAGS) $(SRC) -o grdf

clean:
	rm grdf *.o 
