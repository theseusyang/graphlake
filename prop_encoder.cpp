#include <iostream>
#include <string>
#include <string.h>
#include "prop_encoder.h"

using std::cout;
using std::endl;

status_t 
time_encoder_t::encode(const char* str_time, univ_t& value)
{
    struct tm x;
    memset(&x, 0, sizeof(struct tm));
    strptime(str_time, "%Y-%m-%dT%H:%M:%S", &x);
    value.value_time = timegm(&x);
    return eOK;
}

void
time_encoder_t::print(univ_t value)
{
    struct tm* px;
    struct tm x;
    char buf[255];
    
    memset(&x, 0, sizeof(struct tm));
    px = &x;
    px = gmtime_r(&value.value_time, px);
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S", px);

    cout << buf << endl;
} 

status_t 
int64_encoder_t::encode(const char* str, univ_t& value)
{
    sscanf(str, "%ld", &value.value_64b);
    return eOK;
}

void
int64_encoder_t::print(univ_t value)
{
    cout << value.value_64b << endl;
}
