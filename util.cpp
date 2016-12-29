#include "util.h"

void graph::prep_meta_nt(string idirname)
{
    string type = "<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>";
   
    //spo
    unordered_map<string, int32_t> str_to_sid;
    unordered_map<string, int32_t>::iterator  str_to_sid_iter;
    vector<string> sid_to_str;
    vector<int32_t> sp_count;//in-edges and out-edges count
    //For each subject- predicate pair, how many objects.
    unordered_map<sp_pair_t, int32_t> spo_count;
    
    //For each object, predicate pair, how many subjects.
    unordered_map<op_pair_t, int32_t> ops_count;

    
    //POS
    unordered_map<string, int> str_to_pid;
    vector<string> pid_to_str;
    vector<int> os_count;
    //For each object, predicate pair, how many subjects.
    unordered_map<po_pair_t, int> pos_count;
    
    str_to_pid[type] = 0;
    pid_str[0] = type;
    
    //TS
    unordered_map<string, int> str_to_tid;
    vector<string> tid_to_str;
    vector<int> type_count;

    struct dirent *ptr;
    DIR *dir;
    dir=opendir(idirname);
    
    int spo_id = 0;//IRI subjects/object
    int obj_id = 0; // literal objects
    int p_id = 0;//predicate id
    int t_id = 0;//type id
    
    int file_count = 1;
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.')
            continue;
        ifstream file((idirname + "/" + string(ptr->d_name)).c_str());
        cout << "No." << count<< ", loading " << ptr->d_name<<endl;
        file_count++;
        
        string subject, predict, object, useless_dot;
        int32_t current_sid, current_pid, current_oid;
        
        while (file >> subject >> predict >> object >> useless_dot) {
            
            str_to_sid_iter = str_to_sid_iter.find(subject);
            if (str_to_sid_iter == str_to_sid.end()) {
                assert(is_literal(subject));
    			str_to_sid[subject] = spo_id;
                current_sid = spo_id;
                spo_id++;
                sid_to_str.push_back(subject);
    		} else {
                current_sid = *str_to_sid_iter;
            }


            if (predict == type) { //type case
                str_to_tid_iter = str_to_tid_iter.find(object);
                if (str_to_tid_iter == str_to_tid.end()) {
        			str_to_tid[object] = t_id;
                    t_id++;
                    tid_to_str.push_back(object);
                    type_count[current_tid] = 1;
                } else {
                    current_tid = *str_to_tid_iter;
                    ++type_count[current_tid];
                }

                st

            } else { //predicate case.
                str_to_pid_iter = str_to_pid.find(predict);
                if (str_to_pid_iter == str_to_pid.end()) {
                    str_to_pid[predict] = p_id;
                    current_pid = p_id;
                    p_id++;
                    pid_to_str.push_back(predict);
                } else {
                    current_pid = *str_to_pid_iter;
                }

                if (is_literal(object)) {
                    ++obj_id;

                } else {
                    str_to_sid_iter = str_to_sid.find(object);
                    if (str_to_sid_iter == str_to_sid.end()) {
                        str_to_id[object] = spo_id;
                        spo_id++;
                        sid_to_str.push_back(object);
                    }
                }
            } 
        }
    }

    {
        ofstream f_normal((string(argv[2])+"/str_normal").c_str());
        for(int i=0;i<normal_str.size();i++){
            f_normal<<normal_str[i]<<"\t"<<str_to_id[normal_str[i]]<<endl;
        }
    }
    {
        ofstream f_index((string(argv[2])+"/str_index").c_str());
        for(int i=0;i<index_str.size();i++){
            f_index<<index_str[i]<<"\t"<<str_to_id[index_str[i]]<<endl;
        }
    }
    cout<<"sizeof str_to_id="<<str_to_id.size()<<endl;
    cout<<"sizeof normal_str="<<normal_str.size()<<endl;
    cout<<"sizeof index_str="<<index_str.size()<<endl;
}
