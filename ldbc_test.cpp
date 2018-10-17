#include "all.h"
#include "csv_to_edge.h"
#include "query.h"
//#include "iterative_analytics.h"

void schema_ldbc()
{
    g->cf_info  = new cfinfo_t*[64];
    g->p_info       = new pinfo_t[64];
    
    pinfo_t*    p_info    = g->p_info;
    cfinfo_t*   info      = 0;
    const char* longname  = 0;
    const char* shortname = 0;
    
    longname = "gtype";
    shortname = "gtype";
    info = new typekv_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    ++p_info;
    
    longname = "comment_hasCreator_person";
    shortname = "comment_hasCreator_person";
    info = new many2one_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<0);
    info->flag2 = (1<<2);
    ++p_info;
    
    longname = "comment_hasTag_tag";
    shortname = "comment_hasTag_tag";
    info = new dgraph_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<0);
    info->flag2 = (1<<5);
    ++p_info;
    
    longname = "comment_isLocatedIn_place";
    shortname = "comment_isLocatedIn_place";
    info = new many2one_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<0);
    info->flag2 = (1<<3);
    ++p_info;
    
    longname = "comment_replyOf_comment";
    shortname = "comment_replyOf_comment";
    info = new many2one_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<0);
    info->flag2 = (1<<0);
    ++p_info;
    
    longname = "comment_replyOf_post";
    shortname = "comment_replyof_post";
    info = new many2one_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<0);
    info->flag2 = (1<<4);
    ++p_info;
    
    longname = "post_hasCreator_person";
    shortname = "post_hasCreator_person";
    info = new many2one_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<4);
    info->flag2 = (1<<2);
    ++p_info;
    
    longname = "post_hasTag_tag";
    shortname = "post_hasTag_tag";
    info = new dgraph_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<4);
    info->flag2 = (1<<5);
    ++p_info;
    
    longname = "post_isLocatedIn_place";
    shortname = "post_isLocatedIn_place";
    info = new many2one_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<4);
    info->flag2 = (1<<3);
    ++p_info;
    
    longname = "forum_containerOf_post";
    shortname = "forum_containerOf_post";
    info = new one2many_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<1);
    info->flag2 = (1<<4);
    ++p_info;
    
    //Join Date is missing as property
    longname = "forum_hasMember_person";
    shortname = "forum_hasMember_person";
    info = new dgraph_t;
    //info = new p_dgraph_t;
    //info->add_edge_property("joinDate", new time_encoder_t);
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<1);
    info->flag2 = (1<<2);
    ++p_info;
    
    longname = "forum_hasModerator_person";
    shortname = "forum_hasModerator_person";
    info = new many2one_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<1);
    info->flag2 = (1<<2);
    ++p_info;
    
    longname = "forum_hasTag_tag";
    shortname = "forum_hasTag_tag";
    info = new dgraph_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<1);
    info->flag2 = (1<<5);
    ++p_info;
    
    longname = "organisation_isLocatedIn_place";
    shortname = "organisation_isLocatedIn_place";
    info = new many2one_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<7);
    info->flag2 = (1<<3);
    ++p_info;

    longname = "person_hasInterest_tag";
    shortname = "person_hasInterest_tag";
    info = new dgraph_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<2);
    info->flag2 = (1<<5);
    ++p_info;
    
    longname = "person_isLocatedIn_place";
    shortname = "person_isLocatedIn_place";
    info = new many2one_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<2);
    info->flag2 = (1<<3);
    ++p_info;
    
    //creation Date
    longname = "person_knows_person";
    shortname = "person_knows_person";
    info = new ugraph_t;
    //info = new p_ugraph_t;
    //info->add_edge_property("creationDate", new time_encoder_t);
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<2);
    info->flag2 = (1<<2);
    ++p_info;
   
    //creation date 
    longname = "person_likes_comment";
    shortname = "person_likes_comment";
    info = new dgraph_t;
    //info = new p_dgraph_t;
    //info->add_edge_property("creationDate", new time_encoder_t);
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<2);
    info->flag2 = (1<<0);
    ++p_info;
    
    //creation date
    longname = "person_likes_post";
    shortname = "person_likes_post";
    info = new dgraph_t;
    //info = new p_dgraph_t;
    //info->add_edge_property("creationDate", new time_encoder_t);
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<2);
    info->flag2 = (1<<4);
    ++p_info;
    
    //class year
    longname = "person_studyAt_organisation";
    shortname = "person_studyAt_organisation";
    info = new many2one_t;
    //info = new p_many2one_t;
    //info->add_edge_property("classYear", new int64_encoder_t);
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<2);
    info->flag2 = (1<<7);
    ++p_info;
    
    //workfrom year
    longname = "person_workAt_organisation";
    shortname = "person_workAt_organisation";
    info = new dgraph_t;
    //info = new p_dgraph_t;
    //info->add_edge_property("workFrom", new int64_encoder_t);
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<2);
    info->flag2 = (1<<7);
    ++p_info;

    longname = "place_isPartOf_place";
    shortname = "place_isPartOf_place";
    info = new many2one_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<3);
    info->flag2 = (1<<3);
    ++p_info;
    
    longname = "tagclass_isSubclassOf_tagclass";
    shortname = "tagclass_isSubclassOf_tagclass";
    info = new many2one_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<6);
    info->flag2 = (1<<6);
    ++p_info;

    longname = "tag_hasType_tagclass";
    shortname = "tag_hasType_tagclass";
    info = new many2one_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<5);
    info->flag2 = (1<<6);
    ++p_info;
   
    /*-------------------- Properties ---------------------------*/
    //Easy target of enum, multiple languages XXX
    longname = "person_speaks_language";
    shortname = "person_speaks_language";
    //info = new labelkv_t;
    //info->add_edge_property(longname, new embedstr_encoder_t);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<2);
    ++p_info;

    //XXX : multiple email ids
    longname = "person_email_emailaddress";
    shortname = "person_email_emailaddress";
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<2);
    ++p_info;
   
    longname = "creationDate";
    shortname = "creationDate";
    info = new stringkv_t;
    //info = new labelkv_t;
    //info->add_edge_property(longname, new time_encoder_t);
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<0) | (1<<1) | (1<<2) | (1<<4);
    ++p_info;
    
    longname = "locationIP";
    shortname = "locationIP";
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 =(1<<0) | (1<<2) | (1<<4);
    ++p_info;
    
    longname = "browserUsed";
    shortname = "browserUsed";
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<0)| (1<<2) | (1<<4);
    ++p_info;
    
    
    longname = "content";
    shortname = "content";
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<0) | (1<<4);
    ++p_info;
    
    longname = "length"; 
    shortname = "length"; 
    info = new numberkv_t<uint64_t>;
    //info = new labelkv_t;
    //info->add_edge_property("length", new int64_encoder_t);
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<0) | (1<<4);
    ++p_info;
    
    longname = "title"; 
    shortname = "title"; 
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<1);
    ++p_info;
    
    longname = "type";
    shortname = "type";
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<3) | (1<<7);
    ++p_info;
    
    longname = "name";
    shortname = "name";
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<3) | (1<<5) | (1<<6) | (1<<7);
    ++p_info;

    longname = "url";
    shortname = "url";
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<3) | (1<<5) | (1<<6)| (1<<7);
    ++p_info;
    
    longname = "firstName";
    shortname = "firstName";
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<2);
    ++p_info;
    
    longname = "lastName";
    shortname = "lastName";
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<2);
    ++p_info;
    
    longname = "gender";
    shortname = "gender";
    info = new stringkv_t;
    //info = new labelkv_t;
    //info->add_edge_property("gender", new embedstr_encoder_t);
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<2);
    ++p_info;
    
    longname = "birthday";
    shortname = "birthday";
    info = new stringkv_t;
    //info = new labelkv_t;
    //info->add_edge_property(longname, new time_encoder_t);
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<2);
    ++p_info;

    longname = "imageFile";
    shortname = "imageFile";
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<4);
    ++p_info;
    
    longname = "language";
    shortname = "language";
    info = new stringkv_t;
    //info->add_edge_property(longname, new embedstr_encoder_t);
    g->add_columnfamily(info);
    info->add_column(p_info, longname, shortname);
    info->flag1 = (1<<4);
    ++p_info;
}

