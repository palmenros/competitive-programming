//
// Created by pedro on 20/3/20.
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

//[start, end]
bintree<int> recuperar_arbol_busqueda(const vector<int>& preorden, int start, int end)
{
	if(start > end) {
		return bintree<int>();
	} else if (start == end) {
		return bintree<int>(preorden[start]);
	}

	auto val = preorden[start];

	//start > end

	int startLeft = start + 1, endLeft, startRight, endRight = end;

	//calcular endLeft

	auto it = lower_bound(preorden.begin() + start + 1, preorden.begin() + (end + 1), val);
	endLeft = distance(preorden.begin(), --it);

	auto left = recuperar_arbol_busqueda(preorden, startLeft, endLeft);

	if(left.empty()) {
		startRight = startLeft;
	} else {
		startRight = endLeft + 1;
	}

	auto right = recuperar_arbol_busqueda(preorden, startRight, endRight);
	return bintree<int>(left, val, right);
}

int main()
{
	string a;
	while(getline(cin, a)) {

		vector<int> preorden = stringToVector(a);

		auto bt = recuperar_arbol_busqueda(preorden, 0, preorden.size() - 1);

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