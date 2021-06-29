#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <climits>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <list>
#include "Grafo18.h"
using namespace std;

//Dado el grafo, podemos elegir una pareja de v�rtices A y B y descartar que uno de los dos sea sumidero.
//Ya que si B es sumidero, A->B pero no B->A. Podemos descartar el v�rtice que no tenga arista desde el otro,
//o los dos si hay aristas de uno al otro.
//Hemos cambiado la implementaci�n del grafo para poder comparar dos v�rtices r�pidamente, utilizando unordered_set
//Con esta implementaci�n el coste es lineal en V+E

bool resuelveCaso()
{
	Grafo18 grafo(cin);
	if (!cin) { return false; }
	int ind1 = 0, ind2 = grafo.V() - 1;
	//Explicaci�n
	//Nuestro objetivo es, en cada paso, descartar el �ndice ind1 o el �ndice ind2. Si descartamos ind1, le sumamos
	//1, si descartamos ind2 le restamos 1
	//En alg�n momento ind1=ind2
	//En ese paso tenemos que comprobar que ind1 = ind2 sea sumidero
	while (ind1 != ind2)
	{
		//No lo hacemos dif�cil, nos conformamos con descartar uno a la vez
		//Si hay una arista de ind1 a ind2, ind1 no es sumidero
		//Si no la hay no lo es ind2
		if (grafo.hayArista(ind1, ind2))
		{
			ind1++;
		}
		else
		{
			ind2--;
		}
	}
	//Ahora ya hemos llegado a un nodo que podr�a ser sumidero.
	//Hay que comprobar que lo es
	for (int i = 0; i < grafo.V(); i++)
	{
		if (i != ind1)
		{
			if (grafo.hayArista(ind1, i) || !grafo.hayArista(i,ind1))
			{
				cout << "NO\n"; return true;
			}
		}
	}
	cout << "SI " << ind1 << "\n";
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}