//Autores: Martín Gómez Abejón y Pedro Palacios Almendros
#include <vector>
#include <iostream>

using namespace std;

int merge(vector<int>& v, int a, int m, int b, vector<int>& tmp);

/*
 *  n := b - a
 *	T(n) = |	c1				  si n = 0
 *		   |	2*T(n/2) + c2*n   caso contrario
 *
 * Por el teorema de la división, el coste es O(n*log(n))
 */
int mergeSort(vector<int>& v, int a, int b, vector<int>& tmp) {
	int res = 0;

	if(b > a) {

		int mid = (a + b) / 2;
		res += mergeSort(v, a, mid, tmp);
		res += mergeSort(v, mid + 1, b, tmp);

		res += merge(v, a, mid + 1, b, tmp);
	}

	return res;
}

int merge(vector<int>& v, int a, int m, int b, vector<int>& tmp) {
	int res = 0;

	int i = a, j = m, k = a;
	while((j <= b) && (i <= m - 1)) {
		if(v[i] <= v[j]) {
			tmp[k++] = v[i++];
		} else {
			tmp[k++] = v[j++];
			res += m - i;
		}
	}

	while(i <= m - 1) {
		tmp[k++] = v[i++];
	}

	while(j <= b) {
		tmp[k++] = v[j++];
	}

	for(int l = a; l <= b; l++) {
		v[l] = tmp[l];
	}

	return res;
}


int main() {
	int N;
	while(cin >> N) {
		vector<int> v(N);
		
		for(int i = 0; i < N; i++) {
			cin >> v[i];
		}

		vector<int> tmp(N);
		cout << mergeSort(v, 0, v.size() - 1, tmp) << endl;
	}
}
