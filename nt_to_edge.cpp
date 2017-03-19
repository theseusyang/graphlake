#include <algorithm>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <assert.h>
#include <string>
#include <map>

using namespace std;

void ontology_lubm()
{
    p_info_t* info = new info;
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#advisor>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#affiliatedOrganizationOf>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#affiliateOf>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#degreeFrom>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#doctoralDegreeFrom>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#hasAlumnus>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#headOf>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#listedCourse>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#mastersDegreeFrom>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#member>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#memberOf>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#orgPublication>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#publicationAuthor>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#publicationDate>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#publicationResearch>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#researchProject>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#softwareDocumentation>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#softwareVersion>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#takesCourse>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#teacherOf>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#teachingAssistantOf>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#tenured>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#undergraduateDegreeFrom>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#worksFor>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#subOrganizationOf>");
    
    info->populate_property("<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#age>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#emailAddress>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#name>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#officeNumber>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#researchInterest>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#telephone>");
    info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#title>");
}

static int 
is_literal(string str) {
       return ('<' != str[0]);
}

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
        pid_t pid;
        while (file >> subject >> predicate >> object >> useless_dot) {
            pid = str2pid[predicate];
            p_info[pid].batch_update(subject, object);
        }
    }

    //make graph
    for (int i = 0; i < p_count; i++) {
        p_info[pid]->make_graph_baseline();
    }

    //Store graph
    for (int i = 0; i < p_count; i++) {
        p_info[pid]->store_graph_baseline();
    }

}
