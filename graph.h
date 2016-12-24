#ifndef __GRAPH_H_
#define __GRAPH_H_

typedef int32_t literal_id_t;
typedef char* literal_t;

typedef int32_t index_t;
typedef int32_t flag_t;
typedef int32_t degree_t;
typedef int32_t s_t;
typedef int32_t o_t;

//HashTable/KV-store for literal to ID mapping
class literal2id_t {
};

literal2id_t	literal2id;

//plain array for ID to literal mapping
class id2literal_t {
};

id2literal_t	id2literal; 

//B-tree/hashtable for adjacency list
class adj_index {
	//Some S/0 might have more than one O/S for same P.
	//Such as publication and author relashionship.
	//Here one professor/student can have multiple publication and
	//same publication could have multiple authors.
	
};

/*Top level CSR format (similar to begpos in CSR). A plain array. 
  Each elements contain:
	B-tree/hashtable of in-edges
	in-degree information
	B-tree/hashtable of out-edges
	out-degree information
	Flag
*/
typedef struct __po_t {
	adj_index out_edges;
	adj_index in_edges;
	degree_t out_degree;
	degree_t in_degree;
	flag_t flag;
} po_t;

typedef struct __ps_t {
	adj_index in_edges;
	degree_t in_degree;
	flag_t flag;
} ps_t;


typedef struct __po_indirect_t {
	int32_t count;
	po_t* po;
} po_indirect_t;

po_indirect_t*		spo;

//predicate indices. As per our analysis, we don't need second index on S/O.
//So, it is more like a CSR representation. However, to support dynamic rdf graph,
// we will manage it each adj list separatly. 
//Also, note that, the size of adjacency list of each one is going to be very big,
//as number of predicates are small while number of triples are like billions.

typedef struct __so_t {
	s_t s;
	o_t o;
} so_t;

typedef struct __so_indirect {
	int32_t count;
	so_t* so;
} so_indirect_t;

so_indirect_t*		pso;

#endif
