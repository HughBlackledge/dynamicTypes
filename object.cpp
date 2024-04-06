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
        // data = std::map<std::string, const Dyn&>();
    }
    //Give me a constructor for an initializer list
    Object(std::initializer_list<std::pair<std::string, Dyn>> list) {
        for (auto& [key, value] : list) {
            data[key] = value;
        }
    }
    //Initialise the object with a map
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
        // println(indent * indentString + "}");
        if (indent == 0) {
            println(indent * indentString + "}");
        }
        else std::cout << indent * indentString + "}";

    }
    ~Object() {
    }
    //Add overloads that any binary non assignment operation applied to an object should just give a dyn of error:
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
    // Object operator=(const Dyn& other) {
    //     if (other.type == OBJECT) {
    //         data = extract<Object>(other.data).data;
    //     }
    //     else {
    //         throw std::invalid_argument("Not an object");
    //     }
    //     return *this;
    // }
    std::vector<std::string> keys() {
        std::vector<std::string> result = {};
        for (auto& [key, value] : data) {
            result.push_back(key);
        }
        return result;
    }
};

//Write out a constructor for a dyn that takes in an object
Dyn::Dyn(Object o) {
    type = OBJECT;
    data = new Object(o);
    prototype = Prototype(type);
    this->dataDestructor = [&](void*& data) {delete (Object*)data;data = nullptr;};
    this->assign = [o](void*& data) {data = new Object(o);};
}
//initialize with initializer list
Dyn::Dyn(std::initializer_list<std::pair<std::string, Dyn>> list) {
    type = OBJECT;
    data = new Object(list);
    prototype = Prototype(type);
    this->dataDestructor = [&](void*& data) {delete (Object*)data;data = nullptr;};
    this->assign = [list](void*& data) {data = new Object(list);};
}

// Dyn Error = Dyn();

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