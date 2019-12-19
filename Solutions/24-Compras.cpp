//Autores: Martín Gómez Abejón y Pedro Palacios Almendros

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

typedef vector<int> vi;
typedef const vector<int> cvi;
typedef vector<vi> vii;
typedef const vii cvii;

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

void compra_va(
		vi& sol,
		int k,
		int S,
		int P,
		int coste,
		cvii& precios,
		vi& restantes,
		cvi& minRestantes,
		int& min
	)
{
	for(int i = 0; i < S; i++) {
		sol[k] = i;
		restantes[i]--;
		int nuevoCoste = coste + precios[i][k];

		if(restantes[i] >= 0 && nuevoCoste + minRestantes[k] < min) {
			//completable
			if(k == P - 1) {
				//Ver si es mejor optimización
				if(nuevoCoste <= min) {
					min = nuevoCoste;
				}
			} else if(k < P - 1){
				compra_va(sol, k + 1, S, P, nuevoCoste, precios, restantes, minRestantes, min);
			}

		}

		restantes[i]++;
	}

}

bool compra(int& minimoPrecio, int S, int P, cvii& precios, cvi& minRestantes) {
	minimoPrecio = INT_MAX;
	vi sol(P);
	vi restantes(S, 3);

	compra_va(sol, 0, S, P, 0, precios, restantes, minRestantes, minimoPrecio);

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

		for(int s = 0; s < S; s++) {
			for(int p = 0; p < P; p++) {
				cin >> precios[s][p];
				minProductos[p] = std::min(minProductos[p], precios[s][p]);
			}
		}

		int sum = 0;

		for(int p = P -1; p >= 0; p--) {
			int val = minProductos[p];
			minProductos[p] = sum;
			sum += val;
		}

		int min;
		if(compra(min, S, P, precios, minProductos)) {
			cout << min << endl;
		} else {
			cout << "Sin solucion factible" << endl;
		}

	}

	return 0;
}