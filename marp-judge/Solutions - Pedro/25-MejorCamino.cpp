#include "../DigrafoValorado.h"
#include "../IndexPQ.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

using ll = long long;

struct Result {
	ll minDist;
	ll minStreets;

	Result(ll minDist, ll minStreets)
		: minDist(minDist), minStreets(minStreets)
	{}
};

class Dijkstra {
private:

	DigrafoValorado<ll>& g;
	IndexPQ<ll> pq;
	vector<ll> distTo;
	vector<ll> minStreets;

	vector<vector<ll>> distToGlobal;
	vector<vector<ll>> minStreetsGlobal;

	void relax(AristaDirigida<ll> edge) {
		int v = edge.desde(), w = edge.hasta();

		if(distTo[w] > distTo[v] + edge.valor()) {
			distTo[w] = distTo[v] + edge.valor();
			pq.update(w, distTo[w]);

			minStreets[w] = minStreets[v] + 1;
		} else if (distTo[w] == distTo[v] + edge.valor()) {
			minStreets[w] = min(minStreets[w], minStreets[v] + 1);
		}
	}

	void dijkstra(int O) {
		distTo = vector<ll>(g.V(), INT_MAX);
		minStreets = vector<ll>(g.V(), 0);

		distTo[O] = 0;
		pq.push(O, 0);

		while(!pq.empty()) {
			auto [v, priority] = pq.top();
			pq.pop();

			for(auto edge : g.ady(v)) {
				relax(edge);
			}
		}

		distToGlobal[O] = distTo;
		minStreetsGlobal[O] = minStreets;
	}

public:

	Dijkstra(DigrafoValorado<ll> &g)
		: g(g),
		  pq(g.V())
	{
		distToGlobal.resize(g.V());
		minStreetsGlobal.resize(g.V());
	}

	Result verResultado(int v, int w) {

		if(distToGlobal[v].empty() && distToGlobal[w].empty()) {
			dijkstra(v);
		}

		if(distToGlobal[v].empty()) {
			return { distToGlobal[w][v], minStreetsGlobal[w][v] };
		} else {
			return { distToGlobal[v][w], minStreetsGlobal[v][w] };
		}
	}
};

struct QueueElement {
	int element;
	int distance;

	QueueElement(int element, int distance)
		: element(element), distance(distance)
	{}
};

class BFS {
private:

	DigrafoValorado<ll>& g;
	vector<vector<ll>> globalDistTo;

private:

	void dfs(int source) {
		vector<bool> marcados(g.V(), false);
		queue<QueueElement> q;

		q.push({source, 0});

		globalDistTo[source] = vector<ll>(g.V(), INT_MAX);

		while(!q.empty()) {

			auto e = q.front();
			q.pop();

			globalDistTo[source][e.element] = e.distance;

			int v = e.element;

			for(auto edge : g.ady(v)) {
				int w = edge.hasta();

				if(!marcados[w]) {
					marcados[w] = true;
					q.push({w, e.distance + 1});
				}
			}

		}

	}

public:

	BFS(DigrafoValorado<ll> &g)
		: g(g)
	{
		globalDistTo.resize(g.V());
	}

	int verResultado(int v, int w) {
		if(globalDistTo[v].empty() && globalDistTo[w].empty()) {
			dfs(v);
		}

		if(globalDistTo[v].empty()) {
			return globalDistTo[w][v];
		} else {
			return globalDistTo[v][w];
		}
	}
};

int main()
{
	int N, C;

	while(cin >> N >> C) {

		DigrafoValorado<ll> g{N};

		while(C--) {
			int a, b;
			ll cost;

			cin >> a >> b >> cost;
			a--; b--;

			g.ponArista(AristaDirigida<ll>{a, b, cost});
			g.ponArista(AristaDirigida<ll>{b, a, cost});
		}

		int K;

		cin >> K;

		Dijkstra dijkstra{g};
		BFS bfs{g};

		while(K--) {
			int origen, destino;
			cin >> origen >> destino;
			origen--; destino--;

			auto dijkstraRes = dijkstra.verResultado(origen, destino);
			int minBFS = bfs.verResultado(origen, destino);

			if(dijkstraRes.minDist == INT_MAX) {
				cout << "SIN CAMINO\n";
			} else {
				bool iguales = dijkstraRes.minStreets == minBFS;
				cout << dijkstraRes.minDist << " " << (iguales ? "SI\n" : "NO\n");
			}

		}

		cout << "---\n";

	}

	return 0;
}