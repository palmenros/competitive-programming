#include <iostream>
#include <climits>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {

	int c, m, n;

	while (cin >> c >> m >> n && !(c == 0 && m == 0 && n == 0)) {
		n++;

		int maximo = INT_MIN, minimo = INT_MAX, anterior, peldanoAnterior;
		bool good = true;
		
		cin >> anterior;

		for (int i = 1; i < n; i++) {
			int val;
			cin >> val;

			if (good)
			{
				int peldano = val - anterior;

				maximo = max(maximo, peldano);
				minimo = min(minimo, peldano);

				if (i != 1) {
					
					if (abs(maximo - minimo) > m || abs(peldano - peldanoAnterior) > c) {
						good = false;
					}

				}

				anterior = val;
				peldanoAnterior = peldano;
			}

		}

		if (good) {
			cout << "Ok" << endl;
		} else {
			cout << "Tropiezo" << endl;
		}
	}


}