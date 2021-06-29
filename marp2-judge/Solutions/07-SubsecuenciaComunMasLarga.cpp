#include <iostream>
#include <string>
#include "Matriz.h"

using namespace std;

int lcs(int i, int j, const string& a, const string& b, Matriz<int>& dp) {
	if(i == -1 || j == -1) {
		return 0;
	}

	if(dp[i][j] == -1) {
		if(a[i] == b[j]) {
			dp[i][j] = lcs(i-1, j-1, a, b, dp) + 1;
		} else {
			dp[i][j] = max( lcs(i-1, j, a, b, dp), lcs(i, j-1, a, b, dp) );
		}
	}

	return dp[i][j];
}

string subcadena_comun_mas_larga(const string& a, const string& b) {
	Matriz<int> dp(a.size(), b.size(), -1);
	int tam = lcs(a.size() - 1, b.size() - 1, a, b, dp);

	//Reconstruir
	string res(tam, '?');
	int i = a.size() - 1, j = b.size() - 1;

	while(tam > 0) {
		if(a[i] == b[j]) {
			res[tam - 1] = a[i];
			i--;
			j--;
			tam--;
		} else if (i >= 1 && dp[i][j] == dp[i-1][j]) {
			i--;
		} else {
			j--;
		}
	}

	return res;
}

int main()
{
	string a, b;
	while(cin >> a >> b) {
		cout << subcadena_comun_mas_larga(a, b) << endl;
	}

	return 0;
}