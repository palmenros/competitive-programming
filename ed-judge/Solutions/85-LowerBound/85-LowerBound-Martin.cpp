#include <iostream>
#include "set_eda.h"
using namespace std;

int main()
{
	while (true)
	{
		int n;
		cin >> n;
		if (!n) { return 0; }
		set<int> s;
		for (int i = 0; i < n; i++)
		{
			int aux;
			cin >> aux;
			s.insert(aux);
		}
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			int aux;
			cin >> aux;
			auto t = s.lower_bound(aux);
			if (t.first)
			{
				cout << t.second << "\n";
			}
			else
			{
				cout << "NO HAY\n";
			}
		}
		cout << "---\n";
	}
}