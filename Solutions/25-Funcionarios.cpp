//Autores: Martín Gómez Abejón y Pedro Palacios Almendros
/*
Para ver las definiciones de todas las variables y lo que representan, ir al main
Recomendamos leer primero el main, luego vueltaAtras

La solución es un vector de enteros, V[0..N-1].
Restricciones explícitas: enRango(V,N)
Restricciones implícitas:

Permutación: permutacion(V,N)

Mínimo de esfuerzo: forall W[0..N-1]:enRango(W,N) and permutacion(W,N):suma(V,datos) <= suma(W,datos)

donde

sumaDatos(V,datos) := sum i: 0 <= i <= N-1 : datos[i][V[i]]
enRango(V,N) := forall i: 0<=i<=N-1:0<=V[i]<=N-1
permutacion(V,N) := forall i,j: 0<=i<j<=N-1:V[i]!=V[j]
*/
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

typedef int Datos[20][20];
typedef int MTPTArr[20];
typedef bool MTEArr[20];

void vueltaAtras(int& n,int& profundidadActual,int& acumuladoActual,int& solucionActual,Datos datos,MTPTArr minimoTiempoPorTrabajador,int& optMin,MTEArr marcadorTrabajosElegidos)
{
	//Si es solución, anotar el resultado si procede en solucionActual e ir hacia atrás
	if (n == profundidadActual)
	{
		solucionActual = min(acumuladoActual,solucionActual);
		return;
	}
	//Si no lo es, hay que ir por las ramas posibles utilizando marcadorTrabajosElegidos, y podando las que no interesen
	for (int j = 0;j<n;j++)
	{
		if (marcadorTrabajosElegidos[j] == false) //Si no hemos cogido ese trabajo
		{
			//Marcar
			acumuladoActual+=datos[profundidadActual][j]; //Sumamos el tiempo del trabajador
			optMin-=minimoTiempoPorTrabajador[profundidadActual]; //Restamos de optMin el tiempo mínimo del trabajador
			marcadorTrabajosElegidos[j] = true; //Marcamos el trabajo como elegido
			profundidadActual++; //Pasamos al siguiente trabajador
			//Vuelta atrás, si procede
			//Si la solución que nos encontraremos no es mejor que la que ya tenemos, no entramos
			if (optMin<solucionActual-acumuladoActual)
			{
				vueltaAtras(n,profundidadActual,acumuladoActual,solucionActual,datos,minimoTiempoPorTrabajador,optMin,marcadorTrabajosElegidos);
			}
			//Desmarcar
			profundidadActual--;
			acumuladoActual-=datos[profundidadActual][j];
			optMin+=minimoTiempoPorTrabajador[profundidadActual];
			marcadorTrabajosElegidos[j] = false;
		}
	}
}


int main()
{
	while (true)
	{
		int n;
		cin >> n;
		if (!n){return 0;}
		//Este array tendrá los datos de los tiempos, obtenidos de cin
		Datos datos;
		//Lo que haremos será asignar a cada empleado del estado un trabajo.
		//Cada nivel del árbol de soluciones representará un trabajador.
		//La optimización / poda que proponemos nosotros es la siguiente
		/*

		Si los trabajadores a los que aún les tenemos que asignar trabajos tandan, en cualquier caso, lo suficiente como para que
		la solución que obtengamos sea igual o superior a la obtenida previamente, podemos podar esa rama.
		Para ello, guardamos en un array los tiempos mínimos de cada trabajador
		Si la suma de los tiempos mínimos de los que quedan es mayor o igual a la mejor solución conocida,
		menos la suma de los tiempos de los trabajadores que ya tienen trabajo asignado, entonces se puede podar

		*/
		//Este será el array que tendrá los tiempos mínimos
		MTPTArr minimoTiempoPorTrabajador;
		//Este marcador es para saber los trabajos que ya han sido asignados
		MTEArr marcadorTrabajosElegidos;
		//Esta variable sirve para no tener que sumar los tiempos de los trabajadores que quedan al hacer la verificación
		//de poda. Empezará con la suma de los tiempos mínimos, y su valor se corregirá al marcar / desmarcar con un solo
		//acceso al array de tiempos mínimos.
		int optMin = 0;
		//Tomamos los datos
		for (int i = 0;i<n;i++)
		{
			marcadorTrabajosElegidos[i] = false;
			minimoTiempoPorTrabajador[i] = INT_MAX;
			for (int j = 0;j<n;j++)
			{
				cin >> datos[i][j];
				minimoTiempoPorTrabajador[i] = min(minimoTiempoPorTrabajador[i], datos[i][j]);
			}
			optMin += minimoTiempoPorTrabajador[i];
		}
		//La mejor solución conocida
		int solucionActual = INT_MAX;
		//Esta variable representa esencialmente el trabajador al que le asignamos un trabajo
		int profundidadActual = 0;
		//Suma de los tiempos de los trabajos ya asignados
		int acumuladoActual = 0;
		vueltaAtras(n,profundidadActual,acumuladoActual,solucionActual,datos,minimoTiempoPorTrabajador,optMin,marcadorTrabajosElegidos);
		cout << solucionActual << endl;
	}
}