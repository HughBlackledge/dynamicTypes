
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
// Please also allow these to work with const char*
#define overloadAddForType(type) \
std::string operator+(const std::string& a, type b) { \
    return a + std::to_string(b); \
} \
std::string operator+(type a, const std::string& b) { \
    return std::to_string(a) + b; \
} 

//Please define subtraction between a string and a numeric by converting the string to a float and then subtracting
#define overloadSubForType(type) \
float operator-(const std::string& a, type b) { \
    return std::stof(a) - b; \
} \
float operator-(type a, const std::string& b) { \
    return a - std::stof(b); \
}
// Define multiplication by converting the string to an int and then running repeatString
#define overloadMulForType(type) \
std::string operator*(const std::string& a, type b) { \
    return repeatString(a, int(b)); \
} \
std::string operator*(type a, const std::string& b) { \
    return repeatString(b, int(a)); \
}
// Define division by converting the string to a float and then dividing
#define overloadDivForType(type) \
float operator/(const std::string& a, type b) { \
    return std::stof(a) / b; \
} \
float operator/(type a, const std::string& b) { \
    return a / std::stof(b); \
}
//Overload comparison operators
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

// std::string operator*(const int a, const std::string b) {
//     return repeatString(b, a);
// }



#endif