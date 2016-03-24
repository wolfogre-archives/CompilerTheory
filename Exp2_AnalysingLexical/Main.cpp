#include <iostream>
#include <string>
#include "Glossary.h"

using namespace std;

int main(){
	cout << "Input word to test Glossary:" << endl;
	while (true){
		Glossary g;
		string str;
		cin >> str;
		cout << g.GetValue(str) << endl;
	}
	return 0;
}