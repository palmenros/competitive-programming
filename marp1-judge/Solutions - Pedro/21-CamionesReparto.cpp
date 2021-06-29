#include "../DigrafoValorado.h"
#include "../IndexPQ.h"
#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>
#include <functional>

using namespace std;

using IndexMaxPQ = IndexPQ<int, std::greater<>>;


class CamionesReparto {
private:

	const DigrafoValorado<int>& g;
	vector< vector<int> > vec;

private:

	void relax(AristaDirigida<int> edge, vector<int>& maxWeight, IndexMaxPQ& pq)
	{
		int v = edge.desde();
		int w = edge.hasta();

		if(maxWeight[w] < min(maxWeight[v], edge.valor())) {
			maxWeight[w] = min(maxWeight[v], edge.valor());
			pq.update(w, maxWeight[w]);
		}
	}

	void dijkstra(int s) {
		vector<int> maxWeight(g.V(), 0);
		IndexMaxPQ pq{g.V()};

		maxWeight[s] = INT_MAX;
		pq.push(s, INT_MAX);

		while(!pq.empty()) {
			auto [v, prioridad] = pq.top();
			pq.pop();

			for(auto edge : g.ady(v)) {
				relax(edge, maxWeight, pq);
			}

		}

		vec[s] = maxWeight;
	}

public:

	CamionesReparto(const DigrafoValorado<int> &g)
		: g(g)
	{
		vec.resize(g.V());
	}

	int maximaAnchura(int v, int w) {
		if(vec[v].empty() && vec[w].empty()) {
			dijkstra(v);
		}

		if(vec[v].empty()) {
			return vec[w][v];
		} else {
			return vec[v][w];
		}
	}

};


int main()
{
	int V, E;
	while(cin >> V >> E) {
		DigrafoValorado<int> g{V};

		while(E--) {
			int a, b, valor;
			cin >> a >> b >> valor;
			a--; b--;

			g.ponArista(AristaDirigida<int>{a, b, valor});
			g.ponArista(AristaDirigida<int>{b, a, valor});
		}

		CamionesReparto r{g};

		int K;
		cin >> K;

		while(K--) {
			int origen, destino, anchura;
			cin >> origen >> destino >> anchura;

			origen--; destino--;

			int maximaAnchura = r.maximaAnchura(origen, destino);
			if(maximaAnchura >= anchura) {
				cout << "SI\n";
			} else {
				cout << "NO\n";
			}
		}
	}


	return 0;
}