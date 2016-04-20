#include <iostream>
#include <string>
#include <vector>

#include "LR0_Analyser.h"


using namespace std;

int main()
{
	vector<string> inputs;
	inputs.push_back("a");
	inputs.push_back("b");
	inputs.push_back("b");
	inputs.push_back("c");
	inputs.push_back("d");
	inputs.push_back("e");

	LR0_Analyser la(inputs);

	la.AddProduction("S", "a", "A", "c", "B", "e");
	la.AddProduction("A", "b");
	la.AddProduction("A", "A", "b");
	la.AddProduction("B", "d");

	la.AddAction(0, "a", 'S', 2);
	la.AddAction(1, LR0_Analyser::END_OF_INPUT, 'A', 0);
	la.AddAction(2, "b", 'S', 4);
	la.AddAction(3, "c", 'S', 5);
	la.AddAction(3, "b", 'S', 6);
	la.AddAction(4, LR0_Analyser::ALL_OF_INPUT, 'r', 2);
	la.AddAction(5, "d", 'S', 8);
	la.AddAction(6, LR0_Analyser::ALL_OF_INPUT, 'r', 3);
	la.AddAction(7, "e", 'S', 9);
	la.AddAction(8, LR0_Analyser::ALL_OF_INPUT, 'r', 4);
	la.AddAction(9, LR0_Analyser::ALL_OF_INPUT, 'r', 1);

	la.AddGoto(0, "S", 1);
	la.AddGoto(2, "A", 3);
	la.AddGoto(5, "B", 7);

	cout << la.Analyse() << endl;

	return 0;
}