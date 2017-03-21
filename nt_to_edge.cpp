#include <algorithm>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <assert.h>
#include <string>
#include <map>
#include "graph.h"


using std::ifstream;


void graph::prep_graph(string idirname)
{
    struct dirent *ptr;
    DIR *dir;
    dir = opendir(idirname.c_str());
    string subject, predicate, object, useless_dot;
    int file_count = 1;
    
    //Read graph file
    while (NULL != (ptr = readdir(dir))) {
        if (ptr->d_name[0] == '.') continue;
        
        ifstream file((idirname + "/" + string(ptr->d_name)).c_str());
        file_count++;
        propid_t pid;
        while (file >> subject >> predicate >> object >> useless_dot) {
            pid = str2pid[predicate];
            p_info[pid]->batch_update(subject, object);
        }
    }

    //make graph
    for (int i = 0; i < p_count; i++) {
        p_info[i]->make_graph_baseline();
    }

    //Store graph
    for (int i = 0; i < p_count; i++) {
        p_info[i]->store_graph_baseline(idirname);
    }
}


void ontology_lubm()
{
    p_info_t* info = new many2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#advisor>");
    
    info = new many2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#affiliatedOrganizationOf>");

    info = new many2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#affiliateOf>");
    
    info = new many2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#degreeFrom>");
    
    info = new many2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#doctoralDegreeFrom>");
    
    //inference, inverse of degree from
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#hasAlumnus>");
    
    info = new one2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#headOf>");
    
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#listedCourse>");
    
    info = new many2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#mastersDegreeFrom>");
    
    //inference, inverse of memberof
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#member>");
    
    info = new many2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#memberOf>");
    
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#orgPublication>");
    
    info = new dgraph_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#publicationAuthor>");
    
    
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#publicationResearch>");
    
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#researchProject>");
    
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#softwareDocumentation>");
    
    info = new dgraph_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#takesCourse>");
    
    info = new one2many_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#teacherOf>");
    
    info = new one2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#teachingAssistantOf>");
    
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#tenured>");
    
    info = new many2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#undergraduateDegreeFrom>");
    
    info = new many2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#worksFor>");
    
    info = new many2one_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#subOrganizationOf>");
    
    
    /*********************************************/
    info = new enum8kv_t;
    info->populate_property("<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>");
    
    info = new stringkv_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#publicationDate>");
    
    info = new stringkv_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#softwareVersion>");
    
    
    info = new int8kv_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#age>");
    
    info = new stringkv_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#emailAddress>");
    
    info = new stringkv_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#name>");
    
    info = new int64kv_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#officeNumber>");
    
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#researchInterest>");
    
    info = new int64kv_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#telephone>");
    
    info = new stringkv_t;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#title>");
}


