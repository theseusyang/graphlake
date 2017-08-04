#include "graph.h"
#include "darshan_to_edge.h"
#include "query.h"


static void test1()
{
    
}

static void test2()
{
}

static void test3()
{
}

static void test4()
{
}

void darshan_test0(const string& conf_file, const string& idir, const string& odir)
{
    g->create_schema(256, conf_file);
    
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
