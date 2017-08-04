#pragma once

#include "type.h"

class prop_encoder_t {
    public:
    virtual status_t encode(const char* str_time, univ_t& value) = 0;
    virtual void print(univ_t value) = 0;

};

class time_encoder_t : public prop_encoder_t {
    public:
    status_t encode(const char* str_time, univ_t& value);
    void print(univ_t value);
    static prop_encoder_t* create_instance();

    //Add filters like <, > etc
};

class int64_encoder_t : public prop_encoder_t {
 public:
    status_t encode(const char* str, univ_t& value);
    void print(univ_t value);
    static prop_encoder_t* create_instance();
};

class embedstr_encoder_t : public prop_encoder_t {
 public:
    status_t encode(const char* str, univ_t& value);
    void print(univ_t value);
    static prop_encoder_t* create_instance();
}; 

class double_encoder_t : public prop_encoder_t {
 public:
    status_t encode(const char* str, univ_t& value);
    void print(univ_t value);
    static prop_encoder_t* create_instance();
}; 
