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
	//Lineal en el n�mero de nodos, porque hay como mucho tres llamadas recursivas por nodos y cada llamada es de tiempo constante
	//La funci�n construye un �rbol sabiendo que sus descripciones de preorden e inorden empiezan en beginPre y beginIn,
	//terminan antes de endPre y endIn y el �rbol no contiene un nodo con valor detenerEn
	//Se asume que el �rbol est� bien hecho, y termina en los iteradores del final o cuando aparezca detenerEn en beginIn
	//Los iteradores beginPre y beginIn se desplazar�n al final de las definiciones del �rbol, por inducci�n
	//Primero comprobamos que el �rbol no es vac�o
	if (beginPre == endPre || beginIn == endIn || *beginIn == detenerEn)
	{
		return {};
	}
	//Si no es vac�o, *beginPre tiene el valor de la ra�z
	int raiz = *beginPre;
	//El �rbol izquierdo viene descrito a continuaci�n, desde beginPre + 1 y desde beginIn, por la definici�n de cada orden
	//Sin embargo, cuando aparezca la ra�z en el inorden hay que dejar de construir
	++beginPre;
	bintree<int> hijoIzquierdo = construir(beginPre, endPre, beginIn, endIn, raiz);
	//Ahora aparece la ra�z en el inorden. La saltamos
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