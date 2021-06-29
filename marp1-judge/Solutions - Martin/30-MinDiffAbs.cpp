#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//El emparejamiento �ptimo es ordenar los dos vectores y emparejar los que tienen el mismo �ndice
//Alg. voraz
//Red. diferencias:
/**
* Si no fuera as�, recorriendo el vector de esquiadores desde cierto punto no se seguir�a ese emparejamiento
* Sea E1 ese esquiador
* Sea S2 los esqu�s emparejados a ese esquiador
* Sea S1 los esqu�s emparejados de manera voraz
* Sea E2 el esquiador emparejado a S1 de manera �ptima
* Entonces E1<=E2,S1<=S2
* Se demuestra por casos que mejoramos la funci�n objetivo o la dejamos igual si emparejamos E1-S1, E2-S2 en vez de
* lo anterior
* As� transformamos la �ptima en la voraz
* 
* 
*/
bool resuelveCaso()
{
	int n;
	cin >> n;
	if (!n)
	{
		return false;
	}
	vector<int> v1;
	vector<int> v2;
	for (int i = 0; i < n; i++)
	{
		int aux; cin >> aux; v1.push_back(aux);
	}
	for (int i = 0; i < n; i++)
	{
		int aux; cin >> aux; v2.push_back(aux);
	}
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	long long int sumTotal = 0;
	for (int i = 0; i < n; i++)
	{
		sumTotal += abs(v1[i] - v2[i]);
	}
	cout << sumTotal << "\n";
	return true;

}

int main()
{
	while (resuelveCaso());
	return 0;
}