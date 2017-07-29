#include "graph.h"
#include "csv_to_edge.h"
#include "typekv.h"
#include "query_triple.h"
#include "query_triplewithfilter.h"


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
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new typekv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "comment_hasCreator_person";
    shortname = "comment_hasCreator_person";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "comment_hasTag_tag";
    shortname = "comment_hasTag_tag";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new dgraph_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "comment_isLocatedIn_place";
    shortname = "comment_isLocatedIn_place";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "comment_replyOf_comment";
    shortname = "comment_replyOf_comment";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "comment_replyOf_post";
    shortname = "comment_replyof_post";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "post_hasCreator_person";
    shortname = "post_hasCreator_person";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "post_hasTag_tag";
    shortname = "post_hasTag_tag";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new dgraph_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "post_isLocatedIn_place";
    shortname = "post_isLocatedIn_place";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "forum_containerOf_post";
    shortname = "forum_containerOf_post";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2many_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    //Join Date is missing as property
    longname = "forum_hasMember_person";
    shortname = "forum_hasMember_person";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new dgraph_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "forum_hasModerator_person";
    shortname = "forum_hasModerator_person";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "forum_hasTag_tag";
    shortname = "forum_hasTag_tag";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new dgraph_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "organisation_isLocatedIn_place";
    shortname = "organisation_isLocatedIn_place";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;

    longname = "person_hasInterest_tag";
    shortname = "person_hasInterest_tag";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new dgraph_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "person_isLocatedIn_place";
    shortname = "person_isLocatedIn_place";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    //creation Date
    longname = "person_knows_person";
    shortname = "person_knows_person";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new p_ugraph_t;
    info->add_edge_property("creationDate", new time_encoder_t);
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
   
    //creation date 
    longname = "person_likes_comment";
    shortname = "person_likes_comment";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new p_dgraph_t;
    info->add_edge_property("creationDate", new time_encoder_t);
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    //creation date
    longname = "person_likes_post";
    shortname = "person_likes_post";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new p_dgraph_t;
    info->add_edge_property("creationDate", new time_encoder_t);
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    //class year
    longname = "person_studyAt_organisation";
    shortname = "person_studyAt_organisation";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new p_many2one_t;
    info->add_edge_property("classYear", new int64_encoder_t);
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    //workfrom year
    longname = "person_workAt_organisation";
    shortname = "person_workAt_organisation";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new p_dgraph_t;
    g->add_columnfamily(info);
    info->add_edge_property("workFrom", new int64_encoder_t);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;

    longname = "place_isPartOf_place";
    shortname = "place_isPartOf_place";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "tagclass_isSubclassOf_tagclass";
    shortname = "tagclass_isSubclassOf_tagclass";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;

    longname = "tag_hasType_tagclass";
    shortname = "tag_hasType_tagclass";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new many2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
   
    /*-------------------- Properties ---------------------------*/
    //Easy target of enum, multiple languages XXX
    longname = "person_speaks_language";
    shortname = "person_speaks_language";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;

    //XXX : multiple email ids
    longname = "person_email_emailaddress";
    shortname = "person_email_emailaddress";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
   
    longname = "creationDate";
    shortname = "creationDate";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "locationIP";
    shortname = "locationIP";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "browserUsed";
    shortname = "browserUsed";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    
    longname = "content";
    shortname = "content";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "length"; 
    shortname = "length"; 
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "title"; 
    shortname = "title"; 
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "type";
    shortname = "type";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "name";
    shortname = "name";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;

    longname = "url";
    shortname = "url";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "firstName";
    shortname = "firstName";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "lastName";
    shortname = "lastName";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "gender";
    shortname = "gender";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "birthday";
    shortname = "birthday";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;

    longname = "imageFile";
    shortname = "imageFile";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "language";
    shortname = "language";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new stringkv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
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

void test3()
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

void test4()
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
}

void ldbc_test2(const string& odir)
{
    schema_ldbc();
    g->read_graph_baseline(odir);
    cout << "----------Test 4-----------------" << endl;
    test4();
    cout << "----------Test 1-----------------" << endl;
    test1();
    cout << "----------Test 2-----------------" << endl;
    test2();
    cout << "----------Test 3-----------------" << endl;
    test3();
}
