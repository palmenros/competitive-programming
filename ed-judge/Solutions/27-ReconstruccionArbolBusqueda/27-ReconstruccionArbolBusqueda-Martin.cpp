#include <iostream>
#include <vector>
#include <climits>
#include "bintree_eda.h"
using namespace std;

template <class T>
void capturar(vector<T>& v)
{
	T aux;
	cin >> aux;
	if (!cin) { return; }
	v.push_back(aux);
	char sep = cin.get();
	while (sep == ' ' && cin)
	{
		cin >> aux;
		v.push_back(aux);
		sep = cin.get();

	}
}
template <class T>
void imprimir(vector<T>& v)
{
	bool first = true;
	for (T t : v)
	{
		cout << (first ? "" : " ") << t;
		first = false;
	}
	cout << "\n";
}
//No está hecha con template porque C++ no sabe deducir tipos
//Esta función construye un árbol de búsqueda dado el preorden asumiendo que los datos empiezan en beginToEnd
//y terminan en end o cuando los datos empiezan a tener valores por encima de cotaSup
//beginToEnd se pasa por referencia, saliendo de la función en el valor posterior al último dato
//end no cambia nunca así que se pasa por referencia constante
//Lineal en el número de nodos ya que se hacen como mucho tres recursiones por nodo y cada recursión tiene coste constante
bintree<int> construirDeBusqueda(int cotaSup, vector<int>::iterator& beginToEnd, const vector<int>::iterator& end)
{
	//Caso trivial: árbol vacío
	if (beginToEnd == end || *beginToEnd >= cotaSup)
	{
		return {};
	}
	//Ahora el árbol no es trivial. Obtenemos la raíz y construimos por recursión los dos subárboles
	int raiz = *beginToEnd;
	//Avanzamos
	++beginToEnd;
	//Construimos el árbol izquierdo
	auto izq = construirDeBusqueda(raiz, beginToEnd, end);
	//Construimos el árbol derecho
	auto der = construirDeBusqueda(cotaSup, beginToEnd, end);
	return { izq,raiz,der };


}

int main()
{
	while (true)
	{
		vector<int> v;
		capturar(v);
		if (!v.size())
		{
			return 0;
		}
		auto b = v.begin();
		auto e = v.end();
		bintree<int> arbol = construirDeBusqueda(INT_MAX, b, e);
		auto a = arbol.postorder();
		imprimir(a);
	}
}