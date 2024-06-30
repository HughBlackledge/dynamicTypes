#include<string>
#include<vector>

#ifndef TYPES 
#define TYPES

enum types {
    INT = 0,
    FLOAT,
    BOOL,
    STRING,
    OBJECT,
    ARRAY,
    TYPE_COUNT,
    ERROR,
};

int getType(int n) {
    return INT;
}
int getType(float f) {
    return FLOAT;
}
int getType(bool b) {
    return BOOL;
}
int getType(std::string s) {
    return STRING;
}

template<class T>
int getType(std::vector<T> v) {
    return ARRAY;
}

struct Object;

int getType(Object* o) {
    return OBJECT;
}

template<class T>
int getType(T n) {
    return ERROR;
}

#endif