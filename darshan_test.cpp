#include "graph.h"
#include "darshan_to_edge.h"
#include "typekv.h"
#include "query_triple.h"
#include "query_triplewithfilter.h"

void schema_darshan()
{
    g->cf_info  = new cfinfo_t*[64];
    g->p_info       = new pinfo_t[64];
    
    pinfo_t*    p_info    = g->p_info;
    cfinfo_t*   info      = 0;
    const char* longname  = 0;
    const char* shortname = 0;
    
}
