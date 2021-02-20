#include <iostream>
#include "ConjuntosDisjuntos.h"
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

//Se puede resolver con un algoritmo voraz, recorriendo en sentido ascendente la lista de aristas
//añadiendo aristas si aportan algo
//Funciona la voracidad porque cualquier solución óptima tendría las mismas aristas que la propuesta
//hasta cierto punto.
//En ese punto, lo propuesto tendría la arista, lo dado no.
//A lo dado le añadimos la arista de lo propuesto y retiramos la arista superflua más costosa
//Y queda una solución mejor (o igual)
//El algoritmo está en O(V+E log E)

struct dadosCandidata
{
	int origen;
	int destino;
	int coste;
	dadosCandidata(int origen, int destino, int coste) :origen(origen), destino(destino), coste(coste) { ; }
};

bool operator<(const dadosCandidata& t1, const dadosCandidata& t2)
{
	return t1.coste > t2.coste;
}


bool resuelveCaso()
{
	int n;
	cin >> n;
	if (!cin) { return false; }
	int e;
	cin >> e;
	//Guardamos las aristas en una cola con prioridad para ir sacándolas en orden
	priority_queue<dadosCandidata> datosAristas;
	while (e--)
	{
		int origen, destino, coste;
		cin >> origen >> destino >> coste;
		//Usamos índices empezando por 0
		origen--; destino--;
		datosAristas.push({ origen,destino,coste });

	}
	//Ahora empieza el algoritmo. Elegimos las aristas por orden si podemos.
	ConjuntosDisjuntos datosConexion(n);
	int costeAcumulado = 0; //Costes hasta el momento
	while (!datosAristas.empty() && datosConexion.num_cjtos()!=1)
	{
		dadosCandidata val = datosAristas.top(); datosAristas.pop();
		//Si la arista aporta algo, la cogemos
		if (datosConexion.buscar(val.origen) != datosConexion.buscar(val.destino))
		{
			costeAcumulado += val.coste;
			datosConexion.unir(val.origen, val.destino);
		}
	}
	//Si todo es conexo
	if (datosConexion.num_cjtos() == 1)
	{
		cout << costeAcumulado << "\n";
	}
	//Si no
	else
	{
		cout << "No hay puentes suficientes\n";
	}
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}


