#include <algorithm>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <assert.h>
#include <string>
#include <map>

using namespace std;

typedef uint32_t pid_t;

class p_info_t{
    char*      p_name;
};

map <string, pid_t> p_str2id;
p_info_t*       p_info;
pid_t           p_count = 0

populate_property(const char* value)
{
   p_info[p_count++].p_name = gstrdup(value);

}

void ontologyi_lubm()
{
    populate_property("<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#advisor>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#affiliatedOrganizationOf>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#affiliateOf>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#degreeFrom>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#doctoralDegreeFrom>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#hasAlumnus>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#headOf>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#listedCourse>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#mastersDegreeFrom>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#member>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#memberOf>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#orgPublication>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#publicationAuthor>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#publicationDate>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#publicationResearch>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#researchProject>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#softwareDocumentation>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#softwareVersion>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#takesCourse>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#teacherOf>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#teachingAssistantOf>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#tenured>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#undergraduateDegreeFrom>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#worksFor>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#subOrganizationOf>");
    populate_property("<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#age>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#emailAddress>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#name>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#officeNumber>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#researchInterest>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#telephone>");
    populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#title>");
}

static int 
is_literal(string str) {
       return ('<' != str[0]);
}

void graph::prep_meta_nt(string idirname)
{
