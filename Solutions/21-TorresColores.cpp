//Autores: Martín Gómez y Pedro Palacios

#include <vector>
#include <iostream>

using namespace std;

typedef vector<int> vi;
typedef vi& vir;

enum Color {
	azul = 0,
	rojo = 1,
	verde = 2
};

/*
 * Espacio de soluciones:
 * (c1, ..., cn) := Color de la pieza i-ésima
 *
 * Restriciones implícitas:
 *  ci in [0, 2]
 * Restricciones explícitas:
 *
 * colocadas(c) := (# i : 0 <= i < n : i = c )
 * colocadas_hasta(c, j) := (# i : 0 <= i <= j : i = c )
 *
 * forall c color : ( colocadas(c) = disponibles[c] )	&&
 * c1 = rojo &&
 * colocadas(rojo) > colocadas(azul) + colocadas(verde) &&
 * forall i : 1 <= i < n: ((sol[i-1] = verde and sol[i] = verde) and colocadas_hasta(verde, i) <= colocadas_hasta(azul,i) )
*/
void torres_va(vir sol, vir disponibles, vir colocadas, int k, bool& found, const string colores[]) {
	const int n = sol.size();

	for(int i = 0; i < 3; i++) {
		disponibles[i]--;
		colocadas[i]++;
		sol[k] = i;

		if(disponibles[i] >= 0 && !(sol[k-1] == verde && i == verde) && colocadas[verde] <= colocadas[azul]) {
			if(k == n - 1 && colocadas[rojo] > colocadas[azul] + colocadas[verde]) {
				found = true;
				//Print
				for(int j = 0; j < n - 1; j++) {
					cout << colores[ sol[j] ] << " ";
				}
				cout << colores[ sol[n-1] ] << endl;

			} else if(k < n - 1){
				torres_va(sol, disponibles, colocadas, k + 1, found, colores);
			}
		}

		disponibles[i]++;
		colocadas[i]--;
	}
}

bool torres(vir disponibles, int n) {
	string colores[] = {"azul", "rojo", "verde"};
	bool found = false;
	vi sol(n);

	sol[0] = rojo;
	disponibles[rojo]--;
	if(disponibles[rojo] < 0) {
		return false;
	}

	vi colocadas {0, 0, 0};
	colocadas[rojo] = 1;

	torres_va(sol, disponibles, colocadas, 1, found, colores);
	return found;
}

int main()
{
	int n, a, r, v;
	while(cin >> n >> a >> r >> v && !(n == 0 && a == 0 && r == 0 && v == 0)) {
		vi disponibles = { a, r, v};
		if(!torres(disponibles, n)) {
			cout << "SIN SOLUCION" << endl;
		}
		cout << endl;
	}

	return 0;
}