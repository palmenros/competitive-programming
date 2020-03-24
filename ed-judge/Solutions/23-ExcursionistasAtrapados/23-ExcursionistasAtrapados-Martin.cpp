#include "bintree_eda.h"
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

struct DatosArbol
{
	int sumaMax;
	int nCaminos;
	DatosArbol(int sumaMax, int nCaminos) : sumaMax(sumaMax), nCaminos(nCaminos)
	{
	}
};

bintree<int> buildTree()
{
	int c;
	cin >> c;
	if (c == -1)
	{
		return bintree<int>();
	}
	else
	{
		return bintree<int>(buildTree(), c, buildTree());
	}
}

DatosArbol obtenerDatosArbol(bintree<int> arbol)
{
	//Caso trivial: �rbol vac�o
	if (arbol.empty())
	{
		return DatosArbol(0, 0);
	}
	else
	{
		auto datosIzq = obtenerDatosArbol(arbol.left());
		auto datosDer = obtenerDatosArbol(arbol.right());
		return DatosArbol(
			max(datosIzq.sumaMax,datosDer.sumaMax)+arbol.root(),
			//El m�ximo ir� por el nodo actual y la izquierda (datosIzq.sumaMax+arbol.root)
			//o bien por el nodo actual y la derecha (datosDer.sumaMax+arbol.root). Queremos el m�ximo de las dos.
			datosIzq.nCaminos+datosDer.nCaminos+(!(datosIzq.nCaminos+datosDer.nCaminos)&&arbol.root()?1:0)
			//Si no hay caminos por ning�n lado y hay excursionistas es que no habr� nadie arriba,
			//as� que expresamente tendr� que venir un camino hasta este nodo
		);
	}
}

void resuelveCaso()
{
	bintree<int> arbol = buildTree();
	auto z = obtenerDatosArbol(arbol);
	cout << z.nCaminos << " " << z.sumaMax << '\n';
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