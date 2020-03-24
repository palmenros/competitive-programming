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
	//La funci�n devuelve la altura y el di�metro, calculados de manera recursiva
	//Teniendo esos dos valores la recursi�n es natural
	//Es obvio para las alturas. Para los di�metros, tengamos en cuenta que el di�metro es
	//el m�ximo de los di�metros de cada parte del �rbol y la suma de las alturas de las mitades m�s 1,
	//en funci�n de por d�nde vaya el camino.
	//Caso trivial: �rbol vac�o
	if (arbol.empty())
	{
		return make_pair(0, 0);
	}
	else
	{
		auto datosIzq = obtenerAlturaYDiametro(arbol.left());
		auto datosDer = obtenerAlturaYDiametro(arbol.right());
		return make_pair(
			max(datosDer.first, datosIzq.first) + 1, //La altura es el m�ximo de las alturas m�s 1
			max(max(datosDer.second, datosIzq.second), datosDer.first + datosIzq.first + 1)
			//El di�metro es el m�ximo de los di�metros de cada sub�rbol (consideramos caminos contenidos en ellos
			//y la suma de las alturas m�s 1 (consideramos caminos m�ximales que van de uno a otro)
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