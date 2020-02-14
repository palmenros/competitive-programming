//Autores: Martín Gómez y Pedro Palacios

#include <vector>
#include <iostream>

using namespace std;

struct Pos {
	int r, c;

	Pos(int r, int c) : r(r), c(c) {}

	bool operator==(const Pos& other) const {
		return r == other.r && c == other.c;
	}
	Pos() : r(0), c(0) {}
};

enum Pieza {
	torre = 0,
	reina = 1
};

struct Data {
	Pieza pieza;
	int r;
	Data(Pieza p, int r) : pieza(p), r(r) {}
	Data() {}
};

typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<Pos> vp;
typedef vector<Data> vd;
typedef vb& vbr;
typedef vd& vdr;
typedef const vp& cvpr;

/*
 * 	tipo enumerado Pieza {
 * 		torre,
 * 		reina
 * 	}
 *
 * 	tipo dato {
 * 		pieza : Pieza,
 * 		r	  : ent
 * 	}
 *
 * 	Sea n := T + R
 *
 *	Espacio de soluciones:
 *		(d0, ..., dn-1)		Cada columna tiene una torre/reina en una fila
 *
 *	Restriciones explicitas:
 *
 *		forall i : 0 <= i < n : 0 <= di.r < n		Cada fila es válida
 *
 *  Restricciones implicitas:
 *
 *  	diagPrincipal(a) := a.r - a.c
 *  	diagSecond(a) := a.r + a.c
 *
 *		(# i : 0 <= i < n : di.pieza = torre) = T && (# i : 0 <= i < n : di.pieza = reina) = R		Hay T torres y R reinas
 *		not exists a, b : a != b && sol[a] = sol[b]													No se amenazan en columnas
 *		not exists a=(sol[x], x), b =(sol[y], y) : a != b : diagPrincipal(a) = diagPrincipal(b) ||
 *	 			diagSecond(a) = diagSecond(b) && (a.pieza = reina || b.pieza = reina)				Las reinas no amenazan en diagonal
 *		forall c : 0 <= c < n : ( (sol[c], c) not in rotas )										No hay ninguna pieza en una casilla rota
 *
 */
void inglaterra_va(
	vdr sol,
	int k,
	vbr diagPrincipalesT,
	vbr diagSecundT,
	vbr diagPrincipalesR,
	vbr diagSecundR,
	vbr rows,
	cvpr rotas,
	int& count,
	int& remainingT,
	int& remainingR
	) {

	const int N = sol.size();
	for(int r = 0; r < N; r++) {
		sol[k].r = r;

		bool rota = false;
		Pos myPos(r, k);
		for(Pos p : rotas) {
			if(p == myPos) {rota = true; break;}
		}

		if(!rota && !rows[r]) {
			rows[r] = true;

			//Torre
			sol[k].pieza = torre;
			remainingT--;
			bool diagP = diagPrincipalesT[r-k + N], diagS = diagSecundT[r+k];
			diagPrincipalesT[r-k + N] = true;
			diagSecundT[r+k] = true;

			if(remainingT >= 0 && !(diagPrincipalesR[r-k + N]) && !(diagSecundR[r+k])) {
				//Completable
				if(k == N - 1) {
					count++;
				} else if (k < N - 1) {
					inglaterra_va(sol, k + 1, diagPrincipalesT, diagSecundT, diagPrincipalesR, diagSecundR, rows, rotas, count, remainingT, remainingR);
				}
			}
			remainingT++;
			diagPrincipalesT[r-k + N] = diagP;
			diagSecundT[r+k] = diagS;

			//Reina
			sol[k].pieza = reina;
			if(remainingR > 0 && !(diagPrincipalesT[r-k + N]) && !(diagSecundT[r+k]) && !(diagPrincipalesR[r-k + N]) && !(diagSecundR[r+k]) ) {
				remainingR--;
				diagPrincipalesR[r-k + N] = true;
				diagSecundR[r+k] = true;

				//Completable
				if(k == N - 1) {
					count++;
				} else if (k < N - 1) {
					inglaterra_va(sol, k + 1, diagPrincipalesT, diagSecundT, diagPrincipalesR, diagSecundR, rows, rotas, count, remainingT, remainingR);
				}

				remainingR++;
				diagPrincipalesR[r-k + N] = false;
				diagSecundR[r+k] = false;
			}

			rows[r] = false;
		}

	}
}

int inglaterra(int T, int R, cvpr rotas) {
	const int N = T + R;
	vd sol(N);
	vb diagPT(2*N), diagST(2*N), diagPR(2*N), diagSR(2*N), rows(N);
	int count = 0;
	inglaterra_va(sol, 0, diagPT, diagST, diagPR, diagSR, rows, rotas, count, T, R);
	return count;
}

int main() {
	int T, R, nRotas;
	while(cin >> T >> R) {
		cin >> nRotas;

		vp rotas;
		for(int i = 0; i < nRotas; i++) {
			int r, c;
			cin >> r >> c;
			rotas.push_back(Pos(r-1, c-1));
		}

		cout << inglaterra(T, R, rotas) << endl;
	}

	return 0;
}