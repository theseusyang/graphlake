#include <algorithm>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <assert.h>
#include <string>
#include "graph.h"
#include "util.h"

using namespace std;

static int 
is_literal(string str) {
       return ('<' != str[0]);
}

void graph::prep_meta_nt(string idirname)
{
    string type = "<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>";
    
    //As 0th index is useless due to negative index
    literal_to_str.push_back("literal");
    map<string, int32_t>::iterator  str_to_literal_iter;
   
    //spo
    map<string, int32_t>::iterator  str_to_sid_iter;

    vector<duet_t> sp_count;//in/out edges count
    
    //For each subject-predicate pair, how many objects.
    map<sp_pair_t, int32_t> spo_count;
    map<sp_pair_t, int32_t>::iterator spo_count_iter;
    
    
    //For each object-predicate pair, how many subjects.
    map<op_pair_t, int32_t> ops_count;
    map<op_pair_t, int32_t>::iterator ops_count_iter;

    //POS
    map<string, int32_t>::iterator str_to_pid_iter;
    vector<duet_t> po_count;//in-edges count 

    //For each predicate-object pair, how many subjects.
    map<po_pair_t, int32_t> pos_count;
    map<po_pair_t, int32_t>::iterator pos_count_iter;
    
	//For each predicate-object pair, how many subjects.
    map<ps_pair_t, int32_t> pso_count;
    map<ps_pair_t, int32_t>::iterator pso_count_iter;
    
    str_to_pid[type] = 0;
    pid_to_str.push_back(type);


    //TS
    map<string, int32_t>::iterator str_to_tid_iter;
    vector<int32_t> type_count;//in-edges count
    

    struct dirent *ptr;
    DIR *dir;
    dir = opendir(idirname.c_str());
    
    int32_t spo_id = 0;//IRI subjects/object
    int32_t literal_id = -1; // literal objects. Grows negative
    int32_t p_id = 0;//predicate id
    int t_id = 0;//type id

    sp_pair_t sp_pair;
    duet_t so_pair;
    po_pair_t po_pair;
    ps_pair_t ps_pair;
    op_pair_t op_pair;
        
    string subject, predicate, object, useless_dot;
    int32_t current_sid, current_pid, current_oid = 0, current_tid;
    
    int file_count = 1;
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.')
            continue;
        //cout << "No." << count << ", loading " << ptr->d_name << endl;
        
        ifstream file((idirname + "/" + string(ptr->d_name)).c_str());
        file_count++;
        
        
        while (file >> subject >> predicate >> object >> useless_dot) {
            
            str_to_sid_iter = str_to_sid.find(subject);
            if (str_to_sid_iter == str_to_sid.end()) {
                assert(!is_literal(subject));
    			str_to_sid[subject] = spo_id;
                current_sid = spo_id;
                spo_id++;
                sid_to_str.push_back(subject);
                sp_count.push_back(make_pair(0, 0)); //in/out edge initialization
    		} else {
                current_sid = str_to_sid_iter->second;
            }

            if (predicate == type) { //type case
                str_to_tid_iter = str_to_tid.find(object);
                if (str_to_tid_iter == str_to_tid.end()) {
        			str_to_tid[object] = t_id;
                    current_tid = t_id;
                    t_id++;
                    tid_to_str.push_back(object);
                    type_count.push_back(1); //type initilaization
                } else {
                    current_tid = str_to_tid_iter->second;
                    type_count[current_tid] += 1; // type increment
                }

                //out-edge count for types predicate
                sp_pair.first = current_sid;
                sp_pair.second = 0;
                spo_count_iter = spo_count.find(sp_pair);
                if (spo_count_iter == spo_count.end()) {
                    sp_count[current_sid].first += 1; // out-edges increments
                    spo_count[sp_pair] = 1; //initalization
                } else {
                    spo_count[sp_pair] += 1;
                }

            } else { //predicate case.
                str_to_pid_iter = str_to_pid.find(predicate);
                if (str_to_pid_iter == str_to_pid.end()) {
                    str_to_pid[predicate] = p_id;
                    current_pid = p_id;
                    p_id++;
                    pid_to_str.push_back(predicate);
                    po_count.push_back(make_pair(0,0)); // predicate initialization
                } else {
                    current_pid = str_to_pid_iter->second;
                }
                
				//object handling. XXX blank node handling pending.
                if (is_literal(object)) { //literal objects
                    str_to_literal_iter = str_to_literal.find(object);
                    if (str_to_literal_iter == str_to_literal.end()) {
                        str_to_literal[object] = literal_id;
                        literal_to_str.push_back(object);
                        current_oid = literal_id;
                        --literal_id;
                    } else {
                        current_oid = str_to_literal_iter->second;
                    }
                    //SPO out-edges -> yes
                    //SPO in-edges -> no
                    //PO - yes
                    //POS - yes

                } else { // IRI objects
                    str_to_sid_iter = str_to_sid.find(object);
                    if (str_to_sid_iter == str_to_sid.end()) {
                        str_to_sid[object] = spo_id;
                        current_oid = spo_id;
                        spo_id++;
                        sid_to_str.push_back(object);
                        sp_count.push_back(make_pair(0, 0));//in-edges initialization
                    } else {
                        current_oid = str_to_sid_iter->second;
                    }

                    //in-edge counts for spo table for predicates
                    op_pair.first = current_oid;
                    op_pair.second = current_pid;
                    ops_count_iter = ops_count.find(op_pair);
                    if (ops_count_iter == ops_count.end()) {
                        sp_count[current_oid].second += 1; // in-edges increment
                        ops_count[op_pair] = 1;
                    } else {
                        ops_count[op_pair] += 1;
                    }
                }

                //out-edge counts for spo table for predicates
                sp_pair.first = current_sid;
                sp_pair.second = current_pid;
                spo_count_iter = spo_count.find(sp_pair);
                if (spo_count_iter == spo_count.end()) {
                    sp_count[current_sid].first += 1; // out-edges increment
                    spo_count[sp_pair] = 1;
                } else {
                    spo_count[sp_pair] += 1;
                }


                //POS table 
                po_pair.first = current_pid;
                po_pair.second = current_oid;
                pos_count_iter = pos_count.find(po_pair);
                if (pos_count_iter == pos_count.end()) {
                    po_count[current_pid].second += 1; //predicate increment
                    pos_count[po_pair] = 1;
                } else {
                    pos_count[po_pair] += 1;
                }

                //PSO table
				ps_pair.first = current_pid;
                ps_pair.second = current_pid;
                pso_count_iter = pos_count.find(ps_pair);
                if (pos_count_iter == pos_count.end()) {
                    po_count[current_pid].first += 1; //predicate increment
                    pso_count[ps_pair] = 1;
                } else {
                    pso_count[ps_pair] += 1;
                }
            } 
        }
    }
    /*****************************************************************************************/
    //Printing the stats
    cout << endl << endl;
    cout << "spo_id " << spo_id << endl;
    cout << "literal_id " << literal_id << endl;

    int sp_count_size = sp_count.size();
    int in_edge_count = 0;
    int out_edge_count = 0;
    int only_in_edge = 0;
    int only_out_edge = 0;
    int empty = 0;
    int both = 0;
    cout << "sp_count = " << sp_count_size << endl;
    for (int i = 0 ; i < sp_count_size; ++i ) {
        out_edge_count += sp_count[i].first;
        in_edge_count += sp_count[i].second;
        if (sp_count[i].first != 0 && sp_count[i].second == 0) {
            ++only_out_edge;
        } else if (sp_count[i].first == 0 && sp_count[i].second != 0) {
            ++only_in_edge;
        } else if (sp_count[i].first == 0 && sp_count[i].second == 0) {
            ++empty;
        } else {
            ++both;
        }
    } 
    
    cout << "In edge count = " << in_edge_count << endl;
    cout << "out edge count = " << out_edge_count << endl;
    cout << "only out edge = " << only_out_edge << endl;
    cout << "only_in_edge = " << only_in_edge << endl;
    cout << "both = " << both << endl;
    cout << "empty = " << empty << endl;
    
    cout << endl << endl;
    cout << "spo_count = " << spo_count.size() << endl;
    int total_edges = 0;
    for (spo_count_iter = spo_count.begin(); 
         spo_count_iter != spo_count.end(); 
         ++spo_count_iter) {
        total_edges += spo_count_iter->second;
    }
    cout << "total_edges = " << total_edges << endl;
    
    cout << "ops_count = " << ops_count.size() << endl;
    total_edges = 0;
    for (ops_count_iter = ops_count.begin(); 
         ops_count_iter != ops_count.end(); 
         ++ops_count_iter) {
        total_edges += ops_count_iter->second;
    }
    cout << "total_edges = " << total_edges << endl;


    cout << endl << endl;
    
    cout << "po_count (except type) "   << po_count.size() << endl;
    int po_total = 0;
    for (unsigned int i  = 0; i < po_count.size(); ++i ) {
        po_total += po_count[i].second;
    }
    cout << "po total = " << po_total << endl;
    
    cout << "pos_count "   << pos_count.size() << endl;
    total_edges = 0;
    for (pos_count_iter = pos_count.begin(); 
         pos_count_iter != pos_count.end();
         ++pos_count_iter) {
        total_edges += pos_count_iter->second;
    }
    cout << "total_edges = " << total_edges << endl;
    
    cout << endl << endl;
    
    cout << "type_count " << type_count.size() << endl;
    int total_type = 0;
    for (unsigned int i = 0; i < type_count.size(); ++i) {
        total_type += type_count[i]; 
    }
    cout << "total type = " << total_type << endl;

    /****************************************************************************************/
    //Preparing the representation
    spo = new po_t[spo_id];
    pos = new os_t[p_id];
    ts = new ts_t[t_id];

    int32_t out_degree = 0;
    int32_t in_degree = 0;
    int32_t degree = 0;
    //int32_t leaf_count = 0;
    //int32_t level_count = 0;
    for (int32_t i = 0; i < spo_id; ++i ) {
        out_degree = sp_count[i].first;
        in_degree = sp_count[i].second;

        //out-edges
        spo[i].out_edges.initial_setup(out_degree);
        //in-edges
        spo[i].in_edges.initial_setup(in_degree);

    }

    //Predicates
    for (int32_t i = 0; i < p_id; ++i ) {
        out_degree = po_count[i].first;
        in_degree = po_count[i].second;
        pos[i].out_edges.initial_setup(out_degree);
        pos[i].in_edges.initial_setup(in_degree);
    }
    //Types
    for (int32_t i = 0; i < t_id; ++i) {
        degree = type_count[i];
        ts[i].initial_setup(degree);
    }

    //now populate the B+ trees
    closedir(dir);
    file_count = 0;
    dir = opendir(idirname.c_str());
    int literal = 0;
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.')
            continue;
        
        ifstream file((idirname + "/" + string(ptr->d_name)).c_str());
        file_count++;
        
        while (file >> subject >> predicate >> object >> useless_dot) {
            current_sid = str_to_sid[subject];
            current_pid = str_to_pid[predicate];
            literal = is_literal(object);
            if (literal) {
                current_oid = str_to_literal[object];
            } else {
                current_oid = str_to_sid[object];
            }

            //insert to out-edges
            spo[current_sid].out_edges.initial_insert(current_pid);

            if (0 == current_pid) {
                //Insert to type
                ts[current_oid].initial_insert(current_sid);
            } else if (literal) {
                //insert to predicate
                pos[current_pid].in_edges.initial_insert(current_oid, current_sid);
            } else {
                //insert to in-edge
                spo[current_oid].in_edges.initial_insert(current_pid);
                //insert to predicate
                pos[current_pid].out_edges.initial_insert(current_sid, current_oid);
            }
        }
    }

	

}
