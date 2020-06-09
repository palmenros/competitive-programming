#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main()
{
	while (true)
	{
		//Coste: o(n), ya que el bucle se ejecuta n veces con coste constante en cada vuelta
		int n;
		cin >> n;
		if (!cin) { return 0; }
		//Para hacerlo lineal vamos a utilizar un vector en el que tendremos los números en el orden de salida,
		//y un unordered_map para ayudarnos a trabajar con el vector
		vector<pair<int, int>> v; //Primer entero: dato, segundo entero: n de ocurrencias
		//Este diccionario no ordenado guarda para cada entero en qué posición del vector está, más 1
		//Así el coste es lineal
		unordered_map<int, int> dicc;
		for (int i = 0; i < n; i++)
		{
			int aux;
			cin >> aux;
			//Buscamos la posición
			int& pos = dicc[aux];
			//Si no existía lo añadimos a dicc y al vector
			if (!pos)
			{
				pos = v.size() + 1;
				v.push_back(make_pair(aux, 0));
			}
			//Y añadimos la ocurrencia
			v[pos - 1].second++;
		}
		//Imprimimos
		for (auto e : v)
		{
			cout << e.first << " " << e.second << "\n";
		}
		cout << "---\n";

	}
}