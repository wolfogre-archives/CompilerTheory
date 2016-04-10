#include "Automata.h"
#include <iostream>
#include <string>

using namespace std;
int SimpleTest();
int TestEmail();

int main()
{
	//return SimpleTest();
	return TestEmail();
}


int SimpleTest()
{
	Automata a;
	a.AddStatus("A", true);
	a.AddStatus("B");
	a.AddStatus("C", false, true);
	cout << a.AllStatus() << endl;

	a.AddPath("A", "A", "a");
	a.AddPath("A", "B", "b");
	a.AddPath("B", "B", "b");
	a.AddPath("B", "C", "c");
	a.AddPath("C", "C", "c");
	cout << a.AllPaths() << endl;
	string input;
	while (cin >> input)
	{
		if (a.Run(input))
			cout << a.NowStatus() << endl;
		else
			cout << "Input error!" << endl;
	}
	return 0;
}

void AddLotsOfPath(string pathFrom, string pathTo, Automata &automata)
{
	string all = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
	for (size_t i = 0; i < all.length(); ++i)
	{
		automata.AddPath(pathFrom, pathTo, all.substr(i, 1));
	}
}


int TestEmail()
{
	Automata automata;
	automata.AddStatus("A", true);
	automata.AddStatus("B");
	automata.AddStatus("C");
	automata.AddStatus("D");
	automata.AddStatus("E");
	automata.AddStatus("F");
	automata.AddStatus("G", false, true);

	AddLotsOfPath("A", "B", automata);
	AddLotsOfPath("B", "B", automata);
	automata.AddPath("B", "C", "@");
	AddLotsOfPath("C", "D", automata);
	AddLotsOfPath("D", "E", automata);
	AddLotsOfPath("E", "E", automata);
	automata.AddPath("E", "F", ".");
	AddLotsOfPath("F", "G", automata);
	AddLotsOfPath("G", "G", automata);

	cout << automata.AllPaths();

	cout << "A legal email address should match 'AA*@AAA*.AA*'," << endl;
	cout << "'A' means a numbers, a letter or a underline," << endl;
	while (true)
	{
		cout << "Input a email address:";
		string input;
		getline(cin, input);
		automata.Restart();
		bool needEnd = false;
		for (size_t i = 0; i < input.length(); ++i)
		{
			cout << automata.NowStatus() << endl;
			if (!automata.Run(input.substr(i, 1)))
			{
				cout << "'" << input << "' is not a legal email address" << endl;
				cout << "Stop on " << input.substr(i, 1) << endl;
				needEnd = true;
				break;
			}
		}
		if (needEnd)
			continue;
		if(!automata.IsStopped())
			cout << "'" << input << "' is not a legal email address" << endl;
		else
			cout << "'" << input << "' is a legal email address" << endl;
	}
	return 0;
}