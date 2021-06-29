#include <iostream>
#include <vector>
#include <algorithm>
#include "Matriz.h"

using namespace std;

int max_comida(int i, int j, const vector<int>& v, Matriz<int>& dp)
{
	if(i == j) {
		return v[i];
	}

	if(i+1 == j) {
		return max(v[i], v[j]);
	}

	if(dp[i][j] == -1) {
		//Probamos a coger el de la izquierda
		int val_izq = v[i];

		if(v[i+1] > v[j]) {
			//Devoradora se queda con i+1
			val_izq += max_comida(i+2, j, v, dp);
		} else {
			//Devoradora se queda con j
			val_izq += max_comida(i+1, j-1, v, dp);
		}

		//Probamos a coger el de la derecha
		int val_dch = v[j];

		if(v[i] > v[j-1]) {
			//Devoradora se queda con i
			val_dch += max_comida(i+1, j-1, v, dp);
		} else {
			//Devoradora se queda con j-1
			val_dch += max_comida(i, j-2, v, dp);
		}

		dp[i][j] = max(val_izq, val_dch);
	}

	return dp[i][j];
}

int main()
{
	int N;
	while(cin >> N && N != 0) {
		vector<int> v(N);
		for(int i = 0; i < N; i++) {
			cin >> v[i];
		}

		Matriz<int> dp(N, N, -1);
		cout << max_comida(0, v.size() - 1, v, dp) << endl;

	}

	return 0;
}