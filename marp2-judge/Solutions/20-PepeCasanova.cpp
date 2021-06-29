/*
Cada solución es un vector de enteros, V[0..N-1].
Restricciones explícitas: enRango(V,N,3)
Restricciones implícitas:

Restricciones de los pesos: sum i: 0 <= i < n && V[i] = 1 : datos[i].duracion <= longCinta
							sum i: 0 <= i < n && V[i] = 2 : datos[i].duracion <= longCinta

Máxima satisfacción: forall W[0..N-1]
:
(
enRango(W,N,3)
&& sum i: 0 <= i < n && W[i] = 1 : datos[i].duracion <= longCinta
&& sum i: 0 <= i < n && W[i] = 2 : datos[i].duracion <= longCinta
)
:
sumaSatis(V,datos)>=sumaSatis(W,datos)
donde

enRango(V,N,M) := forall i: 0<=i<=N-1:0<=V[i]<=M-1
sumaSatis(V,datos) := sum i : 0 <= i < n && V[i] != 0 : datos[i].satisfaccion
*/
#include <iostream>
#include <algorithm>
using namespace std;

//Esta estructura representa una canción
typedef struct
{
	int duracion;
	int satisfaccion;
} Cancion;


//Este array almacena los datos de las canciones
typedef Cancion Datos[25];
//Funciones para ordenar las canciones
bool operator<=(Cancion c1,Cancion c2)
{
	float d1 = c1.duracion;
	float d2 = c2.duracion;
	float s1 = c1.satisfaccion;
	float s2 = c2.satisfaccion;
	return s1/d1>=s2/d2;
}
bool operator<(Cancion c1,Cancion c2)
{
	float d1 = c1.duracion;
	float d2 = c2.duracion;
	float s1 = c1.satisfaccion;
	float s2 = c2.satisfaccion;
	return s1/d1>s2/d2;
}
//Esta función comprueba si el restante de las mochilas rellenadas hasta cierto punto puede dar una solución más alta a la mejor conocida
//Para ello, las consideramos como una sola mochila y hacemos el test de la mochila con objetos dividibles
bool esPrometedora(const int& n,const int& longCinta,const Datos datos,int& mochila1,int& mochila2,int& profundidad, int& solActual, int& satAcumulada)
{
	//Al considerarla como una sola mochila, calculamos el espacio restante
	int espacioDisponible = 2 * longCinta - mochila1 - mochila2;
	//Esto es igual que tener una sola mochila
	int i = profundidad;
	int restanteMaximo = 0;
	while (i<n && espacioDisponible >0)
	{
		//Los objetos están ordenados decrecientemente por "densidad" de valor
		//Si podemos coger uno entero, lo cogemos
		if (espacioDisponible >=datos[i].duracion)
		{
			espacioDisponible -= datos[i].duracion;
			restanteMaximo += datos[i].satisfaccion;
		}
		else
		{
			//Si no, cogemos una fracción de él
			restanteMaximo += datos[i].satisfaccion * espacioDisponible / datos[i].duracion;
			espacioDisponible = 0;
		}
		i++;
	}
	//Hacemos el test dentro de la función y devolvemos si es factible o no
	return restanteMaximo > solActual-satAcumulada;
}

void solve(const int& n,const int& longCinta,const Datos datos,int& mochila1,int& mochila2,int& profundidad, int& solActual, int& satAcumulada)
{
	//Si es solución, actualizar el valor de solActual
	if (profundidad == n)
	{
		//Obsérvese que por el test de factibilidad, las soluciones nuevas serán siempre mayores que las anteriores.
		//Sin embargo hacemos el máximo por seguridad
		solActual = max(solActual,satAcumulada);
		return;
	}

	//Primera cinta
	if ((longCinta-mochila1) >= datos[profundidad].duracion)
	{
		//Marcar
		mochila1 += datos[profundidad].duracion;
		satAcumulada+=datos[profundidad].satisfaccion;
		profundidad++;
		//Vuelta atras
		if (esPrometedora(n,longCinta,datos,mochila1,mochila2,profundidad,solActual,satAcumulada))
		{
			solve(n,longCinta,datos,mochila1,mochila2,profundidad,solActual,satAcumulada);
		}
		//Desmarcar
		profundidad--;
		mochila1 -= datos[profundidad].duracion;
		satAcumulada-=datos[profundidad].satisfaccion;
	}	
	//Segunda cinta
	if (longCinta-mochila2 >= datos[profundidad].duracion)
	{
		//Marcar
		mochila2 += datos[profundidad].duracion;
		satAcumulada+=datos[profundidad].satisfaccion;
		profundidad++;
		//Vuelta atras
		if (esPrometedora(n,longCinta,datos,mochila1,mochila2,profundidad,solActual,satAcumulada))
		{
			solve(n,longCinta,datos,mochila1,mochila2,profundidad,solActual,satAcumulada);
		}
		//Desmarcar
		profundidad--;
		mochila2 -= datos[profundidad].duracion;
		satAcumulada-=datos[profundidad].satisfaccion;
	}	
	//A ninguna cinta
	//Marcar
	profundidad++;
	//Vuelta atras
	if (esPrometedora(n,longCinta,datos,mochila1,mochila2,profundidad,solActual,satAcumulada))
	{
		solve(n,longCinta,datos,mochila1,mochila2,profundidad,solActual,satAcumulada);
	}
	//Desmarcar
	profundidad--;
}

int main()
{
	while (true)
	{
		//Número de pistas
		int n;
		cin >> n;
		if (!n) {return 0;}
		//Longitud de cada cara de la cinta
		int longCinta;
		cin >> longCinta;
		//Datos de las pistas
		Datos datos;
		for (int i = 0;i<n;i++)
		{
			cin >> datos[i].duracion >> datos[i].satisfaccion;
		}
		//Ordenamos los datos decrecientemente por densidad de valor. Es un ejercicio del tema anterior
		//Lo hacemos para la poda del problema de una única mochila
		sort(datos,datos+n);
		//Utilizaremos las palabras mochila y cara de la cinta intercambiablemente
		//Estos serán los pesos (en cada momento) de cada mochila / cinta
		int mochila1 = 0;
		int mochila2 = 0;
		//Asignamos a cada objeto la mochila 1, la mochila 2 o ninguna mochila. La profundidad es el nivel de recursión,
		//es decir, el objeto al que le asignamos la mochila
		int profundidad = 0;
		//La mejor solución conocida hasta el momento
		int solActual = 0;
		//La satisfacción acumulada; es decir, la suma de las satisfacciones de los objetos que ya se han metido en alguna mochila
		int satAcumulada = 0;
		solve(n,longCinta,datos,mochila1,mochila2,profundidad,solActual,satAcumulada);
		cout << solActual << endl;
	}
}
