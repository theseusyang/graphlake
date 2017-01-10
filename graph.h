#ifndef __GRAPH_H_
#define __GRAPH_H_

//#include <unordered_map>
#include <string>
#include <stdint.h>
#include <map>
#include <vector>

#include "typedef.h"
#include "btree.h"

using namespace std;


/*B-tree/hashtable for adjacency list 
 * Some S/0 might have more than one O/S for same P.
 * Such as publication and author relashionship.
 * Here one professor/student can have multiple publication and
 * same publication could have multiple authors.
*/	
class edges_t {
private:
	degree_t degree;//Will contain flag, if required
	union {
        btree_t* edges_tree;//many PO
        leaf_node_t* edges;//upto 32 PO
        pair_t edge; //just one PO
    };

public:
    //allocate spaces now so that bulk insert can go fast.
    inline status_t 
    initial_setup (int degree)
    {
        return 0;
    }
    inline status_t 
    initial_insert(key_t key, value_t value)
    { return 0; }
    
    inline status_t 
    initial_insert(pair_t pair)
    { return 0 ; }
    
    inline value_t 
    search(key_t key) {return 0;}

    inline status_t
    insert(key_t key, value_t value)
    { return 0;}

    
    inline status_t
    remove(key_t key, value_t value)
    { return 0;}

    inline status_t
    remove(pair_t pair)
    { return 0;}
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
    edges_t out_edges;
    edges_t in_edges;
} po_t;

//predicate indices. As per our analysis, we need second index on O only. 
//This second index will help in specially FILTER queries 
//So, it is more like a CSR representation. However, to support dynamic rdf graph,
// we will manage it each adj list separatly. 
//Also, note that, the size of adjacency list of each one is going to be very big,
//as number of predicates are small while number of triples are like billions.

typedef struct __os_t {
    edges_t edges;
} os_t;



//Type indices. As per our analysis, we don't need any second index.
//XXX:Let's see if we need second index or not.
//XXX: This could be stored as bitmap as well as almost every S 
//will have a type.

typedef struct __adj_t {
    private:
	degree_t in_degree;//Will contain flag, if required
    //XXX: arranging only keys, not key-value.
    union {
	    btree_t* in_edges_tree; //many PO
        leaf_node_t* in_edges;//upto 32 PO
        pair_t in_edge; //just one PO
    };

    public: 
    //allocate spaces now so that bulk insert can go fast.
    inline status_t 
    initial_setup (int degree)
    {
        return 0;
    }
    inline status_t 
    initial_insert(key_t value)
    { return 0; }
    
    inline value_t 
    search(key_t key) {return 0;}

    inline status_t
    insert(key_t value)
    { return 0;}

    
    inline status_t
    remove(key_t value)
    { return 0;}

    inline status_t
    remove(pair_t pair)
    { return 0;}
} adj_t;

typedef struct __ts_t {
    adj_t plain_edges;
    
} ts_t;


class graph {
private:
    po_t*		spo;
    os_t*       pos;

    //This could be S or O but only those O which are S as well.
    //Literal and type objects are not valid S.
    ts_t*       ts; 
    
    int32_t     count_spo;
    int32_t     count_pos;
    int32_t     count_type;

    //string mappers
    //XXX will be replaced soon.
    vector<string> literal_to_str;
    map<string, int32_t> str_to_literal;
    
    vector<string> sid_to_str;
    map<string, int32_t> str_to_sid;

    vector<string> pid_to_str;
    map<string, int32_t> str_to_pid;
    
    vector<string> tid_to_str;
    map<string, int32_t> str_to_tid;
   
public:
	inline 	s_t 
	find_str2sid(string str) {return -1;}

public:    
    void prep_meta_nt(string idirname);
    status_t run_query(string queryfile);
};

//HashTable/KV-store for literal to ID mapping
//typedef unordered_map<string, literal_id_t> literal2id_t;
//class literal2id_t { };

//literal2id_t	literal2id;

//plain array for ID to literal mapping
/*class id2literal_t {
};

id2literal_t	id2literal; 
*/
#endif
