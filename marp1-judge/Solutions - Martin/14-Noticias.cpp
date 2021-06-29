#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <climits>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <list>
#include "ConjuntosDisjuntos.h"
using namespace std;

//Este problema es fácil. Se trata de hacer las componentes conexas de amigos y ver cuántas personas son cada una.
//El coste es lineal en número de personas + tamaño de la entrada

bool resuelveCaso()
{
	int n, m;
	cin >> n >> m;
	if (!cin) { return false; }
	auto datos = ConjuntosDisjuntos(n);
	while (m--)
	{
		int numPers;
		cin >> numPers;
		if (numPers)
		{
			int aux1, aux2;
			numPers--;
			cin >> aux2;
			aux2--;
			while (numPers--)
			{
				aux1 = aux2;
				cin >> aux2;
				aux2--;
				datos.unir(aux1, aux2);
			}
		}
	}
	//Ya tenemos las componentes conexas
	cout << datos.cardinal(0);
	for (int i = 1; i < n; i++)
	{
		cout << " " << datos.cardinal(i);
	}
	cout << "\n";
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}