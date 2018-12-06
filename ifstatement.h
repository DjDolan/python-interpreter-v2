#ifndef IFSTATEMENT_H_INCLUDED
#define IFSTATEMENT_H_INCLUDED

#include <iostream>
#include <vector>
#include <stdio.h>

extern int yylex();
extern int yylineno;
extern char* yytext;

void evaluate_if_statement(string if_stmnt) {
	cout << if_stmnt << endl;
}

#endif // IFSTATEMENT_H_INCLUDED