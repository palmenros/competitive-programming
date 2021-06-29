#include <iostream>
#include <vector>
#include "Matriz.h"

using namespace std;

typedef long long ll;

ll maxOro(ll i, ll j, const vector<ll>& p, const vector<ll>& v, Matriz<ll>& dp)
{
	if(dp[i][j] == -1) {
		//Casos base
		if(i == 0 || j == 0) {
			dp[i][j] = 0;
		} else {
			//Caso recursivo
			if(3*p[i-1] > j) {
				dp[i][j] = maxOro(i-1, j, p, v, dp);
			} else {
				dp[i][j] = max(maxOro(i-1, j, p, v, dp), maxOro(i-1, j - 3*p[i-1], p, v, dp) + v[i-1]);
			}
		}
	}

	return dp[i][j];
}

struct Data {
	ll profundidad;
	ll oro;

	Data(ll profundidad, ll oro)
		: profundidad(profundidad), oro(oro)
	{}

};

int main()
{
	int T, N;
	while(cin >> T >> N) {
		vector<ll> p(N), v(N);

		for(int i = 0; i < N; i++) {
			cin >> p[i] >> v[i];
		}

		Matriz<ll> dp(N + 1, T + 1, -1);
		auto r = maxOro(N, T, p, v, dp);

		cout << r << endl;

		//Reconstruir
		vector<Data> cofres;

		ll i = N, j = T;

		while(r > 0 && i > 0) {

			if(3*p[i-1] <= j && dp[i][j] == dp[i-1][j-3*p[i-1]] + v[i-1]) {
				//Cogemos este
				cofres.emplace_back(p[i-1], v[i-1]);
				r -= v[i-1];
				j -= 3*p[i-1];
			}

			i--;
		}

		cout << cofres.size() << endl;

		for(int i = cofres.size() - 1; i >= 0; i--) {
			cout << cofres[i].profundidad << " " << cofres[i].oro << endl;
		}


		cout << "---" << endl;

	}

	return 0;
}