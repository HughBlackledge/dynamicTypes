#include<dynamicTypes/dyn.cpp>
#include<dynamicTypes/string_overloads.cpp>
#include <string>

#ifndef FUNCTIONS 
#define FUNCTIONS

typedef std::string string;

#define defineFunction(type1,type2,op,name) \
Dyn name##_##type1##_##type2(const Dyn &a, const Dyn &b) { \
return Dyn(extract<type1>(a) op extract<type2>(b)); \
}

#define defineFunctions(type,op,name) \
defineFunction(type, int, op, name) \
defineFunction(type, float, op, name) \
defineFunction(type, string, op, name) \
defineFunction(type, bool, op, name)

#define defineAllFunctionsForOp(op,name) \
defineFunctions(int, op, name) \
defineFunctions(float, op, name) \
defineFunctions(string, op, name) \
defineFunctions(bool, op, name)

#define defineAllFunctions \
defineAllFunctionsForOp(+,add) \
defineAllFunctionsForOp(-,sub) \
defineAllFunctionsForOp(*,mul) \
defineAllFunctionsForOp(/,div) \
defineAllFunctionsForOp(> , gt) \
defineAllFunctionsForOp(< , lt) \
defineAllFunctionsForOp(>= , gte) \
defineAllFunctionsForOp(<= , lte) \
defineAllFunctionsForOp(== , eq) \
defineAllFunctionsForOp(!= , neq)


defineAllFunctions

std::function<Dyn(const Dyn&, const Dyn&)> allFunctions[TYPE_COUNT][TYPE_COUNT][OP_COUNT] = {
    {{add_int_int, sub_int_int, mul_int_int, div_int_int, gt_int_int, lt_int_int, gte_int_int, lte_int_int, eq_int_int, neq_int_int},
    {add_int_float, sub_int_float, mul_int_float, div_int_float, gt_int_float, lt_int_float, gte_int_float, lte_int_float, eq_int_float, neq_int_float},
    {add_int_string, sub_int_string, mul_int_string, div_int_string, gt_int_string, lt_int_string, gte_int_string, lte_int_string, eq_int_string, neq_int_string},
    {add_int_bool, sub_int_bool, mul_int_bool, div_int_bool, gt_int_bool, lt_int_bool, gte_int_bool, lte_int_bool, eq_int_bool, neq_int_bool}},
    {{add_float_int, sub_float_int, mul_float_int, div_float_int, gt_float_int, lt_float_int, gte_float_int, lte_float_int, eq_float_int, neq_float_int},
    {add_float_float, sub_float_float, mul_float_float, div_float_float, gt_float_float, lt_float_float, gte_float_float, lte_float_float, eq_float_float, neq_float_float},
    {add_float_string, sub_float_string, mul_float_string, div_float_string, gt_float_string, lt_float_string, gte_float_string, lte_float_string, eq_float_string, neq_float_string},
    {add_float_bool, sub_float_bool, mul_float_bool, div_float_bool, gt_float_bool, lt_float_bool, gte_float_bool, lte_float_bool, eq_float_bool, neq_float_bool}},
    {{add_string_int, sub_string_int, mul_string_int, div_string_int, gt_string_int, lt_string_int, gte_string_int, lte_string_int, eq_string_int, neq_string_int},
    {add_string_float, sub_string_float, mul_string_float, div_string_float, gt_string_float, lt_string_float, gte_string_float, lte_string_float, eq_string_float, neq_string_float},
    {add_string_string, sub_string_string, mul_string_string, div_string_string, gt_string_string, lt_string_string, gte_string_string, lte_string_string, eq_string_string, neq_string_string},
    }
};


Prototype::Prototype(int type) {
    functions = allFunctions[type];
}

#endif
