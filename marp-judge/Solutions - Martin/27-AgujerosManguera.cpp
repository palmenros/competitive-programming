#include <iostream>
#include <list>
#include <limits>
#include <climits>
using namespace std;

//Algoritmo voraz
//El algoritmo que utilizamos pone parches desde el principio lo más a la derecha posible
//Red. dif.
/*
* 
* Supongamos que tenemos una sol. óptima.
* Todos los parches desde la izquierda están puestos igual salvo desde cierto índice.
* Movemos ese índice lo más a la derecha posible. Lo podremos mover hasta dejar de cubrir el primer
* agujero que no cubren los anteriores, es decir como se eligió en voraz.
* Repitiendo este proceso transformamos una solución en otra conservando la optimalidad
* Coste trivialmente lineal en el número de agujeros
* Desde luego la primera discrepancia nos la encontramos con la óptima antes, si es después no es factible
* 
* 
*/

bool resuelveCaso()
{
	int n, width; cin >> n >> width; if (!cin) { return false; }
	list<long long int> lista;
	for (int i = 0; i < n; i++)
	{
		long long int aux;
		cin >> aux;
		lista.push_back(aux);
	}
	auto it = lista.begin();
	long long int tope = LLONG_MIN;
	int numTotal = 0;
	while (it != lista.end())
	{
		if (tope < (*it))
		{
			numTotal++;
			tope = (*it) + width;
		}
		++it;
	}
	cout << numTotal << "\n";
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}