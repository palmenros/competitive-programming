#include <iostream>
#include <algorithm>
#include <vector>
#include "Matriz.h"

using namespace std;


// max_grupos usando los conciertos 1..i con dinero j
int max_grupos(int i, int j, const vector<int>& valor, const vector<int>& coste, Matriz<int>& dp)
{
	if(j == 0 || i == 0) {
		return 0;
	}

	if(dp[i][j] == -1) {
		if(coste[i-1] <= j) {
			//Puedo ir al concierto i
			dp[i][j] = max(max_grupos(i-1, j, valor, coste, dp), valor[i-1] + max_grupos(i-1, j-coste[i-1], valor, coste, dp));
		} else {
			//No puedo ir al concierto i
			dp[i][j] = max_grupos(i-1, j, valor, coste, dp);
		}

	}

	return dp[i][j];
}


int main()
{
	int P, N;
	while(cin >> P >> N) {
		vector<int> valor(N), coste(N);

		for(int i = 0; i < N; i++) {
			cin >> valor[i] >> coste[i];
		}

		Matriz<int> dp(N+1, P+1, -1);

		cout << max_grupos(N, P, valor, coste, dp) << endl;
	}

	return 0;
}