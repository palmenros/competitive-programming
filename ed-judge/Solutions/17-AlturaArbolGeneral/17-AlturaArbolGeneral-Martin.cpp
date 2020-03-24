#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;


int resuelveCaso()
{
	int k;
	cin >> k;
	int resultado = 0;
	for (int i = 0; i < k; i++)
	{
		resultado = max(resultado, resuelveCaso());
	}
	resultado++;
	return resultado;
}

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << resuelveCaso() << "\n";
	}
}