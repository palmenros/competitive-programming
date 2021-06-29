#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <climits>
using namespace std;

using lli = long long int;

struct datosTarea
{
	lli inicio; lli fin; lli periodo;
	datosTarea(lli inicio, lli fin, lli periodo) : inicio(inicio), fin(fin), periodo(periodo) { ; }
};

bool operator<(datosTarea t1, datosTarea t2)
{
	return t1.inicio > t2.inicio;
}

bool resuelveCaso()
{
	//Se resuelve con una cola de prioridad en la que guardamos las tareas que aún no se han ejecutado
	//Coste O(n+m log(n+m))
	lli n,m,t;
	cin >> n >> m >> t;
	if (!cin) { return false; }
	//Tomar datos
	priority_queue<datosTarea> prQueue;
	for (int i = 0; i < n; i++)
	{
		lli aux1, aux2;
		cin >> aux1 >> aux2;
		prQueue.push({ aux1,aux2,-1 });
	}
	for (int i = 0; i < m; i++)
	{
		lli aux1, aux2, aux3;
		cin >> aux1 >> aux2 >> aux3;
		prQueue.push({ aux1,aux2,aux3 });
	}
	lli tiempoFinalizacionUltima = INT_MIN;
	//Si no hay colisiones hay un orden lineal en el que los extremos no interfieren entre sí
	//Si una tarea es periódica la volvemos a añadir a la cola para después
	while (!prQueue.empty() && prQueue.top().inicio < t)
	{
		if (prQueue.top().inicio < tiempoFinalizacionUltima) //Si hay colisión
		{
			cout << "SI\n"; return true;
		}
		auto tAct = prQueue.top();
		prQueue.pop();
		tiempoFinalizacionUltima = tAct.fin;
		if (tAct.periodo >= 0)
		{
			tAct.inicio += tAct.periodo;
			tAct.fin += tAct.periodo;
			prQueue.push(tAct);
		}
	}
	cout << "NO\n";
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}