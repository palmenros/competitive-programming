//
// Created by pedro on 17/3/20.
//

#include "../bintree_eda.h"
#include <vector>
#include <iostream>

using namespace std;

void frontera(const bintree<int>& bt, vector<int>& v) {
	if(bt.empty()) { return; }

	bool esHoja = bt.left().empty() && bt.right().empty();
	if(esHoja) {
		v.push_back(bt.root());
	} else {
		frontera(bt.left(), v);
		frontera(bt.right(), v);
	}
}

int main()
{
	int N;
	cin >> N;
	while(N--) {
		bool first = true;
		vector<int> v;
		auto bt = leerArbol<int>(-1);
		frontera(bt, v);

		for(int i : v) {
			if(!first) {
				cout << " ";
			} else {
				first = false;
			}

			cout << i;
		}

		cout << endl;
	}
}