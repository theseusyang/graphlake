#include "graph.h"
#include "csv_to_edge.h"
#include "typekv.h"
#include "query_triple.h"
#include "query_triplewithfilter.h"


void schema_ldbc()
{
    g->cf_info  = new cfinfo_t*[32];
    g->p_info       = new pinfo_t[32];
    
    pinfo_t*    p_info    = g->p_info;
    cfinfo_t*   info      = 0;
    const char* longname  = 0;
    const char* shortname = 0;
    
    longname = "type";
    shortname = "type";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new typekv_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "comment_hasCreator_person";
    longname = "comment_hasCreator_person";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "comment_hasTag_tag";
    longname = "comment_hasTag_tag";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "comment_isLocatedIn_place";
    longname = "comment_isLocatedIn_place";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "comment_replyOf_comment";
    shortname = "comment_replyOf_comment";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "comment_replyOf_post";
    shortname = "comment_replyof_post";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "post_hasCreator_person";
    longname = "post_hasCreator_person";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "post_hasTag_tag";
    longname = "post_hasTag_tag";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "post_isLocatedIn_place";
    shortname = "post_isLocatedIn_place";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "forum_containerOf_post";
    shortname = "forum_containerOf_post";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "forum_hasMember_person";
    shortname = "forum_hasMember_person";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "forum_hasModerator_person";
    shortname = "forum_hasModerator_person";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "forum_hasTag_tag";
    shortname = "forum_hasTag_tag";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "organisation_isLocatedIn_place";
    shortname = "organisation_isLocatedIn_place";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;

    longname = "person_hasInterest_tag";
    shortname = "person_hasInterest_tag";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "person_isLocatedIn_place";
    shortname = "person_isLocatedIn_place";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "person_knows_person";
    shortname = "person_knows_person";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new dgraph_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "person_likes_comment";
    shortname = "person_likes_comment";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "person_likes_post";
    shortname = "person_likes_post";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "person_speaks_language";
    shortname = "person_speaks_language";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "person_studyAt_organisation";
    shortname = "person_studyAt_organisation";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "person_workAt_organisation";
    shortname = "person_workAt_organisation";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;

    longname = "place_isPartOf_place";
    shortname = "place_isPartOf_place";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
    
    longname = "tagclass_isSubclassOf_tagclass";
    shortname = "tagclass_isSubclassOf_tagclass";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;

    longname = "tag_hasType_tagclass";
    shortname = "tag_hasType_tagclass";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new one2one_t;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    ++p_info;
   
    /*-------------------- Properties ---------------------------*/
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
