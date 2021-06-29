//
// Created by pedro on 15/4/21.
//

#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include "Matriz.h"

using namespace std;

enum Simbolo {
	A = 0,
	B = 1,
	C = 2
};

Simbolo mult[3][3] = {
	{B, B, A},
	{C, B, A},
	{A, C, C}
};

enum class Posibilidades {
	Ninguna = 0,

	A = 1,
	B = 2,
	C = 4,

	NoInicializado = 100
};

Posibilidades symbToPos(Simbolo s) {
	switch(s) {
	case A:
		return Posibilidades::A;
	case B:
		return Posibilidades::B;
	case C:
		return Posibilidades::C;
	default:
		assert(false);
	}
}

Simbolo posToSymb(Posibilidades p) {
	switch(p) {
	case Posibilidades::A:
		return A;
	case Posibilidades::B:
		return B;
	case Posibilidades::C:
		return C;
	default:
		assert(false);
	}
}

inline Posibilidades operator|(Posibilidades a, Posibilidades b)
{
	return static_cast<Posibilidades>(static_cast<int>(a) | static_cast<int>(b));
}

inline Posibilidades operator&(Posibilidades a, Posibilidades b)
{
	return static_cast<Posibilidades>(static_cast<int>(a) & static_cast<int>(b));
}

inline Posibilidades operator*(Posibilidades a, Posibilidades b)
{
	Posibilidades res = Posibilidades::Ninguna;
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if((a & Posibilidades(1 << i) ) != Posibilidades::Ninguna && (b & Posibilidades(1 << j)) != Posibilidades::Ninguna) {
				res = res | symbToPos(mult[ posToSymb(Posibilidades(1 << i)) ][posToSymb(Posibilidades(1 << j))]);
			}
		}
	}
	return res;
}

Posibilidades posible(int i, int j, const vector<Simbolo>& v, Matriz<Posibilidades>& dp )
{
	assert(i <= j);

	if(i == j) {
		return symbToPos(v[i]);
	}

	if(dp[i][j] == Posibilidades::NoInicializado) {
		Posibilidades res = Posibilidades::Ninguna;

		for(int k = i; k < j; k++) {
			res = res | posible(i, k, v, dp) * posible(k+1, j, v, dp);
		}

		dp[i][j] = res;
	}

	return dp[i][j];
}

int main()
{
	string str;
	while(cin >> str) {
		vector<Simbolo> v(str.size());
		for(int i = 0; i < str.size(); i++) {
			v[i] = Simbolo(str[i]-'a');
		}

		Matriz<Posibilidades> dp(str.size(), str.size(), Posibilidades::NoInicializado);
		auto res = posible(0, str.size() - 1, v, dp);

		if((res & Posibilidades::A) != Posibilidades::Ninguna) {
			cout << "SI" << endl;
		} else {
			cout << "NO" << endl;
		}

	}

	return 0;
}