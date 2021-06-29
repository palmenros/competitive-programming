#include <iostream>
#include <vector>
#include "Matriz.h"
#include "EnterosInf.h"

using namespace std;

typedef long long ll;

struct Data {
	bool esPosible;
	ll numFormas;
	EntInf minCordeles;
	EntInf minCoste;

	Data(bool esPosible, ll numFormas, const EntInf &minCordeles, const EntInf &minCoste)
		: esPosible(esPosible), numFormas(numFormas), minCordeles(minCordeles), minCoste(minCoste)
	{}
};

Data dp(int i, int j, Matriz<bool>& esPosible, Matriz<ll>& formas, Matriz<EntInf>& minCordeles, Matriz<EntInf>& minCoste, const vector<int>& l, const vector<int>& c)
{
	if(formas[i][j] == -1) {

		//** Casos base +/

		if(j == 0) {
			esPosible[i][j] = true;
			formas[i][j] = 1;
			minCordeles[i][j] = 0;
			minCoste[i][j] = 0;
		} else if(i == 0) {
			esPosible[i][j] = false;
			formas[i][j] = 0;
			minCordeles[i][j] = Infinito;
			minCoste[i][j] = Infinito;
		} else {
			//** Caso recursivo +/

			Data dj = dp(i-1, j, esPosible, formas, minCordeles, minCoste, l, c);

			if(l[i - 1] > j) {
				esPosible[i][j] = dj.esPosible;
				formas[i][j] = dj.numFormas;
				minCordeles[i][j] = dj.minCordeles;
				minCoste[i][j] = dj.minCoste;
			} else {
				Data djli = dp(i-1, j-l[i - 1], esPosible, formas, minCordeles, minCoste, l, c);

				esPosible[i][j] = dj.esPosible || djli.esPosible;
				formas[i][j] = dj.numFormas + djli.numFormas;
				minCordeles[i][j] = min(dj.minCordeles, djli.minCordeles + 1);
				minCoste[i][j] = min(dj.minCoste, djli.minCoste + c[i - 1]);
			}

		}
	}

	return {esPosible[i][j], formas[i][j], minCordeles[i][j], minCoste[i][j]};
}


int main()
{
	int N, L;
	while(cin >> N >> L) {

		vector<int> l, c;

		for(int i = 0; i < N; i++) {
			ll li, ci;
			cin >> li >> ci;
			l.push_back(li);
			c.push_back(ci);
		}

		Matriz<bool> esPosible(N+1, L + 1, false);
		Matriz<ll> formas(N+1, L+1, -1);
		Matriz<EntInf> minCordeles(N+1, L+1, -1);
		Matriz<EntInf> minCoste(N+1, L+1, -1);

		Data d = dp(N, L, esPosible, formas, minCordeles, minCoste, l, c);

		if(d.esPosible) {
			cout <<"SI" << " " << d.numFormas << " " << d.minCordeles << " " << d.minCoste << endl;
		} else {
			cout << "NO" << endl;
		}



	}

	return 0;
}