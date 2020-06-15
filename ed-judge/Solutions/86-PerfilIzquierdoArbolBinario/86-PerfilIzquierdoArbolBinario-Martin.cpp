#include <iostream>
#include <vector>
#include "bintree_eda.h"
using namespace std;

void imprimirVector(vector<int>& v)
{
	if (!v.empty())
	{
		cout << v[0];
	}
	for (unsigned int i = 1; i < v.size(); i++)
	{
		cout << " " << v[i];
	}
}

void resuelveCaso()
{
	vector<int> v; //Para imprimir
	bintree<int> arbol = leerArbol(-1); //Árbol
	//El algoritmo es lineal en el número de nodos, ya que hacemos un recorrido por niveles.
	//Es evidente que el perfil izquierdo puede terminar en cualquier rama, por lo que necesariamente cualquier algoritmo
	//será lineal en el número de nodos (hay que asegurarse de que todas las ramas se cierran)
	//Hacerlo por niveles es natural ya que hay que imprimir el primero de cada nivel
	//En primer lugar inicializamos el recorrido por niveles
	queue<bintree<int>> colaNiveles;
	bool primeroPasado = false; //Hemos pasado ya al primero?
	//Controlaremos el paso de un nivel a otro a través de un nodo fantasma.
	if (!arbol.empty())
	{
		colaNiveles.push(arbol);
	}
	//Fantasma
	colaNiveles.push(bintree<int>());
	while (!colaNiveles.empty())
	{
		auto aux = colaNiveles.front();
		colaNiveles.pop();
		//Distinguimos casos
		if (aux.empty()) //Nuevo nivel
		{
			primeroPasado = false; //Volvemos al principio
			if (!colaNiveles.empty()) //Si hay algo en el siguiente nivel
			{
				colaNiveles.push(bintree<int>()); //Ponemos otro fantasma para el siguiente nivel
			}
		}
		else
		{
			if (!primeroPasado) //Si es el primero
			{
				v.push_back(aux.root()); //Imprimir el primero
			}
			primeroPasado = true; //Ya hemos pasado el primero
			//Guardar hijos
			if (!aux.left().empty())
			{
				colaNiveles.push(aux.left());
			}
			if (!aux.right().empty())
			{
				colaNiveles.push(aux.right());
			}
		}
	}
	imprimirVector(v);
	cout << endl;
}

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		resuelveCaso();
	}
}