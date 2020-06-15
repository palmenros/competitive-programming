#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	cin.ignore(1);
	string linea;
	for (int i = 0; i < n; i++)
	{
		//Obtenemos los datos
		map<string, int> dict1;
		map<string, int> dict2;
		getline(cin, linea);
		stringstream s1(linea);
		string auxClave;
		int auxValor;
		while (s1 >> auxClave >> auxValor)
		{
			dict1[auxClave] = auxValor;
		}
		getline(cin, linea);
		stringstream s2(linea);
		while (s2 >> auxClave >> auxValor)
		{
			dict2[auxClave] = auxValor;
		}
		//Coste n log n, donde n es la suma del n�mero de elementos de cada diccionario
		//El algoritmo es realmente lineal ya que es iterativo y se avanza en uno de los dos iteradores (o en ambos) en cada vuelta
		//Y cada vuelta tiene coste lineal
		//En este problema utilizar los datos tiene menor coste que prepararlos
		//Nos conviene tenerlos ordenados para recorrer en paralelo por lo que utilizamos map
		//El algoritmo recorre los diccionarios en orden, a la vez, para ver si una clave est� repetida o no
		//Recorrer solo uno a la vez es muy poco eficiente
		//Usaremos vectores para guardar lo que vamos averiguando
		vector<string> added;
		vector<string> modified;
		vector<string> removed;
		auto it1 = dict1.begin();
		auto it2 = dict2.begin();
		//La l�gica del algoritmo es la siguiente (supongamos que los iteradores end tienen valor + inf)
		//Si recorremos los diccionarios avanzando en el iterador con clave menor, si son distintas,
		//o en ambos, si las claves son iguales, suceder� lo siguiente:
		//Cuando haya una clave que est� en uno y no en el otro habr� una sola vez en la que la veremos como
		//valor del iterador y menor que la otra clave
		//ya que en alg�n momento se llegar� a ella, y si las claves en el otro diccionario son diferentes el otro diccionario
		//avanzar� hasta tener la clave mayor. �Justo entonces avanzar� la clave de la que hablamos
		//Si est� repetida, una sola vez la veremos en ambos a la vez, y nunca en uno menor que en otra
		//ya que alg�n diccionario llegar� a ella y el otro tiene que pasar por ella en alg�n momento
		//Cuando llegue la veremos en ambos iteradores, que luego avanzar�n
		//Adem�s en cada paso de este recorrido habr� o una clave menor o dos claves iguales
		while (it1 != dict1.end() || it2 != dict2.end())
		{
			if (it1 == dict1.end()) //La clave de it1 es infinito
			{
				//Computar diferencia
				added.push_back((*it2).first);
				//Avanzar
				it2++;
			}
			else if (it2 == dict2.end()) //La clave de it2 es infinito
			{
				//Computar diferencia
				removed.push_back((*it1).first);
				//Avanzar
				it1++;
			}
			else if ((*it1).first < (*it2).first)
			{
				//Computar diferencia
				removed.push_back((*it1).first);
				//Avanzar
				it1++;
			}
			else if ((*it1).first > (*it2).first)
			{
				//Computar diferencia
				added.push_back((*it2).first);
				//Avanzar
				it2++;
			}
			else //Claves iguales
			{
				//Computar diferencia
				if ((*it1).second != (*it2).second)
				{
					modified.push_back((*it1).first);
				}
				//Avanzar
				it1++;
				it2++;
			}
		}
		//Imprimir datos
		if (added.empty() && modified.empty() && removed.empty())
		{
			cout << "Sin cambios\n";
		}
		else
		{
			if (!added.empty())
			{
				cout << "+";
				for (string elem : added)
				{
					cout << " " << elem;
				}
				cout << "\n";
			}
			if (!removed.empty())
			{
				cout << "-";
				for (string elem : removed)
				{
					cout << " " << elem;
				}
				cout << "\n";
			}
			if (!modified.empty())
			{
				cout << "*";
				for (string elem : modified)
				{
					cout << " " << elem;
				}
				cout << "\n";
			}
		}
		cout << "---\n";
	}
}