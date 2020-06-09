#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <string>
using namespace std;

//Comentario sobre el coste
//Utilizamos estructuras ordenadas solo cuando hace falta, el coste es
//O(n+m log m), donde n es la longitud de la entrada y m la longitud de la solución
//Podemos procesar la entrada sin que estén ordenados los problemas
//Pero ordenamos el ránking al final
//Así que coste lineal en la entrada y lineal-log en la salida


struct jugadorProcesado
{
	int problemas;
	int tiempo;
	string id;
	jugadorProcesado(int problemas, int tiempo, string id) : problemas(problemas),tiempo(tiempo),id(id){}
	void imprimir()
	{
		cout << id << " " << problemas << " " << tiempo << "\n";
	}
	bool operator<(const jugadorProcesado& other) const
	{
		//Devolver si tiene que estar antes en el r�nking
		return (
			problemas > other.problemas ||
			(
				problemas == other.problemas &&
				(
					tiempo < other.tiempo ||
					(
						tiempo == other.tiempo &&
						(
						id < other.id
						)
					)
				)
			)
		);
	}
};

struct datosEnvio
{
	//Los env�os llegan en orden, as� que tenemos pocos datos interesantes que retener
	//Booleano; se ha recibido ya una soluci�n?
	bool solRecibida = false;
	//Tiempo que ha tardado. Este tiempo guarda, cuando no se ha entregado el problema a�n, las penalizaciones
	int tiempoAc;
};

void resuelveCaso()
{
	//Creamos una variable auxiliar para capturar las cadenas
	string aux;
	cin >> aux;
	//Creamos un mapa de competidores y datos de competidores. Cada dato de competidor es un mapa de problemas
	//y propiedades de los problemas.
	unordered_map<string, unordered_map<string,datosEnvio>> datos;
	while (aux != "FIN")
	{
		//Lo que hay ahora es el id del competidor
		string idJugador = aux;
		cin >> aux;
		//Ahora, la cadena del problema
		string idProb = aux;
		//Cogemos el tiempo
		int tiempo;
		cin >> tiempo;
		cin >> aux;
		//Ahora el veredicto
		string veredicto = aux;
		//Extraemos de cin para la siguiente entrada
		cin >> aux;
		//Ahora procesamos el problema
		datosEnvio& act = datos[idJugador][idProb];
		if (!act.solRecibida) //Si no se ha entregado a�n
		{
			if (veredicto == "AC") //Si el env�o es correcto
			{
				//Guardamos entrega correcta
				act.solRecibida = true;
				//Guardamos tiempo
				act.tiempoAc += tiempo;
			}
			else
			{
				//Penalizamos
				act.tiempoAc += 20;
			}
		}
	}
	//Ahora vamos a hacer un set para ordenar de forma diferente, y para procesar
	set<jugadorProcesado> resultados;
	for (auto valor : datos) //No hace falta orden
	{
		jugadorProcesado dest(0,0,valor.first);
		//Procesamos los datos del jugador
		for (auto elem : valor.second)
		{
			if (elem.second.solRecibida)
			{
				dest.problemas++;
				dest.tiempo += elem.second.tiempoAc;
			}
		}
		//A�adimos el jugador
		resultados.insert(dest);
	}
	//Los jugadores est�n ordenados y los sacamos por pantalla
	for (jugadorProcesado j : resultados)
	{
		j.imprimir();
	}
	cout << "---\n";
}

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		resuelveCaso();
	}
}