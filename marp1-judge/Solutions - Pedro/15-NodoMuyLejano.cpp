#include "Grafo.h"
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct Element {
	int vertex;
	int level;
};

class BFS {
	const Grafo& g;

	
	int nodosAlcanzables(int v, int ttl) {
		vector<bool> marcas(g.V(), false);
		queue<Element> q;
		
		marcas[v] = true;
		q.push({v, 0});
		
		int n = 0;


		while(!q.empty()) {
			Element top = q.front();
			q.pop();
			
			n++;

			if(top.level == ttl) {
				continue;
			}

			for(auto w : g.ady(top.vertex)) {
				if(!marcas[w]) {
					marcas[w] = true;
					q.push({w, top.level + 1});
				}
			}

		}


		return n;
	}

public:
	
	BFS(const Grafo& g) : g(g)
	{}

	int nodosInalcanzables(int v, int ttl) {
		return g.V() - nodosAlcanzables(v, ttl);
	}
};


int main() {
	int V;
	while(cin >> V) {
		int A;
		cin >> A;
	
		Grafo g{V};

		while(A--) {
			int v, w;
			cin >> v >> w;
			v--;
			w--;
			g.ponArista(v, w);
		}

		BFS bfs{g};
		int K;
		cin >> K;
		
		while(K--) {
			int s, ttl;
			cin >> s >> ttl;
			s--;
			cout << bfs.nodosInalcanzables(s, ttl) << "\n";
		}
		cout << "---\n";
	}

	return 0;
}
