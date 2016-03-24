#include <iostream>
#include <string>
#include <vector>
#include "Analyser.h"

using namespace std;

int main(){
	Analyser analyser;
	string inputFile = "exp2_input.txt";

	ifstream fin(inputFile);
	if (!fin){
		cerr << "Can not open " + inputFile + "!" << endl;
		return -1;
	}
	std::stringstream buffer;
	buffer << fin.rdbuf();
	std::string inputString(buffer.str());
	fin.close();

	vector<pair<string, string>> result = analyser.AnalyseLexical(inputString);
	ofstream fout("exp2_output.txt");
	for (pair<string, string> p : result){
		fout << "(" << p.second << ",\t" << p.first << ")" << endl;
	}
	fout.close();
	cout << "Done!" << endl;
}