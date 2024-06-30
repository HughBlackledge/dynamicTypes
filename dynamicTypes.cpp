#include<dynamicTypes/dyn.cpp>
#include<dynamicTypes/object.cpp>
#include<dynamicTypes/functions.cpp>
#include<io.hpp>
#include<dynamicTypes/types.cpp>
#include<map>

#ifndef KEYS_STUFF
#define KEYS_STUFF

std::vector<std::string> Dyn::keys() {
    std::vector<std::string> result;
    if (type == OBJECT) {
        Object* obj = (Object*)data;
        result = ::keys(obj);
    }
    return result;
}

typedef Dyn let;
typedef Dyn function;

#define array std::vector<Dyn>

#endif