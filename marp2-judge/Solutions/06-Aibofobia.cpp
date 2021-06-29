#include <string>
#include <iostream>
#include "Matriz.h"
#include "EnterosInf.h"

using namespace std;

typedef int Ent;

Ent minLetras(int i, int j, const string& str, Matriz<Ent>& dp) {
	if(dp[i][j] == -1) {
		//Casos base
		if(i == j) {
			dp[i][j] = 0;
		} else if (i > j) {
			dp[i][j] = 0;
		} else {
			//Casos recursivos

			if(str[i] == str[j]) {
				dp[i][j] = minLetras(i+1, j-1, str, dp);
			} else {
				dp[i][j] = min(minLetras(i, j-1, str, dp),  minLetras(i+1, j, str, dp)) + 1;
			}
		}
	}

	return dp[i][j];
}

void reconstruir(int i, int j, int si, int sj, string& res, const string& str, const Matriz<Ent>& dp)
{
	if(i > j) {
		return;
	}

	if(i == j) {
		res[i] = str[si];
		return;
	}

	if(str[si] == str[sj]) {
		res[i] = str[si];
		res[j] = str[si];
		reconstruir(i+1, j-1, si+1, sj-1, res, str, dp);
	} else if(dp[si+1][sj] + 1 == dp[si][sj]){
		res[i] = str[si];
		res[j] = str[si];
		reconstruir(i+1, j-1, si+1, sj, res, str, dp);
	} else {
		res[i] = str[sj];
		res[j] = str[sj];
		reconstruir(i+1, j-1, si, sj-1, res, str, dp);
	}
}

string minPalindromo(const string& str) {
	Matriz<Ent> dp{int(str.size()), int(str.size()), -1};
	Ent tam = minLetras(0, str.size() - 1, str, dp);

	if(tam == 0) {
		return str;
	}

	string res(tam + str.size(), '?');
	reconstruir(0, res.size() - 1, 0, str.size() - 1, res, str, dp);
	return res;
}

int main()
{
	string str;

	while(cin >> str) {
		auto s = minPalindromo(str);
		cout << (s.size() - str.size()) << " " << s << endl;
	}

	return 0;
}