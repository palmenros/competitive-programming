// Autor: Pedro Palacios Almendros
#include <iostream>

using namespace std;

typedef long long int lli;
typedef unsigned long long int ulli;

ulli longitud(unsigned int n) {
	ulli one = 1;
	return (one << (n + 2)) - n - 4;
}

/*
 * repetir(letra, n): | letra							si n = 1
 * 					  | letra + repetir(letra, n - 1) 	caso contrario
 *
 * cadena_grito(n): | "BUH" 														si n = 1
 * 					| cadena_grito(n-1) + repetir("U", n)  + cadena_grito(n-1)		caso contrario
 *
 * Precondición:
 * { n > 0, 0 <= k < longitud(cadena_grito(n)) }
 *
 * fun letra(n : ent, k : ent) dev c : char
 *
 * Postcondición:
 * { c = cadena_grito(n)[k] }
 */
char letra(unsigned int n, ulli k) {
	if(n == 1) {return "BUH"[k];}

	ulli len = longitud(n - 1);
	if(k < len) {
		return letra(n - 1, k);
	} else if (k == len) {
		return 'B';
	} else if (k < len + 2 + n - 1) {
		return 'U';
	} else if (k == len + 2 + n - 1) {
		return 'H';
	} else {
		return letra(n - 1, k - len - 2 - n);
	}

}

int main()
{
	unsigned int n;
	ulli k;
	while(cin >> n >> k) {
		cout << letra(n, k - 1) << endl;
	}

	return 0;
}