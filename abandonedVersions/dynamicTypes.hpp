
#include <io.hpp>
#include <tuple>

using namespace std;

template<class T>

T cast(void* ptr){
  return*(T*)ptr;
}

int (*f_i)(void*) = cast<int>;
float (*f_f)(void*) = cast<float>;
char (*f_c)(void*) = cast<char>;
std::string (*f_s)(void*) = cast<std::string>;

std::tuple cast_list = {f_i,f_f,f_c,f_s};

int get_type(int n){
    return 0;
}

int get_type(float n){
    return 1;
}

int get_type(char n){
    return 2;
}

int get_type(std::string n){
    return 3;
}

struct dyn{
    int type;
    void* data;

    dyn(){

    }

    template<class T>
    dyn(T n){
        data = new T;
        type = get_type(n);
    }

    template<class T>

    void operator=(T n){
        if(type == n.type){
            std::get<type>(cast_list)(data) = std::get<n.type>(cast_list)(n.data);
        }
    }
};
