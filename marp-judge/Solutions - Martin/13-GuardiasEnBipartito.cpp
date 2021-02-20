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
#include "Grafo13.h"
using namespace std;

using lli = long long int;

//Lo que el problema pide realmente es
//Determinar si el grafo es bipartito
//Y si lo es dar una división en dos que respete la biparticidad y tenga el mínimo número de vértices en uno de los conjuntos
//Lo vamos a resolver por componentes conexas,
//resolviendo el problema para cada una.

struct datosVertice
{
	int n;
	bool blanco;
	bool marcado = false;
};

bool procesar(bool esBlanco, list<datosVertice>::iterator elem, int& blancosAct, int& rojosAct, vector<list<datosVertice>::iterator>& elementosABorrar, vector<list<datosVertice>::iterator>& referencias, Grafo13& grafoInicial)
{
	//En primer lugar vemos que no haya contradicciones
	if (elem->marcado && elem->blanco != esBlanco)
	{
		return false;
	}
	//Si ya está procesado no hay nada que hacer
	if (elem->marcado)
	{
		return true;
	}
	//Marcamos y le ponemos el color correspondiente
	elem->marcado = true;
	elem->blanco = esBlanco;
	//Lo marcamos como elemento que queremos borrar una vez procesada la componente
	elementosABorrar.push_back(elem);
	if (esBlanco)
	{
		blancosAct++;
	}
	else
	{
		rojosAct++;
	}
	//Procesamos el resto de vértices
	for (auto otro : grafoInicial.ady(elem->n))
	{
		if (!procesar(!esBlanco, referencias[otro], blancosAct, rojosAct, elementosABorrar, referencias, grafoInicial))
		{
			return false; //Si hay contradicciones en el recorrido posterior hay que pasarlas hacia arriba
		}
	}
	return true;
}

bool resuelveCaso()
{
	//Coste lineal en V+E porque hacemos recorridos lineales
	//Obtener el grafo
	auto grafoInicial = Grafo13(cin);
	if (!cin) { return false; }
	//Hacer componentes conexas y procesarlas de una en una a través de marcados
	//Lista con todos los vértices
	list<datosVertice> listaVertices;
	vector<list<datosVertice>::iterator> referencias;
	int blancosTotales=0; //Nodos que tendrán guardia
	//Procesamos cada componente conexa a través de uno de sus vértices
	//Inicializar listas
	for (int i = 0; i < grafoInicial.V(); i++)
	{
		listaVertices.push_back({ i });
		auto it = listaVertices.end();
		it--;
		referencias.push_back(it);
	}
	while (!listaVertices.empty())
	{
		vector<list<datosVertice>::iterator> elementosABorrar;
		int blancosAct = 0;
		int rojosAct = 0;
		//Cogemos el primer nodo de la lista y lo procesamos. Si la componente conexa es contradictoria salimos
		if (!procesar(true, listaVertices.begin(),blancosAct,rojosAct,elementosABorrar,referencias,grafoInicial)) { cout << "IMPOSIBLE\n"; return true; }
		blancosTotales += min(blancosAct, rojosAct); //Sumamos los guardias que nos hacen falta
		//pero que sean los mínimos posibles
		for (auto it : elementosABorrar)
		{
			listaVertices.erase(it);
		}
	}
	cout << blancosTotales << "\n";
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}