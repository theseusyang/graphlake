#pragma once
#include <stdint.h>
#include <limits.h>

typedef int32_t literal_id_t;
typedef char* literal_t;

//typedef int32_t index_t;
typedef int32_t degree_t;
typedef int32_t s_t;
typedef int32_t o_t;
typedef int32_t p_t;
typedef int32_t flag_t;

typedef int32_t key_t;
typedef int32_t value_t;
typedef int32_t status_t;

typedef struct __pair_t {
    key_t key; // predicate
    value_t value; //subject/object
} pair_t;

#define KEY_MAX INT_MAX

#define success 0
#define keyExist 1 
#define keyvalueExist 2
#define splitLeaf	3
#define keyNotFound	4