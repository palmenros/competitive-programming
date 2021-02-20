#include <iostream>
#include <functional>
#include <queue>
#include <vector>
using namespace std;

using lli = long long int;

struct datosNotif
{
	lli tiempo; lli id; lli periodo;
	datosNotif(lli tiempo, lli id, lli periodo) : tiempo(tiempo), id(id), periodo(periodo) {}
};

bool operator>(datosNotif t1, datosNotif t2)
{
	return t1.tiempo > t2.tiempo || (t1.tiempo == t2.tiempo && t1.id > t2.id);
}

bool resuelveCaso()
{
	//Se resuelve con una cola de prioridad, coste k log usuarios
	//En la cola guardamos las próximas notificaciones
	//Añadimos la siguiente notificación del mismo usuario justo cuando lo hemos avisado
	//El algoritmo es correcto porque las notificaciones salen en orden y siempre se mete la siguiente notificación
	//antes de que tenga que salir
	long long int n;
	cin >> n;
	if (!n) { return false; }
	priority_queue<datosNotif, vector<datosNotif>, greater<datosNotif>> prQueue;
	while (n--)
	{
		long long int tiempo, id;
		cin >> id >> tiempo;
		prQueue.push({ tiempo,id,tiempo });
	}
	int k;
	cin >> k;
	while (k--)
	{
		auto t = prQueue.top();
		prQueue.pop();
		cout << t.id << "\n";
		t.tiempo += t.periodo;
		prQueue.push(t);
	}
	cout << "---\n";
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}