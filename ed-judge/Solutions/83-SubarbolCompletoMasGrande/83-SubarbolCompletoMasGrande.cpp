//
// Created by pedro on 20/3/20.
//

#include "../bintree_eda.h"
#include <iostream>
#include <algorithm>

using namespace std;

struct Result {
	int maxCompleteSubtree;
	int maxCompleteSubtreeFromRoot;

	Result(int maxCompleteSubtree, int maxCompleteSubtreeFromRoot)
		: maxCompleteSubtree(maxCompleteSubtree), maxCompleteSubtreeFromRoot(maxCompleteSubtreeFromRoot)
	{}

	Result()
	{}
};

template <class T>
Result subarbol_completo(const bintree<T>& bt)
{
	if(bt.empty()) {
		return {0, 0};
	}

	auto izq = bt.left();
	auto dch = bt.right();

	Result res, resizq = subarbol_completo(izq), resdch = subarbol_completo(dch);
	//Es posible que el mayor subarbol completo este entre los dos
	res.maxCompleteSubtreeFromRoot = 1 + min(resizq.maxCompleteSubtreeFromRoot, resdch.maxCompleteSubtreeFromRoot);
	res.maxCompleteSubtree = max({resizq.maxCompleteSubtree, resdch.maxCompleteSubtree, res.maxCompleteSubtreeFromRoot});
	return res;
}

int main()
{
	int N;
	cin >> N;
	while(N--) {
		auto bt = leerArbol<char>('.');
		cout << subarbol_completo(bt).maxCompleteSubtree << endl;
	}
}