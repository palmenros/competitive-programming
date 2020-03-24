//
// Created by pedro on 17/3/20.
//

#include <iostream>
#include <algorithm>
#include "../bintree_eda.h"

using namespace std;

struct Result {
	int altura;
	int diametro;

	Result()
	{}

	Result(int altura, int diametro)
		: altura(altura), diametro(diametro)
	{}
};

template<class T>
Result diametro_arbol(const bintree<T>& bt)
{
	if(bt.empty()) {
		return Result(0, 0);
	}

	Result res, izq = diametro_arbol(bt.left()), dch = diametro_arbol(bt.right());

	res.altura = 1 + max(izq.altura, dch.altura);
	res.diametro = max({izq.diametro, dch.diametro, izq.altura + dch.altura + 1});

	return res;
}

int main() {
	int N;
	cin >> N;
	while(N--) {
		Result res = diametro_arbol(leerArbol<char>('.'));
		cout << res.diametro << endl;
	}

}