//Autores: Martín Gómez Abejón y Pedro Palacios Almendros

#include <vector>
#include <iostream>
#include <climits>

using namespace std;

// (n > 0) && ( 0 <= pos < n )
bool isWellDivided(const vector<int>& v, int pos)
{
	int max = INT_MIN;

	//Invariante: (i >= 0) && ( max = máx j : 0 < j <= i : v[j] )
	//Cota: pos - i
	for (int i = 0; i <= pos; i++)
	{
		max = (max > v[i]) ? max : v[i];
	}
	int i = pos + 1;
	bool isWellDivided = true;
	
	//Invariante (i >= pos + 1) && ( forall j : pos < j < i : (forall k : 0 <= k <= pos : v[j] > v[k] ))
	//Cota: n - i
	while (i < v.size() && isWellDivided)
	{
		isWellDivided = v[i] > max;
		i++;
	}
	return isWellDivided;
}
// ret = ( forall i : pos < i < n : (forall j : 0 <= j <= pos : v[i] > v[j] ))

int main()
{
	int nCasos;

	cin >> nCasos;

	for (int i = 0; i < nCasos; i++)
	{
		int longitud;
		int pos;
		cin >> longitud >> pos;
		vector<int> v;
		v.reserve(longitud);
		for (int j = 0; j < longitud; j++)
		{
			int temp;
			cin >> temp;
			v.push_back(temp);
		}
		if (isWellDivided(v, pos))
		{
			cout << "SI" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}
}