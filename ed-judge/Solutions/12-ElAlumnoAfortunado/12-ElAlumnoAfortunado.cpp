#include <iostream>
#include <queue>
using namespace std;

int main()
{
	while (true)
	{
		int longitud; //n de alumnos
		int mod; //Cada cuánto se echa a uno
		int cActual = 1;
		queue<int> cola;
		cin >> longitud >> mod;
		if (!longitud && !mod)
		{
			return 0;
		}
		mod++; //El enunciado nos da realmente mod - 1
		//Rellenamos la cola
		for (int i = 0; i < longitud; i++)
		{
			cola.push(i + 1);
		}
		//Ahora simplemente damos vueltas y retiramos hasta tener solo uno
		int ultimoProcesado = -1; //La idea es que al salir del bucle while esta variable tenga el último eliminado
		//Es decir, el alumno afortunado
		while (!cola.empty())
		{
			ultimoProcesado = cola.front();
			cola.pop();
			if (cActual)
			{
				cola.push(ultimoProcesado);
			}

			cActual++;
			cActual %= mod;
		}
		cout << ultimoProcesado << "\n";

	}
}