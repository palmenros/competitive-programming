#include <iostream>
#include "bintree_eda.h"
using namespace std;

struct Datos
{
	int caudal;
	int tramosNavegables;
	Datos (int a, int b):caudal(a),tramosNavegables(b){}
};

Datos calcularDatos(bintree<int> arbol)
{
	//Lineal en el número de nodos n; se hacen n llamadas recursivas y cada ejecución del cuerpo (no de las llamadas
	//recursivas) de calcularDatos tiene coste constante
	//Este caso sirve para no hacer distinciones en los embalses
	if (arbol.empty())
	{
		return { 0,0 };
	}
	//Caso trivial; manantial
	if (arbol.left().empty() && arbol.right().empty()) //Asumimos que no hay embalses en los manantiales
	{
		return { 1,0 };
	}
	//Gracias al caso del árbol vacío, este código se comporta bien tanto en embalses como en confluencias
	//Y serviría también para tratar una confluencia en la que hubiera un embalse (problema más general)
	Datos izq = calcularDatos(arbol.left());
	Datos der = calcularDatos(arbol.right());
	//En cualquier caso, el caudal saliente es la suma de los de cada rama menos lo que haya en la raíz (si es mayor,0)
	//Y el número de tramos navegables es la suma, pero añadimos si se dan las condiciones adecuadas
	return { max(0,izq.caudal + der.caudal - arbol.root()),
		izq.tramosNavegables + der.tramosNavegables +
		(izq.caudal >= 3 ? 1 : 0) +
		(der.caudal >= 3 ? 1 : 0)
	};

}

void resuelveCaso()
{
	bintree<int> arbol = leerArbol(-1);
	cout << calcularDatos(arbol).tramosNavegables << endl;
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