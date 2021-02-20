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

//Un �rbol es libre si y solo si el n�mero de aristas es uno menos el n�mero de v�rtices y es conexo
//As� que comprobamos esas dos cosas y ya est�.
//Una de ellas se comprueba comparando dos n�meros
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