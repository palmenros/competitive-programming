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
	vector<int> numShortestPaths;

public:

	Dijkstra(DigrafoValorado<int> &g)
		: g(g),
		  pq(g.V()),
		  distTo(g.V(), INT_MAX),
		  numShortestPaths(g.V(), 0)
	{
	}

	void relax(AristaDirigida<int> edge) {
		int v = edge.desde(), w = edge.hasta();

		if(distTo[w] > distTo[v] + edge.valor()) {
			distTo[w] = distTo[v] + edge.valor();
			pq.update(w, distTo[w]);
			numShortestPaths[w] = numShortestPaths[v];
		} else if (distTo[w] == distTo[v] + edge.valor()) {
			numShortestPaths[w] += numShortestPaths[v];
		}
	}

	int numCaminosMinimos() {
		distTo[0] = 0;
		pq.push(0, 0);
		numShortestPaths[0] = 1;

		while(!pq.empty()) {
			auto [v, priority] = pq.top();
			pq.pop();

			for(auto edge : g.ady(v)) {
				relax(edge);
			}
		}

		return numShortestPaths[g.V() - 1];
	}
};

int main()
{
	int N, C;

	while(cin >> N) {
		cin >> C;

		DigrafoValorado<int> g{N};

		while(C--) {
			int a, b, cost;
			cin >> a >> b >> cost;

			a--; b--;
			g.ponArista(AristaDirigida<int>{a, b, cost});
			g.ponArista(AristaDirigida<int>{b, a, cost});
		}

		Dijkstra d{g};
		cout << d.numCaminosMinimos() << "\n";
	}

	return 0;
}