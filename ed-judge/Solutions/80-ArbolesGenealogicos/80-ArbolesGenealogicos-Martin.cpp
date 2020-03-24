#include <iostream>
#include "bintree_eda.h"
#include <climits>
using namespace std;

struct Datos
{
	int correcto;
	int gen;
	int edadRaiz;
	Datos(bool a, int b, int c) :correcto(a), gen(b), edadRaiz(c) {  }
};

Datos obtenerDatosGenealogicos(bintree<int> arbol)
{
	//Lineal en el número de nodos n; n llamadas recursivas, instrucciones propias de cada llamada constantes
	//Caso base
	if (arbol.empty())
	{
		return {true,0,INT_MIN/4};
	}
	//Recursión: ahora tenemos un árbol con dos hijos y sus datos
	Datos izq = obtenerDatosGenealogicos(arbol.left());
	Datos der = obtenerDatosGenealogicos(arbol.right());
	return
	{
		//Está bien construido si y solo si se dan las condiciones del enunciado
		izq.correcto && der.correcto &&
		arbol.root() - izq.edadRaiz >= 18 && arbol.root() - izq.edadRaiz >= 18 &&
		(der.edadRaiz == INT_MIN / 4 || izq.edadRaiz - der.edadRaiz >= 2),
		//Realmente lo que nos piden es el máximo de las dos alturas + 1, para obtener el número de niveles (llenos o no)
		max(izq.gen,der.gen) + 1,
		//Trivial
		arbol.root()
	};


}

void resuelveCaso()
{
	bintree<int> arbol = leerArbol(-1);
	Datos datos = obtenerDatosGenealogicos(arbol);
	cout << (datos.correcto ? "SI " : "NO");
	if (datos.correcto)
	{
		cout << datos.gen;
	}
	cout << endl;
}

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		resuelveCaso();
	}
}