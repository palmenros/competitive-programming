#include "Grafo.h"
#include <vector>
#include <unordered_set>
#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

class GrupoAmigos {
	unordered_set<int> unexplored_vertices;
	vector<bool> marked;
	int currentGroupSize {0};
	int maxGroupSize {0};
	const Grafo& g;
private:
	
	void explorarGrupoAmigosRecursivo(int v) {
		marked[v] = true;
		unexplored_vertices.erase(v);
		currentGroupSize++;
		maxGroupSize = max(maxGroupSize, currentGroupSize);

		for(int w : g.ady(v)) {
			if(!marked[w]) {
				explorarGrupoAmigosRecursivo(w);
			}
		}
	}

public:

	GrupoAmigos(const Grafo& g) 
	: marked(vector<bool>( g.V(), false)),
	  g(g)
	{
		//Fill unexplored vertices
		for(int i = 0; i < g.V(); i++) {
			unexplored_vertices.insert(i);
		}
	}

	int mayorGrupoAmigos() {
		while(!unexplored_vertices.empty()) {
			auto start_vertex = *(unexplored_vertices.begin());
			currentGroupSize = 0;
			explorarGrupoAmigosRecursivo(start_vertex);
		}
		return maxGroupSize;
	}
};

int main()
{
	int N;
	cin >> N;

	while(N--) {
		int V, A;
		cin >> V >> A;
		Grafo g{V};
	
		while(A--) {
			int a, b;
			cin >> a >> b;
			a--;
			b--;
			g.ponArista(a, b);
		}

		GrupoAmigos grupo{g};

		cout << grupo.mayorGrupoAmigos() << "\n";
	}

	return 0;
}
