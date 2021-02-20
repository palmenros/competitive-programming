//Martín Gómez Abejón
//Problema 01 - Es un árbol AVL?
#include <iostream>
#include <algorithm>
#include <climits>
#include "bintree_eda.h"
using namespace std;

struct datosArboles //Struct utilizado para pasar datos recursivamente en esAVLyDatos
{
	bool esAVL;
	int altura;
	int min; //Elemento mínimo
	int max; //Elemento máximo
	datosArboles(bool esAVL, int altura, int min, int max) :esAVL(esAVL), altura(altura), min(min), max(max) {  }
};


datosArboles esAVLyDatos(bintree<int> arbol) //Función recursiva, lineal en número de nodos, que responde 
//a la pregunta de si el arbol es binario de búsqueda y está equilibrado, y proporciona datos extra para poder
//responder en tiempo lineal
{
	if (arbol.empty()) { return { true,0,INT_MAX,INT_MIN }; }
	else
	{
		auto datosIzq = esAVLyDatos(arbol.left());
		auto datosDer = esAVLyDatos(arbol.right());
		return {

			//Que sean AVL los hijos, diferencia de alturas pequeña y que sean de búsqueda (maxizq<root<minder)
			datosIzq.esAVL && datosDer.esAVL && abs(datosIzq.altura - datosDer.altura) <= 1 &&
			datosIzq.max < arbol.root() && arbol.root() < datosDer.min
			,
			max(datosIzq.altura,datosDer.altura) + 1,
			min(min(datosIzq.min,datosDer.min),arbol.root()),
			max(max(datosIzq.max,datosDer.max),arbol.root())
		};
	}
}

void resuelveCaso()
{
	auto a = leerArbol(-1); //Leer arbol
	if (esAVLyDatos(a).esAVL) //Si es completo
	{
		cout << "SI\n";
	}
	else
	{
		cout << "NO\n";
	}
}

int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		resuelveCaso();
	}
	return 0;
}