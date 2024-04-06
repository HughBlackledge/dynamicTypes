#include<dynamicTypes/dynamicTypes.cpp>
#include<io.hpp>

#include<map>
#include<timer.hpp>

/*
This file showcases the use of the dynamic types library.
*/

#define let Dyn
#define function Dyn

#define array std::vector<Dyn>

function f(Dyn& a) {
    return a * 2;
}
/*
You can return whatever you want from a function (currently limited to types: int, float, bool, string, array, object)

Other types will cause segmentation faults and I've explicitly disabled the use of pointers because mixing high level and low level like that is a very bad idea.
*/
function g(int a) {
    switch (a) {
    case 1:
        return "hi";
    case 2:
        return false;
    case 3:
        return 3.0;
    }
    return 0;
}

void benchmarkInc() {
    Dyn a = 1;
    timer t;
    for (int i = 0; i < 1e7f;i++) {
        ++a;
    }
}

/*
About 100x faster for primitive types when using non-destructive assignment
e.g.
Dyn a = 1;
instead of deleting the old value and creating a new one, we just change the value of the old one.
*/
void benchmarkAssignment() {
    Dyn a = 1;
    timer t;
    for (int i = 0; i < 1e7f;i++) {
        a = 1;
    }
}

int main() {
    let a = {
        {"hi", 10},
        {"bye", 20},
        { "object", {
            {"hi", 10},
            {"bye", 20},
        }}
    };
    println(a);
    let v = array{ 1, 2, 3 };
    let v2 = v.map([](let a) { return a * 2; }).filter([](let a) { return a == 4; });
    println(v2);
    println(v);
    let b = Object();
    b["a"] = 1;
    b["b"] = 2;
    println(b);
    println(a.keys());
    println(b.keys());
}