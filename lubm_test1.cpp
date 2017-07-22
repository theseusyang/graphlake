#include "graph.h"
#include "nt_to_edge.h"
#include "typekv.h"
#include "query_triple.h"
#include "query_triplewithfilter.h"


void fill_lubm_inference_type()
{
    typekv_t* typekv = dynamic_cast<typekv_t*>(g->cf_info[0]);
    
    //students
    const char* name = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#Student>";
    const char* member;
    univ_t value;
    tid_t count = 2;
    tid_t* tlist = new tid_t[count];

    member  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#GraduateStudent>"; 
    if (eOK != g->cf_info[0]->get_encoded_value(member, &value)) {
        assert(0);
    }
    tlist[0] = value.value_tid;
    
    member  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#UndergraduateStudent>"; 
    if (eOK != g->cf_info[0]->get_encoded_value(member, &value)) {
        assert(0);
    }
    tlist[1] = value.value_tid;

    typekv->populate_inference_type(name, count, tlist);
    
    //professor
    name = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#Professor>";
    count = 4;
    tlist = new tid_t[count];

    member  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#FullProfessor>"; 
    if (eOK != g->cf_info[0]->get_encoded_value(member, &value)) {
        assert(0);
    }
    tlist[0] = value.value_tid;
    
    member  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#AssociateProfessor>"; 
    if (eOK != g->cf_info[0]->get_encoded_value(member, &value)) {
        assert(0);
    }
    tlist[1] = value.value_tid;

    member  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#AssistantProfessor>"; 
    if (eOK != g->cf_info[0]->get_encoded_value(member, &value)) {
        assert(0);
    }
    tlist[2] = value.value_tid;
    
    member  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#Lecturer>"; 
    if (eOK != g->cf_info[0]->get_encoded_value(member, &value)) {
        assert(0);
    }
    tlist[3] = value.value_tid;
    typekv->populate_inference_type(name, count, tlist);
}

void ontology_lubm()
{
    g->cf_info  = new cfinfo_t*[32];
    g->p_info       = new pinfo_t[32];
    
    pinfo_t*    p_info    = g->p_info;
    cfinfo_t*   info      = 0;
    const char* longname  = 0;
    const char* shortname = 0;
    
    longname = "<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>";
    shortname = "type";
    g->add_property(longname);
    //g->str2pid[longname] = g->p_count;
    //g->p_count++;
    p_info->populate_property(longname, shortname);
    info = new typekv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#advisor>";
    shortname = "advisor";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#affiliatedOrganizationOf>";
    shortname =  "affiliatedOrganizationOf";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;

    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#affiliateOf>";
    shortname = "affiliateOf";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#degreeFrom>";
    shortname =  "degreeFrom";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#doctoralDegreeFrom>";
    shortname = "doctoralDegreeFrom";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    //inference, inverse of degree from
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#hasAlumnus>");
    
    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#headOf>";
    shortname = "headOf";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#listedCourse>","listedCourse");
    
    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#mastersDegreeFrom>";
    shortname = "mastersDegreeFrom";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    //inference, inverse of memberof
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#member>", "member");
    
    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#memberOf>";
    shortname =  "memberOf";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#orgPublication>", "orgPublication");
    
    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#publicationAuthor>";
    shortname = "publicationAuthor";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new dgraph_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#publicationResearch>", "publicationResearch");
    
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#researchProject>", "researchProject");
    
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#softwareDocumentation>", "softwareDocumentation");
    
    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#takesCourse>";
    shortname = "takesCourse";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new dgraph_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#teacherOf>";
    shortname = "teacherOf";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2many_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#teachingAssistantOf>";
    shortname = "teachingAssistantOf";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    //info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#tenured>", "tenured");
    
    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#undergraduateDegreeFrom>";
    shortname = "undergraduateDegreeFrom";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#worksFor>";
    shortname = "worksFor";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#subOrganizationOf>";
    shortname = "subOrganizationOf";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    
    /*********************************************/
    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#publicationDate>";
    shortname = "publicationDate";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#softwareVersion>";
    shortname = "softwareVersion";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
  
  /*  
    p_info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#age>", "age");
    info = new uint8kv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
*/

    /*
    p_info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#officeNumber>", "officeNumber");
    info = new uint64kv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    */

    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#researchInterest>";
    shortname = "researchInterest";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#title>";
    shortname = "title";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    
    /*
    p_info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#name>", "name");
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    p_info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#emailAddress>", "emailAddress");
    //info = new stringkv_t;
    info = new manykv_t;
    info->create_columnfamily(2);
    info->add_column(p_info);
    ++p_info;
    
    //info = new uint64kv_t;
    p_info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#telephone>", "telephone");
    //info = new stringkv_t;
    //g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    */

    /*
    p_info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#emailAddress>", "emailAddress");
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    //info = new uint64kv_t;
    p_info->populate_property("<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#telephone>", "telephone");
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    */

    /********************/
    
    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#name>";
    shortname = "name";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    //info = new stringkv_t;
    info = new manykv_t;
    g->add_columnfamily(info);
    info->create_columns(3);
    info->add_column(p_info);
    ++p_info;
    
    
    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#emailAddress>";
    shortname = "emailAddress";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    //info = new stringkv_t;
    //g->add_columnfamily(info);
    //info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    //info = new uint64kv_t;
    longname = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#telephone>";
    shortname =  "telephone";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    //info = new stringkv_t;
    //g->add_columnfamily(info);
    //info->create_columns();
    info->add_column(p_info);
    ++p_info;
}