static void test1()
{
    const char* src = "person32985348838898";
    const char* pred = "person_knows_person"; 
    
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

static void test2()
{
    const char* src = "person933"; 
    const char* pred = "person_knows_person"; 
    
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
    const char* dst = "person933"; 
    const char* pred = "comment_hasCreator_person"; 
    
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
    const char* src = "person933"; 
    const char* pred = "person_speaks_language"; 
    
    query_clause query;
    query.setup_qid(1, 1);
    srset_t* srset = query.get_srset(0);
    srset->setup_select(2);
    srset->create_select(0, "?x", 0);
    srset->create_select(1, "?Y1", pred);
            
    sid_t sid = g->get_sid(src);
    if (sid == INVALID_SID) assert(0);
    tid_t tid = TO_TID(sid);
    srset->setup(tid);
    srset->rset->setup_frontiers(tid, 1);
    srset->add_frontier(sid);

    
    g->run_query(&query);
}

static void test_bfs()
{
    /*
    const char* pred = "person_knows_person";
	propid_t cf_id = g->get_cfid(pred);
    p_ugraph_t* graph = (p_ugraph_t*)g->cf_info[cf_id];
	tid_t tid = g->get_tid("person");
	sid_t root = TO_SUPER(tid);
	bfs<lite_edge_t>(graph->sgraph, graph->sgraph, root);
    */
}

static void test_pagerank()
{
    /*
    const char* pred = "person_knows_person";
	propid_t cf_id = g->get_cfid(pred);
    p_ugraph_t* graph = (p_ugraph_t*)g->cf_info[cf_id];
	pagerank<lite_edge_t>(graph->sgraph, graph->sgraph, 5);
    */
}

void ldbc_test0(const string& conf_file, const string& idir, const string& odir)
{
    schema_ldbc();
    csv_manager::prep_graph(conf_file, idir, odir);
    cout << "----------Test 4-----------------" << endl;
    test4();
    cout << "----------Test 1-----------------" << endl;
    test1();
    cout << "----------Test 2-----------------" << endl;
    test2();
    cout << "----------Test 3-----------------" << endl;
    test3();
	cout << "-----------BFS -----------------" << endl;
	test_bfs();
	cout << "-----------Pagerank-------------" << endl;
	test_pagerank();
}

void ldbc_test2(const string& odir)
{
    schema_ldbc();
    g->read_graph_baseline();
    cout << "----------Test 4-----------------" << endl;
    test4();
    cout << "----------Test 1-----------------" << endl;
    test1();
    cout << "----------Test 2-----------------" << endl;
    test2();
    cout << "----------Test 3-----------------" << endl;
    test3();
	cout << "-----------BFS -----------------" << endl;
	test_bfs();
	cout << "-----------Pagerank-------------" << endl;
	test_pagerank();
}
