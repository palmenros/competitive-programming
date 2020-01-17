//Martín Gómez Abejón y Pedro Palacios Almendros
#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;
/*
La solución es una longitud-tupla (a[1],...,a[longitud]) indicando en cada posición qué color hay
Restricciones explícitas: forall i:1<=i<=longitud:0<=a[i]<=colores-1
Restricciones implícitas: suma i: 1<=i<=longitud : datosColores[a[i]] <= maxConsumo
forall i : 1 <= i <= longitud - 2 : !(a[i] == a[i+1] and a[i+1] == a[i+2])
forall i : 1 <= i <= longitud : forall j : 0 <= j <= colores - 1 : 2*(#k: 1<=k<=longitud : a[k] = j ) <= 1+i
*/
void vueltaAtras(const int& longitud, const int& colores, const int& maxConsumo, const int& minimoConsumo, int* datosColores, int* marcadorColores, int* solucion, int profundidad, int& nsols, int& consumo)
{
	//Si es solución ir hacia atrás
	if (profundidad == longitud)
	{
		nsols++; 
		//Descomentar para obtener también las soluciones
		//for (int i = 0;i<longitud;i++)
		//{
		//	cout << solucion[i] << " ";
		//}
		//cout << endl;
		return;
	}
	//Exploramos cada rama
	for (int i = 0; i < colores;i++)
	{
		//Marcar
		marcadorColores[i]++;
		solucion[profundidad] = i;
		consumo+=datosColores[i];
		//Comprobar; vuelta atrás o podar
		//La parte más complicada es ver que los colores tienen números bajos en datosColores
		//Lo hacemos con ayuda del marcador que guarda el número de bombillas de cada color
		bool mColoresPlausible = true;
		int j = 0;
		while (j < colores &&mColoresPlausible)
		{
			
			mColoresPlausible = (marcadorColores[i]<=2 + profundidad - marcadorColores[i]);
			j++;
		}
		//Hay que comprobar 3 cosas
		//1: la restricción de consumo (con el marcador de consumo lo hacemos rápidamente)
		//2: la restricción de 3 seguidas del mismo color
		//3: La restricción de la proporción de los colores, almacenada en mColoresPlausible
		if ((mColoresPlausible) && (profundidad<2 || solucion[profundidad-1] != i || solucion[profundidad-2] != i) && (maxConsumo-consumo >= minimoConsumo * (longitud-profundidad-1)))
		{
			vueltaAtras(longitud,colores,maxConsumo,minimoConsumo,datosColores,marcadorColores,solucion,profundidad+1,nsols,consumo);
		}
		//Desmarcar
		marcadorColores[i]--;
		consumo-=datosColores[i];
	}
}

int main()
{
	while (true)
	{
		//Longitud de las soluciones
		int longitud;
		cin >> longitud;
		if(!longitud){return 0;}
		//Numero de colores
		int colores;
		cin >> colores;
		//Maximo consumo
		int maxConsumo;
		cin >> maxConsumo;
		//Datos de consumo de los colores
		int* datosColores = new int[colores];
		//optimización para podar; si el número de bombillas que quedan tiene demasiado consumo cogiéndolas todas con consumo bajo, podamos.
		int minimoConsumo = INT_MAX;
		for(int i = 0;i<colores;i++)
		{
			//Calculamos el consumo mínimo y rellenamos el array
			cin >> datosColores[i];
			minimoConsumo = min(minimoConsumo,datosColores[i]);
		}
		//Marcador para optimizar; que el número de bombillas no supere en más de una unidad a...
		int* marcadorColores = new int[colores];
		for (int i = 0;i<colores;i++)
		{
			marcadorColores[i] = 0;
		}
		//Vector solución
		int* solucion = new int[longitud];
		//Número de soluciones
		int nsols = 0;
		//Marcador; consumo actual
		int consumo = 0;
		int profundidad = 0;
		vueltaAtras(longitud,colores,maxConsumo,minimoConsumo,datosColores,marcadorColores,solucion,profundidad,nsols,consumo);
		cout << nsols << endl;
	}
}