void test1()
{
    const char* src = "<http://www.Department10.University1.edu/UndergraduateStudent2>"; 
    //const char* pred = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#advisor>"; 
    const char* pred = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#takesCourse>"; 
    //const char* dst = "<http://www.Department10.University1.edu/FullProfessor1>" ;
    
    query_clause query;
    query_whereclause qwhere;
    
    
    query_triple qt;
    qt.set_src(src);
    qt.set_pred(pred);
    qt.set_dst("?x", 0);
    qt.set_traverse(eTransform);
    qt.set_query(&query);

    qwhere.add_child(&qt);
    query.add_whereclause(&qwhere);
    query.setup_qid(1, 1);

    srset_t* srset = query.get_srset(0);
    srset->setup_select(1);
    srset->create_select(0, "?x", 0);
    
    g->run_query(&query);
}

void test2()
{
    /* select ?x ?Y1
     * where {
     *   ?x rdf:type    ub:FullProfessor.
     *   ?x ub:worksFor <http://www.Department0.University0.edu>">.
     *   ?y ub:publicationAuthor ?x.
     *   ?y ub:name ?Y1.
     *
     *
     */
    const char* pred1 = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#worksFor>";
    const char* dst1 = "<http://www.Department0.University0.edu>";
    
    //const char* pred = "<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>";
    const char* dst  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#FullProfessor>";
    
    const char* pred2 = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#publicationAuthor>";
    const char* name_pred = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#name>";
    
    query_whereclause qwhere;
    query_clause query;
    query_triple qt1;
    query_triple qt2;
    srset_t* srset;
    typekv_t* typekv = dynamic_cast<typekv_t*>(g->cf_info[0]);
    
    //other setup
    query.add_whereclause(&qwhere);
    query.setup_qid(2, 2);
    
    //first query
    qt1.set_src("?x", 0);
    qt1.set_pred(pred1);
    qt1.set_dst(dst1);
    qt1.set_query(&query);
    qt1.set_traverse(eTransform);
    qwhere.add_child(&qt1);
    
    //Select info
    srset = query.get_srset(0);
    srset->setup_select(1);
    srset->create_select(0, "?x", 0);

    //type filter
    tid_t* tids;
    qid_t  t_counts;
    if (eOK != typekv->get_encoded_values(dst, &tids, &t_counts)) {
        assert(0);
    }
    srset->setup_tfilter(t_counts);
    for (tid_t i = 0; i < t_counts; ++i) {
        srset->create_tfilter(i, tids[i]);
    }
    
    //second query
    qt2.set_src("?y", 1);
    qt2.set_pred(pred2);
    qt2.set_dst("?x", 0);
    qt2.set_qplan(eInward);
    qt2.set_traverse(eExtend);
    qt2.set_query(&query);
    qwhere.add_child(&qt2);
    
    srset = query.get_srset(1);
    srset->setup_select(1);
    srset->create_select(0, "?y", name_pred);

    g->run_query(&query);

}

