#ifndef EXPRESSIONS_H_INCLUDED
#define EXPRESSIONS_H_INCLUDED

#include <stdio.h>
#include <string>
#include <vector>
#include "infixtopostfix.h"
#include "postfixcalculator.h"
#include "function.h"

using namespace std;

bool is_global_var(string exp, vector<Variable> vars, int& pos) {
    for(int i = 0; i < vars.size(); i++) {
        if(exp == vars[i].get_variable_name()) {
            pos = i;
            return true;
            break;
        }
    }
    return false;
}

bool is_func_var(string exp, vector<Variable> func_vars, int& pos) {
    for(int i = 0; i < func_vars.size(); i++) {
        if(exp == func_vars[i].get_variable_name()) {
            pos = i;
            return true;
            break;
        }
    }
    return false;
}

//evaluate expressions
int evaluate(string exp, vector<Variable>& vars, vector<Function>& funcs, vector<Variable>& func_vars) {
    int res = 0;
    int pos = 0;
    bool exists_in_vars = false;
    bool exists_in_func = false;

    if(exp.find("+") != string::npos
    || exp.find("-") != string::npos
    || exp.find("*") != string::npos
    || exp.find("/") != string::npos) {
        exp = InfixToPostfix(exp);
        res = postfix_calculate(exp, vars);
    }
    else if(exp.find("()") != string::npos) {
        for(int i = 0; i < funcs.size(); i++) {
            if(exp == funcs[i].get_func_name()) {
                res = stoi(funcs[i].get_func_value());
            }
        }
    }
    else if(is_global_var(exp, vars, pos) == true)
        res = vars[pos].get_value();
    else if(is_func_var(exp, vars, pos) == true)
        res = func_vars[pos].get_value();
    else 
        res = stoi(exp);

    return res;
}

#endif // EXPRESSIONS_H_INCLUDED
