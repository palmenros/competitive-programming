#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include "ConjuntosDisjuntos.h"
using namespace std;


//Utilizamos ConjuntosDisjuntos. Para evitar recorridos innecesarios, llevaremos una variable que será el tamaño máximo del mayor grupo
//en ese momento.

void resuelveCaso()
{
	int v, e;
	cin >> v >> e;

	auto datosUnion = ConjuntosDisjuntos(v);
	int maxTamano = 1;
	for (int i = 0; i < e; i++)
	{
		int aux1, aux2;
		cin >> aux1 >> aux2;
		aux1--; aux2--;
		datosUnion.unir(aux1, aux2);
		maxTamano = max(maxTamano, datosUnion.cardinal(aux1));
	}
	cout << maxTamano << "\n";
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