#include<dynamicTypes/dyn.cpp>
#include<dynamicTypes/object.cpp>
#include<dynamicTypes/functions.cpp>
#include<io.hpp>
#include<dynamicTypes/types.cpp>
#include<map>

std::vector<std::string> Dyn::keys() {
    std::vector<std::string> result;
    if (type == OBJECT) {
        Object* obj = (Object*)data;
        result = ::keys(obj);
    }
    return result;
}

// #define let Dyn
// #define function Dyn
typedef Dyn let;
typedef Dyn function;

#define array std::vector<Dyn>