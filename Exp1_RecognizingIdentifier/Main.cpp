#include <iostream>
#include <map>
#include <string>
#include "Recognizer.h"
using namespace std;

int main(){
	Recognizer r;

	map<string, int> result = r.RecognizeIdentifier("code.txt");

	for (pair<string, int> p: result){
		cout << p.first << " " << p.second << endl;
	}

	system("pause");
	return 0;
}