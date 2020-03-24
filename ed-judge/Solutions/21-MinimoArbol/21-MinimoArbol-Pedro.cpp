//
// Created by pedro on 17/3/20.
//

#include <iostream>
#include "../bintree_eda.h"

using namespace std;

template <class T>
T min_tree(const bintree<T>& bt) {
	T min = bt.root();

	if(!bt.left().empty()) {
		min = std::min(min, min_tree(bt.left()));
	}

	if(!bt.right().empty()) {
		min = std::min(min, min_tree(bt.right()));
	}

	return min;
}

template <class T>
void resolver(T vacio) {
	bintree<T> bt = leerArbol(vacio);
	if(bt.empty()) {
		cout << endl;
	} else {
		cout << min_tree(bt) << endl;
	}
}

int main()
{
	char c;
	while(cin >> c) {

		if(c == 'N') {
			resolver<int>(-1);
		} else {
			resolver<string>("#");
		}

	}

	return 0;
}