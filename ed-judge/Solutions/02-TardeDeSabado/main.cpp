using namespace std;
#pragma once
#include "pelicula.h"
#include <vector>
#include <algorithm>

int main()
{
	while (true)
	{
		int n;
		cin >> n;
		if (n == 0)
		{
			return 0;
		}
		vector<pelicula> v;
		v.reserve(n);
		for (int i = 0; i < n; i++)
		{
			pelicula p;
			cin >> p;
			v.push_back(p);
		}
		sort(v.begin(), v.end());
		for (int i = 0; i < n; i++)
		{
			cout << v[i] << "\n";
		}
		cout << "---" << "\n";
		
	}
}