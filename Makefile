CC=g++
CFLAGS=-g -Wall -march=native -fopenmp
SRC=main.cpp

DEPS=$(SRC)

grdf: $(DEPS)
	$(CC) $(CFLAGS) $(SRC) -o grdf

clean:
	rm grdf *.o 
