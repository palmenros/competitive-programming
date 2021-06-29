#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include "Grafo24.h"
using namespace std;

using lli = long long int;

//Se resuelve aplicando dos veces Dijkstra

struct nodoActDijkstra
{
	int nodo; lli distancia; int calles;
	nodoActDijkstra(int nodo, lli distancia, int calles) :nodo(nodo), distancia(distancia), calles(calles) { ; }
};



bool resuelveCaso()
{
	auto compPrimerDijkstra = [](nodoActDijkstra t1, nodoActDijkstra t2) //Ordenamos con un orden lineal, con valor calles + M * distancia
	//donde M es arbitrariamente grande
	{
		return t2.distancia < t1.distancia || (t2.distancia == t1.distancia && t2.calles < t1.calles);
	};
	auto compSegundoDijkstra = [](nodoActDijkstra t1, nodoActDijkstra t2)
	{
		return t2.calles < t1.calles;
	};
	Grafo24 grafo(cin);
	if (!cin) { return false; }
	int consultas; cin >> consultas; while (consultas--)
	{
		int origen, destino; cin >> origen >> destino; origen--; destino--;
		//Primer algoritmo de Dijkstra: intentar llegar al nodo de destino con menor longitud y menor número de calles
		int callesMasCorto=-1;
		{
			vector<bool> marcado(grafo.V(), false);
			priority_queue<nodoActDijkstra, vector<nodoActDijkstra>, decltype(compPrimerDijkstra)> colaDijkstra(compPrimerDijkstra);
			colaDijkstra.push({ origen,0,0 });
			while (!colaDijkstra.empty())
			{
				nodoActDijkstra act = colaDijkstra.top(); colaDijkstra.pop();
				if (!marcado[act.nodo])
				{
					marcado[act.nodo] = true;
					if (act.nodo == destino) { cout << act.distancia << " "; callesMasCorto = act.calles; break; }
					for (const auto& val : grafo.ady(act.nodo))
					{
						colaDijkstra.push({ val.first,val.second + act.distancia, act.calles + 1 });
					}
				}
			}
			if (callesMasCorto == -1)
			{
				cout << "SIN CAMINO\n"; continue;
			}
		}
		//Segundo algoritmo de Dijkstra
		{
			vector<bool> marcado(grafo.V(), false);
			priority_queue<nodoActDijkstra, vector<nodoActDijkstra>, decltype(compSegundoDijkstra)> colaDijkstra(compSegundoDijkstra);
			colaDijkstra.push({ origen,0,0 });
			while (!colaDijkstra.empty())
			{
				nodoActDijkstra act = colaDijkstra.top(); colaDijkstra.pop();
				if (!marcado[act.nodo])
				{
					marcado[act.nodo] = true;
					if (act.nodo == destino) { cout << (act.calles == callesMasCorto ? "SI" : "NO") << "\n"; break; }
					for (const auto& val : grafo.ady(act.nodo))
					{
						colaDijkstra.push({ val.first, 0, act.calles + 1 });
					}
				}
			}
		}

	}
	cout << "---\n";
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}