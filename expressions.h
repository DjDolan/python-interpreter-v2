#ifndef EXPRESSIONS_H_INCLUDED
#define EXPRESSIONS_H_INCLUDED

#include <stdio.h>
#include <string>
#include <vector>
#include "infixtopostfix.h"
#include "postfixcalculator.h"

using namespace std;

//evaluate expressions
int evaluate(string exp, vector<Variable>& vars) {

    if(exp.find("+") != string::npos
    || exp.find("-") != string::npos
    || exp.find("*") != string::npos
    || exp.find("/") != string::npos) {

        exp = InfixToPostfix(exp);
        int res = postfix_calculate(exp, vars);
        return res;
    }
    else {
        int res = stoi(exp);
        return res;
    }
}

#endif // EXPRESSIONS_H_INCLUDED
