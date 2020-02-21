#pragma once
#include "queue_eda.h"
#include <iostream>
#include <stdexcept>
//Siento haber subido el queue_eda pero Visual confunde las dos queues
template <class T>
class listaDuplicadora : public queue_eda<T>
{
	using Nodo = typename queue_eda<T>::Nodo;
public:
	void duplicar() //Orden exacto lineal de la longitud
	{
		//Caso especial: no hacer nada
		if (!this->nelems) { return; }
		//Caso general; primero duplicamos elementos
		this->nelems *= 2;
		//Cogemos ahora el primer elemento
		auto act = this->prim;
		//Lo que viene ahora sirve en general, también para el caso de un elemento
		//Primero recorremos hasta llegar al último (tal vez esto no se ejecute)
		while (act != this->ult)
		{
			//Creamos un nodo igual que el que ya tenemos
			Nodo* nuevo = new Nodo(act->elem, act->sig);
			//Ahora cambiamos el siguiente de act
			act->sig = nuevo;
			//Por último, pasamos al siguiente
			act = nuevo->sig;
		}
		//Bien, hecho eso llegamos al último
		//Simplemente creamos un nodo nuevo al final y cambiamos referencia del último
		Nodo* nuevo = new Nodo(this->ult->elem, nullptr);
		this->ult->sig = nuevo;
		this->ult = nuevo;
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