#include "graph.h"
#include "darshan_to_edge.h"
#include "query.h"


static void test1()
{
    //const char* src = "1873093688";
    const char* dst = "553013589";
    const char* pred = "job_to_exe";
    
    query_clause query;
    query_whereclause qwhere;
    
    query_triple qt;
    qt.set_dst(dst);
    qt.set_pred(pred);
    qt.set_src("?x", 0);
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

static void test2()
{
    //const char* dst = "643414734603356867";
    const char* pred = "CP_BYTES_READ";
    const char* src = "18730936880";
    
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

static void test3()
{
    //const char* dst = "16159277956655692221";
    const char* dst = "6643414734603356867";
    //const char* pred = "CP_POSIX_READS";
    const char* pred = "CP_F_OPEN_TIMESTAMP";
    //const char* src = "18730936882";
    
    query_clause query;
    query_whereclause qwhere;
    
    query_triple qt;
    qt.set_dst(dst);
    qt.set_pred(pred);
    qt.set_src("?x", 0);
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

static void test4()
{
}

void darshan_test0(const string& conf_file, const string& idir, const string& odir)
{
    g->create_schema(255, conf_file);
    
    darshan_manager::prep_graph(conf_file, idir, odir);
    cout << "----------Test 1-----------------" << endl;
    test1();
    cout << "----------Test 2-----------------" << endl;
    test2();
    cout << "----------Test 3-----------------" << endl;
    test3();
    cout << "----------Test 4-----------------" << endl;
    test4();
}
