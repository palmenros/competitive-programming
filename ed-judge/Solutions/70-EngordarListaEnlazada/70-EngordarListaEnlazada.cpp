//
// Created by pedro on 20/3/20.
//

#include "deque_eda.h"
#include <iostream>
#include <iomanip>

using namespace std;

enum Posicion {
	Delante = 0,
	Atras	= 1
};
template<class T>
class fatten_deque : public deque<T> {
	using Nodo = typename deque<T>::Nodo;

public:

	void engordar(fatten_deque<T>& other) {
		if(other.nelems == 0) {
			return;
		}

		this->nelems += other.nelems;
		Posicion pos = Delante;

		Nodo* n = other.fantasma->sig;
		while(n != other.fantasma) {

			Nodo* siguienteARecorrer = n->sig;

			if(pos == Delante) {
				//Insertar n delante

				n->ant = this->fantasma;
				n->sig = this->fantasma->sig;
				n->sig->ant = n;
				this->fantasma->sig = n;

				pos = Atras;
			} else {
				//Insertar n detras
				n->sig = this->fantasma;
				n->ant = this->fantasma->ant;
				n->ant->sig = n;
				this->fantasma->ant = n;

				pos = Delante;
			}

			n = siguienteARecorrer;
		}

		//Vaciar la otra lista
		other.fantasma->sig = other.fantasma;
		other.fantasma->ant = other.fantasma;
		other.nelems = 0;
	}

	void print() const {
		if(this->nelems == 0) {
			return;
		}

		Nodo* n = this->fantasma->sig;

		bool first = true;
		while(n != this->fantasma) {
			if(first) {
				first = false;
			} else {
				cout << " ";
			}

			cout << n->elem;
			n = n->sig;
		}
		cout << endl;
	}

};

fatten_deque<int> leer_lista(int n) {
	fatten_deque<int> q;

	for(int i = 0; i < n; i++) {
		int val;
		cin >> val;
		q.push_back(val);
	}

	return q;
}

int main()
{
	int N;
	cin >> N;
	while(N--) {
		int a;
		cin >> a;

		auto qa = leer_lista(a);

		int b;
		cin >> b;

		auto qb = leer_lista(b);

		qa.engordar(qb);
		qa.print();
	}

	return 0;
}