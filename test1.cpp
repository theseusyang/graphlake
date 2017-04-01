#include "graph.h"

#include "query_triple.h"

void test1()
{
    const char* src = "<http://www.Department10.University1.edu/UndergraduateStudent2>"; 
    const char* pred = "<http://www.lehigh.edu/~zhp2/2004/0401/univ-bench.owl#advisor>"; 
    //const char* dst = "<http://www.Department10.University1.edu/FullProfessor1>" ;
    
    query_triple qt;
    qt.set_src(src);
    qt.set_pred(pred);
    qt.set_dst("?x");
    
    query_whereclause qwhere;
    qwhere.add_child(&qt);
    
    query_clause query;
    query.add_whereclause(&qwhere);

    g->run_query(&query);
}
