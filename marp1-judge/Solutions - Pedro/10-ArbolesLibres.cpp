#include "Grafo.h"
#include <iostream>
#include <unordered_set>

using namespace std;

class EsArbolLibre {
	int visited_vertices{0};
	vector<bool> marked;
	vector<int> edgeTo;

	const Grafo& g;

	bool esArbolLibreRecursivo(int v) {
		marked[v] = true;
		visited_vertices++;

		bool res = true;
		for(int w : g.ady(v)) {
			if(marked[w]) {
				//O es ciclico o es el nodo del que viene v
				if(w != edgeTo[v]) {
					return false;
				} else {
					continue;
				}
			}

			edgeTo[w] = v;
			res = res && esArbolLibreRecursivo(w);
		}

		return res;
	}

public:
	EsArbolLibre(const Grafo& g) : 
		g(g), 
		marked(vector<bool>(g.V(), false)), 
		edgeTo(vector<int>(g.V(), 0)) 
	{}

	bool esArbolLibre() {
		bool res = esArbolLibreRecursivo(0);
		if(!res) {
			return false;
		}
		return visited_vertices == g.V();
	}
};

int main()
{
	int V;
	while(cin >> V) {
		int A;
		cin >> A;
		Grafo g{V};

		while(A--) {
			int a, b;
			cin >> a >> b;
			g.ponArista(a, b);
		}

		EsArbolLibre a{g};
		bool b = a.esArbolLibre();
		if(b) {
			cout << "SI\n";
		} else {
			cout << "NO\n";
		}
	}

	return 0;
}
