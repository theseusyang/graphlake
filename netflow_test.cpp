
#include "all.h"
#include "netflow_to_edge.h"


netflow_manager_t netflow_manager;

void netflow_test(const string& idir, const string& odir, int job) 
{
    switch(job) {
        case 0:
        netflow_manager.prep_graph(idir, odir);
        break;

        case 1:
        netflow_manager.netflow_text_to_bin_idir(idir, odir);
        break;
    }
}
