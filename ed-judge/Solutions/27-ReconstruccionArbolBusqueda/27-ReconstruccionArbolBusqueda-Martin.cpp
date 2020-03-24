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
//No est� hecha con template porque C++ no sabe deducir tipos
//Esta funci�n construye un �rbol de b�squeda dado el preorden asumiendo que los datos empiezan en beginToEnd
//y terminan en end o cuando los datos empiezan a tener valores por encima de cotaSup
//beginToEnd se pasa por referencia, saliendo de la funci�n en el valor posterior al �ltimo dato
//end no cambia nunca as� que se pasa por referencia constante
//Lineal en el n�mero de nodos ya que se hacen como mucho tres recursiones por nodo y cada recursi�n tiene coste constante
bintree<int> construirDeBusqueda(int cotaSup, vector<int>::iterator& beginToEnd, const vector<int>::iterator& end)
{
	//Caso trivial: �rbol vac�o
	if (beginToEnd == end || *beginToEnd >= cotaSup)
	{
		return {};
	}
	//Ahora el �rbol no es trivial. Obtenemos la ra�z y construimos por recursi�n los dos sub�rboles
	int raiz = *beginToEnd;
	//Avanzamos
	++beginToEnd;
	//Construimos el �rbol izquierdo
	auto izq = construirDeBusqueda(raiz, beginToEnd, end);
	//Construimos el �rbol derecho
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