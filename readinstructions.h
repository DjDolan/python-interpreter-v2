#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

//create symbol table and tokenizer

//recursively read the instructions
void read_instructions(vector<string>& ins) {

	if(ins.empty()) {
		cout << "end of instructions" << endl;
	}
	else {
		cout << ins.front() << endl;
		ins.erase(ins.begin());
		read_instructions(ins);
	}

}