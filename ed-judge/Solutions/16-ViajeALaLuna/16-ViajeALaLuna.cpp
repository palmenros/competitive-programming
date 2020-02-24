#include "persona.h"
#include "listaFiltrante.h"
#include <iostream>
using namespace std;

int main()
{
	while (true)
	{
		int n, edadMinima, edadMaxima;
		cin >> n >> edadMinima >> edadMaxima;
		if (!n || !cin) { return 0; }
		listaFiltrante<persona> l;
		for (int i = 0; i < n; i++)
		{
			persona aux;
			cin >> aux;
			l.push_back(aux);
		}
		l.remove_if([edadMinima, edadMaxima](persona& p) {return p.getEdad() < edadMinima || p.getEdad() > edadMaxima; });
		l.imprimirEnCout();
	}
}