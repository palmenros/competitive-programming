//Martín Gómez Abejón
//Problema 2: k-ésimo elemento en AVL
#include <iostream>
using namespace std;
#include "02-TreeSetAVL.h"


bool resuelveCaso()
{
	int n;
	cin >> n;
	if (!n)
	{
		return false;
	}
	Set<int> s;
	for (int i = 0; i < n; i++)
	{
		int aux;
		cin >> aux;
		s.insert(aux);
	}
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		try
		{
			int aux;
			cin >> aux;
			cout << s.kesimo(aux) << "\n";
		}
		catch (const std::exception& e)
		{
			cout << e.what();
		}
	}
	cout << "---\n";
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;

}