#include "listaInsertora.h"

int main()
{
	while (true)
	{
		int n;
		int m;
		int donde;
		std::cin >> n;
		if (!std::cin)
		{
			return 0;
		}
		listaInsertora<int> l;
		int aux;
		for (int i = 0;i<n;i++)
		{
			std::cin >> aux;
			l.push(aux);
		}
		listaInsertora<int> otra;
		std::cin >> m >> donde;
		for (int i = 0; i < m; i++)
		{
			std::cin >> aux;
			otra.push(aux);
		}
		l.annadirEnIndice(otra, donde);
		l.imprimirEnCout();
	}
}