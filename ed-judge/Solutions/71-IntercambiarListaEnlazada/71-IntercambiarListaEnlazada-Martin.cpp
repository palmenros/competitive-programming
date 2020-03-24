#include <iostream>
#include "queue_eda.h"
using namespace std;

template <class T>
class colaInsertora : public queue<T>
{
	using Nodo = typename queue<T>::Nodo;
public:
	void intercambiarDosEnDos()
	{
		//Trivialmente lineal; en un bucle con coste de cada vuelta constante recorremos dos elementos
		//Distinguimos casos
		if (this->nelems<2)
		{
			return;
		}
		//Ahora tenemos garantizado que hay dos elementos
		Nodo* act1 = this->prim;
		Nodo* act2 = act1->sig;
		//Para cambiar punteros más tarde
		Nodo* ant = nullptr;
		//El primero se convierte en el segundo
		this->prim = act2;
		//Recorremos la cola
		while (act1 != nullptr && act2 != nullptr) //Con act2 != nullptr bastaría pero así queda claro
		{
			//Hay que intercambiarlos y avanzar
			//Para interambiar, hay que cambiar los punteros de los tres elementos
			Nodo* aux = act2->sig;
			//Distinguimos casos en función de si estamos en la primera iteración o no
			if (ant != nullptr)
			{
				ant->sig = act2;
			}
			act2->sig = act1;
			act1->sig = aux;
			//Hay que avanzar cuidadosamente (de dos en dos)
			ant = act1;
			act1 = act1->sig;
			//Aquí está el peligro; al ser de dos en dos hay que distinguir casos
			act2 = (act1==nullptr?nullptr:act1->sig);
		}
		//En este punto act2 va a ser sí o sí nullptr
		//Guardamos el último
		//Teniendo cuidado con cada caso
		this->ult = (act1 == nullptr?ant:act1);

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
		colaInsertora<int> c;
		for (int i = 0; i < n; i++)
		{
			int aux;
			cin >> aux;
			c.push(aux);
		}
		c.intercambiarDosEnDos();
		c.imprimirEnCout();
	}
}