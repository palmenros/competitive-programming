#include <iostream>
#include <algorithm>
#include "bintree_eda.h"
using namespace std;

struct Datos
{
	int mayorActual;
	int mayorPrevio;
	Datos (int a, int b):mayorActual(a),mayorPrevio(b){}
};

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
Datos mayorCompleto(bintree<T> arbol)
{
	//Para hacer esta función asumimos que los subárboles "se comportan bien"
	//Es decir que el resultado depende de qué consideremos como raíz
	//Y los subárboles van hacia abajo
	/*
	Por lo que 
	O
	 \
	  O
	   \
	    O
	tiene que devolver 1, no 2.
	*/
	//Lineal en el número de nodos n, ya que se llama a mayorCompleto n veces y cada llamada tiene coste
	//(sin contar llamadas recursivas) constante
	//Devolvemos la altura del árbol completo más grande desde la raíz, y la altura más grande del encontrado nunca
	//Caso trivial
	if (arbol.empty())
	{
		return { 0,0 };
	}
	//Caso recursivo
	//El mayor actual tiene evidentemente altura 1 + el mínimo de las alturas actuales
	//Y el mayor previo es el máximo de los mayores previos de cada árbol y la altura del actual (por si el mayor actual fuera el mayor de todos)
	Datos izq = mayorCompleto(arbol.left());
	Datos der = mayorCompleto(arbol.right());
	int nuevoActual = 1 + min(izq.mayorActual, der.mayorActual);
	return { nuevoActual, max(nuevoActual,max(izq.mayorPrevio,der.mayorPrevio)) };
}

void resuelveCaso()
{
	bintree<bool> arbol = buildTree();
	cout << mayorCompleto(arbol).mayorPrevio << endl;
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