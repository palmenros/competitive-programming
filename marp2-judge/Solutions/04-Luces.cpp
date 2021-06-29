#include <iostream>
#include "Matriz.h"
#include "EnterosInf.h"

using namespace std;
typedef long long ll;

struct Data {
	EntInf coste;
	EntInf potencia;

	Data(const EntInf &coste, const EntInf &potencia)
		: coste(coste), potencia(potencia)
	{}
};

Data minCoste(ll i, ll j, const vector<ll>& c, const vector<ll>& p, Matriz<Data>& dp, int threshold) {

	//Casos base
	if(0 >= j && j >= threshold) {
		return Data{0, 0};
	}

	if(i == 0 || j < threshold) {
		return Data{Infinito, Infinito};
	}

	if(dp[i][j].coste == -1) {
		Data cogiendo = minCoste(i, j-p[i-1], c, p, dp, threshold);
		Data noCogiendo = minCoste(i-1, j, c, p, dp, threshold);

		cogiendo.coste = cogiendo.coste + c[i-1];
		cogiendo.potencia = cogiendo.potencia + p[i-1];

		if(
			(cogiendo.coste < noCogiendo.coste) ||
			((cogiendo.coste == noCogiendo.coste) && (cogiendo.potencia < noCogiendo.potencia))
			) {
			//Coger
			dp[i][j] = cogiendo;
		} else {
			//No coger
			dp[i][j] = noCogiendo;
		}
	}

	return dp[i][j];
}

int main()
{
	int N, PMax, PMin;
	while(cin >> N >> PMax >> PMin) {
		vector<ll> c(N);
		vector<ll> p(N);

		for(int i = 0; i < N; i++) {
			cin >> p[i];
		}

		for(int i = 0; i < N; i++) {
			cin >> c[i];
		}

		Matriz<Data> dp (N + 1, PMin + 1, Data{-1, -1});
		auto res = minCoste(N, PMin, c, p, dp, PMin - PMax);

		if(res.coste == Infinito) {
			cout << "IMPOSIBLE" << endl;
		} else {
			cout << res.coste << " " << res.potencia << endl;
		}

	}

	return 0;
}