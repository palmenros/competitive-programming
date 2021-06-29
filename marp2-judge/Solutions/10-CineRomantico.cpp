//
// Created by pedro on 15/4/21.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include "Matriz.h"
#include <climits>

using namespace std;

struct Pelicula {
	int comienzo;
	int final;
	int duracion;

	Pelicula(int comienzo, int final, int duracion)
		: comienzo(comienzo), final(final), duracion(duracion)
	{}

	bool operator<(const Pelicula &rhs) const {
		return comienzo < rhs.comienzo;
	}
};

int max_duracion(int i, int j, Matriz<int>& dp, const vector<Pelicula>& v, int N) {
	//j indice comienzo ultima pelicula
	if(i == 0) {
		return 0;
	}

	if(dp[i][j] == -1) {
		if(j == N || v[j].comienzo > v[i-1].final) {
			//Puedo ver la pelicula i
			dp[i][j] = max( max_duracion(i-1, j, dp, v, N), max_duracion(i-1, i-1, dp, v, N) + v[i-1].duracion );
		} else {
			//No puedo ver la pelicula i
			dp[i][j] = max_duracion(i-1, j, dp, v, N);
		}
	}

	return dp[i][j];
}

int main()
{
	int N;
	while(cin >> N && N != 0) {
		vector<Pelicula> v;

		for(int i = 0; i < N; i++) {
			int hh, mm, d;
			char tmp;
			cin >> hh >> tmp >> mm >> d;
			v.emplace_back(hh * 60 + mm, hh*60 + mm + d + 10 - 1, d);
		}

		Matriz<int> dp(N+1, N+1, -1);

		sort(v.begin(), v.end());

		cout << max_duracion(N, N, dp, v, N) << "\n";
	}

	return 0;
}