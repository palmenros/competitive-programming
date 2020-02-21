#pragma once
#include "deque_eda.h"
#include <iostream>
#include <stdexcept>
//Siento haber subido el deque_eda pero Visual confunde las dos deques
template <class T>
class listaReversible : public deque_eda<T>
{
	using Nodo = typename deque_eda<T>::Nodo;
public:
	void reverse() //Orden exacto lineal de la longitud
	{
		//Lo que vamos a hacer es coger cada elemento, invertirlo y seguir adelante en el nuevo orden
		//Hasta llegar a fantasma
		//Primero lo hacemos con el fantasma
		Nodo* act = this->fantasma;
		//Siempre lo hacemos con el fantasma, y luego seguimos hasta llegar al fantasma.
		//Esto es válido también si no hay elementos
		do
		{
			Nodo* a = act->sig;
			Nodo* b = act->ant;
			act->sig = b;
			act->ant = a;
			act = act->sig;
		}
		while (act != this->fantasma);
	}
	void imprimirEnCout() //Trivialmente lineal
	{
		Nodo* aImprimir = this->fantasma->sig; //Vamos a sacarlos, imprimirlos y volverlos a poner, para poder utilizar esta función sin alterar
		while (aImprimir != this->fantasma)
		{
			if (aImprimir != this->fantasma->sig) { std::cout << " "; }
			std::cout << aImprimir->elem;
			aImprimir = aImprimir->sig;
		}
		std::cout << "\n";
	}
};