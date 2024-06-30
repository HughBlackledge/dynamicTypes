
#ifndef STRING_OVERLOADS 
#define STRING_OVERLOADS

#include <string>

std::string repeatString(const std::string& original, int n) {
    std::string result;
    for (int i = 0; i < n; ++i) {
        result += original;
    }
    return result;
}

#define overloadAddForType(type) \
std::string operator+(const std::string& a, type b) { \
    return a + std::to_string(b); \
} \
std::string operator+(type a, const std::string& b) { \
    return std::to_string(a) + b; \
} 

#define overloadSubForType(type) \
float operator-(const std::string& a, type b) { \
    return std::stof(a) - b; \
} \
float operator-(type a, const std::string& b) { \
    return a - std::stof(b); \
}

#define overloadMulForType(type) \
std::string operator*(const std::string& a, type b) { \
    return repeatString(a, int(b)); \
} \
std::string operator*(type a, const std::string& b) { \
    return repeatString(b, int(a)); \
}

#define overloadDivForType(type) \
float operator/(const std::string& a, type b) { \
    return std::stof(a) / b; \
} \
float operator/(type a, const std::string& b) { \
    return a / std::stof(b); \
}

#define overloadCompForType(type) \
bool operator>(const std::string& a, type b) { \
    return a > std::to_string(b); \
} \
bool operator>(type a, const std::string& b) { \
    return std::to_string(a) > b; \
} \
bool operator<(const std::string& a, type b) { \
    return a < std::to_string(b); \
} \
bool operator<(type a, const std::string& b) { \
    return std::to_string(a) < b; \
} \
bool operator>=(const std::string& a, type b) { \
    return a >= std::to_string(b); \
} \
bool operator>=(type a, const std::string& b) { \
    return std::to_string(a) >= b; \
} \
bool operator<=(const std::string& a, type b) { \
    return a <= std::to_string(b); \
} \
bool operator<=(type a, const std::string& b) { \
    return std::to_string(a) <= b; \
} \
bool operator==(const std::string& a, type b) { \
    return a == std::to_string(b); \
} \
bool operator==(type a, const std::string& b) { \
    return std::to_string(a) == b; \
} \
bool operator!=(const std::string& a, type b) { \
    return a != std::to_string(b); \
} \
bool operator!=(type a, const std::string& b) { \
    return std::to_string(a) != b; \
}



overloadAddForType(int)
overloadAddForType(float)
overloadAddForType(bool)

overloadSubForType(int)
overloadSubForType(float)
overloadSubForType(bool)

overloadMulForType(int)
overloadMulForType(float)
overloadMulForType(bool)

overloadDivForType(int)
overloadDivForType(float)
overloadDivForType(bool)

overloadCompForType(int)
overloadCompForType(float)
overloadCompForType(bool)


float operator-(const std::string& a, const std::string& b) {
    return std::stof(a) - std::stof(b);
}

std::string operator*(const std::string& a, const std::string& b) {
    return repeatString(a, std::stoi(b));
}

float operator/(const std::string& a, const std::string& b) {
    return std::stof(a) / std::stof(b);
}



#endif