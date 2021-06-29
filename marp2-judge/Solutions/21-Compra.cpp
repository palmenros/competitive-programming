#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <algorithm>

using namespace std;

typedef vector<int> vi;
typedef const vector<int> cvi;
typedef vector<vi> vii;
typedef const vii cvii;


struct Node {
	vi sol;
	int k;
	vi restantes;
	cvi& minRestantes;
	cvi& maxRestantes;
	int coste;

	explicit Node(int P, int S, cvi& minRestantes, cvi& maxRestantes)
		: sol(P, 0), k(0), restantes(S, 3), coste(0), minRestantes(minRestantes), maxRestantes(maxRestantes)
	{
	}

	Node& operator=(const Node& o) {
		sol = o.sol;
		k = o.k;
		restantes = o.restantes;
		coste = o.coste;

		return *this;
	}


	int cota_optimista() const {
		if(k < minRestantes.size()) {
			return coste + minRestantes.at(k);
		}
		return coste;
	}

	int cota_pesimista() const {
		return coste + maxRestantes.at(k);
	}

	bool operator<(const Node &rhs) const
	{
		return cota_optimista() > rhs.cota_optimista();
	}
	bool operator>(const Node &rhs) const
	{
		return rhs < *this;
	}
	bool operator<=(const Node &rhs) const
	{
		return !(rhs < *this);
	}
	bool operator>=(const Node &rhs) const
	{
		return !(*this < rhs);
	}
};

/*
 * Espacio de soluciones:
 *
 * (s0,..., sn-1)		Supermercado en el que compra el iésimo producto
 *
 * Restriciones explicitas:
 *
 *		forall i : 0 <= i < n : 0 <= si < S		Cada supermercado es válido
 *
 * Restricciones implícitas:
 *
 * 		forall s : 0 <= s < S : ((# i : 0 <= i < n : si = s) <= 3 )	Como mucho se compran 3 productos en un mismo supermercado
 */
bool compra(int& minimoPrecio, int S, int P, cvii& precios, cvi& minRestantes, cvi& maxRestantes) {
	minimoPrecio = INT_MAX;
	priority_queue<Node> pq;
	pq.emplace(P, S, minRestantes, maxRestantes);

	while(!pq.empty() && pq.top().cota_optimista() <= minimoPrecio) {
		auto el = pq.top();
		pq.pop();

		for(int i = 0; i < S; i++) {
			auto e = el;

			e.sol.at(e.k) = i;
			e.restantes.at(i)--;
			e.coste += precios.at(i).at(e.k);
			e.k++;

			if(e.restantes[i] >= 0 && e.cota_optimista() < minimoPrecio) {
				//completable
				if(e.k == P) {
					//Ver si es mejor optimización
					if(e.coste <= minimoPrecio) {
						minimoPrecio = e.coste;
					}
				} else if(e.k < P){
					pq.push(e);
					minimoPrecio = min(minimoPrecio, e.cota_pesimista());
				}

			}

		}

	}
	return minimoPrecio != INT_MAX;
}

int main() {
	int nCasos;
	cin >> nCasos;
	while(nCasos--) {
		int S, P;
		cin >> S >> P;
		vii precios(S, vi(P));

		vi minProductos(P, INT_MAX);
		vi maxProductos(P, INT_MIN);

		for(int s = 0; s < S; s++) {
			for(int p = 0; p < P; p++) {
				cin >> precios[s][p];
				minProductos[p] = std::min(minProductos[p], precios[s][p]);
				maxProductos[p] = std::max(maxProductos[p], precios[s][p]);
			}
		}

		int sumMin = 0;
		int sumMax = 0;

		for(int p = P-1; p >= 0; p--) {
			sumMin += minProductos[p];
			sumMax += maxProductos[p];
			minProductos[p] = sumMin;
			maxProductos[p] = sumMax;
		}

		int min;
		if(compra(min, S, P, precios, minProductos, maxProductos)) {
			cout << min << endl;
		} else {
			cout << "Sin solucion factible" << endl;
		}

	}

	return 0;
}
