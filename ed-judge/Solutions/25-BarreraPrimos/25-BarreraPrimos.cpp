//
// Created by pedro on 20/3/20.
//

#include "../bintree_eda.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<bool> criba_eratostenes(int N)
{
	vector<bool> primes(N, true);
	primes[0] = false;
	primes[1] = false;

	for(int i = 2; i*i <= N ; i++) {
		if(primes[i]) {
			//Delete all multiples
			for(int j = 2*i; j < N; j += i) {
				primes[j] = false;
			}
		}
	}

	return primes;
}

struct Result {
	bool found;
	int nodo;
	int profundidad;

	Result(bool found)
		: found(found)
	{}

	Result(int nodo, int profundidad)
		: nodo(nodo), profundidad(profundidad), found(true)
	{}
};

struct Nodo {
	bintree<int> bt;
	int profundidad;

	Nodo(bintree<int> bt, int profundidad)
		: bt(bt), profundidad(profundidad)
	{}
};

//Coste lineal: Recorrido por niveles
Result barrera_primos(const vector<bool>& primes, const bintree<int>& bt)
{
	if(bt.empty()) {
		return {false};
	}

	queue<Nodo> q;
	q.push({bt, 1});

	while(!q.empty()) {
		//El primero que encontremos será el que satisfaga las condiciones requeridas
		Nodo n = q.front();
		q.pop();

		auto val = n.bt.root();

		if(!primes[val]) {

			//¿Es solución valida?
			if(val % 7 == 0) {
				return {val, n.profundidad};
			}

			//Agregar hijo izquierdo y derecho
			auto izq = n.bt.left();
			auto dch = n.bt.right();

			if(!izq.empty()) {
				q.push({izq, n.profundidad + 1});
			}

			if(!dch.empty()) {
				q.push({dch, n.profundidad + 1});
			}
		}

	}

	//Si hemos llegado aquí es que no se ha encontrado ninguno
	return {false};
}

int main()
{
	const int COTA_SUPERIOR_NUMEROS = 5001;
	auto primes = criba_eratostenes(COTA_SUPERIOR_NUMEROS);

	int N;
	cin >> N;
	while(N--) {
		auto bt = leerArbol<int>(-1);
		auto res = barrera_primos(primes, bt);

		if(!res.found) {
			cout << "NO HAY" << endl;
		} else {
			cout << res.nodo << " " << res.profundidad << endl;
		}
	}

	return 0;
}