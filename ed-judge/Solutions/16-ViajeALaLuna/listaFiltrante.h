#include "list_eda.h"
#include <iostream>

template <class T>
class listaFiltrante : public list<T>
{
public:
	using Nodo = typename list<T>::Nodo;
	template <class Predicate>
	void remove_if(Predicate pred)
	{
		auto apuntado = this->begin();
		while (apuntado != this->end())
		{
			if (pred(*apuntado))
			{
				apuntado = this->erase(apuntado);
			}
			else
			{
				apuntado++;
			}
		}

	}
	void imprimirEnCout() //Trivialmente lineal
	{
		Nodo* aImprimir = this->fantasma->sig; //Vamos a sacarlos, imprimirlos y volverlos a poner, para poder utilizar esta función sin alterar
		while (aImprimir != this->fantasma)
		{
			
			std::cout << aImprimir->elem;
			aImprimir = aImprimir->sig;
		}
		std::cout << "---\n";
	}
};