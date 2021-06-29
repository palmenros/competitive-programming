#include <iostream>
#include <functional>
#include <queue>
#include <vector>
using namespace std;

using lli = long long int;

struct datosCaja
{
	lli numero; lli tiempo;
	datosCaja(lli numero, lli tiempo) : numero(numero), tiempo(tiempo) {}
};

bool operator<(datosCaja t1, datosCaja t2)
{
	return t1.tiempo > t2.tiempo || (t1.tiempo == t2.tiempo && t1.numero > t2.numero);
}

bool resuelveCaso()
{
	//Se resuelve con una cola de prioridad y una cola, coste en clientes log cajas
	//Los clientes forman una cola normal. El sistema de cajas es una cola de prioridad que van estando disponibles
	//segun los requisitos dados
	lli n;
	cin >> n;
	if (!n) { return false; }
	lli c;
	cin >> c;
	priority_queue<datosCaja> prQueue;
	for (int i = 1; i <= n; i++)
	{
		prQueue.push({ i,0 });
	}
	queue<int> colaClientes;
	for (int i = 0; i < c; i++)
	{
		int aux;
		cin >> aux;
		colaClientes.push(aux);
	}
	while (!colaClientes.empty())
	{
		auto val = prQueue.top();
		prQueue.pop();
		val.tiempo += colaClientes.front();
		colaClientes.pop();
		prQueue.push(val);
	}
	cout << prQueue.top().numero << '\n';
	
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}