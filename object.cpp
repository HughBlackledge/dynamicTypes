#include <initializer_list>
#include<map>
#include<io.hpp>
#include<dynamicTypes/dyn.cpp>
#include<dynamicTypes/string_overloads.cpp>

#ifndef OBJECT_H
#define OBJECT_H

struct Object {
    std::map<std::string, Dyn> data;
    Object() {
        data = {};
    }

    Object(std::initializer_list<std::pair<std::string, Dyn>> list) {
        for (auto& [key, value] : list) {
            data[key] = value;
        }
    }

    Object(std::map<std::string, Dyn> map) {
        data = map;
    }
    const Dyn& operator[](std::string key) const {
        return data.at(key);
    }
    Dyn& operator[](std::string key) {
        return data[key];
    }
    Dyn& operator[](const Dyn& key) {
        if (key.type != STRING) {
            throw std::invalid_argument("Key must be a string");
        }
        std::string keyString = *(std::string*)key.data;
        return data[keyString];
    }
    void print(int indent = 0) {
        auto it = data.end();
        it--;
        std::string lastKey = it->first;
        println("{");
        for (auto [key, value] : data) {
            std::cout << (1 + indent) * indentString + key << ": ";
            value.print(indent + 1);
            if (key != lastKey) {
                println(",");
            }
        }
        println();
        if (indent == 0) {
            println(indent * indentString + "}");
        }
        else std::cout << indent * indentString + "}";

    }
    ~Object() {
    }

    Dyn operator+(const Dyn& other) {
        return Dyn();
    }
    Dyn operator-(const Dyn& other) {
        return Dyn();
    }
    Dyn operator*(const Dyn& other) {
        return Dyn();
    }
    Dyn operator/(const Dyn& other) {
        return Dyn();
    }
    Dyn operator%(const Dyn& other) {
        return Dyn();
    }
    Dyn operator^(const Dyn& other) {
        return Dyn();
    }
    Dyn operator&(const Dyn& other) {
        return Dyn();
    }
    Dyn operator|(const Dyn& other) {
        return Dyn();
    }
    Dyn operator<<(const Dyn& other) {
        return Dyn();
    }
    Dyn operator>>(const Dyn& other) {
        return Dyn();
    }
    Dyn operator&&(const Dyn& other) {
        return Dyn();
    }
    Dyn operator||(const Dyn& other) {
        return Dyn();
    }
    Dyn operator<(const Dyn& other) {
        return Dyn();
    }
    Dyn operator>(const Dyn& other) {
        return Dyn();
    }
    Dyn operator<=(const Dyn& other) {
        return Dyn();
    }
    Dyn operator>=(const Dyn& other) {
        return Dyn();
    }
    Dyn operator==(const Dyn& other) {
        return Dyn();
    }
    Dyn operator!=(const Dyn& other) {
        return Dyn();
    }
    Dyn operator()(const Dyn& other) {
        return Dyn();
    }
    Object operator=(const Dyn& other) {
        return *this;
    }
    std::vector<std::string> keys() {
        std::vector<std::string> result = {};
        for (auto& [key, value] : data) {
            result.push_back(key);
        }
        return result;
    }
};


Dyn::Dyn(Object o) {
    type = OBJECT;
    data = new Object(o);
    prototype = Prototype(type);
    this->dataDestructor = [&](void*& data) {delete (Object*)data;data = nullptr;};
    this->assign = [o](void*& data) {data = new Object(o);};
}

Dyn::Dyn(std::initializer_list<std::pair<std::string, Dyn>> list) {
    type = OBJECT;
    data = new Object(list);
    prototype = Prototype(type);
    this->dataDestructor = [&](void*& data) {delete (Object*)data;data = nullptr;};
    this->assign = [list](void*& data) {data = new Object(list);};
}

const Dyn& Dyn::operator[](std::string key) const {
    if (type != OBJECT) {
        throw std::out_of_range("Not an object");
    }
    return (*(Object*)data)[key];
}

Dyn& Dyn::operator[](std::string key) {
    if (type != OBJECT) {
        throw std::out_of_range("Not an object");
    }
    return (*(Object*)data)[key];
}

void Dyn::printObject(int indent) const {
    (*(Object*)data).print(indent);
}

std::vector < std::string> keys(Object* obj) {
    std::vector<std::string> result = obj->keys();
    return result;
}

#endif