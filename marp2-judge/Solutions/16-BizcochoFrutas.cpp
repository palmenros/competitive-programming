#include <iostream>
#include <vector>
#include "Matriz.h"
#include <algorithm>

using namespace std;

int max_dias(int i, int j, const vector<int>& v, Matriz<int>& dp)
{
	if(i > j) {
		return 0;
	}

	if(dp[i][j] == -1) {
		if(v[i] == v[j] && v[i] != 0) {
			dp[i][j] = 1 + max_dias(i+1, j-1, v, dp);
		} else {
			int m = max({
				max_dias(i+1, j-1, v, dp),
				max_dias(i, j-2, v, dp),
				max_dias(i+2, j, v, dp)
			});

			dp[i][j] = m;
		}


	}

	return dp[i][j];
}

int main()
{
	int N;
	while(cin >> N) {

		vector<int> v(N);
		for(int i = 0; i < N; i++) {
			cin >> v[i];
		}

		Matriz<int> dp(N, N, -1);

		cout << max_dias(0, N-1, v, dp) << endl;

	}

	return 0;
}