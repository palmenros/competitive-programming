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

//Lo haremos con conjuntos disjuntos de esta forma:
//Uniremos en un mismo conjunto cada mancha
//El número de manchas será el número de conjuntos menos el número de blancas.
//El número más alto será como en el problema anterior.
//No hace falta guardar todos los datos a la vez, se puede hacer por filas

bool resuelveCaso()
{
	int r, c;
	cin >> r >> c;
	if (!cin) { return false; }
	vector<bool> datosFilaAnterior;
	//Datos de los conjuntos
	ConjuntosDisjuntos datosPixeles = { r * c };
	int tamanoMax = 0;
	int numeroDeBlancos = 0;
	for (int i = 0; i < r; i++)
	{
		vector<bool> datosFilaNueva;
		for (int j = 0; j < c; j++)
		{
			char aux;
			cin >> aux;
			if (aux == '-')
			{
				datosFilaNueva.push_back(false);
				numeroDeBlancos++;
			}
			else
			{
				datosFilaNueva.push_back(true);
				if (i > 0 && datosFilaAnterior[j])
				{
					datosPixeles.unir(c * i + j, c * (i - 1) + j);
				}
				if (j > 0 && datosFilaNueva[j - 1])
				{
					datosPixeles.unir(c * i + j, c * i + j - 1);
				}
				tamanoMax = max(tamanoMax, datosPixeles.cardinal(c * i + j));
			}
		}
		datosFilaAnterior.swap(datosFilaNueva);
	}
	cout << datosPixeles.num_cjtos() - numeroDeBlancos << " " << tamanoMax << "\n";
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}