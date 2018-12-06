#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "variable.h"
#include "expressions.h"
#include "ifstatement.h"

using namespace std;

extern int yylex();
extern int yylineno;
extern char* yytext;

int main() {

	vector<Variable> vars;
	vector<string> mutated_vars;
	int token; 
	int storage_id = 0;

	token = yylex();

	while(token) {
		//cout << token << " : " << yytext << endl;
		//if token is a print statement
		if(token == 1) {
			string statement = "";
			while(token) {
				if(token == 13) {
					cout << statement << endl;
					break;
				}
				else if(token == 16) {
					//print out anything in quotes and parentheses
					statement = statement + yytext + ' ';
					statement.erase(remove(statement.begin(), statement.end(), '"'), statement.end());
					statement.erase(remove(statement.begin(), statement.end(), ')'), statement.end());
				}
				else if(token == 9) {
					//check the variable data for
					//existing data
					for(int i = 0; i < vars.size(); i++) {
						if(vars[i].get_variable_name() == yytext) {
							statement += to_string(vars[i].get_value());
						}
					}
				}

				token = yylex();
			}
		}
		else if(token == 3) {
			string if_statement = "";

			//evaluate if statement
			while(token) {
				if(token == 6) {
					evaluate_if_statement(if_statement);
					break;
				}

				if_statement += yytext;
				token = yylex();
			}
		}
		//if it an identifier or variable
		else if(token == 9) {
			bool exists = false;
			string expression = "";

			//check if identifier exists
			for(int i = 0; i < vars.size(); i++) {
				if(yytext == vars[i].get_variable_name()) {
					mutated_vars.push_back(yytext);
					exists = true;
					break;
				}
			}

			//if it does not exist in variables
			//then create one
			if(exists == false) {
				Variable *newVar = new Variable;
				newVar->set_variable_name(yytext);
				newVar->set_storage_location_number(storage_id); storage_id++;

				//get expression
				while(token) {
					//evaluate the expression to push to vector
					if(token == 13) {
						newVar->set_value(evaluate(expression, vars));
						break;
					}
					//skip variable name and equal sign
					else if(yytext == newVar->get_variable_name() || token == 2) 
						token = yylex();
					else
						expression += yytext;

					token = yylex();
				}
				vars.push_back(*newVar);
			}
			//else if it does exist
			else {
				//cout << "mutated variable" << endl;
			}
		}
		//if comment ignore
		else if(token == 12) {
			while(token) {
				if(token == 13) {
					token = yylex();
					break;
				}

				token == yylex();
			}
		}

		token = yylex();
	}
		
	// cout << "Variables: \n";
	// for(int i = 0; i < vars.size(); i++) {
	// 	cout << "[" << vars[i].get_variable_name() << "][" << vars[i].get_value() << "]" << endl;
	// }	

	return 0;
}