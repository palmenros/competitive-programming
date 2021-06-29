#include <iostream>
#include "Matriz.h"

typedef long long ll;

using namespace std;

ll num_formas(int i, int j, Matriz<ll>& dp, const Matriz<char>& G) {
	if(i < 0 || j < 0) {
		return 0;
	}

	if(i == 0 && j == 0) {
		return 1;
	}

	if(dp[i][j] == -1) {
		if(G[i][j] == 'P') {
			dp[i][j] = 0;
		} else {
			dp[i][j] = num_formas(i-1, j, dp, G) + num_formas(i, j-1, dp, G);
		}

	}

	return dp[i][j];
}

int main()
{
	int N, M;
	while(cin >> N >> M) {

		Matriz<char> G(N, M, '?');

		for(int r = 0; r < N; r++) {
			for(int c = 0; c < M; c++) {
				cin >> G[r][c];
			}
		}

		Matriz<ll> dp(N, M, -1);
		cout << num_formas(N-1, M-1, dp, G) << endl;
	}

	return 0;
}