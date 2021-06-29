#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <exception>

using namespace std;
using ll = long long;

struct Trabajo {
	ll c, f;
	Trabajo(ll c, ll f) :
		c(c), f(f)
	{}
};

ll min_trabajos(ll C, ll F, vector<Trabajo>& v)
{
	sort(v.begin(), v.end(), [](const Trabajo& a, const Trabajo& b) {
		return a.c < b.c;
	});

	//v está ordenado en orden creciente
	
	//Todos los intervalos son semiabiertos: [C, F) y [c_i, f_i)
	
	if(v.empty() || v[0].c > C) {
		throw exception();
	}

	//Calculamos el intervalo inicial
	ll max_end = LONG_LONG_MIN;

	ll i = 0;
	while(i < v.size()) {
		ll c = v[i].c, f = v[i].f;

		if(c > C) {
			break;
		}
	
		max_end = max(max_end, f);
		i++;
	}
	
	//Calculamos el resto de intervalos

	ll current_end = max_end;
	ll res = 1;

	for(;  i < v.size() && max_end < F; i++ ) {
		ll c = v[i].c, f = v[i].f;

		if(c <= current_end) {
			max_end = max(max_end, f);
			continue;
		}

		if(max_end < c) {
			throw exception();
		}

		res++;
		current_end = max_end;
		max_end = max(max_end, f);
	}

	if(current_end >= F) {
		return res;
	}

	if(max_end >= F) {
		return res + 1;
	}

	throw exception();
}

int main()
{
	ll C, F, N;
	while(cin >> C >> F >> N && (C + F + N) != 0)
	{
		vector<Trabajo> v;
		while(N--) {
			ll c, f;
			cin >> c >> f;

			if(f <= C || c >= F) {
				continue;
			}

			v.emplace_back(c, f);
		}

		try {
			ll res = min_trabajos(C, F, v);
			cout << res << "\n";
		} catch(exception& e) {
			cout << "Imposible\n";
		}

	}

	return 0;
}
