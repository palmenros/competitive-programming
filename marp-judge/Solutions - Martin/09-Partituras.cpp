#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <climits>
#include <deque>
#include <algorithm>
using namespace std;

using lli = long long int;
struct instrumento
{
	lli nIntegrantes;
	lli nAtriles;
	lli cocienteHondt() const
	{
		return ((nIntegrantes - 1) / nAtriles) + 1;
	}
	instrumento(lli nIntegrantes, lli nAtriles) :nIntegrantes(nIntegrantes), nAtriles(nAtriles) { ; }
};
bool operator<(instrumento t1, instrumento t2)
{
	return (t1.cocienteHondt() < t2.cocienteHondt());
}

bool resuelveCaso()
{
	//Lo resolvemos con una cola de prioridad. Es aplicar el método de d'Hondt, tomando como escaños las copias
	//que se pueden comprar pero no son necesarias.
	//La prioridad viene dada por el cociente del método de d'Hondt. Hay que coger los cocientes mayores.

	lli p, n;
	cin >> p >> n;
	if (!cin) { return false; }
	//Tomar datos
	lli nCiclos = p - n;
	priority_queue<instrumento> prQueue;
	for (lli i = 0; i < n; i++)
	{
		lli aux;
		cin >> aux;
		prQueue.push({ aux,1 });
	}
	while (nCiclos--)
	{
		auto elem = prQueue.top();
		prQueue.pop();
		elem.nAtriles++;
		prQueue.push(elem);
	}
	lli maxPersonas = 0;
	while (!prQueue.empty())
	{
		maxPersonas = max(maxPersonas, (prQueue.top()).cocienteHondt());
		prQueue.pop();
	}
	cout << maxPersonas << "\n";
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}