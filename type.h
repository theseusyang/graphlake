#pragma once
#include <stdint.h>
#include <limits.h>
#include <string>

using std::string;


typedef uint32_t propid_t;
typedef uint64_t vid_t;
typedef uint64_t sid_t;
typedef uint64_t index_t;
typedef uint32_t tid_t;
typedef uint64_t sflag_t;
typedef uint16_t qid_t;
//typedef int32_t status_t;

#define VBIT 40
#define VMASK 0xffffffffff


#define TO_TID(sid) (sid >> VBIT)
#define TO_VID(sid)  (sid & VMASK)
#define TO_SUPER(tid) (((sid_t)(tid)) << VBIT)

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
    eQueryFail,
    eUnknown        
};

typedef union __univeral_type {
    char*    value_charp;
    uint64_t value_64b;
    uint8_t  value_8b;
    uint16_t value16b;
    tid_t    value_tid;
    vid_t    value_vid;
    sid_t    value_sid;
}univ_t;

typedef struct __sid_set_t {
public:
    int count;
    sid_t* sids;
} sid_set_t;

enum filter_fn_t {
    fn_out = 0,//simple lookup 
    fn_ein, //simple inward lookup
};

typedef struct __filter_info_t {
    pinfo_t* rgraph;
    univ_t   value;
    filter_fn_t filter_fn;
} filter_info_t;

typedef struct __select_info_t {
    pinfo_t* rgraph;
    string name; 
} select_info_t;



/////// Function//////////////
inline tid_t get_sindex(tid_t tid, sflag_t sflag)
{
    sflag_t flag_mask = sflag & ((1L << (tid +1)) - 1);
    tid_t        pos = __builtin_popcountll(flag_mask) - 1;
    return pos;
}
