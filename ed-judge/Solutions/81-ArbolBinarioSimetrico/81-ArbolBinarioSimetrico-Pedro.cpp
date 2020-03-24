//
// Created by pedro on 20/3/20.
//

#include "../bintree_eda.h"
#include <iostream>

using namespace std;

template <class T>
bool misma_estructura(const bintree<T>& a, const bintree<T>& b)
{
	if(a.empty() || b.empty()) {
		return a.empty() == b.empty();
	}

	return misma_estructura(a.left(), b.right()) && misma_estructura(a.right(), b.left());
}

template <class T>
bool simetrico(const bintree<T>& bt)
{
	if(bt.empty()) {
		return true;
	}

	return misma_estructura(bt.left(), bt.right());
}

int main()
{
	int N;
	cin >> N;
	while(N--) {
		auto bt = leerArbol<char>('.');
		if(simetrico(bt)) {
			cout << "SI" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
}