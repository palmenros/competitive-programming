//
// Created by pedro on 20/3/20.
//

#include "../bintree_eda.h"
#include <iostream>
#include <algorithm>

using namespace std;

struct Result {
	bool res;
	int max;
	int min;

	Result(bool res)
		: res(res)
	{}

	Result(int max, int min)
		: res(true), max(max), min(min)
	{}

	Result(bool res, int max, int min)
		: res(res), max(max), min(min)
	{}
};

//El coste es lineal porque accedemos a cada nodo una sola vez
template <class T>
Result arbol_busqueda(const bintree<T>& bt)
{
	if(bt.empty()) {
		return Result(true);
	}

	auto val = bt.root();

	//Es hoja
	if(bt.left().empty() && bt.right().empty()) {
		return Result(val, val);
	}

	auto izq = bt.left();
	auto dch = bt.right();

	bool resultado = true;
	int maximo = val, minimo = val;

	if(!izq.empty()) {
		Result resizq = arbol_busqueda(izq);
		resultado = resultado && resizq.res && resizq.max < val;
		maximo = max(maximo, resizq.max);
		minimo = min(minimo, resizq.min);
	}

	if(resultado && !dch.empty()) {
		Result resdch = arbol_busqueda(dch);
		resultado = resultado && resdch.res && resdch.min > val;
		maximo = max(maximo, resdch.max);
		minimo = min(minimo, resdch.min);
	}

	return Result(resultado, maximo, minimo);
}

int main()
{
	int N;
	cin >> N;
	while(N--) {
		auto bt = leerArbol<int>(-1);
		if(arbol_busqueda(bt).res) {
			cout << "SI" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
}