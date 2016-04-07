#include "Automata.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	Automata a;
	a.AddStatus("A", true);
	a.AddStatus("B");
	a.AddStatus("C", false, true);
	a.AddPath("A", "A", "a");
	a.AddPath("A", "B", "b");
	a.AddPath("B", "B", "b");
	a.AddPath("B", "C", "c");
	a.AddPath("C", "C", "c");
	cout << a.Show();
	string input;
	while (cin >> input)
	{
		if (a.Run(input))
			cout << a.Show();
		else
			cout << "Input error!" << endl;
	}
	return 0;
}