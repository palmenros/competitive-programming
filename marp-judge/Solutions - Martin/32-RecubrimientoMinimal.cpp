#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//Algoritmo voraz similar pero opuesto al problema de la maratón de películas
//El mismo uso de iteradores pero con criterios de descarte diferentes
//En cada iteración, si uno de los intervalos está contenido en otro, descartamos el más pequeño
//Si no,
//si el intervalo sig está pegado al candidato, elegimos el candidato y resolvemos el problema con
//el intervalo de vulnerabilidad adaptado
//Si no están pegados es infactible
//Red. dif.
/**
* Sea, con el orden lexicográfico, i el primero que es diferente
* Si está en óptima y no en voraz,
* es porque fue descartado frente a otro u otros dos más grande(s)
* cogemos el(los) más grande(s) en vez de ese. (Uno de ellos estará ya cogido porque estará antes en el orden lex)
* Si está en voraz y no en óptima, se puede intercambiar el que se había elegido justo después en la óptima con
* el elegido en el voraz,si no fuera así la solución óptima sería infactible.
* 
* 
*/
pair<int, int> intervaloInterseccion(int c, int f, pair<int, int> intervalo)
{
	return { min(max(intervalo.first,c),f),min(max(intervalo.second,c),f) };
}


bool resuelveCaso()
{
	int c, f, n;
	cin >> c >> f >> n;
	if (!c&&!f&&!n) { return false; }
	vector<pair<int, int>> v;
	for (int i = 0; i < n; i++)
	{
		int aux1, aux2;
		cin >> aux1 >> aux2;
		v.push_back({ aux1,aux2 });
	}
	sort(v.begin(), v.end());
	if (v.begin() == v.end() || c == f) //Casos triviales
	{
		if (c == f)
		{
			cout << "0\n";
		}
		else
		{
			cout << "Imposible\n";
		}
		return true;
	}
	if (v.begin()->first > c) { cout << "Imposible\n"; return true; }
	//Cambiamos c y f dinámicamente en función de lo que hayamos cubierto hasta ahora
	auto itsig = v.begin(); itsig++;
	auto itcand = v.begin();
	int numeroTotal = 0;
	while (itsig != v.end())
	{
		auto sig = intervaloInterseccion(c, f, *itsig);
		auto cand = intervaloInterseccion(c, f, *itcand);
		if (sig.first == cand.first)
		{
			if (cand.second < sig.second)
			{
				itcand = itsig;
				itsig++;
			}
			else
			{
				itsig++;
			}
		}
		else
		{
			if (sig.first > cand.second)
			{
				cout << "Imposible\n"; return true;
			}
			else
			{
				itcand = itsig;
				itsig++; numeroTotal++;
				c = cand.second;
			}
		}
	}
	auto cand = intervaloInterseccion(c, f, *itcand);
	if (f == cand.second)
	{
		if (cand.first != cand.second)
		{
			numeroTotal++;
		}
		cout << numeroTotal << "\n";
	}
	else
	{
		cout << "Imposible\n";
	}
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
	
}