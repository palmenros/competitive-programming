//
// Created by pedro on 15/4/21.
//

#include <iostream>
#include <vector>
#include <deque>
#include "EnterosInf.h"
#include "Matriz.h"


using namespace std;

EntInf minMonedas(int N, int P, const vector<int>& valores, const vector<int>& cantidad, Matriz<EntInf>& dp)
{
	for(int i = 0; i <= N; i++) {
		dp[i][0] = 0;
	}

	for(int j = 1; j <= P; j++) {
		dp[0][j] = Infinito;
	}

	for(int i = 1; i <= N; i++) {
		for(int j = 0; j <= P; j++) {
			EntInf m = Infinito;
			int limit = min(j/valores[i-1], cantidad[i-1]);
			for(int k = 0; k <= limit; k++) {
				m = min(m, dp[i-1][j-k*valores[i-1]] + k);
			}
			dp[i][j] = m;
		}
	}

	return dp[N][P];
}

int main()
{
	int N;
	while(cin >> N) {

		vector<int> valores(N), cantidad(N);
		for(int i = 0; i < N; i++) {
			cin >> valores[i];
		}

		for(int i = 0; i < N; i++) {
			cin >> cantidad[i];
		}

		int P;
		cin >> P;

		Matriz<EntInf> dp(N + 1, P + 1, 0);
		auto res = minMonedas(N, P, valores, cantidad, dp);

		if(res != Infinito) {
			cout << "SI " << res << endl;
		} else {
			cout << "NO" << endl;
		}

	}

	return 0;
}