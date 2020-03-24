#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;

int resuelveCaso(int k)
{
	int z;
	cin >> z;
	if (!z && !k) //Si no hay nadie por debajo
	{
		return 1;
	}
	int res = 0;
	for (int i = 0; i < z; i++)
	{
		res += resuelveCaso((k?k-1:k));
	}
	return res;
}

int main()
{
	while (true)
	{
		int k;
		cin >> k;
		if (!cin) { return 0; }
		cout << resuelveCaso(k) << "\n";
	}
}