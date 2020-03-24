#include "bintree_eda.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

bintree<int> buildTree()
{
	int c;
	cin >> c;
	if (c == -1)
	{
		return bintree<int>();
	}
	else
	{
		auto a = buildTree();
		auto b = buildTree();
		return bintree<int>(a, c, b);
	}
}
template <class T>
void imprimir(vector<T>& v)
{
	bool first = true;
	for (T t : v)
	{
		cout << (first ? "" : " ") << t;
		first = false;
	}
	cout << "\n";
}
void obtenerFrontera(bintree<int> arbol, vector<int>& v)
{
	//Caso trivial: árbol vacío
	if (arbol.empty())
	{
		return;
	}
	else
	{
		//LLamar a la recursión
		obtenerFrontera(arbol.left(), v);
		obtenerFrontera(arbol.right(), v);
		if (arbol.left().empty() && arbol.right().empty()) //Hoja
		{
			v.push_back(arbol.root());
		}
	}
}

void resuelveCaso()
{
	bintree<int> arbol = buildTree();
	vector<int> v;
	obtenerFrontera(arbol,v);
	imprimir(v);
}

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		resuelveCaso();
	}
}