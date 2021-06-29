#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//Algoritmo voraz
//El algoritmo que utilizamos manda tropas por orden descendente a las ciudades con m�s tropas factibles
//Red. dif.
/*
*
* Supongamos que tenemos una sol. �ptima.
* La transformamos de forma que tropas m�s grandes ataquen ciudades con tropas m�s grandes (esto siempre es posible
* intercambiando parejas donde est�n invertidos y se conserva factibilidad)
* La transformamos tambi�n de forma que las tropas m�s grandes est�n lo m�s ocupadas posible y ataquen las ciudades m�s invadidas
* que puedan.
* Si la soluci�n transformada no fuera la voraz, a partir de cierta tropa (descendentemente) las asignaciones ser�an distintas.
* Si esa tropa no ataca ninguna ciudad o ataca una con menos tropas en la soluci�n original modificada, entonces
* la podemos transformar para que lo haga, contradicci�n.
* Si esa tropa ataca en la soluci�n �ptima transformada pero no en la voraz, llegamos a una contradicci�n porque entonces
* la podr�amos haber elegido en la voraz y no ha sido as�.
* As� que despu�s de transformar las dos soluciones son iguales, sin perder la optimalidad.
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