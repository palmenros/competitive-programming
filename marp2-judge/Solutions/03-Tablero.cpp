#include <iostream>
#include <algorithm>
#include "Matriz.h"

using namespace std;

typedef long long ll;

ll max_suma(int i, int j, const Matriz<ll>& m, Matriz<ll>& s) {
	if(i == 0 || j == 0 || i > m.numcols()) {
		return 0;
	}

	auto f = [&](int x, int y) {
		return max_suma(x, y, m, s);
	};

	if(s[i-1][j-1] == -1) {
		s[i-1][j-1] = m[i-1][j-1] + max({ f(i-1, j-1), f(i, j-1), f(i+1, j - 1) });
	}

	return s[i-1][j-1];
}

int main()
{
	int N;
	while(cin >> N) {
		Matriz<ll> m(N, N);

		for(int y = 0; y < N; y++)
			for(int x = 0; x < N; x++)
				cin >> m[x][y];

		ll max = -1;
		int max_index = -1;
		Matriz<ll> s(N, N, -1);

		for(int i = 1; i <= N; i++) {
			auto ls = max_suma(i, N, m, s);
			if(ls > max) {
				max = ls;
				max_index = i;
			}
		}

		cout << max << " " << max_index << endl;


	}

	return 0;
}