void lubm_1()
{
/*    
# Query1
# This query bears large input and high selectivity. It queries about just one class and
# one property and does not assume any hierarchy information or inference.
    PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>
    PREFIX ub: <http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#>
    SELECT ?X  WHERE {
     ?X rdf:type ub:GraduateStudent .
     ?X ub:takesCourse <http://www.Department0.University0.edu/GraduateCourse0>
    }
*/
    //const char* pred = "<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>";
    const char* dst  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#GraduateStudent>";
    //const char* dst  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#UndergraduateStudent>";
    
    const char* pred1 = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#takesCourse>";
    const char* dst1 = "<http://www.Department0.University0.edu/GraduateCourse0>";
    
    query_whereclause qwhere;
    query_clause query;
    query.add_whereclause(&qwhere);
    query.setup_qid(1,1);
    srset_t* srset;
    typekv_t* typekv = dynamic_cast<typekv_t*>(g->cf_info[0]);

    query_triple qt1;
    qt1.set_src("?x", 0);
    qt1.set_pred(pred1);
    qt1.set_dst(dst1);
    qt1.set_traverse(eTransform);
    qt1.set_query(&query);
   
    //select info
    srset = query.get_srset(0);
    srset->setup_select(1);
    srset->create_select(0, "?x", 0);
    
    //type filter
    tid_t* tids;
    qid_t  t_counts;
    if (eOK != typekv->get_encoded_values(dst, &tids, &t_counts)) {
        assert(0);
    }
    srset->setup_tfilter(t_counts);
    for (tid_t i = 0; i < t_counts; ++i) {
        srset->create_tfilter(i, tids[i]);
    }

    qwhere.add_child(&qt1);
    g->run_query(&query);
}

void lubm_1_1()
{
/*    
# Query1
# This query bears large input and high selectivity. It queries about just one class and
# one property and does not assume any hierarchy information or inference.
    PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>
    PREFIX ub: <http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#>
    SELECT ?X  WHERE {
     ?X rdf:type ub:GraduateStudent .
     ?X ub:takesCourse <http://www.Department0.University0.edu/GraduateCourse0>
    }
*/
    //const char* pred = "<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>";
    //const char* dst  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#GraduateStudent>";
    const char* dst  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#Student>";
    
    const char* pred1 = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#takesCourse>";
    const char* dst1 = "<http://www.Department0.University0.edu/GraduateCourse0>";
    
    query_whereclause qwhere;
    query_clause query;
    query.add_whereclause(&qwhere);
    query.setup_qid(1,1);
    srset_t* srset;
    typekv_t* typekv = dynamic_cast<typekv_t*>(g->cf_info[0]);

    query_triple qt1;
    qt1.set_src("?x", 0);
    qt1.set_pred(pred1);
    qt1.set_dst(dst1);
    qt1.set_traverse(eTransform);
    qt1.set_query(&query);
   
    //select info
    srset = query.get_srset(0);
    srset->setup_select(1);
    srset->create_select(0, "?x", 0);
    
    //type filter
    tid_t* tids;
    qid_t  t_counts;
    if (eOK != typekv->get_encoded_values(dst, &tids, &t_counts)) {
        assert(0);
    }
    srset->setup_tfilter(t_counts);
    for (tid_t i = 0; i < t_counts; ++i) {
        srset->create_tfilter(i, tids[i]);
    }

    qwhere.add_child(&qt1);
    g->run_query(&query);
}

void lubm_4()
{

/* Query 4
 * SELECT ?X, ?Y1, ?Y2, ?Y3
        WHERE
        {?X rdf:type ub:Professor .
        ?X ub:worksFor <http://www.Department0.University0.edu> .
        ?X ub:name ?Y1 .
        ?X ub:emailAddress ?Y2 .
        ?X ub:telephone ?Y3}
*/
    //const char* pred = "<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>";
    const char* dst  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#FullProfessor>";
    
    const char* pred1 = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#worksFor>";
    const char* dst1 = "<http://www.Department0.University0.edu>";
    
    const char* name_pred = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#name>";
    const char* email_pred = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#emailAddress>";
    const char* telephone_pred = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#telephone>";
    
    query_whereclause qwhere;
    query_clause query;
    query.add_whereclause(&qwhere);
    query.setup_qid(1,1);
    srset_t* srset;
    typekv_t* typekv = dynamic_cast<typekv_t*>(g->cf_info[0]);
    
    query_triple qt1;
    qt1.set_src("?x", 0);
    qt1.set_pred(pred1);
    qt1.set_dst(dst1);
    qt1.set_traverse(eTransform);
    qt1.set_query(&query);
    
    //select info
    srset = query.get_srset(0);
    srset->setup_select(4);
    srset->create_select(0, "?x1", 0);
    srset->create_select(1, "?Y1", name_pred);
    srset->create_select(2, "?Y2", email_pred);
    srset->create_select(3, "?Y3", telephone_pred);
    
    //type filter
    tid_t* tids;
    qid_t  t_counts;
    if (eOK != typekv->get_encoded_values(dst, &tids, &t_counts)) {
        assert(0);
    }
    srset->setup_tfilter(t_counts);
    for (tid_t i = 0; i < t_counts; ++i) {
        srset->create_tfilter(i, tids[i]);
    }

    qwhere.add_child(&qt1);
    g->run_query(&query);
}

