#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

//Algoritmo voraz
//Red. dif.
/**
* Tomamos los túneles desde la izquierda lo más a la derecha posible
* Dada sol. óptima y solución voraz, todos están igual desde la izquierda hasta cierto punto
* En ese punto hay un túnel óptimo to y un túnel voraz tv.
* Si tv>to, podemos mover to hasta tv. Estará en contacto con al menos los mismos edificios que el original
* Así que no se pierde factibilidad
* Si tv<to, hay un edificio que no es cubierto por to. Contradicción
* 
* 
*/


bool resuelveCaso()
{
	int n;
	cin >> n;
	if(!n)
	{
		return 0;
	}
	vector<pair<int, int>> v;
	for (int i = 0; i < n; i++)
	{
		int aux1, aux2; cin >> aux1 >> aux2; v.push_back({ aux1,aux2 });
	}
	sort(v.begin(), v.end());
	auto it = v.begin();
	int maxReq = INT_MIN;
	int numTotal = 0;
	while (it != v.end())
	{
		if (it->first >= maxReq)
		{
			numTotal++;
			maxReq = it->second;
		}
		else
		{
			maxReq = min(maxReq, it->second);
		}
		++it;
	}
	cout << numTotal << "\n"; return true;
}


int main()
{
	while (resuelveCaso());
	return 0;
}