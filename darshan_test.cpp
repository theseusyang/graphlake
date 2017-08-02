#include "graph.h"
#include "darshan_to_edge.h"
#include "typekv.h"
#include "query_triple.h"
#include "query_triplewithfilter.h"

typedef cfinfo_t* (*get_graph_instance)();
typedef prop_encoder_t* (*get_encoder_instance)();


map<string, get_graph_instance>  graph_instance;
map<string, get_encoder_instance>  encoder_instance;

void schema_darshan(const string& conf_file)
{
    g->cf_info  = new cfinfo_t*[64];
    g->p_info       = new pinfo_t[64];
    
    pinfo_t*    p_info    = g->p_info;
    cfinfo_t*   info      = 0;
    prop_encoder_t* encoder = 0;
    const char* longname  = 0;
    const char* shortname = 0;
    const char* p_name = 0;
    const char* p_type = 0;

    //read the conf file
    char* line = 0;
    size_t len = 0;
    ssize_t read;
    char* saveptr;
    char* token;
    int value = -1;
    char splchar = '%'; 
    string delim = " ";
    string schema = "%%schema%%";
    map<string, get_graph_instance>::iterator iter1;
    map<string, get_encoder_instance>::iterator iter2;


    FILE* fp = fopen(conf_file.c_str(), "r");
    if (NULL == fp) assert(0);

    while((read = getline(&line, &len, fp)) != -1) {
        if (line[0] == splchar && line[1] == splchar) {
            if (0 == strncmp(line, schema.c_str(), 10)) value = 0;
            else assert(0);
        
        } else {
            if (0 == value) {
                if( 0 == (token = strtok_r(line, delim.c_str(), &saveptr))) {
                    assert(0);
                }
                longname = token;
                shortname = token;
                g->add_property(longname);
                p_info->populate_property(longname, shortname);
                
                if( 0 == (token = strtok_r(line, delim.c_str(), &saveptr))) {
                    assert(0);
                }
                iter1 = graph_instance.find(token);
                if (graph_instance.end() == iter1) {
                    assert(0);
                }
                info = iter1->second();

                if( 0 != (token = strtok_r(line, delim.c_str(), &saveptr))) {
                    p_name = token;
                    token = strtok_r(line, delim.c_str(), &saveptr);
                    iter2 = encoder_instance.find(token);
                    if (encoder_instance.end() == iter2) {
                        assert(0);
                    }
                    encoder = iter2->second();
                    info->add_edge_property(p_name, encoder);
                }
                g->add_columnfamily(info);
                info->create_columns();
                info->add_column(p_info);
                ++p_info;
            }
        
        }
    }
}
