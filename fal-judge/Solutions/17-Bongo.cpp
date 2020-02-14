//Autores: Martín Gómez Abejón y Pedro Palacios Almendros

#include <iostream>
#include <vector>

using namespace std;

/*
 *  Si n := b - a + 1
 *	T(n) = |	c1				si 0
 *		   |	T(n/2) + c2		en caso contrario
 *	El coste del algoritmo es logarítmico, al ser equivalente a una búsqueda binaria. También se puede ver por el teorema de la división
 */
bool bongo(const vector<int>& v, int val, int a, int b, int& pos) {
	
	if(a > b) {return false;}

	int mid = (a + b) / 2;
	if(mid + val == v[mid]) {
		pos = mid;
		return true;
	} else if (mid + val < v[mid]) {
		return bongo(v, val, a, mid - 1, pos);
	} else {
		return bongo(v, val, mid + 1, b, pos);
	}

}

int main() {
	
	int nCasos;
	cin >> nCasos;
	while(nCasos--) {
		int N; int val;
		cin >> N >> val;
		
		vector<int> v;

		for(int i = 0; i < N; i++) {
			int tmp;
			cin >> tmp;
			v.push_back(tmp);
		}

		int pos;
		if(bongo(v, val, 0, v.size() - 1, pos)) {
			cout << pos + val << endl;
		} else {
			cout << "NO" << endl;
		}

	}

	return 0;
}
