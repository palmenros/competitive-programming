#include <iostream>
#include <vector>
#include <queue>
#include "Grafo21.h"
#include "ConjuntosDisjuntos.h"
using namespace std;

//Este problema se resuelve haciendo componentes conexas dada cierta anchura
//Por lo que el coste de una consulta es cuasi lineal en V+E
bool resuelveCaso()
{
	Grafo21 grafo(cin);
	if (!cin) { return false; }
	int nConsultas;
	cin >> nConsultas;
	while (nConsultas--)
	{
		ConjuntosDisjuntos componentes(grafo.V());
		int origen;
		int destino;
		int anchura;
		vector<bool> marcados(grafo.V(), false);
		cin >> origen >> destino >> anchura;
		origen--; destino--;
		queue<int> porExplorar;
		porExplorar.push(origen);
		marcados[origen] = true;
		while (!porExplorar.empty())
		{
			int act = porExplorar.front(); porExplorar.pop();
			for (auto& otro : grafo.ady(act))
			{
				if (otro.second >= anchura && !marcados[otro.first])
				{
					componentes.unir(act, otro.first);
					porExplorar.push(otro.first);
					marcados[otro.first] = true;
				}
			}
		}
		if (componentes.unidos(origen, destino))
		{
			cout << "SI\n";
		}
		else
		{
			cout << "NO\n";
		}
	}
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}