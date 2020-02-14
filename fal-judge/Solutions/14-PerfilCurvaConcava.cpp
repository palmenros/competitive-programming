//Autores: Martín Gómez Abejón y Pedro Palacios Almendros

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Divide y vencerás en [a, b]
int minimo_concavo(const vector<int>& v, int a, int b) {
	if (a == b) {
		return v[a];
	}

	int mid = (a + b) / 2;

	bool crecienteDerecha = v[mid + 1] - v[mid] > 0;
	if (crecienteDerecha) {
		return minimo_concavo(v, a, mid);
	} else {
		return minimo_concavo(v, mid + 1, b);
	}
}

int main() {
	
	int N;
	while (cin >> N) {

		vector<int> v;

		for (int i = 0; i < N; i++) {
			int tmp;
			cin >> tmp;	
			v.push_back(tmp);
		}

		cout << minimo_concavo(v, 0, v.size() - 1) << endl;
	}

	return 0;
}