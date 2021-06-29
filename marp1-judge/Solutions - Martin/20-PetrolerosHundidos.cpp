#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "ConjuntosDisjuntos.h"
using namespace std;
constexpr pair<int, int> direcciones[] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };
bool resuelveCaso()
{
	int r, c; cin >> r >> c; if (!cin) { return false; }
	//Utilizamos ConjuntosDisjuntos para hacer componentes conexas de manchas
	ConjuntosDisjuntos datosComp(r * c);
	int maximoT = 0;
	vector<vector<bool>> v(r, vector<bool>(c, false));
	string aux;
	getline(cin, aux);
	for (int i = 0; i < r; i++)
	{
		getline(cin, aux);
		for (int j=0;j<c;j++)
		{
			if (aux[j] == '#')
			{
				v[i][j] = true;
				for (auto d : direcciones)
				{
					if (i + d.first >= 0 && i + d.first < r && j + d.second >= 0 && j + d.second < c && v[i + d.first][j + d.second])
					{
						datosComp.unir(i * c + j, (i + d.first) * c + (j + d.second));
						
					}
				}
				maximoT = max(maximoT, datosComp.cardinal(i * c + j));
			}
		}
	}
	cout << maximoT;
	int n; cin >> n;
	while (n--)
	{
		int i, j;
		cin >> i >> j; i--; j--;
		v[i][j] = true;
		for (auto d : direcciones)
		{
			if (i + d.first >= 0 && i + d.first < r && j + d.second >= 0 && j + d.second < c && v[i + d.first][j + d.second])
			{
				datosComp.unir(i * c + j, (i + d.first) * c + (j + d.second));
				
			}
		}
		maximoT = max(maximoT, datosComp.cardinal(i * c + j));
		cout << " " << maximoT;
	}
	cout << "\n";
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}