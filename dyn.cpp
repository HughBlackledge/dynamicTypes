#include <vector>
#include <array>
#include <functional>

#include<dynamicTypes/types.cpp>
#include<iostream>
#include <initializer_list>
#include<io.hpp>
#include<vectorplus.hpp>
#include<dynamicTypes/string_overloads.cpp>

#ifndef DYN_H 
#define DYN_H

std::string operator "" _s(const char* str, size_t) {
    return std::string(str);
}

const std::string indentString = "  ";

enum ops {
    ADD = 0,
    SUB,
    MUL,
    DIV,
    GT,
    LT,
    GTE,
    LTE,
    EQ,
    NEQ,
    OP_COUNT,
    ASSIGN,
};

class Dyn;

typedef std::function < Dyn(const Dyn&, const Dyn&)> dyn_function;


struct Prototype {
    dyn_function(*functions)[OP_COUNT];


    Prototype(int type);
    Prototype() {
        functions = nullptr;
    }
};

struct Object;

bool isNoneOperationalType(int type) {
    return type > STRING;
}

struct Dyn {
    Prototype prototype;
    int type = ERROR;
    void* data = nullptr;

    std::function<void(void*&)> dataDestructor = nullptr;
    std::function<void(void*&)> assign;

    Dyn(const char s[]) {
        type = STRING;
        data = new std::string(s);
        prototype = Prototype(type);
        this->dataDestructor = [&](void*& data) {delete (std::string*)data;data = nullptr;};
        this->assign = [s](void*& data) {data = new std::string(s);};
    }
    Dyn(vectorplus<Dyn> v) {
        type = ARRAY;
        data = new vectorplus<Dyn>(v);
        prototype = Prototype(type);
        this->dataDestructor = [&](void*& data) {delete (vectorplus<Dyn>*)data;data = nullptr;};
        this->assign = [v](void*& data) {data = new vectorplus<Dyn>(v);};
    }
    Dyn(Object o);

    Dyn(const Dyn& other) {
        type = other.type;
        prototype = other.prototype;
        if (other.assign != nullptr) {
            other.assign(data);
        }
        else data = nullptr;
        this->assign = other.assign;
        this->dataDestructor = other.dataDestructor;
    }

    template<class T>

    Dyn(T n) {
        static_assert(!std::is_pointer<T>::value, "T cannot be a pointer");
        type = getType(n);
        if (type == ERROR) {
            throw std::invalid_argument("Invalid type");
        }
        data = new T(n);
        prototype = Prototype(type);
        this->dataDestructor = [&](void*& data) {delete (T*)data;};
        this->assign = [n](void*& data) {data = new T(n);};
    }

    Dyn() {
        prototype = Prototype(type);
    }
    ~Dyn() {
        if (dataDestructor != nullptr && data != nullptr) {
            dataDestructor(data);
            data = nullptr;
        }
    }

    Dyn operator+(const Dyn& other) {
        if ((isNoneOperationalType(type) || isNoneOperationalType(other.type))) {
            return Dyn();
        }
        return prototype.functions[other.type][ADD](*this, other);
    }
    Dyn operator-(const Dyn& other) {
        if ((isNoneOperationalType(type) || isNoneOperationalType(other.type))) {
            return Dyn();
        }
        return prototype.functions[other.type][SUB](*this, other);
    }
    Dyn operator*(const Dyn& other) {
        if ((isNoneOperationalType(type) || isNoneOperationalType(other.type))) {
            return Dyn();
        }
        return prototype.functions[other.type][MUL](*this, other);
    }
    Dyn operator/(const Dyn& other) {
        if ((isNoneOperationalType(type) || isNoneOperationalType(other.type))) {
            return Dyn();
        }
        return prototype.functions[other.type][DIV](*this, other);
    }
    Dyn& operator++() {
        if (type == INT) {
            *(int*)data += 1;
        }
        else if (type == FLOAT) {
            *(float*)data += 1;
        }
        return *this;
    }

    bool runComparison(const Dyn& other, int op);

    bool operator>(const Dyn& other);
    bool operator<(const Dyn& other);
    bool operator>=(const Dyn& other);
    bool operator<=(const Dyn& other);
    bool operator==(const Dyn& other);
    bool operator!=(const Dyn& other);

    Dyn operator=(const Dyn& other) {
        if (dataDestructor != nullptr) {
            dataDestructor(data);
        }
        type = other.type;
        prototype = Prototype(type);
        this->dataDestructor = other.dataDestructor;
        this->assign = other.assign;
        return *this;
    }
    template<class T>
    Dyn& operator=(T n) {
        if (type == getType(n) && type < STRING) {
            *(T*)data = n;
            return *this;
        }
        if (dataDestructor != nullptr) {
            dataDestructor(data);
        }
        data = new T(n);
        type = getType(n);
        prototype = Prototype(type);
        this->dataDestructor = [&](void*& data) {delete (T*)data;};
        this->assign = [n](void*& data) {data = new T(n);};
        return *this;
    }

