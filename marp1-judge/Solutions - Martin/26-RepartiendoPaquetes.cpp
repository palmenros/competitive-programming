#include <iostream>
#include "Grafo26.h"
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;


//Este problema se resuelve fácilmente utilizando Dijkstra en el grafo y en su inverso, es decir,
//el que tiene las mismas aristas pero dadas la vuelta.
//Dijkstra en el grafo normal nos calcula la distancia entre la oficina y cada casa
//Dijkstra en el inverso nos calcula la distancia entre cada casa y la oficina

struct datosVerticeAct
{
	int verticeDestino;
	int distanciaRecorrida;
	datosVerticeAct(int verticeDestino, int distanciaRecorrida) :verticeDestino(verticeDestino), distanciaRecorrida(distanciaRecorrida) {  }
};

bool operator<(const datosVerticeAct& t1, const datosVerticeAct& t2)
{
	return t2.distanciaRecorrida < t1.distanciaRecorrida;
}

bool resuelveCaso()
{
	//Implementamos Dijkstra con una cola que no nos deja acceder a los elementos, por lo que
	//puede haber información superflua, aunque esta no hace la complejidad peor
	//porque O(log(V+E)) \subseteq O(log(V))
	Grafo26 grafo(cin);
	if (!cin) { return false; }
	vector<int> distanciasIda(grafo.V(),-1);
	vector<int> distanciasVuelta(grafo.V(), -1);
	int oficina;
	cin >> oficina;
	oficina--;
	//Primer Dijkstra
	{
		priority_queue<datosVerticeAct> cola;
		cola.push({ oficina,0 });
		vector<bool> marcados(grafo.V(), false);
		while (!cola.empty())
		{
			datosVerticeAct act = cola.top(); cola.pop();
			if (!marcados[act.verticeDestino])
			{
				marcados[act.verticeDestino] = true;
				distanciasIda[act.verticeDestino] = act.distanciaRecorrida;
				for (auto& vertNuevo : grafo.ady(act.verticeDestino))
				{
					cola.push({ vertNuevo.first,act.distanciaRecorrida + vertNuevo.second });
				}
			}
		}
	}
	//Segundo Dijkstra
	{
		priority_queue<datosVerticeAct> cola;
		cola.push({ oficina,0 });
		vector<bool> marcados(grafo.V(), false);
		while (!cola.empty())
		{
			datosVerticeAct act = cola.top(); cola.pop();
			if (!marcados[act.verticeDestino])
			{
				marcados[act.verticeDestino] = true;
				distanciasVuelta[act.verticeDestino] = act.distanciaRecorrida;
				for (auto& vertNuevo : grafo.adyDual(act.verticeDestino))
				{
					cola.push({ vertNuevo.first,act.distanciaRecorrida + vertNuevo.second });
				}
			}
		}
	}
	//Procesar peticiones
	int numP;
	cin >> numP;
	bool factible = true;
	int distTotal = 0;
	while (numP--)
	{
		int aux;
		cin >> aux;
		aux--;
		int distIda = distanciasIda[aux];
		int distVuelta = distanciasVuelta[aux];
		if (distIda == -1 || distVuelta == -1)
		{
			factible = false;
		}
		distTotal += (distIda + distVuelta);
	}
	if (factible)
	{
		cout << distTotal << "\n";
	}
	else
	{
		cout << "Imposible\n";
	}
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}