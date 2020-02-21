#include "listaDuplicadora.h"

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
		listaDuplicadora<int> l;
		while (aux)
		{
			l.push(aux);
			std::cin >> aux;
		}
		l.duplicar();
		l.imprimirEnCout();
	}
}