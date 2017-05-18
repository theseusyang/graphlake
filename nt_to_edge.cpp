#include <algorithm>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <assert.h>
#include <string>
#include <map>
#include "graph.h"


using std::ifstream;

void fill_lubm_inference_type();

void graph::prep_graph(string typefile, string idirname, string odirname)
{
    struct dirent *ptr;
    DIR *dir;
    string subject, predicate, object, useless_dot;
    int file_count = 0;
    
    //Read typefile for types 
        ifstream file(typefile.c_str());
        int nt_count= 0;
        file_count++;
        file >> subject >> predicate >> object >> useless_dot;
        file >> subject >> predicate >> object >> useless_dot;
        propid_t pid;
        map<string, propid_t>::iterator str2pid_iter;
        while (file >> subject >> predicate >> object >> useless_dot) {
            str2pid_iter = str2pid.find(predicate);
            if (str2pid_iter == str2pid.end()) {
                assert(0);
            }
            pid = str2pid_iter->second;
            if( pid == 0) { // type
                g->type_update(subject, object);
                ++nt_count;
            }
        }
    g->type_done();
    
    
    //Read graph file
    dir = opendir(idirname.c_str());
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        
        ifstream file((idirname + "/" + string(ptr->d_name)).c_str());
        int nt_count= 0;
        file_count++;
        file >> subject >> predicate >> object >> useless_dot;
        file >> subject >> predicate >> object >> useless_dot;
        propid_t pid;
        map<string, propid_t>::iterator str2pid_iter;
        while (file >> subject >> predicate >> object >> useless_dot) {
            str2pid_iter = str2pid.find(predicate);
            if (str2pid_iter == str2pid.end()) {
                assert(0);
            }
            pid = str2pid_iter->second;
            if (pid != 0) { //non-type
                p_info[pid]->batch_update(subject, object);
                ++nt_count;
            //} else { //Is already handled above
            }
        }
    }
    closedir(dir);

    //swap 
    for (int i = 0; i < p_count; i++) {
        p_info[i]->swap_log_buffer();
    }
    
    //make graph
    for (int i = 0; i < p_count; i++) {
        p_info[i]->make_graph_baseline();
    }

    //Store graph
    for (int i = 0; i < p_count; i++) {
        p_info[i]->store_graph_baseline(odirname);
    }
}

void graph::update_graph(string idirname, string odirname)
{
    struct dirent *ptr;
    DIR *dir;
    string subject, predicate, object, useless_dot;
    int file_count = 0;

    //reset the log buffer, flags
    for (int i = 0; i < p_count; i++) {
        p_info[i]->reset();
    }
    
    //Read graph file for types 
    dir = opendir(idirname.c_str());
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        
        ifstream file((idirname + "/" + string(ptr->d_name)).c_str());
        int nt_count= 0;
        file_count++;
        file >> subject >> predicate >> object >> useless_dot;
        file >> subject >> predicate >> object >> useless_dot;
        propid_t pid;
        map<string, propid_t>::iterator str2pid_iter;
        while (file >> subject >> predicate >> object >> useless_dot) {
            str2pid_iter = str2pid.find(predicate);
            if (str2pid_iter == str2pid.end()) {
                assert(0);
            }
            pid = str2pid_iter->second;
            if( pid == 0) { // type
                g->type_update(subject, object);
                ++nt_count;
            }
        }
    }
    closedir(dir);
    g->type_done();
    
    
    //Read graph file
    dir = opendir(idirname.c_str());
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        
        ifstream file((idirname + "/" + string(ptr->d_name)).c_str());
        int nt_count= 0;
        file_count++;
        file >> subject >> predicate >> object >> useless_dot;
        file >> subject >> predicate >> object >> useless_dot;
        propid_t pid;
        map<string, propid_t>::iterator str2pid_iter;
        while (file >> subject >> predicate >> object >> useless_dot) {
            str2pid_iter = str2pid.find(predicate);
            if (str2pid_iter == str2pid.end()) {
                assert(0);
            }
            pid = str2pid_iter->second;
            if (pid != 0) { //non-type
                p_info[pid]->batch_update(subject, object);
                ++nt_count;
            }
        }
    }
    closedir(dir);

    //swap 
    for (int i = 0; i < p_count; i++) {
        p_info[i]->swap_log_buffer();
    }
    //make graph
    for (int i = 0; i < p_count; i++) {
        p_info[i]->make_graph_update();
    }

    //Store graph
    for (int i = 0; i < p_count; i++) {
        p_info[i]->store_graph_update(odirname);
    }
}

