#include "bintree_eda.h"
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

struct DatosArbol
{
	int nodos;
	int hojas;
	int altura;
	DatosArbol(int a, int b, int c) : nodos(a), hojas(b), altura(c)
	{
		nodos = a;
		hojas = b;
		altura = c;
	}
};

template <class T>
class bintree_ext : public bintree<T>
{
	using Link = typename bintree<T>::Link;
public:
	bintree_ext() : bintree<T>() {}
	bintree_ext(bintree_ext<T> const& l, T const& e, bintree_ext<T> const& r) : bintree<T>(l, e, r) {}

	DatosArbol datos() const {
		return datos(this->raiz);
	}

private:
	static DatosArbol datos(Link r) {
		if (r == nullptr) {
			return DatosArbol(0, 0, 0);
		}
		else {
			auto datosIzq = datos(r->left);
			auto datosDer = datos(r->right);
			return DatosArbol(
				datosIzq.nodos + datosDer.nodos + 1, //Número de nodos; la suma de los de la izquierda, la derecha y la raíz (1)
				datosIzq.hojas + datosDer.hojas + (!datosIzq.hojas && !datosDer.hojas ? 1 : 0), //Suma de las hojas de la izquierda
				//y la derecha; añadimos uno si los dos árboles son vacíos i.e. no tienen hojas
				max(datosIzq.altura, datosDer.altura) + 1 //Esto ya es evidente
			);
		}
	}

};

bintree_ext<bool> buildTree()
{
	char c;
	cin >> c;
	if (c == '.')
	{
		return bintree_ext<bool>();
	}
	else
	{
		return bintree_ext<bool>(buildTree(), false, buildTree());
	}
}


void resuelveCaso()
{
	bintree_ext<bool> arbol = buildTree();
	auto z = arbol.datos();
	cout << z.nodos << " " << z.hojas << " " << z.altura << '\n';
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