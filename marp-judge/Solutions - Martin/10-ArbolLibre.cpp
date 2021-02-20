#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <climits>
#include <deque>
#include <algorithm>
#include "ConjuntosDisjuntos.h"
using namespace std;

using lli = long long int;

//Un árbol es libre si y solo si el número de aristas es uno menos el número de vértices y es conexo
//Así que comprobamos esas dos cosas y ya está.
//Una de ellas se comprueba comparando dos números
//La otra se comprueba con ConjuntosDisjuntos

bool resuelveCaso()
{
	int v, e;
	cin >> v >> e;
	if (!cin) { return false; }
	if (v - 1 != e)
	{
		for (int i = 0; i < 2 * e; i++) { int aux; cin >> aux; }
		cout << "NO" << "\n";
	}
	else
	{
		auto datosUnion = ConjuntosDisjuntos(v);
		for (int i = 0; i < e; i++)
		{
			int aux1, aux2;
			cin >> aux1 >> aux2;
			datosUnion.unir(aux1, aux2);
		}
		if (datosUnion.num_cjtos() == 1)
		{
			cout << "SI" << "\n";
		}
		else
		{
			cout << "NO" << "\n";
		}
	}
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}