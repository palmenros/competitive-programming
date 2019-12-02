//D. Martín Gómez Abejón y D. Pedro Palacios Almendros
#include <iostream>
#include <vector>
using namespace std;
//El problema es trivial cuando el número de entrada es una potencia de 10,
//por lo que el problema es lineal en el número de dígitos
//Precondición: {0<=n<=10^18}
//proc contarSinUnos(n ent.) dev d ent.
//Postcondición: {d = # i:0<=i<=n:forall e: 0 <= e <= 18 : i/(10^e) % 10 != 1}


long long int contarSinUnos(long long int n)
{
	vector<short int> v;
	//En primer lugar pasamos el entero a un vector
	while (n) {v.push_back(n % 10); n /= 10;}
	//Miramos hasta qué punto es un número que termina en nueves.
	//Todo esto es correcto por la lazy evaluation de C++ y vale también para el 0
	int red = 0;
	while (red < v.size() && v[red] == 9){red++;}
	//Calculemos ahora el caso trivial para el número que obtenemos con las posiciones 0 hasta red
	long long int formasRed = 1;
	//Con exponentes tan pequeños la exponenciación binaria no es más eficiente
	//que la lineal
	for (int i = 0; i < red; i++)
	{
		formasRed *= 9;
	}
	//Este es el caso trivial, también aplicable al 0. Por combinatoria elemental,
	//si n = 99...99 (red veces), la solución a nuestro problema es trivialmente
	//9 elevado a k
	if (red == v.size())
	{
		return formasRed;
	}
	//Ahora, casos triviales aparte, hagamos recursión.
	//La idea intuitiva es alargar en cada paso la cadena de nueves
	//hasta que el número sea un caso trivial.
	//Si a la izquierda de la futura cadena alargada hay unos, podemos alargar la cadena sin quitar casos
	bool unosALaIzquierda = false;
	for (int i = red + 1; i < v.size() && !unosALaIzquierda;i++)
	{
		if (v[i] == 1) {unosALaIzquierda = true;}
	}
	//Ahora, hagamos recursión
	long long int resParcial = 0;
	while (v[red]!= 0)
	{
		resParcial+=(!unosALaIzquierda&&v[red]!=1?formasRed:0); //Añadimos casos si no hay unos después de la posición red
															 	//y v[red] no es 1
		v[red]--;
	}
	//Ahora v[red] es 0 y en resParcial tenemos los casos que hemos quitado. Hagamos que sea 9 si a la izquierda de v[red] hay algo,
	//y si no ya tenemos un caso trivial
	if (v.size()>red + 1)
	{
		resParcial+=(!unosALaIzquierda?formasRed:0);
		//Ahora restamos 10 ^ red al vector
		v[red]--;
		//Este bucle termina por las precondición de que hay algo a la izquierda
		while(v[red] == -1)
		{
			v[red] = 9;
			red++;
			v[red]--;
		}
	}
	//Ya hemos hecho un vector más cercano al caso trivial. Ahora solo falta llamar a la función de nuevo.
	long long int z = 0;
	long long int potencia = 1;
	for (int i = 0; i < v.size(); i++)
	{
		z+=v[i] * potencia;
		potencia *= 10;
	}
	//Ahora llamamos recursivamente
	return resParcial + contarSinUnos(z);
}


int main()
{
	while (true)
	{
		long long int k;
		cin >> k;
		if (!cin) {return 0;}
		cout << contarSinUnos(k) << endl;
	}
}