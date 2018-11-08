#include <iostream>
#include <vector>
#include "inputfile.h"
#include "readinstructions.h"

using namespace std;

/*
* create symbol table
* make a tokenizer function
* assign each key word to a token
* a token determines what it will do
*/

int main(int argc, char** argv) {

	vector<string> instructions;

	get_instructions(instructions, "python-text.txt");

	read_instructions(instructions);

	return 0;
}