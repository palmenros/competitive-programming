//
// Created by pedro on 17/3/20.
//

#include <algorithm>
#include "../bintree_eda.h"

using namespace std;

struct Datos {
	int numNodos;
	int numHojas;
	int altura;

	Datos(int numNodos, int numHojas, int altura)
		: numNodos(numNodos), numHojas(numHojas), altura(altura)
	{}
};

template<class T>
Datos resolver(bintree<T> bintree)
{
	if(bintree.empty()) {
		return Datos(0, 0, 0);
	}

	bool esHoja = bintree.left().empty() && bintree.right().empty();
	if(esHoja) {
		return Datos(1, 1, 1);
	}

	int sumNodos = 0, sumHojas = 0, maxAltura = 0;

	Datos di = resolver(bintree.left());
	sumNodos += di.numNodos;
	sumHojas += di.numHojas;
	maxAltura = max(maxAltura, di.altura);

	Datos dd = resolver(bintree.right());
	sumNodos += dd.numNodos;
	sumHojas += dd.numHojas;
	maxAltura = max(maxAltura, dd.altura);

	Datos res(sumNodos + 1, sumHojas, maxAltura + 1);
	return res;
}

template<class T>
bintree<T> leer_arbol()
{
	char c;
	cin >> c;

	if(c == '.') {
		//Arbol vacio
		return bintree<T>();
	} else {
		auto izquierda = leer_arbol<T>();
		auto derecha = leer_arbol<T>();
		return bintree<T>(izquierda, T{}, derecha);
	}
}


int main()
{
	int N;
	cin >> N;

	while(N--) {

		bintree<char> bt = leer_arbol<char>();
		Datos d = resolver(bt);
		cout << d.numNodos << " " << d.numHojas << " " << d.altura << endl;
	}

	return 0;
}
