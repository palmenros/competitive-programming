#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void resuelveCaso()
{
	int n, cap;
	cin >> n >> cap;
	vector<int> v;
	for (int i = 0; i < n; i++)
	{
		int aux;
		cin >> aux;
		v.push_back(aux);
	}
	sort(v.begin(), v.end());
	auto itderecho = v.end(); itderecho--;
	auto itizquierdo = v.begin();
	int asignadosTotales = 0;
	while (itizquierdo != itderecho)
	{
		if ((*itizquierdo) + (*itderecho) >= cap)
		{
			asignadosTotales++;
			itizquierdo++;
			if (itizquierdo != itderecho)
			{
				itderecho--;
			}
		}
		else
		{
			itizquierdo++;
		}
	}
	cout << asignadosTotales << "\n";
}

int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		resuelveCaso();
	}
	return 0;
}