#include "graph.h"

#include "query_triple.h"
#include "query_triplewithfilter.h"


void test1()
{
    const char* src = "<http://www.Department10.University1.edu/UndergraduateStudent2>"; 
    const char* pred = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#advisor>"; 
    //const char* dst = "<http://www.Department10.University1.edu/FullProfessor1>" ;
    
    query_clause query;
    query_whereclause qwhere;
    
    
    query_triple qt;
    qt.set_src(src);
    qt.set_pred(pred);
    qt.set_dst("?x", 0);
    qt.set_query(&query);

    qwhere.add_child(&qt);
    query.add_whereclause(&qwhere);
    query.setup_qid(1);
    query.add_selectclause(NULL, 0, 1);

    g->run_query(&query);
}

void test2()
{
    const char* pred1 = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#worksFor>";
    const char* dst1 = "<http://www.Department0.University0.edu>";
    
    const char* pred = "<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>";
    const char* dst  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#FullProfessor>";
    
    const char* pred2 = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#publicationAuthor>";
    const char* name_pred = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#name>";
    
    query_whereclause qwhere;
    query_clause query;
    query_triplewithfilter qt1;
    query_triple qt2;
    
    //first query
    qt1.set_src("?x", 1);
    qt1.set_pred(pred1);
    qt1.set_dst(dst1);
    qt1.set_query(&query);

    //Get the filter details
    pid_t type_pid = g->get_pid(pred);
    pinfo_t *labelgraph = g->p_info[type_pid];
    univ_t typevalue;
    if (eOK != g->p_info[0]->get_encoded_value(dst, &typevalue)) {
        assert(0);
    }
    qt1.set_filterobj(labelgraph, typevalue, fn_out);
    
    qwhere.add_child(&qt1);
    
    //second query
    qt2.set_src("?y", 0);
    qt2.set_pred(pred2);
    qt2.set_dst("?x", 1);
    qt2.set_qplan(eInward);
    qt2.set_query(&query);
    
    qwhere.add_child(&qt2);

    //other setup
    query.add_whereclause(&qwhere);
    query.setup_qid(2);

    select_info_t select_info[1];
    select_info[0].name = gstrdup("Y1");
    select_info[0].rgraph = g->p_info[g->get_pid(name_pred)];
    
    query.add_selectclause(select_info, 1, 1);

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
    const char* pred = "<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>";
    const char* dst  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#GraduateStudent>";
    //const char* dst  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#UndergraduateStudent>";
    
    const char* pred1 = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#takesCourse>";
    const char* dst1 = "<http://www.Department0.University0.edu/GraduateCourse0>";
    
    query_whereclause qwhere;
    query_clause query;
    
    query_triplewithfilter qt1;
    qt1.set_src("?x", 0);
    qt1.set_pred(pred1);
    qt1.set_dst(dst1);
    qt1.set_query(&query);

    //Get the filter details
    pid_t type_pid = g->get_pid(pred);
    pinfo_t *labelgraph = g->p_info[type_pid];
    univ_t typevalue;
    if (eOK != g->p_info[0]->get_encoded_value(dst, &typevalue)) {
        assert(0);
    }
    qt1.set_filterobj(labelgraph, typevalue, fn_out);
    
    qwhere.add_child(&qt1);
    
    query.add_whereclause(&qwhere);
    query.setup_qid(1);
    
    query.add_selectclause(NULL, 0, 1);

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
    const char* pred = "<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>";
    const char* dst  = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#FullProfessor>";
    
    const char* pred1 = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#worksFor>";
    const char* dst1 = "<http://www.Department0.University0.edu>";
    
    const char* name_pred = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#name>";
    const char* email_pred = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#emailAddress>";
    const char* telephone_pred = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#telephone>";
    
    query_whereclause qwhere;
    query_clause query;
    
    /*
    query_triple qt;
    qt.set_src("?x", 0);
    qt.set_pred(pred);
    qt.set_dst(dst);
    qwhere.add_child(&qt);
    */

    query_triplewithfilter qt1;
    qt1.set_src("?x", 0);
    qt1.set_pred(pred1);
    qt1.set_dst(dst1);
    qt1.set_query(&query);

    //Get the filter details
    pid_t type_pid = g->get_pid(pred);
    pinfo_t *labelgraph = g->p_info[type_pid];
    univ_t typevalue;
    if (eOK != g->p_info[0]->get_encoded_value(dst, &typevalue)) {
        assert(0);
    }
    qt1.set_filterobj(labelgraph, typevalue, fn_out);
    
    qwhere.add_child(&qt1);
    
    query.add_whereclause(&qwhere);
    query.setup_qid(1);

    select_info_t select_info[3];
    select_info[0].name = gstrdup("Y1");
    select_info[1].name = gstrdup("Y2");
    select_info[2].name = gstrdup("Y3");

    select_info[0].rgraph = g->p_info[g->get_pid(name_pred)];
    select_info[1].rgraph = g->p_info[g->get_pid(email_pred)];
    select_info[2].rgraph = g->p_info[g->get_pid(telephone_pred)];
    
    query.add_selectclause(select_info, 3, 1);

    g->run_query(&query);
}

void lubm() 
{
    test1();
    lubm_1();
    lubm_4();
    test2();
}

