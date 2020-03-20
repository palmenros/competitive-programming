//
// Created by pedro on 20/3/20.
//

#include "../bintree_eda.h"
#include <iostream>

using namespace std;

struct Result {
	int caudal;
	int tramosNavegables;

	Result(int caudal, int tramosNavegables)
		: caudal(caudal), tramosNavegables(tramosNavegables)
	{}

};

//El coste es lineal porque solo accedemos una vez a cada nodo
Result caudal(const bintree<int>& bt)
{
	if(bt.empty()) {
		return {0, 0};
	}

	auto izq = bt.left();
	auto dch = bt.right();
	if(izq.empty() && dch.empty()) {
		return {1, 0};
	}

	Result resizq = caudal(izq), resdch = caudal(dch);
	int caudal = max(resizq.caudal + resdch.caudal - bt.root(), 0);
	int navegables = resizq.tramosNavegables + resdch.tramosNavegables;

	if(caudal >= 3) {
		navegables++;
	}

	return {caudal, navegables};
}

int navegables(const bintree<int>& bt) {
	Result res = caudal(bt);
	if(res.caudal >= 3) {
		//No tenemos que contar el primer nodo como tramo navegable
		res.tramosNavegables--;
	}

	return res.tramosNavegables;
}

int main()
{
	int N;
	cin >> N;
	while(N--) {
		auto bt = leerArbol<int>(-1);
		cout << navegables(bt) << endl;
	}

	return 0;
}