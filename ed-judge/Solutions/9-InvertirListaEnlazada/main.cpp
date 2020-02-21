#include "listaReversible.h"

int main()
{
	while (true)
	{
		int aux;
		std::cin >> aux;
		if (!std::cin)
		{
			return 0;
		}
		listaReversible<int> l;
		while (aux)
		{
			l.push_back(aux);
			std::cin >> aux;
		}
		l.reverse();
		l.imprimirEnCout();
	}
}