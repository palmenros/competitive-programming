//Autores: Marta Gago Macías y Pedro Palacios Almendros

#include <vector>
#include <iostream>

using namespace std;

// {N >= 0 && D >= 0}
// fun(cotas[0...N] de ent, D ent) dev r : bool
bool hayDiferenciaMayorQueD(int D, const vector<int>& cotas)
{
	const int N = cotas.size();
	bool r = false;
	int n = 1;
	int s = 0;

	// Función de cota: N - n

	//Definiciones auxiliares:
	// crec(a, b) := ( forall i : a < i <= b : cotas[i] < cotas[i - 1] )
	// sum(a, b) :=  cotas[b] - cotas[a]

	// Invariante: 
	// 1 <= n <= N														&& 
	// s = min p : 0 <= p < n && crec(p, n - 1) : p						&&
	// r = (exists p, q : 0 <= p < q < n && crec(p, q) : sum(p, q) > D)

	while (n != N && !r) {
		
		int diff = cotas[n] - cotas[n - 1];

		if (diff > 0) {
			r = r || (cotas[n] - cotas[s] > D);
		} else {
			s = n;
		}

		n++;
	}

	return r;
}
// { r = (exists p, q : 0 <= p < q < N && crec(p, q) : sum(p, q) > D) } 

int main()
{
	int D;
	while (cin >> D)
	{
		int N;
		cin >> N;
		vector<int> cotas;

		for (int i = 0; i < N; i++) {
			int tmp;
			cin >> tmp;
			cotas.push_back(tmp);
		}

		if (hayDiferenciaMayorQueD(D, cotas)) {
			cout << "NO APTA" << endl;
		} else {
			cout << "APTA" << endl;
		}

	}

	return 0;
}