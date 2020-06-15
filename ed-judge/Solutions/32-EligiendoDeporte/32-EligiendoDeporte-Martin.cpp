#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <iostream>
using namespace std;

bool resuelveCaso()
{
	//COMENTARIO SOBRE EL COSTE
	//Depende mucho de la forma de los datos, pero habiendo tenido cuidado de utilizar estructuras ordenadas al final,
	//que es cuando importa, el coste es O(n+m log m) donde n es el número de alumnos y m el número de deportes
	//Esto es porque cuando procesamos todos los datos al principio no necesitamos orden
	//Pero al final sí para sacar la lista
	//Y la lista tiene el tamaño del número de deportes


	//Creamos una variable auxiliar para capturar las cadenas
	string aux;
	//Comprobamos que hay datos
	if (!(cin >> aux))
	{
		return false;
	}
	//Creamos un mapa de ni�os y lista de deportes
	//Claves: ni�o, valores: set de deportes, as� quitamos los dobles deportes de forma eficiente
	unordered_map<string, unordered_set<string>> datos;
	//Cadena para guardar el deporte actual
	string deporte;
	//Hacemos un mapa deportes-n�m. de ni�os para procesar los datos a posteriori y para recordar los deportes sin inscritos
	unordered_map<string, int> mapaDeportes;
	//Procesar datos
	while (aux != "_FIN_")
	{
		//Deporte o ni�o? May�sculas < Min�sculas
		if (aux[0] < 'a') //Deporte
		{
			
			deporte = aux;
			mapaDeportes[aux]; //Recordar un posible deporte sin inscritos
		}
		else //Ni�o
		{
			datos[aux].insert(deporte); //Es un set, no insertamos repetidos. S� insertamos distintos
		}
		cin >> aux;
	}
	for (auto valor : datos)
	{
		if (valor.second.size() == 1) //Si el ni�o tiene un solo deporte
		{
			mapaDeportes[(*(valor.second.begin()))]++; //Sumamos 1 persona a ese deporte
		}
	}
	//Ahora tenemos que ordenar de otra forma, por lo que haremos un map especial al que a�adiremos los elementos de mapaDeportes
	map<int, set<string>> mapaFrecuencias;
	//Movemos de uno a otro
	for (auto valor : mapaDeportes)
	{
		mapaFrecuencias[valor.second].insert(valor.first);
	}
	//Ahora recorremos mapaFrecuencias hacia abajo, con reversed iterators
	auto it = mapaFrecuencias.rbegin();
	while (it != mapaFrecuencias.rend())
	{
		
		for (string valor : (*it).second)
		{
			cout << valor << " " << (*it).first << "\n";
		}
		it++;
	}
	cout << "---\n";
	return true;
}

int main()
{
	while (resuelveCaso()){}
	return 0;
}