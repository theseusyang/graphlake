#ifndef __GRAPH_H_
#define __GRAPH_H_



#include "btree.h"

typedef int32_t literal_id_t;
typedef char* literal_t;

typedef int32_t index_t;
typedef int32_t degree_t;
typedef int32_t s_t;
typedef int32_t o_t;

class btree_node;

//HashTable/KV-store for literal to ID mapping
typedef unordered_map<string, literal_id_t> literal2id_t
//class literal2id_t { };

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
	union {
        btree_t* out_edges_tree;//many PO
        leaf_node_t* out_edges;//upto 32 PO
        pair_t out_edge; //just one PO
    };
    union {
	    btree_t* in_edges_tree; //many PO
        leaf_node_t* in_edges;//upto 32 PO
        pair_t in_edge; //just one PO
    };
	degree_t out_degree;//Will contain flag, if required
	degree_t in_degree;//Will contain flag, if required
} po_t;


po_t*		spo;
int32_t     count_spo;

//predicate indices. As per our analysis, we need second index on O only. 
//This second index will help in specially FILTER queries 
//So, it is more like a CSR representation. However, to support dynamic rdf graph,
// we will manage it each adj list separatly. 
//Also, note that, the size of adjacency list of each one is going to be very big,
//as number of predicates are small while number of triples are like billions.

typedef struct __so_t {
	o_t o;
	s_t s;
} so_t;

typedef struct __so_indirect {
	int32_t count;
	so_t* os; //B-tree/Hashtable key = object.
} so_indirect_t;

so_indirect_t*		pos;


//Type indices. As per our analysis, we don't need any second index.
//XXX:Let's see if we need second index or not.
//XXX: This could be stored as bitmap as well as almost every S 
//will have a type.
s_t** ts; //This could be S or O but only those O which are S as well.


class graph {

}

#endif
