CC=g++
EXE1=graphone32
EXE2=graphone64
EXE3=graphlake32
EXE4=graphlake64
#CFLAGS=-g -Wall -std=gnu++11  -march=native -DB64 -fopenmp
CFLAGS=-g -Wall -std=gnu++11 -march=native -fopenmp -lpthread
#CFLAGS=-O3 -Wall -std=gnu++11  -march=native -fopenmp -lpthread
SRC=main.cpp \
	cf_info.cpp\
	graph.cpp\
	sgraph.cpp\
	mlabel.cpp\
	stringkv.cpp\
	typekv.cpp\
    vgraph.cpp\
	nt_to_edge.cpp\
	csv_to_edge.cpp\
	darshan_to_edge.cpp\
	plain_to_edge.cpp\
	query_triple.cpp\
	graph_query.cpp\
	graph_base.cpp\
	rset.cpp\
	prop_encoder.cpp\
	propkv.cpp\
	lubm_test1.cpp\
	ldbc_test.cpp\
	darshan_test.cpp\
	plaingraph_test.cpp\
	llama_test.cpp\
	
#lite_sgraph.cpp\
#p_sgraph.cpp\

HEADER=graph.h\
	cf_info.h\
	sgraph.h\
	prop_encoder.h\
	propkv.h\
	stringkv.h\
	mlabel.h\
	typekv.h\
	query_node.h\
	query_triple.h\
	type.h\
	graph_base.h\
	rset.h\
    query_clause.h\
	iterative_analytics.h\
	ext_iterative_analytics.h\
	mem_iterative_analytics.h\
	snap_iterative_analytics.h\
	nt_to_edge.h\
	csv_to_edge.h\
	darshan_to_edge.h\

#	lite_sgraph.h\
#	p_sgraph.h\

#INCLUDES= -Iantlr4/include -Iantlr4
#LIBDIRS= -Lantlr4/lib
INCLUDES=
LIBDIRS=

DEPS=$(SRC) $(HEADER)

all:${EXE1} ${EXE2}

${EXE1}: $(DEPS)
	$(CC) $(CFLAGS) -DB32 -DPLAIN_GRAPH $(INCLUDES) $(LIBDIRS) $(SRC)  -o ${EXE1}

${EXE2}: $(DEPS)
	$(CC) $(CFLAGS) -DB64 -DPLAIN_GRAPH $(INCLUDES) $(LIBDIRS) $(SRC)  -o ${EXE2}

clean:
	rm ${EXE1} ${EXE2} 
