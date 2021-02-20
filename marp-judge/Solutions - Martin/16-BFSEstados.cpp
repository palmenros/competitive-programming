#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <climits>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <list>
using namespace std;

//Hacemos un recorrido en anchura en el grafo imaginario de los estados de la m�quina.
//El coste de cada pregunta est� en O(V+E) del correspondiente grafo, aunque tambi�n est� en
//O(3^N) donde N es la soluci�n
//Para valores arbitrariamente grandes (e incluso infinitos) de V+E el otro coste es el adecuado
//Utilizamos un vector de longitud V para marcar. Realmente su utilidad depende mucho de lo que nos pregunten. Pero
//con �l podemos evitar muchos c�lculos innecesarios.

bool resuelveCaso()
{
	int n1, n2;
	cin >> n1 >> n2;
	if (!cin) { return false; }
	queue<pair<int, int>> colaBFS;
	colaBFS.push({ n1,0 });
	vector<bool> marcado = vector<bool>(10000, false);
	while (true) //Ponemos true; la cola nunca estar� vac�a.
	{
		auto val = colaBFS.front(); colaBFS.pop();
		if (val.first == n2) { cout << val.second << "\n"; return true; }
		if (marcado[val.first] == false)
		{
			marcado[val.first] = true;
			colaBFS.push({ (val.first + 1) % 10000, val.second + 1 });
			colaBFS.push({ (val.first * 2) % 10000, val.second + 1 });
			colaBFS.push({ (val.first / 3) % 10000, val.second + 1 });
		}
	}
}

int main()
{
	while (resuelveCaso());
	return 0;
}