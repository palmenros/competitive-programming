#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <climits>
#include "Matriz.h"

using namespace std;

typedef long long ll;

ll min_esfuerzo(int i, int j, const vector<ll>& c, Matriz<ll>& dp)
{
	assert(i < j);

	if(i + 1 == j) {
		return 0;
	}

	if(dp[i][j] == -1) {
		ll m = LONG_LONG_MAX;
		for(int k = i+1; k < j; k++) {
			m = min(m, min_esfuerzo(i, k, c, dp) + min_esfuerzo(k, j, c, dp) + 2*(c[j]-c[i]));
		}
		dp[i][j] = m;
	}

	return dp[i][j];
}

int main()
{
	ll L;
	int N;
	while(cin >> L >> N && !(L == 0 && N == 0)) {
		vector<ll> c(N+2);
		for(int i = 0; i < N; i++) {
			cin >> c[i+1];
		}

		c[0] = 0;
		c[N+1] = L;

		Matriz<ll> dp{N+2, N+2, -1};

		cout << min_esfuerzo(0, N+1, c, dp) << endl;
	}

	return 0;
}