void fill_lubm_inference_type()
{
    typekv_t* typekv = dynamic_cast<typekv_t*>(g->p_info[0]);
    
    //students
    const char* name = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#Student>";
    const char* member;
    univ_t value;
    tid_t count = 2;
    tid_t* tlist = new tid_t[count];

    member  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#GraduateStudent>"; 
    if (eOK != g->p_info[0]->get_encoded_value(member, &value)) {
        assert(0);
    }
    tlist[0] = value.value_tid;
    
    member  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#UndergraduateStudent>"; 
    if (eOK != g->p_info[0]->get_encoded_value(member, &value)) {
        assert(0);
    }
    tlist[1] = value.value_tid;

    typekv->populate_inference_type(name, count, tlist);
    
    //professor
    name = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#Professor>";
    count = 4;
    tlist = new tid_t[count];

    member  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#FullProfessor>"; 
    if (eOK != g->p_info[0]->get_encoded_value(member, &value)) {
        assert(0);
    }
    tlist[0] = value.value_tid;
    
    member  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#AssociateProfessor>"; 
    if (eOK != g->p_info[0]->get_encoded_value(member, &value)) {
        assert(0);
    }
    tlist[1] = value.value_tid;

    member  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#AssistantProfessor>"; 
    if (eOK != g->p_info[0]->get_encoded_value(member, &value)) {
        assert(0);
    }
    tlist[2] = value.value_tid;
    
    member  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#Lecturer>"; 
    if (eOK != g->p_info[0]->get_encoded_value(member, &value)) {
        assert(0);
    }
    tlist[3] = value.value_tid;
    typekv->populate_inference_type(name, count, tlist);

}

void ontology_lubm(string typefile, string idirname, string odirname)
{
    pinfo_t*  info = 0; 
    g->p_info       = new pinfo_t*[32];
    
    info = new typekv_t;
    info->populate_property("<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>", "type");
    
    info = new many2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#advisor>", "advisor");
    
    info = new many2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#affiliatedOrganizationOf>", "affiliatedOrganizationOf");

    info = new many2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#affiliateOf>","affiliateOf");
    
    info = new many2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#degreeFrom>", "degreeFrom");
    
    info = new many2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#doctoralDegreeFrom>","doctoralDegreeFrom");
    
    //inference, inverse of degree from
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#hasAlumnus>");
    
    info = new one2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#headOf>", "headOf");
    
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#listedCourse>","listedCourse");
    
    info = new many2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#mastersDegreeFrom>","mastersDegreeFrom");
    
    //inference, inverse of memberof
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#member>", "member");
    
    info = new many2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#memberOf>", "memberOf");
    
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#orgPublication>", "orgPublication");
    
    info = new dgraph_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#publicationAuthor>", "publicationAuthor");
    
    
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#publicationResearch>", "publicationResearch");
    
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#researchProject>", "researchProject");
    
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#softwareDocumentation>", "softwareDocumentation");
    
    info = new dgraph_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#takesCourse>", "takesCourse");
    
    info = new one2many_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#teacherOf>", "teacherOf");
    
    info = new one2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#teachingAssistantOf>", "teachingAssistantOf");
    
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#tenured>", "tenured");
    
    info = new many2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#undergraduateDegreeFrom>", "undergraduateDegreeFrom");
    
    info = new many2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#worksFor>", "worksFor");
    
    info = new many2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#subOrganizationOf>", "subOrganizationOf");
    
    
    /*********************************************/
    
    info = new stringkv_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#publicationDate>", "publicationDate");
    
    info = new stringkv_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#softwareVersion>", "softwareVersion");
    
    info = new uint8kv_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#age>", "age");
    
    info = new stringkv_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#emailAddress>", "emailAddress");
    
    info = new stringkv_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#name>", "name");
    
    info = new uint64kv_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#officeNumber>", "officeNumber");
    
    info = new stringkv_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#researchInterest>", "researchInterest");
    
    //info = new uint64kv_t;
    info = new stringkv_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#telephone>", "telephone");
    
    info = new stringkv_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#title>", "title");

    g->prep_graph(typefile, idirname, odirname);
    fill_lubm_inference_type();
}
