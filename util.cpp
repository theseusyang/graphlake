#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <assert.h>
#include <string>
#include "graph.h"
#include "util.h"
#include <map>

#define unordered_map map

using namespace std;


static int 
is_literal(string str) {
       return ('<' != str[0]);
}

void graph::prep_meta_nt(string idirname)
{
    string type = "<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>";
   
    //spo
    vector<string> sid_to_str;
    map<string, int32_t> str_to_sid;
    map<string, int32_t>::iterator  str_to_sid_iter;

    vector<int32_t> sp_count;//out-edges count
    vector<int32_t> op_count;//in-edges count
    
    //For each subject-predicate pair, how many objects.
    map<sp_pair_t, int32_t> spo_count;
    map<sp_pair_t, int32_t>::iterator spo_count_iter;
    
    
    //For each object-predicate pair, how many subjects.
    map<op_pair_t, int32_t> ops_count;
    map<op_pair_t, int32_t>::iterator ops_count_iter;

    
    //POS
    vector<string> pid_to_str;
    map<string, int> str_to_pid;
    map<string, int>::iterator str_to_pid_iter;
    vector<int> po_count;//in-edges count 

    //For each predicate-object pair, how many subjects.
    map<po_pair_t, int> pos_count;
    map<po_pair_t, int>::iterator pos_count_iter;
    
    str_to_pid[type] = 0;
    pid_to_str[0] = type;
    
    //TS
    map<string, int32_t> str_to_tid;
    map<string, int32_t>::iterator str_to_tid_iter;
    vector<string> tid_to_str;
    vector<int32_t> type_count;//in-edges count

    struct dirent *ptr;
    DIR *dir;
    dir = opendir(idirname.c_str());
    
    int spo_id = 0;//IRI subjects/object
    int literal_id = 0; // literal objects
    int p_id = 0;//predicate id
    int t_id = 0;//type id

    sp_pair_t sp_pair;
    duet_t so_pair;
    po_pair_t po_pair;
    op_pair_t op_pair;
    
    int file_count = 1;
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.')
            continue;
        //cout << "No." << count << ", loading " << ptr->d_name << endl;
        
        ifstream file((idirname + "/" + string(ptr->d_name)).c_str());
        file_count++;
        
        string subject, predict, object, useless_dot;
        int32_t current_sid, current_pid, current_oid = 0, current_tid;
        
        while (file >> subject >> predict >> object >> useless_dot) {
            
            str_to_sid_iter = str_to_sid.find(subject);
            if (str_to_sid_iter == str_to_sid.end()) {
                assert(is_literal(subject));
    			str_to_sid[subject] = spo_id;
                current_sid = spo_id;
                spo_id++;
                sid_to_str.push_back(subject);
                sp_count[current_sid] = 0; // out-edge
    		} else {
                current_sid = str_to_sid_iter->second;
            }


            if (predict == type) { //type case
                str_to_tid_iter = str_to_tid.find(object);
                if (str_to_tid_iter == str_to_tid.end()) {
        			str_to_tid[object] = t_id;
                    current_tid = t_id;
                    t_id++;
                    tid_to_str.push_back(object);
                    type_count[current_tid] = 1; //type initilaization
                } else {
                    current_tid = str_to_tid_iter->second;
                    type_count[current_tid] += 1; // type increment
                }

                //out-edge count for types predicate
                sp_pair.first = current_sid;
                sp_pair.second = 0;
                spo_count_iter = spo_count.find(sp_pair);
                if (spo_count_iter == spo_count.end()) {
                    sp_count[current_sid] = +1; // out-edges increments
                    spo_count[sp_pair] = 1;
                } else {
                    spo_count[sp_pair] += 1;
                }

            } else { //predicate case.
                str_to_pid_iter = str_to_pid.find(predict);
                if (str_to_pid_iter == str_to_pid.end()) {
                    str_to_pid[predict] = p_id;
                    current_pid = p_id;
                    p_id++;
                    pid_to_str.push_back(predict);
                    po_count[current_pid] = 0; // predicate initialization
                } else {
                    current_pid = str_to_pid_iter->second;
                }

                //object handling. XXX blank node handling pending.
                if (is_literal(object)) { //literal objects
                    //out-edges-yes
                    //in-edges- no
                    //PO - yes
                    //POS - yes
                    str_to_sid_iter = str_to_sid.find(object);
                    if (str_to_sid_iter == str_to_sid.end()) {
                        ++literal_id;
                        str_to_sid[object] = spo_id;
                        current_oid = spo_id;
                        spo_id++;
                        sid_to_str.push_back(object);
                    } else {
                        current_oid = spo_id;
                    }

                } else { // IRI objects
                    str_to_sid_iter = str_to_sid.find(object);
                    if (str_to_sid_iter == str_to_sid.end()) {
                        str_to_sid[object] = spo_id;
                        current_oid = spo_id;
                        spo_id++;
                        sid_to_str.push_back(object);
                        op_count[current_oid] = 0;//in-edges initialization
                    } else {
                        current_oid = str_to_sid_iter->second;
                    }

                    //in-edge counts for spo table for predicates
                    op_pair.first = current_oid;
                    op_pair.second = current_pid;
                    ops_count_iter = ops_count.find(op_pair);
                    if (ops_count_iter == ops_count.end()) {
                        op_count[current_oid] = +1; // in-edges increment
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
                    sp_count[current_sid] = +1; // out-edges increment
                    spo_count[sp_pair] = 1;
                } else {
                    spo_count[sp_pair] += 1;
                }


                //POS table 
                po_pair.first = current_pid;
                po_pair.second = current_oid;
                pos_count_iter = pos_count.find(po_pair);
                if (pos_count_iter == pos_count.end()) {
                    po_count[current_pid] += 1; //predicate increment
                    pos_count[po_pair] = 1;
                } else {
                    pos_count[po_pair] += 1;
                }
            } 

        }
    }

    cout<<"sizeof str_to_id="<<str_to_sid.size()<<endl;
}
