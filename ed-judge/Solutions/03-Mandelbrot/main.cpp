#include "complejo.h"
#include <iostream>
using namespace std;


void resuelveCaso()
{
	float f1;
	float f2;
	int iter;
	cin >> f1 >> f2 >> iter;
	complejo c(f1, f2);
	complejo iterado(0, 0);
	int i = 0;
	while (i < iter && iterado.modulo() <= 2)
	{
		i++;
		iterado = iterado * iterado + c;
	}
	if (iterado.modulo() > 2)
	{
		cout << "NO" << endl;
	}
	else
	{
		cout << "SI" << endl;
	}
}

int main()
{
	int n;
	cin >> n;
	for (int i = 0;i<n;i++)
	{
		resuelveCaso();
	}
	return 0;
}

