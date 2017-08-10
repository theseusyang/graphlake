#pragma once
#include <stdint.h>
#include <limits.h>
#include <string>
#include <time.h>
#include <assert.h>
#include "bitmap.h"

using std::string;


typedef uint16_t propid_t;
typedef uint64_t vid_t;
typedef uint64_t sid_t;
typedef uint64_t eid_t;
typedef uint64_t index_t;
typedef uint32_t tid_t;
typedef uint64_t sflag_t;
typedef uint16_t qid_t;
typedef uint32_t pos_t; //adj list position, how long an adj list can be
//typedef int32_t status_t;

#define VBIT 40
#define VMASK 0xffffffffff
#define THIGH_MASK 0x7FFFFF0000000000
#define DEL_MASK   0x8000000000000000
#define SID_MASK   0x7FFFFFFFFFFFFFFF


#define TO_TID(sid)  ((sid & THIGH_MASK) >> VBIT)
#define TO_VID(sid)  (sid & VMASK)
#define TO_SID(sid)  (sid & SID_MASK)
#define TO_SUPER(tid) (((sid_t)(tid)) << VBIT)
#define TO_THIGH(sid) (sid & THIGH_MASK)
#define DEL_SID(sid) (sid | DEL_MASK)
#define IS_DEL(sid) (sid & DEL_MASK)

#define TID_TO_SFLAG(tid) (1L << tid)
#define WORD_COUNT(count) ((count + 63) >> 6)

extern propid_t INVALID_PID;
extern tid_t    INVALID_TID;
extern sid_t    INVALID_SID;

//#define INVALID_PID 0xFFFF
//#define INVALID_TID 0xFFFFFFFF
//#define INVALID_SID 0xFFFFFFFFFFFFFFFF

#define NO_QID 0xFFFF

off_t fsize(const string& fname);

enum direction_t {
    eout = 0, 
    ein
};

enum status_t {
    eOK = 0,
    eInvalidPID,
    eInvalidVID,
    eQueryFail,
    eEndBatch,
    eDelete,
    eUnknown        
};

typedef union __univeral_type {
    char*    value_charp;
    char     value_string[8];
    double   value_double;
    int64_t value_64b;
    uint8_t  value_8b;
    uint16_t value16b;
    tid_t    value_tid;
    vid_t    value_vid;
    sid_t    value_sid;
    eid_t    value_eid;
    time_t   value_time;
}univ_t;


template <class T>
class  edgeT_t {
 public:
    sid_t src_id;
    T     dst_id;
};

//First can be nebr sid, while the second could be edge id/property
class lite_edge_t {
 public:
    sid_t first;
    univ_t second;
};

typedef edgeT_t<sid_t> edge_t;
typedef edgeT_t<lite_edge_t> ledge_t;


/*
class ledge_t {
 public:
     sid_t src_id;
     sid_t dst_id;
     univ_t prop;
};
*/

class pedge_t {
 public:
    propid_t pid;
    sid_t src_id;
    univ_t dst_id;
};


class disk_vtable_t {
    public:
    vid_t    vid;
    uint64_t degree;
    uint64_t file_offset;
};

//property name value pair
struct prop_pair_t {
    string name;
    string value;
};


typedef struct __econf_t {
    string filename;
    string predicate;
    string src_type;
    string dst_type;
    string edge_prop;
} econf_t; 

typedef struct __vconf_t {
    string filename;
    string predicate;
} vconf_t; 

