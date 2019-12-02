#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * 	izquierda(v, a, b) := parcialmente_ordenado(v, a, (a + b) / 2)
 * 	derecha(v, a, b) := parcialmente_ordenado(v, (a + b) / 2 + 1, b)
 *
 *  { N > 0, 0 <= a <= b < N }
 *	fun parcialmente_ordenado(v[0...N) de ent, a : ent, b : ent) : dev r : bool, maximo : ent, minimo : ent
 *	{
 *		r = a == b || (
 *			b = izquierda(v, a, b).r && derecha(v, a, b).r 		 &&
			derecha(v, a, b).maximo >= izquierda(v, a, b).maximo &&
 *			izquierda(v, a, b).minimo <= derecha(v, a, b).minimo
 *		) &&
 *		maximo = max i : a <= i <= b : v[i] &&
 *		minimo = min i : a <= i <= b : v[i] &&
 *	}
 */
bool parcialmente_ordenado(const vector<int>& v, int a, int b, int& maximo, int& minimo) {
	if(a == b) {
		maximo = v[a];
		minimo = v[a];
		return true;
	}

	int mid = (a + b) / 2;
	int maxA, minA, maxB, minB;
	if(!parcialmente_ordenado(v, a, mid, maxA, minA) || !parcialmente_ordenado(v, mid + 1, b, maxB, minB)) {
		return false;
	}

	maximo = max(maxA, maxB);
	minimo = min(minA, minB);

	return maxB >= maxA && minA <= minB;
}


int main() {

	int first;
	while(cin >> first && first != 0) {
		vector<int> v;
		v.push_back(first);

		int tmp;
		while(cin >> tmp && tmp != 0) {v.push_back(tmp);}

		int maximo, minimo;
		cout << (parcialmente_ordenado(v, 0, v.size() - 1, maximo, minimo) ? "SI" : "NO") << endl;

	}

	return 0;
}