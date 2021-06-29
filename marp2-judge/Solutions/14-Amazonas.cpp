#include <iostream>
#include <climits>
#include <algorithm>
#include "Matriz.h"

using namespace std;

int min_coste(int i, int j, Matriz<int>& dp, const Matriz<int>& G) {

	if(i == j) {
		return 0;
	}

	if(dp[i][j] == -1) {
		int m = INT_MAX;
		for(int k = i + 1; k < j; k++) {
			m = min(m, min_coste(i, k, dp, G) + min_coste(k, j, dp, G));
		}

		dp[i][j] = min(G[i][j], m);
	}

	return dp[i][j];
}

int main()
{
	int N;
	while(cin >> N) {

		Matriz<int> G(N, N, 0);

		for(int orig = 0; orig < N; orig++) {
			for(int dest = orig + 1; dest < N; dest++) {
				cin >> G[orig][dest];
			}
		}

		Matriz<int> dp(N, N, -1);

		for(int orig = 0; orig < N; orig++) {
			string c = "";

			for(int dest = orig + 1; dest < N; dest++) {
				cout << c << min_coste(orig, dest, dp, G);
				c = " ";
			}

			cout << endl;
		}



	}

	return 0;
}