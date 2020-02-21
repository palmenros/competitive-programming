#pragma once
#include "queue_eda.h"
#include <iostream>
#include <stdexcept>
//Siento haber subido el queue_eda pero Visual confunde las dos queues
template <class T>
class listaMergeadora : public queue_eda<T>
{
	using Nodo = typename queue_eda<T>::Nodo;
public:
	void mergear(listaMergeadora<int>& otra) //Coste lineal
	{
		//Lo que hay que hacer es ver cu�l tiene el front menor e insertar ese. Hay que dejar de coger de this
		//cuando ya hayamos cogido todos sus elementos
		//Primero procesamos el n�mero de elementos
		this->nelems += otra.nelems;
		otra.nelems = 0;
		auto actA = this->prim;
		auto actB = otra.prim;
		//Este ser� el �ltimo procesado.
		Nodo* lastAdded = nullptr;
		//Lo haremos de forma que sea correcto en cualquier caso extremo
		otra.prim = nullptr;
		otra.ult = nullptr;

		
		while (actA!=nullptr || actB!=nullptr)
		{
			Nodo* elegido;
			if (actA != nullptr && actB == nullptr) //Solo podemos coger elementos de this
			{
				elegido = actA; actA = actA->sig;
			}
			else if (actA == nullptr && actB != nullptr) //Solo podemos coger elementos de otra
			{
				elegido = actB; actB = actB->sig;
			}
			else //Hay que elegir cu�l cogemos para mantener el orden
			{
				if (actA->elem < actB->elem)
				{
					elegido = actA; actA = actA->sig;
				}
				else
				{
					elegido = actB; actB = actB->sig;
				}

			}
			//Si no hemos a�adido ninguno, tendremos que cambiar el puntero del primero
			if (lastAdded == nullptr)
			{
				this->prim = elegido;
			}
			//Si ya hemos a�adido, hay que enlazar
			else
			{
				lastAdded->sig = elegido;
			}
			//Avanzamos
			lastAdded = elegido;
		}
		//Ya hemos terminado. Ahora bien, el �ltimo tiene como siguiente nullptr porque era el �ltimo de alguna cola
		//Simplemente actualizamos el �ltimo de this
		this->ult = lastAdded;
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