//Martín Gómez Abejón y Pedro Palacios Almendros
#include <iostream>
using namespace std;

/*
La solución es una 8-upla, indicando en función de la columna, en qué fila está cada reina
(a_1,a_2,...,a_i)
Restricciones explícitas: forall i:1<=i<=n:1<=a_i<=n
Restricciones implícitas: forall i:1<=i<=n:forall j:1<=j<=n and j!=i: a_i!=a_j and abs(j-i)!=abs(a_j-a_i)
Optimizaremos el problema marcando filas y diagonales
*/
typedef bool Filas[14];
typedef bool Diagonales[27];
void vueltaAtras(int n, Filas filas, Diagonales diagonalesAbajo, Diagonales diagonalesArriba, int profundidad, int& sol)
{
	if (profundidad == n){sol++;return;}
	for (int i = 0;i<n;i++)
	{
		//Con este bucle exploramos todas las ramas posibles
		//Si el caso es plausible, nos adentramos y hacemos vuelta atrás
		if (!filas[i] && !diagonalesAbajo[n-1+profundidad-i] && !diagonalesArriba[profundidad+i])
		{
			//Marcar
			filas[i] = true;
			diagonalesAbajo[n-1+profundidad-i] = true;
			diagonalesArriba[profundidad+i] = true;
			//Vuelta atrás
			vueltaAtras(n,filas,diagonalesAbajo,diagonalesArriba,profundidad+1,sol);
			//Desmarcar
			filas[i] = false;
			diagonalesAbajo[n-1+profundidad-i] = false;
			diagonalesArriba[profundidad+i] = false;
		}
	}
}
void procesarCaso()
{
	
	int n;
	cin >> n;
	//Marcador de filas
	Filas filas;
	//Marcador de diagonales de izquierda a derecha y arriba a abajo
	Diagonales diagonalesAbajo;
	//Marcador de diagonales de derecha a izquierda y arriba a abajo
	Diagonales diagonalesArriba;
	//Los arrays tienen el tamaño máximo para evitar utilizar memoria dinámica
	for (int i = 0;i<n;i++)
	{
		filas[i] = false;
	}
	for (int i = 0;i<2*n-1;i++)
	{
		diagonalesArriba[i] = false;
		diagonalesAbajo[i] = false;
	}
	int sol = 0;
	vueltaAtras(n,filas,diagonalesAbajo,diagonalesArriba,0,sol);
	cout << sol << endl;

}

int main()
{
	int casos;
	cin >> casos;
	for (int i = 0;i<casos;i++)
	{
		procesarCaso();
	}
}