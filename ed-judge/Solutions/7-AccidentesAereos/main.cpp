#include "fecha.h"
#include <iostream>
#include <stack>
using namespace std;

typedef pair<fecha, int> tPareja;

int main()
{
	while (true)
	{
		int n;
		cin >> n;
		if (!cin) { return 0; }
		stack<tPareja> pila;
		//Hacemos una pila con los peores accidentes desde la eternidad, no guardando accidentes que sucedieron antes
		//que otros con menos v�ctimas. As� sabemos r�pidamente cu�l fue el m�s reciente con m�s v�ctimas.
		for (int i = 0; i < n; i++)
		{
			tPareja aux;
			cin >> aux.first >> aux.second;
			while (!pila.empty() && pila.top().second <= aux.second)
			{
				pila.pop();
			}
			if (!pila.empty())
			{
				cout << pila.top().first << "\n";
			}
			else
			{
				cout << "NO HAY\n";
			}
			pila.push(aux);

		}
		cout << "---\n";
	}
}