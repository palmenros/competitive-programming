#include <vector>
#include <iostream>
#include "../ConjuntosDisjuntos.h"
#include "../GrafoValorado.h"
#include <queue>

using namespace std;


int arbol_recubrimiento_minimo(const GrafoValorado<int>& g)
{
	auto cmp = [](const Arista<int>& a, const Arista<int>& b) {
		return a > b;
	};

	priority_queue<Arista<int>, vector<Arista<int>>, decltype(cmp)> pq{cmp};
	ConjuntosDisjuntos conjuntosDisjuntos{g.V()};

	for(auto edge : g.aristas()) {
		pq.push(edge);
	}

	int size = 0, cost = 0;
	while(!pq.empty() && size < g.V() - 1) {
		auto edge = pq.top();
		pq.pop();

		int v = edge.uno();
		int w = edge.otro(v);

		if(!conjuntosDisjuntos.unidos(v, w)) {
			conjuntosDisjuntos.unir(v, w);
			size++;
			cost += edge.valor();
		}
	}

	if( size != g.V() - 1) {
		return -1;
	}

	return cost;
}



int main()
{
	int I, P;

	while(cin >> I >> P) {

		GrafoValorado<int> g{I};

		while(P--) {
			int a, b, precio;

			cin >> a >> b >> precio;
			a--; b--;

			g.ponArista(Arista<int>{a, b, precio});
		}

		int coste = arbol_recubrimiento_minimo(g);

		if(coste == -1) {
			cout << "No hay puentes suficientes\n";
		} else {
			cout << coste << "\n";
		}
	}

	return 0;
}