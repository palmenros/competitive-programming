#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//Algoritmo voraz
//El algoritmo que utilizamos manda tropas por orden descendente a las ciudades con más tropas factibles
//Red. dif.
/*
*
* Supongamos que tenemos una sol. óptima.
* La transformamos de forma que tropas más grandes ataquen ciudades con tropas más grandes (esto siempre es posible
* intercambiando parejas donde estén invertidos y se conserva factibilidad)
* La transformamos también de forma que las tropas más grandes estén lo más ocupadas posible y ataquen las ciudades más invadidas
* que puedan.
* Si la solución transformada no fuera la voraz, a partir de cierta tropa (descendentemente) las asignaciones serían distintas.
* Si esa tropa no ataca ninguna ciudad o ataca una con menos tropas en la solución original modificada, entonces
* la podemos transformar para que lo haga, contradicción.
* Si esa tropa ataca en la solución óptima transformada pero no en la voraz, llegamos a una contradicción porque entonces
* la podríamos haber elegido en la voraz y no ha sido así.
* Así que después de transformar las dos soluciones son iguales, sin perder la optimalidad.
*
* Lineal en n
*/

bool resuelveCaso()
{
	int n;
	cin >> n;
	if (!cin) { return false; }
	vector<int> enemigos;
	vector<int> defensas;
	enemigos.reserve(n);
	defensas.reserve(n);
	for (int i = 0; i < n; i++)
	{
		int aux; cin >> aux;
		enemigos.push_back(aux);
	}
	for (int i = 0; i < n; i++)
	{
		int aux; cin >> aux;
		defensas.push_back(aux);
	}
	sort(enemigos.rbegin(), enemigos.rend());
	sort(defensas.rbegin(), defensas.rend());
	auto itenemigos = enemigos.begin(); auto itdefensas = defensas.begin();
	int emparejamientos = 0;
	while (itdefensas != defensas.end())
	{
		while (itenemigos != enemigos.end() && (*itenemigos) > (*itdefensas))
		{
			itenemigos++;
		}
		if (itenemigos != enemigos.end())
		{
			itenemigos++; emparejamientos++;
		}
		itdefensas++;
	}
	cout << emparejamientos << "\n";

	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}