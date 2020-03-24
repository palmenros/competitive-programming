//
// Created by pedro on 20/3/20.
//

#include "../bintree_eda.h"
#include <iostream>

using namespace std;

struct Result {
	bool res;
	int altura;

	Result(bool res, int altura)
		: res(res), altura(altura)
	{}

	Result(bool res)
		: res(res)
	{}
};

//El tiempo es lineal porque solo accede una vez a cada nodo
Result arbol_genealogico(const bintree<int>& bt)
{
	if(bt.empty()) {
		return {true, 0};
	}

	auto izq = bt.left();
	auto dch = bt.right();

	auto val = bt.root();

	Result resizq = arbol_genealogico(izq), resdch = arbol_genealogico(dch);
	bool res = resizq.res && resdch.res;
	int altura = max(resizq.altura, resdch.altura) + 1;

	//edadPadre - edadHijo >= 18
	if(!izq.empty()) {
		auto lval = izq.root();
		res = res && val - lval >= 18;
	}

	if(!dch.empty()) {
		if(izq.empty()) { return {false}; }

		auto rval = dch.root();
		res = res && val - rval >= 18;
		auto lval = izq.root();
		res = res && lval - rval >= 2;
	}

	return {res, altura};
}

int main()
{
	int N;
	cin >> N;
	while(N--) {
		auto bt = leerArbol<int>(-1);
		Result res = arbol_genealogico(bt);
		if(res.res) {
			cout << "SI " << res.altura << endl;
		} else {
			cout << "NO" << endl;
		}
	}

}