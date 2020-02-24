#include <iostream>
#include <deque>
#include <cmath>
#include <algorithm>
using namespace std;

typedef struct
{
	long long int elem;
	int pos;
} elemento;

int main()
{
	while (true)
	{
		//Se puede optimizar recordando solo ciertos máximos (cuando a la izquierda de un elemento hay
		//cosas más pequeñas se pueden olvidar)
		int n;
		cin >> n;
		if (!n) { return 0; }
		//La cola doble donde guardaremos los máximos anteriores
		deque<elemento> d;
		//Longitud del intervalo de los máximos
		int k;
		cin >> k;
		//Para imprimir; nada importante del algoritmo
		bool firstElem = true;
		//Índice por el que vamos
		int j = 0;
		while (j<n)
		{
			//Cogemos de cin
			long long int aux;
			cin >> aux;
			//Ahora generamos el elemento tal y como iría en la cola doble
			elemento aInsertar;
			aInsertar.elem = aux;
			aInsertar.pos = j;
			//Lo que hacemos ahora es retirar los menores por la derecha, como comentamos antes
			while (!d.empty() && d.back().elem <= aInsertar.elem)
			{
				d.pop_back();
			}
			//Metemos el nuevo
			d.push_back(aInsertar);
			//Avanzamos
			j++;
			//Retiramos el elemento de la izquierda si está desactualizado (ya no está dentro de la lista de k elementos)
			if (d.front().pos<j-k)
			{
				d.pop_front();
			}
			//Si ya tenemos un bloque, imprimimos
			if (j >= k)
			{
				cout << (firstElem?"":" ") << d.front().elem;
				firstElem = false;
			}
		}
		cout << "\n";

	}
}