//
// Created by pedro on 10/11/20.
//

#include "../bintree_eda.h"
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

struct Res {
	bool res;
	int altura;
	int min;
	int max;
};

Res esAVL_g(const bintree<int>& arbol) {
	if(arbol.empty()) {
		return {true, 0, INT_MAX, INT_MIN};
	}

	auto izq = esAVL_g(arbol.left());
	auto dch = esAVL_g(arbol.right());

	auto& r = arbol.root();

	return
	{
		izq.res && dch.res && abs(izq.altura - dch.altura) <= 1 && r > izq.max && r < dch.min,
		max(izq.altura, dch.altura) + 1,
		min({izq.min, dch.min, r}),
		max({izq.max, dch.max, r})
	};
}

bool esAVL(const bintree<int>& arbol) {
	return esAVL_g(arbol).res;
}

int main()
{
	int N;
	cin >> N;
	while(N--) {
		bintree<int> arbol = leerArbol(-1);
		if(esAVL(arbol)) {
			cout << "SI" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
}