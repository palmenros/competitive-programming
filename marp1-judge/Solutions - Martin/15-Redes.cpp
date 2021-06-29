#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <climits>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <list>
#include "Grafo13.h"
using namespace std;

//Hacemos un recorrido en anchura con una cola
//Y luego sacamos una lista de nodos inaccesibles
//Lineal en (V+E) * N, donde N es el número de consultas sobre el grafo
//Ya que el recorrido en anchura tiene complejidad O(V+E)

bool resuelveCaso()
{
	Grafo13 grafo = Grafo13(cin);
	if (!cin) { return false; }
	int numConsultas;
	cin >> numConsultas;
	while (numConsultas--)
	{
		int nodo, ttl;
		cin >> nodo >> ttl;
		nodo--;
		queue<pair<int, int>> colaBFS;
		colaBFS.push({ nodo,ttl });
		vector<bool> marcado = vector<bool>(grafo.V(), false);
		int numeroFalsos = grafo.V();
		while (!colaBFS.empty())
		{
			auto val = colaBFS.front(); colaBFS.pop();
			if (marcado[val.first] == false)
			{
				marcado[val.first] = true;
				numeroFalsos--;
				if (val.second)
				{
					for (auto otro : grafo.ady(val.first))
					{
						colaBFS.push({ otro, val.second - 1 });
					}
				}
			}
		}
		cout << numeroFalsos << "\n";

	}
	cout << "---\n";
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}