#include <iostream>
#include <list>
#include <vector>
#include <unordered_set>
#include "Grafo17.h"
using namespace std;


//El problema es el de obtener el orden topológico de un grafo, se puede resolver con un recorrido iterativo
//en profundidad, coste lineal en V+E

bool visitar(int nodoAct, unordered_set<int>& noMarcados, vector<bool>& marcasPermanentes, vector<bool>& marcasTemporales, const Grafo17& grafo, list<int>& listaOrden)
{
	if (marcasPermanentes[nodoAct]) { return true; } //Si lo visitamos en una iteración anterior no es relevante
	if (marcasTemporales[nodoAct]) { return false; } //Misma iteración => ciclo, es imposible hacer orden lineal
	marcasTemporales[nodoAct] = true; //Añadir marca temporal
	for (auto val : grafo.ady(nodoAct))
	{
		if (!visitar(val, noMarcados, marcasPermanentes, marcasTemporales, grafo, listaOrden))
		{
			return false; //VIsitamos recursivamente, si va mal devolvemos false
		}
	}
	marcasTemporales[nodoAct] = false; //Retirar marca temporal
	//Marcar definitivamente y añadir al orden
	marcasPermanentes[nodoAct] = true;
	noMarcados.erase(nodoAct);
	listaOrden.push_front(nodoAct);
	return true;

}

bool resuelveCaso()
{
	Grafo17 grafo(cin);
	if (!cin)
	{
		return false;
	}
	//Lista con el orden obtenido
	list<int> listaOrden;
	//Marcas
	vector<bool> marcasPermanentes(grafo.V() + 1, false);
	vector<bool> marcasTemporales(grafo.V() + 1, false);
	//Conjunto con los nodos no procesados
	unordered_set<int> noMarcados;
	for (int i = 1; i <= grafo.V(); i++)
	{
		noMarcados.insert(i);
	}
	while (true)
	{
		auto it = noMarcados.begin();
		if (it == noMarcados.end()) { break; }
		int nodoAct = *it;
		if (!visitar(nodoAct, noMarcados, marcasPermanentes, marcasTemporales, grafo, listaOrden))
		{
			cout << "Imposible\n"; return true;
		}
	}
	//Ya hemos obtenido el orden. Lo mostramos
	auto it = listaOrden.begin();
	if (it != listaOrden.end())
	{
		cout << *it; ++it;
	}
	while (it != listaOrden.end())
	{
		cout << " " << *it; ++it;
	}
	cout << "\n"; return true;
}


int main()
{
	while (resuelveCaso());
	return 0;
}