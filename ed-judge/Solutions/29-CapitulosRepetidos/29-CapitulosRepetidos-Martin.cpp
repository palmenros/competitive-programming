#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;

void resuelveCaso()
{
	//Lineal en lVec, ya que en cada vuelta avanzamos alg�n iterador,
	//cada vuelta tiene coste constante (unordered_set)
	//y cada iterador avanza lVec posiciones
	int lVec;
	cin >> lVec;
	int lMaxima = 0; //Variable que tendr� el dato que nos interesa
	vector<int> v;
	v.reserve(lVec);
	//Leer datos
	for (int i = 0; i < lVec; i++)
	{
		int aux;
		cin >> aux;
		v.push_back(aux);
	}
	//Tendremos dos iteradores, uno al principio de un segmento y otro al final
	//Haremos avanzar los iteradores de forma que marquen el comienzo y el final de los segmentos que nos interesan
	//Conjunto de elementos en el intervalo en el que estamos
	unordered_set<int> enIntervaloActual;
	//Iteradores
	auto it1 = v.begin();
	auto it2 = v.begin();
	//Bucle para avanzar los iteradores
	while (it2 != v.end()) //Cuando el iterador de la derecha llegue al final, ya no habr� longitudes m�s largas
	{
		int elemPrevio = *it2;
		//Avanzar por la derecha
		it2++;
		//Distinguir entre estar repitiendo elemento o no
		if (enIntervaloActual.count(elemPrevio)) //Si el elemento est� en el conjunto
		{
			//Retiramos hasta retirar elemPrevio
			int retirado;
			do
			{
				retirado = *it1;
				it1++;
				enIntervaloActual.erase(retirado);
			} while (elemPrevio != retirado);
			//A�adimos elemPrevio
			enIntervaloActual.insert(elemPrevio);
		}
		else //Si no est�
		{
			//A�adir
			enIntervaloActual.insert(elemPrevio);
			//Actualizar longitud
			lMaxima = max(lMaxima, (int)(it2-it1));
		}



	}
	cout << lMaxima << "\n";
}


int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		resuelveCaso();
	}
	return 0;
}