#include "type.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
using namespace rapidjson;


struct wls_t {
    string     user_name;
    string     domainName;
    string     subject_user_name;
    string     subjectdomainName;
    vid_t      log_host;
    uint32_t   time;
    uint16_t   event_id;
    uint16_t   logonType;
    uint16_t   logon_id;
    uint16_t   subject_logon_id;
    string     logon_description; //string for logon type
    
    vid_t      proc_id;
    vid_t      proc_name;
    vid_t      parent_proc_id;
    vid_t      parent_proc_name;
    
    vid_t      src_computer;
    string     servicename;
    vid_t      dst_computer;
    string     auth_package;
    uint8_t    status;
    string     failure_reason;
};

struct wls_dst_t {
    uint32_t time;
    uint16_t event_id;
    uint16_t logon_id;
};

inline index_t parse_wls_line(char* line, edgeT_t<netflow_dst_t>& netflow)
{
    if (line[0] == '%') {
        return 0;
    }
    
    Document d;
    d.Parse(line);

    //string user_name = d["UserName"].getString();
    //user_name += "@" + d["DomainName"];


    //Value& s = d["Time"];
    //int i = s.GetInt();
    
    return 0;

}

//--------------- netflow functions ------------------
// Actual parse function, one line at a time
inline index_t parse_netflow_line(char* line, edgeT_t<netflow_dst_t>& netflow) 
{
    if (line[0] == '%') {
        return 0;
    }
    
    //const char* del = ",\n";
    char* token = 0;
    
    token = strtok_r(line, ",\n", &line);
    netflow.dst_id.second.time = atoi(token);
    token = strtok_r(line, ",\n", &line);
    netflow.dst_id.second.duration = atoi(token);
    
    token = strtok_r(line, ",\n", &line);
    netflow.src_id = g->type_update(token);
    token = strtok_r(line, ",\n", &line);
    netflow.dst_id.first = g->type_update(token);
    
    token = strtok_r(line, ",\n", &line);
    netflow.dst_id.second.protocol = atoi(token);
    
    token = strtok_r(line, ",\n", &line);
    if (token[0] == 'P') {
        netflow.dst_id.second.src_port = atoi(token+4);
    } else {
        netflow.dst_id.second.src_port = atoi(token);
    }
    token = strtok_r(line, ",\n", &line);
    if (token[0] == 'P') {
        netflow.dst_id.second.dst_port = atoi(token+4);
    } else {
        netflow.dst_id.second.dst_port = atoi(token);
    }
    token = strtok_r(line, ",\n", &line);
    
    netflow.dst_id.second.src_packet = atoi(token);
    token = strtok_r(line, ",\n", &line);
    netflow.dst_id.second.dst_packet = atoi(token);
    token = strtok_r(line, ",\n", &line);
    netflow.dst_id.second.src_bytes = atoi(token);
    token = strtok_r(line, ",\n", &line);
    netflow.dst_id.second.dst_bytes = atoi(token);
        
    return 0;
}
//---------------netflow functions done---------


//-----Two high level functions can be used by many single stream graph ----
template <class T>
index_t parsefile_and_insert(const string& textfile, const string& ofile, pgraph_t<T>* pgraph) 
{
    FILE* file = fopen(textfile.c_str(), "r");
    assert(file);
    
    edgeT_t<T> netflow;
    index_t icount = 0;
	char sss[512];
    char* line = sss;

    while (fgets(sss, sizeof(sss), file)) {
        line = sss;
        parse_netflow_line(line, netflow);
        pgraph->batch_edge(netflow);
        icount++;
    }
    
    fclose(file);
    return 0;
}


template <class T>
index_t parsefile_to_bin(const string& textfile, const string& ofile, pgraph_t<T>*pgraph)
{
	size_t file_size = fsize(textfile.c_str());
    size_t estimated_count = file_size/sizeof(edgeT_t<T>);
    
    
    FILE* file = fopen(textfile.c_str(), "r");
    assert(file);
    
    edgeT_t<T>* netflow_array = (edgeT_t<T>*)calloc(estimated_count, 
                                                      sizeof(edgeT_t<T>));
    assert(netflow_array);

    edgeT_t<T>* netflow = netflow_array;
    
    index_t icount = 0;
	char sss[512];
    char* line = sss;

    while (fgets(sss, sizeof(sss), file)) {
        line = sss;
        parse_netflow_line(line, *netflow);
        netflow++;
        icount++;
    }
    
    fclose(file);
    
    //write the binary file
    file = fopen(ofile.c_str(), "wb");
    fwrite(netflow_array, sizeof(edgeT_t<T>), icount, file);
    fclose(file);
    
    free(netflow_array);
    return 0;
}

