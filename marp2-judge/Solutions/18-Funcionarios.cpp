//
// Created by pedro on 16/4/21.
//

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include "Matriz.h"
#include <climits>

using namespace std;

typedef long long ll;

struct Nodo {
	vector<int> sol;
	vector<bool> used;

	ll cota_optimista;
	ll coste_real;
	ll cota_pesimista;

	Nodo(ll cotaOptimista, ll cotaPesimista, int N)
		: cota_optimista(cotaOptimista), used(N, false), coste_real(0), cota_pesimista(cotaPesimista)
	{
		sol.reserve(N);
	}

	bool operator<(const Nodo &rhs) const
	{
		return cota_optimista < rhs.cota_optimista;
	}
	bool operator>(const Nodo &rhs) const
	{
		return rhs < *this;
	}
	bool operator<=(const Nodo &rhs) const
	{
		return !(rhs < *this);
	}
	bool operator>=(const Nodo &rhs) const
	{
		return !(*this < rhs);
	}
};

void calcula_estimaciones(const Matriz<ll>& T, vector<ll>& opt, vector<ll>& pes)
{
	//Calculo de los mínimos y máximos por filas
	const int N = T.numcols();
	vector<ll> rapido(N, 0), lento(N, 0);

	for(int i = 0; i < N; i++) {
		rapido[i] = T[i][0];
		lento[i] = T[i][0];
		for(int j = 1; j < N; ++j) {
			rapido[i] = min(rapido[i], T[i][j]);
			lento[i] = max(lento[i], T[i][j]);
		}
	}

	//Calculo de las estimaciones
	opt[N] = 0; pes[N] = 0;

	for(int i = N-1; i >= 0; --i) {
		opt[i] = opt[i + 1] + rapido[i];
		pes[i] = pes[i + 1] + lento[i];
	}
}

ll min_tiempos(int N, const Matriz<ll>& mat) {
	priority_queue<Nodo, vector<Nodo>, greater<Nodo> > pq;
	ll coste_mejor = INT_MAX;

	vector<ll> opt(N+1, 0), pes(N+1, 0);
	calcula_estimaciones(mat, opt, pes);

	//vector<ll> opt(N, -1), pes(N, INT_MAX);


	pq.emplace(opt[0], pes[0], N);

	while(!pq.empty() && pq.top().cota_optimista <= coste_mejor) {
		auto e = pq.top();
		pq.pop();

		for(int i = 0; i < N; i++) {
			if(e.used[i]) {
				continue;
			}

			auto el = e;

			el.sol.push_back(i);
			el.used[i] = true;
			el.coste_real += mat[el.sol.size() - 1][i];

			if(el.sol.size() == N) {
				//Es solucion
				if(el.coste_real <= coste_mejor) {
					coste_mejor = el.coste_real;
				}
			} else {
				el.cota_optimista = el.coste_real + opt[el.sol.size()];
				el.cota_pesimista = el.coste_real + pes[el.sol.size()];

				if(el.cota_optimista < coste_mejor) {
					pq.push(el);
					coste_mejor = min(coste_mejor, el.cota_pesimista);
				}
			}
		}
	}

	return coste_mejor;
}

int main()
{
	int N;
	while(cin >> N && N != 0) {
		Matriz<ll> mat(N, N, 0);
		for(int r = 0; r < N; r++) {
			for(int c = 0; c < N; c++) {
				cin >> mat[r][c];
			}
		}

		cout << min_tiempos(N, mat) << endl;

	}

	return 0;
}