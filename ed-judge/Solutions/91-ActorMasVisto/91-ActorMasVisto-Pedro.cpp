//
// Created by pedro on 2/4/20.
//

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//El coste es p*log(p) + a*log(a) donde p es el numero de peliculas distintas y a el numero de actores distintos
//El coste es ese por la ordenación

struct Pelicula {
	string name;
	int numeroVisualizaciones;
	int ultimaVisualizacion;

	Pelicula(const string &name, int numeroVisualizaciones, int ultimaVisualizacion)
		: name(name), numeroVisualizaciones(numeroVisualizaciones), ultimaVisualizacion(ultimaVisualizacion)
	{}

	bool operator<(const Pelicula& other)
	{
		if(other.numeroVisualizaciones != numeroVisualizaciones) {
			return numeroVisualizaciones > other.numeroVisualizaciones;
		}

		return ultimaVisualizacion > other.ultimaVisualizacion;
	}
};

struct Actor
{
	string name;
	int minutos;

	Actor(const string &name, int minutos)
		: name(name), minutos(minutos)
	{}

	bool operator<(const Actor& other)
	{
		if(minutos != other.minutos) {
			return minutos > other.minutos;
		}

		return name < other.name;
	}

};


void resolver(int nPeliculas)
{
	//m[nombrePelicula] = { numeroVisualizaciones, ultimaVisualizacion }
	unordered_map<string, vector<pair<string, int>>> datos;
	unordered_map<string, pair<int, int>> p;
	unordered_map<string, int> a;

	for(int i = 0; i < nPeliculas; i++)
	{
		string name; cin >> name;
		int nActores; cin >> nActores;

		auto& vec = datos[name];

		while(nActores--) {
			string actor;
			int minutos;
			cin >> actor >> minutos;
			vec.emplace_back(actor, minutos);
		}
	}

	int totalVis;
	cin >> totalVis;

	for(int i = 0; i < totalVis; i++)
	{
		string name; cin >> name;

		auto& [numVis, ultVis] = p[name];
		numVis++;
		ultVis = i;

		for(const auto& [nombreActor, minutes] : datos[name]) {
			a[nombreActor] += minutes;
		}

	}

	//Ordenar
	vector<Pelicula> vp;
	vector<Actor> va;

	for(const auto& [nombre, other] : p ) {
		const auto& [numVis, ultVis] = other;
		vp.emplace_back(nombre, numVis, ultVis);
	}

	for(const auto& [nombre, minutos] : a) {
		va.emplace_back(nombre, minutos);
	}

	sort(vp.begin(), vp.end());
	sort(va.begin(), va.end());

	//Imprimir
	const auto& peli = vp[0];
	cout << peli.numeroVisualizaciones << " " << peli.name << endl;

	int maxMinutos = va[0].minutos;
	cout << maxMinutos;

	for(const auto& actor : va) {
		if(actor.minutos != maxMinutos) { break; }
		cout << " " << actor.name;
	}

	cout << endl;

}

int main()
{
	int n;
	while(cin >> n && n != 0) {
		resolver(n);
	}

	return 0;
}