    void print(int indent = 0) {
        if (type == INT) {
            std::cout << *(int*)data;
        }
        else if (type == FLOAT) {
            std::cout << *(float*)data;
        }
        else if (type == BOOL) {
            std::cout << *(bool*)data;
        }
        else if (type == STRING) {
            std::cout << *(std::string*)data;
        }
        else if (type == OBJECT) {
            printObject(indent);
        }
        else if (type == ARRAY) {
            vectorplus<Dyn> v = *(vectorplus<Dyn>*)data;
            std::cout << "[";
            if (v.size() > 0) {
                if (v[0].type == OBJECT) std::cout << "\n" + indent * indentString;
                v[0].print(indent);
                for (int i = 1; i < v.size(); i++) {
                    std::cout << ",";
                    if (v[i - 1].type == OBJECT) {
                        std::cout << "\n" + indent * indentString;
                    }
                    v[i].print(indent);
                }
            }
            std::cout << "]";
        }
        else {
            std::cout << "ERROR";
        }
    }
    void printObject(int indent) const;

    const Dyn& operator[](std::string key) const;
    Dyn& operator[](std::string key);
    Dyn(std::initializer_list<std::pair<std::string, Dyn>> list);
    Dyn map(Dyn mapFunction(Dyn n));
    Dyn filter(bool filter(Dyn n));

    std::string getTypename() {
        switch (type) {
        case INT:
            return "INT";
        case FLOAT:
            return "FLOAT";
        case BOOL:
            return "BOOL";
        case STRING:
            return "STRING";
        case OBJECT:
            return "OBJECT";
        case ARRAY:
            return "ARRAY";
        default:
            return "ERROR";
        }
    }
    void printType() {
        switch (type) {
        case INT:
            std::cout << "INT";
            break;
        case FLOAT:
            std::cout << "FLOAT";
            break;
        case BOOL:
            std::cout << "BOOL";
            break;
        case STRING:
            std::cout << "STRING";
            break;
        case OBJECT:
            std::cout << "OBJECT";
            break;
        case ARRAY:
            std::cout << "ARRAY";
            break;
        default:
            std::cout << "ERROR";
        }
    }
    bool isError() {
        return type == ERROR;
    }
    std::vector<std::string> keys();
};

int getType(const Dyn& n) {
    return n.type;
}

template<class T>
T extract(const Dyn& dyn) {
    return *(T*)dyn.data;
}

Dyn Dyn::map(Dyn mapFunction(Dyn n)) {
    if (type != ARRAY) {
        throw std::invalid_argument("Not an array");
    }
    vectorplus<Dyn> result = extract<vectorplus<Dyn>>(*this);
    return result.map(mapFunction);
}

Dyn Dyn::filter(bool filter(Dyn n)) {
    if (type != ARRAY) {
        throw std::invalid_argument("Not an array");
    }
    vectorplus<Dyn> result = extract<vectorplus<Dyn>>(*this);
    return result.filter(filter);

}

bool Dyn::runComparison(const Dyn& other, int op) {
    if ((isNoneOperationalType(type) || isNoneOperationalType(other.type))) {
        return false;
    }
    return extract<bool>(prototype.functions[other.type][op](*this, other));
}

bool Dyn::operator>(const Dyn& other) {
    return runComparison(other, GT);
}
bool  Dyn::operator<(const Dyn& other) {
    return runComparison(other, LT);
}
bool  Dyn::operator>=(const Dyn& other) {
    return runComparison(other, GTE);
}
bool  Dyn::operator<=(const Dyn& other) {
    return runComparison(other, LTE);
}
bool  Dyn::operator==(const Dyn& other) {
    return runComparison(other, EQ);
}
bool  Dyn::operator!=(const Dyn& other) {
    return runComparison(other, NEQ);
}

void println(std::vector<std::string> v) {
    std::cout << "[";
    if (v.size() > 0) {
        std::cout << v[0];
        for (int i = 1; i < v.size(); i++) {
            std::cout << "," << v[i];
        }
    }
    println("]");
}

void print(const Dyn& d) {
    switch (d.type) {
    case INT:
        std::cout << extract<int>(d);
        break;
    case FLOAT:
        std::cout << extract<float>(d);
        break;
    case BOOL:
        std::cout << extract<bool>(d);
        break;
    case STRING:
        std::cout << extract<std::string>(d);
        break;
    case OBJECT: {
        d.printObject(0);
        break;
    }
    default:
        std::cout << "ERROR";
    }
}

void println(const Dyn& d) {
    switch (d.type) {
    case INT:
        std::cout << extract<int>(d) << std::endl;
        break;
    case FLOAT:
        std::cout << extract<float>(d) << std::endl;
        break;
    case BOOL:
        std::cout << extract<bool>(d) << std::endl;
        break;
    case STRING:
        std::cout << extract<std::string>(d) << std::endl;
        break;
    case OBJECT:
        d.printObject(0);
        break;
    case ARRAY:
    {
        vectorplus<Dyn> v = extract<vectorplus<Dyn>>(d);
        std::cout << "[";
        if (v.size() > 0) {
            print(v[0]);
            for (int i = 1; i < v.size(); i++) {
                const Dyn& e = v[i];
                print(e);
                print(",");
            }
        }
        println("]");
    }
    break;
    default:
        std::cout << "ERROR" << std::endl;
    }
}
#endif