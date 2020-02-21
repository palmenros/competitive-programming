#pragma once
#include "queue_eda.h"
#include <iostream>
#include <stdexcept>
//Siento haber subido el queue_eda pero Visual confunde las dos queues
template <class T>
class listaInsertora : public queue_eda<T>
{
	using Nodo = typename queue_eda<T>::Nodo;
public:
	void annadirEnIndice(listaInsertora<T>& otra, const int& donde) //Orden exacto de donde más el tamaño de la otra
	{
		if (!otra.nelems) { return; } //Caso especial; nada que hacer
		//Vamosa recorrer la cola internamente hasta llegar al sitio adecuado, y después engancharemos una a la otra
		int n = this->nelems;
		if (!(donde >= 0 && donde <= n)) { throw std::domain_error("Indice no valido"); } //Comprobar indice
		this->nelems += otra.nelems;
		otra.nelems = 0;
		
		//Caso especial: nuestra cola está vacía
		if (this->prim == nullptr)
		{
			this->prim = otra.prim;
			this->ult = otra.ult;
			otra.prim = nullptr;
			otra.ult = nullptr;
		}
		//Caso especial: meterlos al principio
		else if (!donde)
		{
			//Enlazamos una con otra
			otra.ult->sig = this->prim;
			//Cambiamos referencias prim/ult
			this->prim = otra.prim;
			otra.prim = nullptr;
			otra.ult = nullptr;

		}
		//Caso especial: meterlos al final
		else if (donde == n)
		{
			//Enlazamos una con otra
			this->ult->sig = otra.prim;
			//Cambiamos referencias prim/ult
			this->ult = otra.ult;
			otra.prim = nullptr;
			otra.ult = nullptr;
		}
		else
		{
			auto act = this->prim;
			auto actant = this->prim;
			//Encontramos dónde hay que meter
			for (int i = 0; i < donde; i++)
			{
				actant = act;
				act = act->sig;
			}
			//Ahora tenemos que enlazar
			actant->sig = otra.prim;
			otra.ult->sig = act;
			//Ahora otra se borra
			otra.prim = nullptr;
			otra.ult = nullptr;
		}
		

	}
	void imprimirEnCout() //Trivialmente lineal
	{
		Nodo* aImprimir = this->prim; //Vamos a sacarlos, imprimirlos y volverlos a poner, para poder utilizar esta función sin alterar
		while (aImprimir != nullptr)
		{
			if (aImprimir != this->prim) { std::cout << " "; }
			std::cout << aImprimir->elem;
			aImprimir = aImprimir->sig;
		}
		std::cout << "\n";
	}
};