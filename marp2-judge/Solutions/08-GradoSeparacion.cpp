#include <iostream>
#include <vector>
#include <unordered_map>
#include "Matriz.h"
#include "EnterosInf.h"

using namespace std;

EntInf& at(Matriz<EntInf>& dp, int i, int j) {
	if(i <= j) {
		return dp[i][j];
	}
	return dp[j][i];
}

EntInf grado_separacion(Matriz<EntInf>& dp, int P)
{
	for(int i = 0; i < P; i++) {
		//Una persona tiene consigo misma un grado de separación de 0
		dp[i][i] = 0;
	}

	EntInf max_grado = -1;

	for(int k = 1; k <= P; k++) {
		for(int i = 0; i < P; i++) {
			for(int j = i; j < P; j++) {
				EntInf val = min(at(dp, i, j), at(dp, i, k-1) + at(dp, k-1, j));
				at(dp, i, j) = val;
				if(k == P) {
					max_grado = max(max_grado, val);
				}
			}
		}
	}

	return max_grado;
}


int main()
{
	int P, R;
	while(cin >> P >> R) {

		int i = 0;
		unordered_map<string, int> map;
		Matriz<EntInf> dp{P, P, Infinito};

		for(int j = 0; j < R; j++) {
			string a, b;
			cin >> a >> b;

			auto itA = map.find(a);
			int posA;
			if(itA == map.end()) {
				posA = i;
				map[a] = posA;
				i++;
			} else {
				posA = itA->second;
			}

			auto itB = map.find(b);
			int posB;
			if(itB == map.end()) {
				posB = i;
				map[b] = posB;
				i++;
			} else {
				posB = itB->second;
			}

			dp[posA][posB] = 1;
			dp[posB][posA] = 1;
		}

		EntInf max_grado = grado_separacion(dp, P);

		if(max_grado == Infinito) {
			cout << "DESCONECTADA" << endl;
		} else {
			cout << max_grado << endl;
		}

	}

	return 0;
}