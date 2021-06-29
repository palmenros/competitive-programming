#include <iostream>
#include <functional>
#include <queue>
#include <vector>
using namespace std;

using lli = long long int;

struct datosPaciente
{
	lli gravedad; lli tiempoEntrada; string id;
	datosPaciente(lli gravedad, lli tiempoEntrada, string id) : gravedad(gravedad), tiempoEntrada(tiempoEntrada), id(id) {}
};

bool operator<(datosPaciente t1, datosPaciente t2)
{
	return t1.gravedad < t2.gravedad || (t1.gravedad == t2.gravedad && t1.tiempoEntrada > t2.tiempoEntrada);
}

bool resuelveCaso()
{
	//Se resuelve con una cola de prioridad, coste n log n con n número de eventos
	//Se van insertando cuando llegan y se atienden cuando llega el correspondiente evento
	lli n;
	cin >> n;
	if (!n) { return false; }
	priority_queue<datosPaciente> prQueue;
	for (int i = 0; i < n; i++)
	{
		string aux; string id; lli gravedad;
		cin >> aux;
		if (aux == "I")
		{
			cin >> id >> gravedad;
			prQueue.push({ gravedad,i,id });
		}
		else
		{
			auto elem = prQueue.top();
			prQueue.pop();
			cout << elem.id << "\n";
		}
	}
	
	cout << "---\n";
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}