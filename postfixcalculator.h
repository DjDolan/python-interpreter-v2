#ifndef POSTFIXCALCULATOR_H_INCLUDED
#define POSTFIXCALCULATOR_H_INCLUDED

#include <stdio.h>
#include <stack>
#include <vector>
#include <string>
#include "infixtopostfix.h"
#include "variable.h"

using namespace std;

int operation(char, int, int);

int postfix_calculate(string exp, vector<Variable> vars) {

    stack<int> s;
    int result = 0;
    string var = "";

    for(int i = 0; i < exp.length(); i++) {
        //if it is a digit
        if(IsOperand(exp[i])) {
            int operand = 0;

            //check if its a long integer
            while(i < exp.length() && IsOperand(exp[i])) {
                operand = (operand * 10) + (exp[i] - '0');
                i++;
            }
            i--;

            s.push(operand);
        }
        else if(IsVariable(exp[i])) {
            var += exp[i];

            if(!IsVariable(exp[i+1])) {
                for(int k = 0; k != vars.size(); k++) {
                    if(var == vars[k].get_variable_name()) {
                        s.push(vars[k].get_value());
                        break;
                    }
                }
                var = "";
            }
        }
        else if(IsOperator(exp[i])) {
            int op1 = s.top(); s.pop();
            int op2 = s.top(); s.pop();

            result = operation(exp[i], op1, op2);

            s.push(result);
        }

    }

    while(!s.empty()) {
        result = s.top(); s.pop();
    }
    
    return result;
}

int operation(char op, int op1, int op2) {
    int result = 0;

    switch(op) {
        case '+':
            result = op2 + op1;
            break;
        case '-':
            result = op2 - op1;
            break;
        case '*':
            result = op2 * op1;
            break;
        case '/':
            result = op2 / op1;
            break;
        default:
            break;
    }

    return result;
}

#endif // POSTFIXCALCULATOR_H_INCLUDED