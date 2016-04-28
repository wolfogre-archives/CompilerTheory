#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "LR0_Analyser.h"
#include "Analyser.h"
#include "Glossary.h"

using namespace std;

int TestLR0_Analyer();
vector<string> Escape(vector<pair<string, string>> lexResult);

int main()
{
	//return TestLR0_Analyer();
	LR0_Analyser la;

	la.AddProduction("E", "E", "+", "E");
	la.AddProduction("E", "E", "*", "E");
	la.AddProduction("E", "(", "E", ")");
	la.AddProduction("E", "i");

	la.AddAction(0, "(", 'S', 2);
	la.AddAction(0, "i", 'S', 3);
	la.AddAction(1, "+", 'S', 4);
	la.AddAction(1, "*", 'S', 5);
	la.AddAction(1, LR0_Analyser::END_OF_INPUT, 'A', 0);
	la.AddAction(2, "(", 'S', 2);
	la.AddAction(2, "i", 'S', 3);
	la.AddAction(3, "+", 'r', 4);
	la.AddAction(3, "*", 'r', 4);
	la.AddAction(3, ")", 'r', 4);
	la.AddAction(3, LR0_Analyser::END_OF_INPUT, 'r', 4);
	la.AddAction(4, "(", 'S', 2);
	la.AddAction(4, "i", 'S', 3);
	la.AddAction(5, "(", 'S', 2);
	la.AddAction(5, "i", 'S', 3);
	la.AddAction(6, "+", 'S', 4);
	la.AddAction(6, "*", 'S', 5);
	la.AddAction(6, ")", 'S', 9);
	la.AddAction(7, "+", 'r', 1);
	la.AddAction(7, "*", 'S', 5);
	la.AddAction(7, ")", 'r', 1);
	la.AddAction(7, LR0_Analyser::END_OF_INPUT, 'r', 1);
	la.AddAction(8, "+", 'r', 2);
	la.AddAction(8, "*", 'r', 2);
	la.AddAction(8, ")", 'r', 2);
	la.AddAction(8, LR0_Analyser::END_OF_INPUT, 'r', 2);
	la.AddAction(9, "+", 'r', 3);
	la.AddAction(9, "*", 'r', 3);
	la.AddAction(9, ")", 'r', 3);
	la.AddAction(9, LR0_Analyser::END_OF_INPUT, 'r', 3);

	la.AddGoto(0, "E", 1);
	la.AddGoto(2, "E", 6);
	la.AddGoto(4, "E", 7);
	la.AddGoto(5, "E", 8);

	Analyser analyser;
	string input_string;

	while (cout << "input expression: ", getline(cin, input_string))
	{
		vector<pair<string, string>> lex_result = analyser.AnalyseLexical(input_string);
		int error_index = -1;
		for (size_t i = 0; i < lex_result.size(); ++i)
		{
			if (lex_result[i].second == "unknown")
				error_index = i;
		}
		if (error_index != -1)
		{
			cout << "Error on: " << lex_result[error_index].first << endl;
			continue;
		}
		vector<string> escape_result = Escape(lex_result);
		for (string str : escape_result)
			cout << str << " ";
		la.Input(escape_result);
		cout << endl;

		if ((error_index = la.Analyse()) != -1)
		{
			if (error_index == lex_result.size())
				cout << "Error on: the end of input" << endl;
			else
				cout << "Error on: " << lex_result[error_index].first << endl;
			continue;
		}

		cout << "Right!" << endl;;
	}
}

vector<string> Escape(vector<pair<string, string>> lexResult)
{
	map<string, string> escape_tactics;
	Glossary glossary;
	escape_tactics.insert(pair<string, string>(glossary.GetValue("+"), string("+")));
	escape_tactics.insert(pair<string, string>(glossary.GetValue("-"), string("+")));
	escape_tactics.insert(pair<string, string>(glossary.GetValue("*"), string("*")));
	escape_tactics.insert(pair<string, string>(glossary.GetValue("/"), string("*")));
	escape_tactics.insert(pair<string, string>(glossary.GetValue("name"), string("i")));
	escape_tactics.insert(pair<string, string>(glossary.GetValue("100"), string("i")));
	escape_tactics.insert(pair<string, string>(glossary.GetValue("("), string("(")));
	escape_tactics.insert(pair<string, string>(glossary.GetValue(")"), string(")")));

	vector<string> result;
	for (pair<string, string> p : lexResult)
	{
		map<string, string>::iterator it = escape_tactics.find(p.second);
		result.push_back(it->second);
	}

	return result;
}

int TestLR0_Analyer()
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