void lubm_4_1()
{

/* Query 4
 * SELECT ?X, ?Y1, ?Y2, ?Y3
        WHERE
        {?X rdf:type ub:Professor .
        ?X ub:worksFor <http://www.Department0.University0.edu> .
        ?X ub:name ?Y1 .
        ?X ub:emailAddress ?Y2 .
        ?X ub:telephone ?Y3}
*/
    //const char* pred = "<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>";
    const char* dst  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#Professor>";
    
    const char* pred1 = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#worksFor>";
    const char* dst1 = "<http://www.Department0.University0.edu>";
    
    const char* name_pred = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#name>";
    const char* email_pred = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#emailAddress>";
    const char* telephone_pred = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#telephone>";
    
    query_whereclause qwhere;
    query_clause query;
    query.add_whereclause(&qwhere);
    query.setup_qid(1,1);
    srset_t* srset;
    typekv_t* typekv = dynamic_cast<typekv_t*>(g->cf_info[0]);
    
    query_triple qt1;
    qt1.set_src("?x", 0);
    qt1.set_pred(pred1);
    qt1.set_dst(dst1);
    qt1.set_traverse(eTransform);
    qt1.set_query(&query);
    
    //select info
    srset = query.get_srset(0);
    srset->setup_select(4);
    srset->create_select(0, "?x1", 0);
    srset->create_select(1, "?Y1", name_pred);
    srset->create_select(2, "?Y2", email_pred);
    srset->create_select(3, "?Y3", telephone_pred);
    
    //type filter
    tid_t* tids;
    qid_t  t_counts;
    if (eOK != typekv->get_encoded_values(dst, &tids, &t_counts)) {
        assert(0);
    }
    srset->setup_tfilter(t_counts);
    for (tid_t i = 0; i < t_counts; ++i) {
        srset->create_tfilter(i, tids[i]);
    }

    qwhere.add_child(&qt1);
    g->run_query(&query);
}

void test3()
{
    const char* src = "<http://www.Department10.University3.edu/UndergraduateStudent2>"; 
    //const char* pred = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#advisor>"; 
    const char* pred = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#takesCourse>"; 
    //const char* dst = "<http://www.Department10.University1.edu/FullProfessor1>" ;
    
    query_clause query;
    query_whereclause qwhere;
    
    
    query_triple qt;
    qt.set_src(src);
    qt.set_pred(pred);
    qt.set_dst("?x", 0);
    qt.set_traverse(eTransform);
    qt.set_query(&query);

    qwhere.add_child(&qt);
    query.add_whereclause(&qwhere);
    query.setup_qid(1, 1);

    srset_t* srset = query.get_srset(0);
    srset->setup_select(1);
    srset->create_select(0, "?x", 0);
    
    g->run_query(&query);
}

void test_update()
{
    string idir = "/mnt/raid0_huge/rdfdata/lubm-4univ-seed0/nt-data-rest/";
    string odir = "del/";
    string typefile = "/mnt/raid0_huge/rdfdata/lubm-4univ-seed0/type-rest.txt";
    ntriple_manager::prep_type(typefile, odir);
    ntriple_manager::prep_graph(idir, odir);
}

void lubm_test0(const string& typefile, const string& idir, const string& odir)
{
    ontology_lubm();
    if (!typefile.empty()) {
        ntriple_manager::prep_type(typefile, odir);
        fill_lubm_inference_type();
    }
    ntriple_manager::prep_graph(idir, odir);
    
    test1();
    test2();
    lubm_1();
    lubm_1_1();
    lubm_4(); 
    lubm_4_1();
    cout << "----------test3-------------" << endl;
    test3();
    /* */
}


void lubm_test1(const string& typefile, const string& idir, const string& odir)
{
    ontology_lubm();
    if (!typefile.empty()) {
        ntriple_manager::prep_type(typefile, odir);
        fill_lubm_inference_type();
    }
    ntriple_manager::prep_graph(idir, odir);
    
    test1();
    test2();
    lubm_1();
    lubm_1_1();
    lubm_4(); 
    lubm_4_1();
    test_update();
    cout << "----------test3-------------" << endl;
    test3();
    /* */
}

void lubm_test2(const string& odir)
{
    ontology_lubm();
    g->read_graph_baseline(odir);
    fill_lubm_inference_type();
    test1();
    test2();
    lubm_1();
    lubm_1_1();
    lubm_4(); 
    lubm_4_1();
    cout << "----------test3-------------" << endl;
    test3();
}
