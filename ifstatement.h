#ifndef IFSTATEMENT_H_INCLUDED
#define IFSTATEMENT_H_INCLUDED

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include "variable.h"

using namespace std;

extern int yylex();
extern int yylineno;
extern char* yytext;

bool evaluate_if_statement(string op1, string op2, string cmp) {
	if(cmp == ">") {
		if(stoi(op1) > stoi(op2)) return true;
		else return false;
	}
	else if(cmp == "<") {
		if(stoi(op1) < stoi(op2)) return true;
		else return false;
	}
	else if(cmp == ">=") {
		if(stoi(op1) >= stoi(op2)) return true;
		else return false;
	}
	else if(cmp == "<=") {
		if(stoi(op1) <= stoi(op2)) return true;
		else return false;
	}
	else if(cmp == "==") {
		if(stoi(op1) == stoi(op2)) return true;
		else return false;
	}
	else if(cmp == "!=") {
		if(stoi(op1) != stoi(op2)) return true;
		else return false;
	}
	else {
		cerr << "error : no comparator" << endl;
		exit(1);
	}
}

#endif // IFSTATEMENT_H_INCLUDED