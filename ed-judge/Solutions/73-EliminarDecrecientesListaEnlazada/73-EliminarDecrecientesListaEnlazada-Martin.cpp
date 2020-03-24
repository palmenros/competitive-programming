#include <iostream>
#include "queue_eda.h"
#include "horas.h"
using namespace std;

template <class T>
class colaEliminadora : public queue<T>
{
	using Nodo = typename queue<T>::Nodo;
public:
	void eliminarCrecientemente()
	{
		//La recorremos desde el principio, retirando los elementos que no cumplan la condici�n
		Nodo* act = this->prim;
		//Guardaremos el nodo anterior para comparar, dejar la cola en buen estado y cambiar punteros
		Nodo* ant = nullptr;
		//El primero ser� siendo el primero por las especificaciones del problema
		//Recorremos la cola
		while (act != nullptr)
		{
			//Retiramos si procede
			if (ant != nullptr && act->elem < ant->elem)
			{
				this->nelems--; //Hay que dejar la cola en buen estado
				ant->sig = act->sig;
				delete act;
				act = ant; //Para avanzar correctamente
			}
			//Avanzamos
			ant = act;
			act = act->sig;
		}
		//Guardamos el �ltimo
		this->ult = ant;

	}
	void imprimirEnCout() //Trivialmente lineal
	{
		Nodo* aImprimir = this->prim; //Vamos a sacarlos, imprimirlos y volverlos a poner, para poder utilizar esta funci�n sin alterar
		while (aImprimir != nullptr)
		{
			if (aImprimir != this->prim) { std::cout << " "; }
			std::cout << aImprimir->elem;
			aImprimir = aImprimir->sig;
		}
		std::cout << "\n";
	}
};

int main()
{
	while (true)
	{
		int n;
		cin >> n;
		if (!n)
		{
			return 0;
		}
		colaEliminadora<horas> c;
		for (int i = 0; i < n; i++)
		{
			horas aux;
			cin >> aux;
			c.push(aux);
		}
		c.eliminarCrecientemente();
		c.imprimirEnCout();
	}
}