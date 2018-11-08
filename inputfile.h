#include <fstream>
#include <string>
#include <vector>

using namespace std;

void get_instructions(vector<string>& ins, string file_name) {
	ifstream input;
	string line;

	input.open(file_name);

	while(getline(input, line)) {
		ins.push_back(line);
	}

	input.close();

	return;
}