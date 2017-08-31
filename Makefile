CC=g++
#CFLAGS=-g -Wall -std=gnu++11  -march=native -DB64 -fopenmp
#CFLAGS=-g -Wall -std=gnu++11  -march=native -DB32 -DPLAIN_GRAPH -fopenmp -lpthread
CFLAGS=-O3 -Wall -std=gnu++11  -march=native -DB32 -DPLAIN_GRAPH -fopenmp -lpthread
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
	p_sgraph.cpp\
	prop_encoder.cpp\
	propkv.cpp\
	lubm_test1.cpp\
	ldbc_test.cpp\
	darshan_test.cpp\
	plaingraph_test.cpp\
	
#lite_sgraph.cpp\

	

HEADER=graph.h\
	cf_info.h\
	sgraph.h\
	p_sgraph.h\
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
	snap_iterative_analytics.h\
	nt_to_edge.h\
	csv_to_edge.h\
	darshan_to_edge.h\

#	lite_sgraph.h\

#INCLUDES= -Iantlr4/include -Iantlr4
#LIBDIRS= -Lantlr4/lib
INCLUDES=
LIBDIRS=

DEPS=$(SRC) $(HEADER)

grdf: $(DEPS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBDIRS) $(SRC)  -o grdf

clean:
	rm grdf *.o 
