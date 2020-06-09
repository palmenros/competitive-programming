#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;

//Para hacer hashes de pairs
struct pair_hash {
	template <class T1, class T2>
	std::size_t operator () (const std::pair<T1, T2>& p) const {
		auto h1 = std::hash<T1>{}(p.first);
		auto h2 = std::hash<T2>{}(p.second);
		//No es muy bueno pero es aceptable
		return h1 ^ h2;
	}
};
bool resuelveCaso()
{
	//El algoritmo es O(n log n) con n = el n�mero de entradas, ya que ordenamos los actores alfab�ticamente
	//Si no hubiera que ordenar los actores el algoritmo ser�a lineal, ya que todo se puede hacer con costes constantes
	//utilizando estructuras no ordenadas

	//Diccionario para asociar a cada pel�cula sus caracter�sticas
	unordered_map<string, unordered_set<pair<string, int>,pair_hash>> datosPeliculas;
	//Para almacenar n�mero de veces que se emite cada pel�cula
	unordered_map<string, int> nEmisionesPeliculas;
	//Para almacenar participaci�n de cada actor
	unordered_map<string, int> participacionActores;

	int n;
	cin >> n;
	if (!n)
	{
		return false;
	}
	for (int i = 0; i < n; i++)
	{
		string pelicula;
		cin >> pelicula;
		int nAct;
		cin >> nAct;
		//Creamos la entrada en el diccionario para evitar copiar m�s tarde
		auto& actoresActuales = datosPeliculas[pelicula];
		for (int i = 0; i < nAct; i++)
		{
			string actor;
			int minutos;
			cin >> actor >> minutos;
			actoresActuales.insert(make_pair(actor, minutos));
		}
	}
	//Variables para hacer (parte de) la selecci�n de la pel�cula m�s emitida y los actores m�s emitidos, lineal
	string peliculaAdecuada; //Almacena la soluci�n del problema hasta este momento
	int maxEmisiones = 0; //Almacena el n�mero m�ximo de emisiones hasta ahora de cada pel�cula
	vector<string> actoresAdecuados; //Soluci�n desordenada de los actores hasta el momento
	int maxParticipacion = 0; //An�logo a maxEmisiones
	int m;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		string aux; //Pel�cula emitida
		cin >> aux;
		//Procesar la parte de las pel�culas
		nEmisionesPeliculas[aux]++; //Actualizar datos
		if (nEmisionesPeliculas[aux] > maxEmisiones) { maxEmisiones++; } //Actualizar variables auxiliares
		if (nEmisionesPeliculas[aux] == maxEmisiones) { peliculaAdecuada = aux; } //Actualizar soluci�n
		//Procesar la parte de los actores
		for (auto valor : datosPeliculas[aux])
		{
			participacionActores[valor.first] += valor.second; //Actualizar datos
			if (participacionActores[valor.first] > maxParticipacion) //Actualizar variables auxiliares / soluci�n
			{
				maxParticipacion = participacionActores[valor.first];
				actoresAdecuados.clear();
			}
			if (participacionActores[valor.first] == maxParticipacion) //Actualizar soluci�n con dato actual
			{
				actoresAdecuados.push_back(valor.first);
			}
		}
	}
	//Ordenar actores adecuados
	sort(actoresAdecuados.begin(), actoresAdecuados.end());
	//Imprimir
	cout << maxEmisiones << " " << peliculaAdecuada << "\n" << maxParticipacion;
	for (string e : actoresAdecuados)
	{
		cout << " " << e;
	}
	cout << "\n";


	return true;
}

int main()
{
	while(resuelveCaso())
	{ }
	return 0;
}