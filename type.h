#pragma once
#include <stdint.h>
#include <limits.h>


typedef uint32_t propid_t;
typedef uint64_t vid_t;
typedef uint64_t sid_t;
typedef uint64_t index_t;
typedef uint32_t tid_t;
typedef uint64_t sflag_t;
typedef uint16_t qid_t;
//typedef int32_t status_t;

#define TO_TID(sid) (sid >> 40)
#define TO_VID(sid)  (sid & 0xffffffffff)
#define TO_SUPER(tid) (((sid_t)(tid)) << 40)

#define TID_TO_SFLAG(tid) (1L << tid)
#define WORD_COUNT(count) ((count + 63) >> 6)

#define INVALID_PID 0xFFFFFFFF
#define INVALID_SID 0xFFFFFFFFFFFFFFFF

#define NO_QID 0xFFFF

class pinfo_t;


enum direction_t {
    eout = 0, 
    ein
};

enum status_t {
    eOK = 0,
    eInvalidPID,
    eInvalidVID,
    eUnknown        
};

typedef struct __sid_set_t {
public:
    int count;
    sid_t* sids;
} sid_set_t;

enum filter_fn_t {
    fn_out = 0,//simple lookup 
    fn_ein, //simple inward lookup
};

struct filter_info_t {
    pinfo_t* rgraph;
    void* value;
    filter_fn_t filter_fn;
};
