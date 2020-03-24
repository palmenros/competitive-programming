#include "bintree_eda.h"
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

bintree<bool> buildTree()
{
	char c;
	cin >> c;
	if (c == '.')
	{
		return bintree<bool>();
	}
	else
	{
		return bintree<bool>(buildTree(), false, buildTree());
	}
}
template <class T>
pair <int, int> obtenerAlturaYDiametro(bintree<T> arbol)
{
	//La función devuelve la altura y el diámetro, calculados de manera recursiva
	//Teniendo esos dos valores la recursión es natural
	//Es obvio para las alturas. Para los diámetros, tengamos en cuenta que el diámetro es
	//el máximo de los diámetros de cada parte del árbol y la suma de las alturas de las mitades más 1,
	//en función de por dónde vaya el camino.
	//Caso trivial: árbol vacío
	if (arbol.empty())
	{
		return make_pair(0, 0);
	}
	else
	{
		auto datosIzq = obtenerAlturaYDiametro(arbol.left());
		auto datosDer = obtenerAlturaYDiametro(arbol.right());
		return make_pair(
			max(datosDer.first, datosIzq.first) + 1, //La altura es el máximo de las alturas más 1
			max(max(datosDer.second, datosIzq.second), datosDer.first + datosIzq.first + 1)
			//El diámetro es el máximo de los diámetros de cada subárbol (consideramos caminos contenidos en ellos
			//y la suma de las alturas más 1 (consideramos caminos máximales que van de uno a otro)
		);
	}
}

void resuelveCaso()
{
	bintree<bool> arbol = buildTree();
	cout << obtenerAlturaYDiametro(arbol).second << '\n';
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