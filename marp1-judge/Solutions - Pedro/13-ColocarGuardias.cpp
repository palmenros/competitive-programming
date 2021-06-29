#include "../Grafo.h"
#include <vector>
#include <unordered_set>
#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

class ColocarGuardias {

	const Grafo& g;

	vector<bool> marcados;
	vector<bool> hayGuardiaVector;

	unordered_set<int> explored_vertices;
	bool isFirstPass = true;

private:

	int minimo_num_recursivo(int v, bool hayGuardia) {

		if(marcados[v]) {
			//Ya hemos pasado por este
			if(hayGuardiaVector[v] == hayGuardia) {
				//No hay problema
				return 0;
			} else {
				//Esta solución es infactible
				return -1;
			}
		}

		//Primera vez que pasamos por este vertice
		if(isFirstPass) {
			explored_vertices.erase(v);
		}

		hayGuardiaVector[v] = hayGuardia;
		marcados[v] = true;

		int sum = hayGuardia ? 1 : 0;
		for(int w : g.ady(v)) {
			int res = minimo_num_recursivo(w, !hayGuardia);
			if(res == -1) {
				return -1;
			} else {
				sum += res;
			}
		}

		return sum;
	}

public:

	ColocarGuardias(const Grafo &g)
		: g(g)
	{}

	int minimo_numero() {

		marcados = vector<bool>(g.V(), false);
		hayGuardiaVector = vector<bool>(g.V(), false);

		for(int i = 0; i < g.V(); i++) {
			explored_vertices.insert(i);
		}

		int sum = 0;

		while(!explored_vertices.empty()) {
			int v = *explored_vertices.begin();
			isFirstPass = true;

			int resA = minimo_num_recursivo(v, true);

			isFirstPass = false;
			marcados = vector<bool>(g.V(), false);

			int resB = minimo_num_recursivo(v, false);

			if(resA == -1) {
				resA = INT_MAX;
			}

			if(resB == -1) {
				resB = INT_MAX;
			}

			int finalRes = min(resA, resB);

			if(finalRes == INT_MAX) {
				//infactible
				throw domain_error("");
			} else {
				sum += finalRes;
			}

		}

		return sum;
	}

};

int main()
{
	int N, C;

	while(cin >> N >> C) {
		Grafo g{N};

		while(C--) {
			int a, b;
			cin >> a >> b;

			a--; b--;
			g.ponArista(a, b);
		}

		ColocarGuardias colocarGuardias{g};

		try {
			int n = colocarGuardias.minimo_numero();
			cout << n << "\n";
		} catch(exception& e) {
			cout << "IMPOSIBLE\n";
		}

	};


	return 0;
}