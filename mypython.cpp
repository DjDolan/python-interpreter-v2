#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include "variable.h"
#include "expressions.h"
#include "ifstatement.h"
#include "function.h"

using namespace std;

extern int yylex();
extern int yylineno;
extern char* yytext;

int main() {

	vector<Variable> vars;
	vector<Function> funcs;
	vector<Variable> func_vars;
	vector<string> func_names;
	vector<string> mutated_vars;
	int token; 
	int storage_id = 0;
	bool is_true = false;

	token = yylex();

	while(token) {
		//cout << "[" << token << "][" << yytext << "]" << endl;
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
				else if(token == 2) token = yylex();

				token = yylex();
			}
		}
		else if(token == 3) {
			//variables needed
			stack<string> operands;
			string operand1 = "";
			string operand2 = "";
			string comparator = "";
			string str = "";

			token = yylex(); //skips if statement

			//evaluate if statement
			while(token) {
				//if it is the colon then break
				if(token == 6) break;
				//if it is a indentifier check for
				//in variables
				else if(token == 9) {
					for(int i = 0; i < vars.size(); i++) {
						//if it is then push to stack and break
						if(vars[i].get_variable_name() == yytext) {
							// cout << vars[i].get_value() << endl;
							operands.push(to_string(vars[i].get_value()));
							break;
						}
						//else throw error and break
						else {
							cerr << "error : variable does not exist" << endl;
							break;
						}
					}
				}
				//if integer then push to stack
				else if(token == 10)
					operands.push(yytext);
				//if comparison then store for evaluation
				else if(token == 5)
					comparator = yytext;
				
				token = yylex();
			}

			if(!operands.empty()) {
				operand2 = operands.top(); operands.pop();
				operand1 = operands.top(); operands.pop();
			}

			//evaluate if statement
			is_true = evaluate_if_statement(operand1, operand2, comparator);

			//if the statement is true then return to original program
			//and let it evaluate it itself
			if(is_true == true) {
				token = yylex(); token = yylex();
			}
			else {
				token = yylex(); token = yylex();
				if(token == 15) {
					while(token) {
						if(token == 13) {
							token = yylex();
							break;
						}
						token = yylex();
					}
				}
			}
		}
		//if its a else statement
		else if(token == 4) {
			token = yylex();
			//if statement is true
			if(is_true == true) {
				token = yylex(); token = yylex();
				if(token == 15) {
					while(token) {
						if(token == 13) {
							token = yylex();
							break;
						}
						token = yylex();
					}
				}
			}
			//if statement is false
			else {
				token = yylex(); token = yylex();	
			}
		}
		//if its a function definition
		else if(token == 7) {
			string func_name = "";
			bool func_exists = false;

			token = yylex();
			//get func name
			while(token) {
				if(token == 6) break;
				else if(token == 14) token = yylex();

				func_name += yytext;
				token = yylex();
			}

			for(int i = 0; i < func_names.size(); i++) {
				if(func_names[i] == func_name) {
					func_exists = true;
				}
			}

			if(func_exists == true) {
				cout << "TRUE: Override the function." << endl;
			}
			else {
				//create new function
				Function *newFunc = new Function();
				newFunc->set_func_name(func_name);

				stack<string> operands;
				string operand1;
				string operand2;
				string comparator;

				//find return statement to do get function value
				while(token) {
					//return statement
					if(token == 17) {
						token = yylex(); //get the return

						if(token == 9) {
							for(int i = 0; i < func_vars.size(); i++) {
								if(func_vars[i].get_variable_name() == yytext) {
									newFunc->set_func_value(to_string(func_vars[i].get_value()));
								}
							}
						}

						funcs.push_back(*newFunc);

						break;
					}

					//variables in function
					else if(token == 9) {
						bool exists = false;
						string expression = "";

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
									newVar->set_value(evaluate(expression, func_vars, funcs, func_vars));
									break;
								}
								//skip variable name and equal sign
								else if(yytext == newVar->get_variable_name() || token == 2) 
									token = yylex();
								else
									expression += yytext;

								token = yylex();
							}

							func_vars.push_back(*newVar);
						}
						//else if it does exist
						else {
							string mutated_var = yytext;

							while(token) {
								if(token == 13) {
									expression += '\n';
									break;
								}
								else if(yytext == mutated_var || token == 2) 
									token = yylex();
								else
									expression += yytext;

								token = yylex();
							}

							for(int i = 0; i < func_vars.size(); i++) {
								if(func_vars[i].get_variable_name() == mutated_var) {
									func_vars[i].set_value(evaluate(expression, vars, funcs, func_vars));
									break;
								}
							}
						}
					}
					//if statements
					else if(token == 3) {
						//get if statement values
						while(token) {
							//if colon end if statement
							if(token == 6) break;
							//if identifier then push value
							else if(token == 9) {
								for(int i = 0; i < func_vars.size(); i++) {
									if(yytext == func_vars[i].get_variable_name()) {
										operands.push(to_string(func_vars[i].get_value()));
										break;
									}
								}
							}
							//if integer push
							else if(token == 10) {
								operands.push(yytext);
							}
							//if comparator
							else if(token == 5) {
								comparator = yytext;
							}

							token = yylex();
						}

						while(!operands.empty()) {
							operand2 = operands.top(); operands.pop();
							operand1 = operands.top(); operands.pop();
						}
						
						is_true = evaluate_if_statement(operand1, operand2, comparator);

						//TRUE if statement
						if(is_true == true) {
							token = yylex(); token = yylex();
						}
						//FALSE if statement
						else {
							token = yylex(); token = yylex();
							if(token == 15) {
								while(token) {
									if(token == 13) {
										token = yylex();
										break;
									}
									token = yylex();
								}
							}
						}
					}
					//else statement
					else if(token == 4) {
						if(is_true == true) {
							token = yylex(); token = yylex(); token = yylex();
							if(token == 15) {
								token = yylex();
								while(token) {
									if(token == 15) {
										token = yylex();
										break;
									}
									cout << "skip " << yytext << endl;
									token = yylex();
								}
							}
						}
						else {
							token = yylex(); token = yylex();
						}
					}

					token = yylex();
				}
			}
		}
		//if it an identifier or variable
		else if(token == 9) {
				bool exists_var = false;
				string expression = "";

				//if it does not exist in variables
				//then create one
				if(exists_var == false) {
					Variable *newVar = new Variable;
					newVar->set_variable_name(yytext);
					newVar->set_storage_location_number(storage_id); storage_id++;

					//get expression
					while(token) {
						//evaluate the expression to push to vector
						if(token == 13) {
							newVar->set_value(evaluate(expression, vars, funcs, func_vars));
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
					string mutated_var = yytext;

					while(token) {
						if(token == 13) {
							expression += '\n';
							break;
						}
						else if(yytext == mutated_var || token == 2) 
							token = yylex();
						else
							expression += yytext;

						token = yylex();
					}

					for(int i = 0; i < vars.size(); i++) {
						if(vars[i].get_variable_name() == mutated_var) {
							vars[i].set_value(evaluate(expression, vars, funcs, func_vars));
							break;
						}
					}
				}
		}
		//if comment ignore
		else if(token == 12) {
			while(token) {
				if(token == 13) {
					token = yylex();
					break;
				}
				token = yylex();
			}
		}

		token = yylex();
	}

	return 0;
}