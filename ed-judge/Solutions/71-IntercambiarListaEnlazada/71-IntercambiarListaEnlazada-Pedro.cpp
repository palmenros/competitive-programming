//
// Created by pedro on 20/3/20.
//

#include "../queue_eda.h"
#include <iostream>

using namespace std;

template<class T>
class swap_queue : public queue<T> {
	using Nodo = typename queue<T>::Nodo;

public:

	void swap() {

		if(this->nelems <= 1) {
			return;
		}

		Nodo* ant = nullptr;
		Nodo* n = this->prim;

		//Actualizar la referencia al primer nodo
		this->prim = n->sig;

		while(n != nullptr) {

			if(n->sig != nullptr) {
				//Intercambiar este y el siguiente
				Nodo* nuevoSig = n->sig->sig;
				Nodo* nuevoPrim = n->sig;

				if(ant != nullptr) {
					ant->sig = nuevoPrim;
				}
				nuevoPrim->sig = n;
				n->sig = nuevoSig;
			}

			ant = n;
			n = n->sig;
		}

		this->ult = ant;
	}

	void print() const {
		Nodo* n = this->prim;
		bool first = true;
		while(n != nullptr) {
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

int main()
{
	int N;
	while(cin >> N && N != 0) {
		swap_queue<int> q;
		for(int i = 0; i < N; i++) {
			int val;
			cin >> val;
			q.push(val);
		}

		q.swap();
		q.print();
	}

	return 0;
}