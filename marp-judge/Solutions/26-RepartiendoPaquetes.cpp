#include "../DigrafoValorado.h"
#include "../IndexPQ.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

using ll = long long;

class Dijkstra {
private:

	DigrafoValorado<ll>& g;
	IndexPQ<ll> pq;
	vector<ll> distTo;

public:

	Dijkstra(DigrafoValorado<ll> &g)
		: g(g),
		  pq(g.V()),
		  distTo(g.V(), INT_MAX)
	{
	}

	void relax(AristaDirigida<ll> edge) {
		int v = edge.desde(), w = edge.hasta();

		if(distTo[w] > distTo[v] + edge.valor()) {
			distTo[w] = distTo[v] + edge.valor();
			pq.update(w, distTo[w]);
		}

	}

	void calcular(int O) {
		distTo[O] = 0;
		pq.push(O, 0);

		while(!pq.empty()) {
			auto [v, priority] = pq.top();
			pq.pop();

			for(auto edge : g.ady(v)) {
				relax(edge);
			}
		}
	}

	ll minimaDistanciaA(int v) {
		return distTo[v];
	}
};

int main()
{
	int N, C;

	while(cin >> N >> C) {

		DigrafoValorado<ll> g{N};
		DigrafoValorado<ll> gt{N};

		while(C--) {
			int a, b;
			ll coste;
			cin >> a >> b >> coste;
			a--; b--;

			g.ponArista(AristaDirigida<ll>{ a, b, coste });
			gt.ponArista(AristaDirigida<ll>{ b, a, coste });
		}

		int O;
		cin >> O;
		O--;

		Dijkstra d{g};
		Dijkstra dt{gt};

		d.calcular(O);
		dt.calcular(O);

		int P;
		cin >> P;

		ll sum = 0;
		bool allPathsExist = true;

		while(P--) {
			int dest;
			cin >> dest;

			if(allPathsExist) {
				dest--;

				ll a = d.minimaDistanciaA(dest);
				ll b = dt.minimaDistanciaA(dest);

				if (a == INT_MAX || b == INT_MAX) {
					allPathsExist = false;
				}

				sum += a + b;
			}
		}

		if(allPathsExist) {
			cout << sum << "\n";
		} else {
			cout << "Imposible\n";
		}

	}

	return 0;
}