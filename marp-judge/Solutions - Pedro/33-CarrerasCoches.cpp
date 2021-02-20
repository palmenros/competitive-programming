#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

ll max_num_coches(vector<ll>& v, ll V)
{
	sort(v.begin(), v.end());

	int s = 0, e = v.size() - 1;
	ll res = 0;

	while(s < e) {

		//Esta pareja es valida
		if(v[s] + v[e] >= V) {
			res++;
			s++;
			e--;
			continue;
		}
		
		//Esta pareja no es valida, coger uno más grande por la izquierda
		s++;
	}

	return res;
}

int main() {
	int nCasos;
	cin >> nCasos;

	while(nCasos--) {
		ll N, V;
		cin >> N >> V;

		vector<ll> v;

		while(N--) {
			ll tmp;
			cin >> tmp;
			v.push_back(tmp);
		}

		cout << max_num_coches(v, V) << "\n";
	}

	return 0;
}
