#include "multi_graph.h"

multi_graph_t::multi_graph_t()
{
}

void multi_graph_t::schema()
{
    g->cf_info = new cfinfo_t*[3];
    g->p_info = new pinfo_t[3];
    
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
    
    typekv_t* typekv = g->get_typekv();
    typekv->manual_setup(1<<20, "process");//processes are tid 0
    typekv->manual_setup(1<<20, "user");//users are tid 1
    
    longname = "proc2parent";
    shortname = "proc2parent";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new unigraph<sid_t>;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    info->flag1 = 1;
    info->flag2 = 1;
    ++p_info;
    
    longname = "user2proc";
    shortname = "user2proc";
    g->add_property(longname);
    p_info->populate_property(longname, shortname);
    info = new unigraph<wls_dst_t>;
    g->add_columnfamily(info);
    info->create_columns();
    info->add_column(p_info);
    info->flag1 = 2;
    info->flag2 = 1;
    ++p_info;
    
    
    g->prep_graph_baseline();
    g->file_open(true);
   // g->make_graph_baseline();
   // g->store_graph_baseline(); 
}

void multi_graph_t::prep_graph_fromtext(const string& idirname, const string& odirname, 
                                        typename callback<wls_dst_t>::parse_fn_t parsefile_fn)
{
    //-----
    g->create_snapthread();
    usleep(1000);
    //-----
    ugraph<wls_dst_t>* ugraph = 0; 
    //Batch and Make Graph
    double start = mywtime();
    read_idir_text<wls_dst_t>(idirname, odirname, ugraph, parsefile_fn);    
    double end = mywtime ();
    cout << "Batch Update Time = " << end - start << endl;
    
    /*
    blog_t<T>* blog = ugraph->blog;
    index_t marker = blog->blog_head;

    //----------
    if (marker != blog->blog_marker) {
        ugraph->create_marker(marker);
    }

    //Wait for make graph
    while (blog->blog_tail != blog->blog_head) {
        usleep(1);
    }
    */
    end = mywtime();
    cout << "Make graph time = " << end - start << endl;
    //---------
    
}
