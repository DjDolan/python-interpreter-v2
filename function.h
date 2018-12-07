#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class Function {
private:
	string function_name;
	string function_value;
public:
	Function() {
		function_name = "none";
		function_value = "0000";
	}
	~Function() {
		function_name = "none";
		function_value = "0000";
	}
	
	void set_func_name(string name) { function_name = name; }
	string get_func_name() { return function_name; }

	void set_func_value(string val) { function_value = val; }
	string get_func_value() { return function_value; }
};

#endif // FUNCTIONS_H_INCLUDED