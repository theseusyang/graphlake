#pragma once



//------- LANL 2017 -----
struct netflow_weight_t {
    uint32_t time;
    uint32_t duration;
    uint32_t protocol;
    uint16_t src_port;
    uint16_t dst_port;
    uint32_t src_packet;
    uint32_t dst_packet;
    uint32_t src_bytes;
    uint32_t dst_bytes;
};

typedef dst_weight_t<netflow_weight_t> netflow_dst_t;
typedef edgeT_t<netflow_dst_t> netflow_edge_t;
//------------

//------ LANL 2015 -----
//vid_t    src_user;
//vid_t    dst_user;
struct auth_weight_t {
    uint32_t time;
    vid_t    src_computer;
    vid_t    dst_computer;
    uint8_t  auth_type;
    uint8_t  logon_type;
    uint8_t  status;
};

//user
//computer
struct auth_proc_t {
    uint32_t time;
    uint16_t proc;
    uint8_t  action;
};

//src computer
//dst computer
struct auth_flow_t {
    uint32_t time;
    uint32_t duration;
    uint16_t src_port;
    uint16_t dst_port;
    uint32_t protocol;
    uint32_t packet_count;
    uint32_t byte_count;
};

//src_computer
//resolved computer
struct auth_dns_t {
    uint32_t time;
};

//src_user
//dst_computer
struct auth_redteam_t {
    uint32_t time;
    vid_t    src_computer;
};

typedef dst_weight_t<auth_weight_t> auth_dst_t;
typedef edgeT_t<auth_dst_t> auth_edge_t;
//----------------


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
//-----------------
