CC=g++
EXE1=graphone32
EXE2=graphone64
EXE3=graphlake32
EXE4=graphlake64
#CFLAGS=-g -Wall -std=gnu++11 -march=native -fopenmp -lpthread -DOVER_COMMIT
CFLAGS=-O3 -Wall -std=gnu++11  -march=native -fopenmp -lpthread -DOVER_COMMIT
#CFLAGS=-O3 -Wall -std=gnu++11  -march=native -fopenmp -lpthread -DBULK

SRC=main.cpp \
	cf_info.cpp\
	graph.cpp\
	sgraph.cpp\
	stringkv.cpp\
	typekv.cpp\
    vgraph.cpp\
	nt_to_edge.cpp\
	csv_to_edge.cpp\
	netflow_to_edge.cpp\
	query_triple.cpp\
	graph_query.cpp\
	graph_base.cpp\
	rset.cpp\
	propkv.cpp\
	plaingraph_test.cpp\
    netflow_test.cpp\
	llama_test.cpp\
	
#weight_graph.cpp\
#lite_sgraph.cpp\
#p_sgraph.cpp\


SRC64=mlabel.cpp\
	prop_encoder.cpp\
	lubm_test1.cpp\
	darshan_to_edge.cpp\
	darshan_test.cpp\
	ldbc_test.cpp\

HEADER=graph.h\
	cf_info.h\
	sgraph.h\
	sgraph2.h\
	skv.h\
	wgraph.h\
	prop_encoder.h\
	propkv.h\
	stringkv.h\
	mlabel.h\
	typekv.h\
	query_node.h\
	query_triple.h\
	type.h\
	graph_base.h\
	onegraph.h\
	onekv.h\
	rset.h\
    query_clause.h\
	iterative_analytics.h\
	ext_iterative_analytics.h\
	ext2_iterative_analytics.h\
	mem_iterative_analytics.h\
	snap_iterative_analytics.h\
	stream_analytics.h\
	nt_to_edge.h\
	netflow_to_edge.h\
	csv_to_edge.h\
	plain_to_edge.h\
	darshan_to_edge.h\
	util.h\

#	lite_sgraph.h\
#	p_sgraph.h\

#INCLUDES= -Iantlr4/include -Iantlr4
#LIBDIRS= -Lantlr4/lib
INCLUDES=
LIBDIRS=

DEPS=$(SRC) $(HEADER)

all:${EXE1} ${EXE2}

${EXE1}: $(DEPS)
	$(CC) $(CFLAGS) -DB32 -DPLAIN_GRAPH $(INCLUDES) $(LIBDIRS) $(SRC)  -o ${EXE1} -laio

${EXE2}: $(DEPS)
	$(CC) $(CFLAGS) -DB64 -DPLAIN_GRAPH $(INCLUDES) $(LIBDIRS) $(SRC) ${SRC64} -o ${EXE2} -laio

clean:
	rm ${EXE1} ${EXE2} 
