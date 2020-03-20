//
// Created by pedro on 17/3/20.
//

#include "../bintree_eda.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>

using namespace std;

vector<int> stringToVector(const string& str)
{
	stringstream ss(str);

	vector<int> v;
	int i;
	while(ss >> i) {
		v.push_back(i);
	}

	return v;
}

//El coste es cuadrático por culpa del find, pero se podría añadir un mapa desordenado para convertirlo en
//coste constante a cambio espacio.
// [start, end]
bintree<int> recuperar_arbol(
	const vector<int>& preorden,
	int preorderStart,
	int preorderEnd,
	int inorderStart,
	int inorderEnd,
	const vector<int>& inorden
	)
{
	if(preorderStart > preorderEnd) {
		return bintree<int>();
	} else if (preorderStart == preorderEnd) {
		return bintree<int>(preorden[preorderStart]);
	}

	auto val = preorden[preorderStart];

	//preorderStart > preorderEnd

	int startLeft = preorderStart + 1, endLeft, startRight, endRight = preorderEnd;

	//calcular endLeft

	auto it = find(inorden.begin() + inorderStart, inorden.begin() + inorderEnd + 1, val);
	int inordenIndex = distance(inorden.begin(), it);

	int leftTreeSize = inordenIndex - inorderStart;
	endLeft = startLeft + leftTreeSize - 1;

	//Construir arbol

	auto left = recuperar_arbol(preorden, startLeft, endLeft, inorderStart, inordenIndex - 1, inorden);

	if(left.empty()) {
		startRight = startLeft;
	} else {
		startRight = endLeft + 1;
	}

	auto right = recuperar_arbol(preorden, startRight, endRight, inordenIndex + 1, inorderEnd, inorden);
	return bintree<int>(left, val, right);
}

int main()
{
	string a;
	while(getline(cin, a)) {
		string b;
		getline(cin, b);

		vector<int> preorden = stringToVector(a);
		vector<int> inorden = stringToVector(b);

		auto bt = recuperar_arbol(preorden, 0, inorden.size() - 1, 0, inorden.size() - 1, inorden);

		bool first = true;
		for(int i : bt.postorder()) {
			if(first) {
				first = false;
			} else {
				cout << " ";
			}
			cout << i;
		}
		cout << endl;
	}

	return 0;
}