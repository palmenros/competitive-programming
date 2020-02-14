#pragma once
#include "set.h"
using namespace std;
#include <iostream>

int main()
{
	while (true)
	{
		char aux;
		cin >> aux;
		if (!cin) { return 0; }
		int longitud;
		cin >> longitud;
		if (aux == 'P')
		{
			set<string> s;
			string aux;
			cin >> aux;
			while (aux != "FIN")
			{
				s.insert(aux);
				cin >> aux;
				if (s.size()>longitud)
				{
					s.delMinimo();
				}
			}
			while (s.size() > 0)
			{
				string k = s.minimo();
				cout << k;
				s.delMinimo();
				if (s.size())
				{
					cout << " ";
				}
				else
				{
					cout << "\n";
				}
			}

		}
		if (aux == 'N')
		{
			set<int> s;
			int aux;
			cin >> aux;
			while (aux != -1)
			{
				s.insert(aux);
				cin >> aux;
				if (s.size() > longitud)
				{
					s.delMinimo();
				}
			}
			while (s.size() > 0)
			{
				int k = s.minimo();
				cout << k;
				s.delMinimo();
				if (s.size())
				{
					cout << " ";
				}
				else
				{
					cout << "\n";
				}
			}
		}
	}
}