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

struct wls_weight_t {
    uint32_t time;
    uint16_t event_id;
    uint16_t logon_id;
};

typedef dst_weight_t<wls_weight_t> wls_dst_t;

inline index_t parse_wls_line(char* line, edgeT_t<wls_dst_t>& wls)
{
    if (line[0] == '%') {
        return eNotValid;
    }
    
    Document d;
    d.Parse(line);
    
    Value::ConstMemberIterator itr = d.FindMember("ProcessID");
    if (itr != d.MemberEnd()) {
        string proc_id = itr->value.GetString();
        //wls.dst_id.first = strtol(proc_id.c_str(), NULL, 0); 
        wls.dst_id.first = g->type_update(proc_id.c_str(), "process");
    } else {
        return eNotValid;
    }

    string user_name = d["UserName"].GetString();
    user_name += "@";
    
    itr = d.FindMember("DomainName");
    if (itr != d.MemberEnd()) {
        user_name += d["DomainName"].GetString();
        wls.src_id = g->type_update(user_name.c_str(), "user");
    } else {
        return eNotValid;
    }
    

    //Value& s = d["Time"];
    //int i = s.GetInt();
    
    wls.dst_id.second.time = d["Time"].GetInt();
    wls.dst_id.second.event_id = d["EventID"].GetInt();

    string logon_id = d["LogonID"].GetString();
    wls.dst_id.second.logon_id = strtol(logon_id.c_str(), NULL, 0); 
    
    //insert
    pgraph_t<wls_dst_t>* pgraph = (pgraph_t<wls_dst_t>*)g->get_sgraph(2);
    pgraph->batch_edge(wls);

    edge_t edge;
    itr = d.FindMember("ParentProcessID");
    if (itr != d.MemberEnd()) {
        string proc_id = itr->value.GetString();
        //edge.dst_id = strtol(proc_id.c_str(), NULL, 0); 
        edge.dst_id = g->type_update(proc_id.c_str(), "process");
        edge.src_id = wls.dst_id.first;

        //insert
        pgraph_t<sid_t>* pgraph = (pgraph_t<sid_t>*)g->get_sgraph(1);
        pgraph->batch_edge(edge);
    }
    
    return eOK;
}

template <class T>
index_t parsefile_and_multi_insert(const string& textfile, const string& ofile, pgraph_t<T>* pgraph) 
{
    FILE* file = fopen(textfile.c_str(), "r");
    assert(file);
    
    edgeT_t<T> netflow;
    index_t icount = 0;
	char sss[512];
    char* line = sss;

    while (fgets(sss, sizeof(sss), file)) {
        line = sss;
        if (eOK == parse_wls_line(line, netflow)) {
            icount++;
        }
    }
    
    fclose(file);
    return 0;
}

//--------------- netflow functions ------------------
// Actual parse function, one line at a time
inline index_t parse_netflow_line(char* line, edgeT_t<netflow_dst_t>& netflow) 
{
    if (line[0] == '%') {
        return eNotValid;
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
        
    return eOK;
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
        if (eOK == parse_netflow_line(line, netflow)) {
            pgraph->batch_edge(netflow);
        }
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

