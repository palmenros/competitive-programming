#include "../DigrafoValorado.h"
#include "../IndexPQ.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Dijkstra {
private:

	DigrafoValorado<int>& g;
	IndexPQ<int> pq;
	vector<int> distTo;

public:

	Dijkstra(DigrafoValorado<int> &g)
		: g(g),
		pq(g.V()),
		distTo(g.V(), INT_MAX)
	{
	}

	void relax(AristaDirigida<int> edge) {
		int v = edge.desde(), w = edge.hasta();

		if(distTo[w] > distTo[v] + edge.valor()) {
			distTo[w] = distTo[v] + edge.valor();
			pq.update(w, distTo[w]);
		}

	}

	int minimoTiempo() {
		distTo[0] = 0;
		pq.push(0, 0);

		while(!pq.empty()) {
			auto [v, priority] = pq.top();
			pq.pop();

			for(auto edge : g.ady(v)) {
				relax(edge);
			}
		}

		return distTo[g.V() - 1];
	}
};

int main()
{
	int N;

	while(cin >> N && N != 0) {

		vector<int> tiemposCarga(N, 0);

		//Tiempos de carga
		for(int i = 0; i < N; i++) {
			int t;
			cin >> t;

			tiemposCarga[i] = t;
		}

		//Enlces
		int M;
		cin >> M;

		DigrafoValorado<int> g{N};

		while(M--) {
			int a, b, t;
			cin >> a >> b >> t;

			a--; b--;
			t += tiemposCarga[a];
			g.ponArista(AristaDirigida<int>{a, b, t});
		}

		Dijkstra d{g};

		int t = d.minimoTiempo();

		if(t == INT_MAX) {
			cout << "IMPOSIBLE\n";
		} else {
			t += tiemposCarga[N - 1];
			cout << t << "\n";
		}

	}

	return 0;
}