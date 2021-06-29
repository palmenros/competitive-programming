#include <iostream>
#include <functional>
#include <queue>
using namespace std;

bool resuelveCaso()
{
	//El coste mínimo se obtiene cuando la primera suma es la de los dos elementos menores
	long long int n;
	cin >> n;
	if (!n) { return false; }
	priority_queue<long long int, vector<long long int>, greater<long long int>> prQueue;
	while (n--)
	{
		long long int aux;
		cin >> aux;
		prQueue.push(aux);
	}
	long long int costeTotal = 0;
	while (prQueue.size() >= 2)
	{
		long long int a = prQueue.top();
		prQueue.pop();
		long long int b = prQueue.top();
		prQueue.pop();
		costeTotal += (a + b);
		prQueue.push(a + b);
	}
	cout << costeTotal << '\n';
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}