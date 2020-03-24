#include <iostream>
#include "bintree_eda.h"
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
		auto izq = buildTree();
		auto der = buildTree();
		return bintree<bool>(izq, false, der);
	}
}
template <class T>
bool simetricos(bintree<T> arbol1, bintree<T> arbol2)
{
	//Son sim�tricos si y solo si la ra�z tiene el mismo valor (aunque no sea relevante en las llamadas de este problema),
	//y son sim�tricos un hijo izquierdo con el hijo del otro derecho
	//Que la ra�z tenga el mismo valor quiere decir tambi�n que ambas existan o no existan a la vez
	return
		arbol1.empty() == arbol2.empty() && //Circuito corto; seguro
		(arbol1.empty() || // (circuito corto) Si los �rboles no est�n vac�os, se tiene que dar la simetr�a recursiva
		(simetricos(arbol1.left(), arbol2.right()) &&
			simetricos(arbol1.right(), arbol2.left())));
}
template <class T>
bool simetrico(bintree<T> arbol)
{
	//Es lineal en el n�mero de nodos n, porque llamamos a una recursi�n n veces y cada cuerpo de cada llamada (sin
	//contar las llamadas recursivas) es constante
	if (arbol.empty())
	{
		return true;
	}
	else
	{
		return simetricos(arbol.left(), arbol.right());
	}
}
void resuelveCaso()
{
	bintree<bool> arbol = buildTree();
	cout << (simetrico(arbol) ? "SI\n" : "NO\n");
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