#ifndef __GRAPH_H_
#define __GRAPH_H_

//#include <unordered_map>
#include <string>
#include <map>
#include <vector>

#include "edges.h"

using namespace std;


/*B-tree/hashtable for adjacency list 
 * Some S/0 might have more than one O/S for same P.
 * Such as publication and author relashionship.
 * Here one professor/student can have multiple publication and
 * same publication could have multiple authors.
*/	


/*SPO/OPS: Top level CSR format (similar to begpos in CSR). A plain array. 
  Each elements contain:
	B-tree/hashtable of in-edges
	in-degree information
	B-tree/hashtable of out-edges
	out-degree information
	Flag
*/

typedef d_unlabeled_edges_t po_t;

//PSO/POS: predicate indices. As per our analysis, we need second index on O only. 
//This second index will help in specially FILTER queries 
//So, it is more like a CSR representation. However, to support dynamic rdf graph,
// we will manage it each adj list separatly. 
//Also, note that, the size of adjacency list of each one is going to be very big,
//as number of predicates are small while number of triples are like billions.

typedef d_labeled_edges_t os_t;


//Type indices. As per our analysis, we don't need any second index.
//XXX:Let's see if we need second index or not.
//XXX: This could be stored as bitmap as well as almost every S 
//will have a type.


typedef kbtree_t ts_t;


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
	find_str2sid(string str) 
	{
		map<string, int32_t>::iterator str_to_sid_iter = str_to_sid.find(str);
		if (str_to_sid.end() != str_to_sid_iter) {
			return str_to_sid_iter->second;
		}	

		return -1;
	}
	inline p_t
	find_str2pred(string str) 
	{
		map<string, int32_t>::iterator str_to_pid_iter = str_to_pid.find(str);
		if (str_to_pid.end() != str_to_pid_iter) {
			return str_to_pid_iter->second;
		}
		return -1;
	}
	
	inline o_t
	find_str2type(string str) 
	{
		map<string, int32_t>::iterator str_to_tid_iter = str_to_tid.find(str);
		if (str_to_tid.end() != str_to_tid_iter) {
			return str_to_tid_iter->second;
		}
		return -1;
	}
	
	inline o_t
	find_str2literalid(string str) 
	{
		map<string, int32_t>::iterator str_to_literal_iter = str_to_literal.find(str);
		if (str_to_literal.end() != str_to_literal_iter) {
			return str_to_literal_iter->second;
		}
		return 0;
	}

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
