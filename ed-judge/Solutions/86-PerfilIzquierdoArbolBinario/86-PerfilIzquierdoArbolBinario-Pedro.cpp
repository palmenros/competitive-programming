//
// Created by pedro on 1/4/20.
//

#include "bintree_eda.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//El coste es lineal respecto al numero de elementos del arbol porque es un recorrido en anchura
template <class T>
vector<T> perfil_izquierdo(const bintree<T>& root)
{
	vector<T> v;
	if(root.empty()) { return v; }

	//[arbol, profundidad]
	queue<pair<bintree<T>, int>> q;
	q.push(make_pair(root, 1));

	int lastDepth = 0;

	while(!q.empty()) {
		const auto& [bt, profundidad] = q.front();

		if(profundidad != lastDepth) {
			v.push_back(bt.root());
		}

		lastDepth = profundidad;

		if(!bt.left().empty()) {
			q.push(make_pair(bt.left(), profundidad + 1));
		}

		if(!bt.right().empty()) {
			q.push(make_pair(bt.right(), profundidad + 1));
		}

		q.pop();
	}
	return v;
}

int main()
{
	int N;
	cin >> N;
	while(N--)
	{
		auto bt = leerArbol<int>(-1);

		bool first = true;
		for(auto e : perfil_izquierdo(bt)) {
			if(first) {
				first = false;
			} else {
				cout << " ";
			}
			cout << e;
		}

		cout << endl;
	}
}
