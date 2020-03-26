//
// Created by pedro on 26/3/20.
//

#include "bintree_eda.h"
#include <iostream>
#include <queue>

using namespace std;

enum Result {
	Completo,
	Semicompleto,
	Nada
};

template <class T>
Result es_completo(const bintree<T>& bt) {
	if(bt.empty()) {
		return Completo;
	}

	queue<pair<int, bintree<T>>> q;
	q.push(make_pair(1, bt));

	int alturaAnterior = 0;
	Result result = Completo;
	bool res = true;
	bool algunHueco = false;

	while(res && !q.empty()) {

		auto p = q.front();
		q.pop();

		int alturaActual = p.first;
		auto arbol = p.second;

		if(arbol.empty()) {
			if(!algunHueco) {
				algunHueco = true;
				if(alturaAnterior == alturaActual) {
					result = Semicompleto;
				} else {
					result = Completo;
				}
			}
		} else {
			if(algunHueco) {
				res = false;
			} else {
				q.push(make_pair(alturaActual + 1, arbol.left()));
				q.push(make_pair(alturaActual + 1, arbol.right()));
			}
		}

		alturaAnterior = alturaActual;
	}

	if(!res) {
		return Nada;
	}

	return result;
}

int main()
{
	int N;
	cin >> N;
	while(N--) {
		auto bt = leerArbol<char>('.');
		string str;

		switch(es_completo(bt)) {
		case Completo:
			str = "COMPLETO";
			break;
		case Semicompleto:
			str = "SEMICOMPLETO";
			break;
		case Nada:
			str = "NADA";
			break;
		}

		cout << str << endl;
	}

	return 0;
}