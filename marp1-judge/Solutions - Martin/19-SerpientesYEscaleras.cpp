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

//Se resuelve haciendo un recorrido en anchura. Utilizando marcados adecuados, el coste est� en O(V+E) = O(V) ya que E<=V.

bool resuelveCaso()
{
	//Vamos a representar la informaci�n de una manera directa y sin utilizar las estructuras de grafo,
	//ya que es un tipo de grafo muy especial.
	int n, caras, i1, i2;
	cin >> n >> caras >> i1 >> i2;
	if (!n) { return false; }
	n = n * n; //Hacemos que n sea el tama�o real del tablero
	//Utilizamos �ndices desde 0
	//Hemos pasado ya por el v�rtice?
	vector<bool> marcaje = vector<bool>(n,false);
	//Si hay serpiente o escalera, este vector lo indica guardando el destino
	//N�tese que las serpientes y las escaleras son lo mismo, aunque unas sumen y otras resten
	vector<int> enlaces = vector<int>(n,-1);
	while (i1--)
	{
		int aux1, aux2; cin >> aux1 >> aux2; aux1--; aux2--; //Tomar datos
		//Actualizar
		enlaces[aux1] = aux2;
	}
	while (i2--)
	{
		int aux1, aux2; cin >> aux1 >> aux2; aux1--; aux2--; //Tomar datos
		//Actualizar
		enlaces[aux1] = aux2;
	}
	//Recorrido en anchura
	queue<pair<int,int>> colaBFS;
	colaBFS.push({ 0,0 }); //Empezamos en la casilla 1 en el turno 0. first casilla, second turno
	while (true) //Siempre hay soluci�n, por lo que la cola nunca est� vac�a
	{
		pair<int,int> val = colaBFS.front(); colaBFS.pop();
		if (val.first == n-1) { cout << val.second << "\n"; return true; }
		if (marcaje[val.first] == false)
		{
			marcaje[val.first] = true;
			for (int i = 1; i <= caras && val.first + i < n; i++)
			{
				int destino = val.first + i;
				//Despu�s de tirar el dado, pasamos por una sucesi�n de serpiescaleras hasta llegar a un destino sin serpiescaleras.
				//Vamos marcando el camino
				while (enlaces[destino] != -1)
				{
					marcaje[destino] = true;
					destino = enlaces[destino];
				}
				//Ya est�, ahora utilizamos la cola para guardar este destino y visitarlo despu�s
				colaBFS.push({ destino,val.second + 1 });
			}
		}
	}
}

int main()
{
	while (resuelveCaso());
	return 0;
}