#include <queue>
#include <iostream>

using namespace std;

using ll = long long int;

struct Caja {
	ll N;
	ll end_time;

	Caja(ll n, ll endTime)
		: N(n), end_time(endTime)
	{}
};

int main()
{
	ll N, C;
	while(cin >> N >> C && ! ( N == 0 && C == 0 )) {

		auto cmp = [](const Caja& a, const Caja & b) {
			if(a.end_time == b.end_time) {
				return a.N > b.N;
			}
			return a.end_time > b.end_time;
		};

		priority_queue<Caja, vector<Caja>, decltype(cmp)> cajas{cmp};
		queue<ll> clientes;

		for(int i = 1; i <= N; i++) {
			cajas.push({i, 0});
		}

		while(C--) {
			ll t;
			cin >> t;
			clientes.push(t);
		}

		while(!clientes.empty()) {
			auto caja = cajas.top();
			auto cliente = clientes.front();
			clientes.pop();

			cajas.pop();
			cajas.push({caja.N, caja.end_time + cliente});
		}

		auto res = cajas.top();
		cout << res.N << '\n';
	}

	cout << flush;

	return 0;
}