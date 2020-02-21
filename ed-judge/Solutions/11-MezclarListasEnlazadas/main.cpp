#include "listaMergeadora.h"

void resuelveCaso()
{
	//Entrada a una
	int aux;
	std::cin >> aux;
	listaMergeadora<int> l;
	while (aux)
	{
		l.push(aux);
		std::cin >> aux;
	}
	//Entrada a otra
	std::cin >> aux;
	listaMergeadora<int> otra;
	while (aux)
	{
		otra.push(aux);
		std::cin >> aux;
	}
	
	
	l.mergear(otra);
	l.imprimirEnCout();
}

int main()
{
	int n;
	std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		resuelveCaso();
	}
}