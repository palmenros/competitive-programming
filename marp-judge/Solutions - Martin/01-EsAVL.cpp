//Mart�n G�mez Abej�n
//Problema 01 - Es un �rbol AVL?
#include <iostream>
#include <algorithm>
#include <climits>
#include "bintree_eda.h"
using namespace std;

struct datosArboles //Struct utilizado para pasar datos recursivamente en esAVLyDatos
{
	bool esAVL;
	int altura;
	int min; //Elemento m�nimo
	int max; //Elemento m�ximo
	datosArboles(bool esAVL, int altura, int min, int max) :esAVL(esAVL), altura(altura), min(min), max(max) {  }
};


datosArboles esAVLyDatos(bintree<int> arbol) //Funci�n recursiva, lineal en n�mero de nodos, que responde 
//a la pregunta de si el arbol es binario de b�squeda y est� equilibrado, y proporciona datos extra para poder
//responder en tiempo lineal
{
	if (arbol.empty()) { return { true,0,INT_MAX,INT_MIN }; }
	else
	{
		auto datosIzq = esAVLyDatos(arbol.left());
		auto datosDer = esAVLyDatos(arbol.right());
		return {

			//Que sean AVL los hijos, diferencia de alturas peque�a y que sean de b�squeda (maxizq<root<minder)
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