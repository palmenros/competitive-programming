#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include "Grafo24.h"
using namespace std;

using lli = long long int;

//Lo resolvemos aplicando Dijkstra en primer lugar para saber la distancia del colegio a cada vértice
//Luego hacemos un procedimiento recursivo que poda adecuadamente y devuelve finalmente lo pedido
//Coste en O(E * (log(V) + 1)) = O(E log(V))

struct nodoActDijkstra
{
	int nodo; lli distancia;
	nodoActDijkstra(int nodo, lli distancia) :nodo(nodo), distancia(distancia) { ; }
};

bool operator<(nodoActDijkstra t1, nodoActDijkstra t2)
{
	return t2.distancia < t1.distancia;
}

lli numeroDeFormas(int vertice, const vector<lli>& distancias, vector<lli>& resultadosIntermedios, vector<bool>& visitados, const Grafo24& grafo)
{
	//Caso trivial
	if (distancias[vertice] == -1) { return 0; }
	//Si hemos obtenido la solución antes, la devolvemos
	if (visitados[vertice]) { return resultadosIntermedios[vertice]; }
	lli nFormas = 0;
	//Para cada vértice, sumamos el número de formas de cada vértice adyacente que cumpla la condición descrita en resuelveCaso()
	//No hace falta marcar el recorrido que va haciendo la recursión, ya que por las condiciones del problema
	//nos dirigimos a vértices con menor distancia al colegio
	for (const auto& val : grafo.ady(vertice))
	{
		if (distancias[val.first] + val.second == distancias[vertice]) //Si se puede hacer un camino por esa arista
		{
			nFormas += numeroDeFormas(val.first, distancias, resultadosIntermedios, visitados, grafo);
		}
	}
	//Guardamos la solución, así no tenemos que volver a recorrer los caminos de este vértice si lo volvemos a llamar
	visitados[vertice] = true; resultadosIntermedios[vertice] = nFormas;
	return nFormas;
}

bool resuelveCaso()
{
	Grafo24 grafo(cin);
	if (!cin) { return false; }
	//Algoritmo de Dijkstra
	vector<lli> distancias(grafo.V(), -1);
	vector<bool> marcado(grafo.V(), false);
	priority_queue<nodoActDijkstra> colaDijkstra;
	colaDijkstra.push({ grafo.V() - 1,0 });
	while (!colaDijkstra.empty())
	{
		nodoActDijkstra act = colaDijkstra.top(); colaDijkstra.pop();
		if (!marcado[act.nodo])
		{
			marcado[act.nodo] = true;
			distancias[act.nodo] = act.distancia;
			for (const auto& val : grafo.ady(act.nodo))
			{
				colaDijkstra.push({ val.first,val.second + act.distancia });
			}
		}
	}
	//Ahora ejecutamos el algoritmo que devuelve el número de caminos.
	//El algoritmo se basa en este principio: el número de formas de ir de un nodo al colegio es sumar el número de
	//formas de hacerlo desde los nodos adyacentes, para los cuales su distancia al colegio más el peso de la arista
	//sea igual a la distancia del nodo principal al colegio.
	//Para que el algoritmo sea barato, guardamos los resultados intermedios en un vector para no tener que recorrer
	//todos los caminos al hacer recursión
	vector<lli> resultadosIntermedios(grafo.V());
	vector<bool> visitados(grafo.V(), false);
	visitados[grafo.V() - 1] = true; resultadosIntermedios[grafo.V() - 1] = 1;
	cout << numeroDeFormas(0, distancias, resultadosIntermedios, visitados, grafo) << "\n";
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}