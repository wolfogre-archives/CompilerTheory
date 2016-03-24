#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "Recognizer.h"
using namespace std;

int main(){
	Recognizer r;
	string inputFile = "exp1_input.txt";

	std::ifstream fin(inputFile);
	if (!fin){
		cerr << "Can not open " + inputFile + "!"<< endl;
		return -1;
	}
	std::stringstream buffer;
	buffer << fin.rdbuf();
	std::string inputString(buffer.str());
	fin.close();

	map<string, int> result = r.RecognizeIdentifier(inputString);
	ofstream fout("exp1_output.txt");
	for (pair<string, int> p: result){
		fout << "(" << p.first << ":\t" << p.second << ")" << endl;
	}
	fout.close();
	cout << "Done!" << endl;

	system("pause");
	return 0;
}