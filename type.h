#pragma once
#include <stdint.h>
#include <limits.h>


typedef uint32_t propid_t;
typedef uint64_t vid_t;
typedef uint64_t sid_t;
typedef uint64_t index_t;
typedef uint32_t tid_t;
typedef uint64_t sflag_t;

#define TO_TID(sid) (sid >> 40)
#define TO_VID(sid)  (sid & 0xffffffffff)
#define TO_SUPER(tid) (((sid_t)(tid)) << 40)
