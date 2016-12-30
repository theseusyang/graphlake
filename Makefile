CC=g++
CFLAGS=-g -Wall  -std=gnu++11  -march=native -fopenmp
SRC=main.cpp util.cpp
HEADER=graph.h btree.h

DEPS=$(SRC) $(HEADER)

grdf: $(DEPS)
	$(CC) $(CFLAGS) $(SRC) -o grdf

clean:
	rm grdf *.o 
