#include <iostream>
#include <stack>
#include <algorithm>
#include "bintree_eda.h"
using namespace std;



void capturar(vector<int>& v)
{
	int aux;
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

bintree<int> construir(vector<int>::iterator& beginPre, const vector<int>::iterator& endPre, vector<int>::iterator& beginIn, const vector<int>::iterator& endIn, const int& detenerEn)
{
	//Lineal en el número de nodos, porque hay como mucho tres llamadas recursivas por nodos y cada llamada es de tiempo constante
	//La función construye un árbol sabiendo que sus descripciones de preorden e inorden empiezan en beginPre y beginIn,
	//terminan antes de endPre y endIn y el árbol no contiene un nodo con valor detenerEn
	//Se asume que el árbol está bien hecho, y termina en los iteradores del final o cuando aparezca detenerEn en beginIn
	//Los iteradores beginPre y beginIn se desplazarán al final de las definiciones del árbol, por inducción
	//Primero comprobamos que el árbol no es vacío
	if (beginPre == endPre || beginIn == endIn || *beginIn == detenerEn)
	{
		return {};
	}
	//Si no es vacío, *beginPre tiene el valor de la raíz
	int raiz = *beginPre;
	//El árbol izquierdo viene descrito a continuación, desde beginPre + 1 y desde beginIn, por la definición de cada orden
	//Sin embargo, cuando aparezca la raíz en el inorden hay que dejar de construir
	++beginPre;
	bintree<int> hijoIzquierdo = construir(beginPre, endPre, beginIn, endIn, raiz);
	//Ahora aparece la raíz en el inorden. La saltamos
	++beginIn;
	//Y construimos el hijo derecho
	bintree<int> hijoDerecho = construir(beginPre, endPre, beginIn, endIn, detenerEn);
	return { hijoIzquierdo,raiz,hijoDerecho };
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

int main()
{
	while (true)
	{
		vector<int> preorden, inorden;
		capturar(preorden); capturar(inorden);
		if (!preorden.size()) { return 0; }
		auto b = preorden.begin();
		auto e = inorden.begin();
		bintree<int> arbol = construir(b, preorden.end(), e, inorden.end(), 0);
		auto a = arbol.postorder();
		imprimir(a);
	}
}