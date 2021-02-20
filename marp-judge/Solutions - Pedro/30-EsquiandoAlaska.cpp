#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

using ll = long long;

int main()
{
	int N;
	while(cin >> N && N != 0)
	{
		vector<ll> esquis(N, 0);
		vector<ll> alturas(N, 0);

		for(int i = 0; i < N; i++) {
			cin >> esquis[i];
		}

		for(int i = 0; i < N; i++) {
			cin >> alturas[i];
		}

		//Hallar minima diferencia de valores absolutos
		sort(esquis.begin(), esquis.end());
		sort(alturas.begin(), alturas.end());

		ll res = 0;
		for(int i = 0; i < esquis.size(); i++) {
			res += abs(esquis[i] - alturas[i]);
		}

		cout << res << "\n";
	}

	return 0;
}