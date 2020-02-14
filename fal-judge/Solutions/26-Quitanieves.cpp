//Autores: Martin Gomez Abejon y Pedro Palacios Almendros

#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<bool> vb;
typedef const vector<int> cvi;
typedef vector<vi> vii;
typedef const vii cvii;

/*
 * Espacio de soluciones:
 *
 * (m0,..., mc-1)		Máquina que limpia la iésima carretera (-1 es ninguna)
 *
 * Restriciones explicitas:
 *
 *		forall i : 0 <= i < C : -1 <= mi < M		Cada máquina es válida
 *
 * Restricciones implícitas:
 *
 * 		forall m : 0 <= m < M : ((# i : 0 <= i < C : mi = m) <= 1 )	 &&							Como mucho se usa una sola vez cada máquina
 * 		forall i : 0 <= i < C : (mi == -1) || anchurasCarreteras[i] >= anchurasMaquinas[mi]		Las anchuras se respetan
 */
void quitanieves_va(vi& sol, int k, int M, int C, cvi& anchurasMaquinas, cvi& anchurasCarreteras, cvii& calidades, vb& usadas, int calidad, int& max)
{
	//-1 representa que esta carretera no se limpia
	for(int i = -1; i < M; i++) {
		sol[k] = i;

		if(i == -1 || (!usadas[i] && anchurasCarreteras[k] >= anchurasMaquinas[i] ) ) {
			int nuevaCalidad = calidad;
			if(i != -1) {
				usadas[i] = true;
				nuevaCalidad += calidades[i][k];
			}

			//Optimizar
			if(k == C - 1) {

				if(nuevaCalidad > max) { max = nuevaCalidad;}

			} else {

				quitanieves_va(sol, k + 1, M, C, anchurasMaquinas, anchurasCarreteras, calidades, usadas, nuevaCalidad, max);

			}


			if(i != -1) { usadas[i] = false; }
		}

	}
}


int quitanieves(int M, int C, cvi& anchurasMaquinas, cvi& anchurasCarreteras, cvii& calidades)
{
	int max = 0;
	vi sol(C);
	vb usadas(M, false);

	quitanieves_va(sol, 0, M, C, anchurasMaquinas, anchurasCarreteras, calidades, usadas, 0, max);

	return max;
}

int main() {
	int nCasos;
	cin >> nCasos;

	while(nCasos--) {
		int M, C;
		cin >> M >> C;
		vi anchurasMaquinas(M);
		vi anchurasCarreteras(C);

		for(int i = 0; i < M; i++) {
			cin >> anchurasMaquinas[i];
		}

		for(int i = 0; i < C; i++) {
			cin >> anchurasCarreteras[i];
		}

		//calidades[m][c]
		vii calidades(M, vi(C));
		for(int m  = 0; m < M; m++) {
			for(int c = 0; c < C; c++) {
				cin >> calidades[m][c];
			}
		}

		cout << quitanieves(M, C, anchurasMaquinas, anchurasCarreteras, calidades) << endl;
	}

	return 0;
}