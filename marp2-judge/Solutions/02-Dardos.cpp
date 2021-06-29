#include <iostream>
#include "EnterosInf.h"
#include "Matriz.h"

using namespace std;

EntInf suma(int i, int j, const vector<int>& v, Matriz<EntInf>& m) {
	if(m[i][j] == -1) {
		//Casos base
		if(j == 0) {
			m[i][j] = 0;
		} else if (i == 0) {
			m[i][j] = Infinito;
		} else {
			//Caso recursivo

			if(v[i-1] > j) {
				m[i][j] = suma(i-1, j, v, m);
			} else {
				m[i][j] = min(suma(i - 1, j, v, m), suma(i, j - v[i - 1], v, m) + 1);
			}
		}

	}

	return m[i][j];
}

void escribir_solucion(int i, int j, const vector<int>& v, const Matriz<EntInf>& m) {

	if(j == 0 || i == 0) {
		//Hemos terminado
		return;
	}



	if(v[i-1] > j) {
		//No cogemos este
		escribir_solucion(i-1, j, v, m);
	} else if(m[i][j] == m[i][j - v[i - 1]] + 1) {
		//Cogemos el valor
		cout << " " << v[i - 1];
		escribir_solucion(i, j - v[i - 1], v, m);
	} else {
		//No cogemos este
		escribir_solucion(i-1, j, v, m);
	}

}

int main() {

	int C, S;
	while(cin >> C >> S) {
		vector<int> v(S);
		for(int i = 0; i < S; ++i) {
			cin >> v[i];
		}

		Matriz<EntInf> m(S+1, C+1, -1);
		auto res = suma(S, C, v, m);

		if(res == Infinito) {
			cout << "Imposible" << endl;
		} else {
			cout << res << ":";

			//Reconstruir
			escribir_solucion(S, C, v, m);

			cout << endl;
		}


	}


	return 0;
}