#include "bintree_eda.h"
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
template <class T>
bintree<T> buildTree(T eot)
{
	T c;
	cin >> c;
	if (c == eot)
	{
		return bintree<T>();
	}
	else
	{
		bintree<T> a = buildTree(eot);
		bintree<T> b = buildTree(eot);
		return bintree<T>(a, c, b);
	}
}
template <class T>
T obtenerMinimo(bintree<T> arbol, T marcadorVacio)
{
	//Caso trivial: árbol vacío
	if (arbol.empty())
	{
		return marcadorVacio;
	}
	else
	{
		auto datosIzq = obtenerMinimo(arbol.left(),marcadorVacio);
		auto datosDer = obtenerMinimo(arbol.right(),marcadorVacio);
		if (datosDer == marcadorVacio && datosIzq == marcadorVacio) //Hoja
		{
			return arbol.root();
		}
		else if (datosDer == marcadorVacio) //Como ya hemos considerado el caso anterior, el nodo no es hoja
		{
			//Así que el mínimo es el mínimo de la rama izquierda y el nodo actual
			return min(datosIzq,arbol.root());
		}
		else if (datosIzq == marcadorVacio) //Análogo del caso anterior
		{
			return min(datosDer,arbol.root());
		}
		else //Hay árboles no triviales en ambas ramas
		{
			return min(min(datosDer,datosIzq),arbol.root());
		}
	}
}
template <class T>
void resuelveCaso(T t)
{
	bintree<T> arbol = buildTree(t);
	cout << obtenerMinimo(arbol,t) << '\n';
}

int main()
{
	while (true)
	{
		char c;
		cin >> c;
		if (!cin) { return 0; }
		if (c == 'N')
		{
			resuelveCaso(-1);
		}
		if (c == 'P')
		{
			resuelveCaso((string)("#"));
		}
		
	}
}