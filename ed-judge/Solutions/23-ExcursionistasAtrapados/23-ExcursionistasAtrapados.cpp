//
// Created by pedro on 17/3/20.
//

#include <iostream>
#include "../bintree_eda.h"

using namespace std;

struct Result {
	int numEquipos;
	int maxNumExcursionistas;

	Result(int numEquipos, int maxNumExcursionistas)
		: numEquipos(numEquipos), maxNumExcursionistas(maxNumExcursionistas)
	{
	}

	Result()
	{}
};

Result excursionista(const bintree<int>& bt)
{
	if(bt.empty()) {
		return Result(0, 0);
	}

	Result res, izq = excursionista(bt.left()), dch = excursionista(bt.right());
	res.maxNumExcursionistas =  bt.root() + max(izq.maxNumExcursionistas, dch.maxNumExcursionistas);

	res.numEquipos = izq.numEquipos + dch.numEquipos;
	if(res.numEquipos == 0 && bt.root() != 0) {
		res.numEquipos = 1;
	}

	return res;
}

int main()
{
	int N;
	cin >> N;
	while(N--) {
		Result res = excursionista(leerArbol(-1));
		cout << res.numEquipos << " " << res.maxNumExcursionistas << endl;
	}

	return 0;
}