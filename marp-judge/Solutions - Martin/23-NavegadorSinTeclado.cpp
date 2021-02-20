#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;
//Se resuelve con recorrido típico con cola de prioridad
//Dando prioridad a los nodos con coste acumulado más bajo
//Es un algoritmo voraz del cual extraemos una parte muy concreta de la solución
//Coste en O(v + e log e), que es el coste del recorrido con prioridad
struct datosEnlace
{
	int destino;
	int coste;
	datosEnlace(int destino, int coste) :destino(destino), coste(coste) { ; }
};

struct nodoActual
{
	int vertice;
	int costeAcumulado;
	nodoActual(int vertice, int costeAcumulado) :vertice(vertice), costeAcumulado(costeAcumulado) { ; }
};

bool operator<(const nodoActual& t1, const nodoActual& t2)
{
	return t2.costeAcumulado < t1.costeAcumulado;
}

bool resuelveCaso()
{
	int n;
	cin >> n;
	if (!n) { return false; }
	vector<bool> marcados = vector<bool>(n, false);
	vector<int> pesosNodos;
	vector<vector<datosEnlace>> enlaces = vector<vector<datosEnlace>>(n);
	priority_queue<nodoActual> colaPFS;
	for (int i = 0; i < n; i++)
	{
		int aux; cin >> aux; pesosNodos.push_back(aux);
	}
	int e; cin >> e; for (int i = 0; i < e; i++)
	{
		int aux1, aux2, aux3;
		cin >> aux1 >> aux2 >> aux3;
		aux1--; aux2--; //Usamos números 0 a n-1
		enlaces[aux1].push_back({ aux2,aux3 });
	}
	colaPFS.push({ 0,0 });
	while (!colaPFS.empty())
	{
		auto val = colaPFS.top(); colaPFS.pop();
		if (!marcados[val.vertice])
		{
			marcados[val.vertice] = true;
			//Si hemos llegado al deseado
			if (val.vertice == n - 1)
			{
				cout << val.costeAcumulado + pesosNodos[n - 1] << "\n";
				return true;
			}
			//Procesamos el vértice, cargando en la cola de prioridad los vértices conectados
			for (auto dest : enlaces[val.vertice])
			{
				colaPFS.push({ dest.destino,val.costeAcumulado + pesosNodos[val.vertice] + dest.coste });
			}
		}
	}
	//No hemos llegado al final
	cout << "IMPOSIBLE\n";
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}