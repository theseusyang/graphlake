#ifndef __UTIL_H_
#define __UTIL_H_

#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

struct __duet_t {
    int32_t first;
    int32_t second;
} duet_t;

typedef sp_pair_t duet_t;
typedef op_pair_t duet_t;
typedef po_pair_t duet_t;

struct __ts_t {
    int32_t 
} ts_t;

static int 
is_literal(string str) {
       return ('<' != str[0]);
}


#endif
