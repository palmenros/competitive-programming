//Autor: Pedro Palacios

#include <iostream>
#include <cmath>

using namespace std;

/*
 *  n_digitos(n) := floor(log10(n)) + 1
 * 	polidivisible(n) := n > 0 && forall i : 0 <= i < n_digitos(n) : n / 10^(n_digitos(n) - i) = 0 (mod i)
 *
 *	{ polidivisible(raiz), n = n_digitos(raiz), maxDigitos > 0 }
 * 	fun gescribePolidivisibles(raiz : ent, n : ent, maxDigitos : ent) : dev s : conjunto de ent
 *  {
 *  	forall n : polidivisible(n) && n_digitos(n) <= maxDigitos : n pertenece a s &&
 *  	forall n : n pertenece a s : polidivisible(n) && n_digitos(n) <= maxDigitos
 *  }
 *
 */
void gescribePolidivisibles(long long raiz, int n, int maxDigitos) {

	if(n > maxDigitos) {
		return;
	}

	cout << raiz << endl;

	for(int i = 0; i < 10; i++) {
		long long num = raiz * 10 + i;
		if(num % (n + 1) == 0) {
			gescribePolidivisibles(num, n + 1, maxDigitos);
		}
	}
}

void escribePolidivisibles(long long raiz, int maxDigitos) {
	gescribePolidivisibles(raiz, floor(log10(raiz)) + 1, maxDigitos);
}

int main() {
	long long N;
	int D;
	while(cin >> N >> D) {
		escribePolidivisibles(N, D);
		cout << "---" << endl;
	}
	return 0;
}