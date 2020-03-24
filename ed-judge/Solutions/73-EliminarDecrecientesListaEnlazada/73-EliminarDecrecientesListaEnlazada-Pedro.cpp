//
// Created by pedro on 20/3/20.
//

#include "../queue_eda.h"
#include <iostream>
#include <iomanip>

using namespace std;

template<class T>
class delete_queue : public queue<T> {
	using Nodo = typename queue<T>::Nodo;

public:

	void borrar() {
		if(this->nelems <= 1) {
			return;
		}

		Nodo* ant = this->prim;
		Nodo* n = ant->sig;

		while(n != nullptr) {

			if(n->elem < ant->elem) {
				//Borrar n
				ant->sig = n->sig;
				this->nelems--;
				delete n;
			} else {
				ant = n;
			}
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

class horas {
private:
	int HH; // las horas
	int MM; // los minutos
	int SS; // los segundos

	bool check(int h, int m, int s) {
		return 0 <= h && h < 24 && 0 <= m && m < 60 && 0 <= s && s < 60;
	}

public:

	horas() : horas(0, 0, 0)
	{
	}

	// constructora
	horas(int h, int m, int s) : HH(h), MM(m), SS(s) {
		if (!check(h, m, s)) { throw std::domain_error("ERROR"); }
	}

	// observadoras
	int hora() const { return HH; }
	int minuto() const { return MM; }
	int segundo() const { return SS; }

	// operador de comparación
	bool operator<(horas const& h) const {
		return HH * 3600 + MM * 60 + SS < h.HH * 3600 + h.MM * 60 + h.SS;
	}

	void read(std::istream & input = std::cin) {
		char c;
		cin >> HH >> c >> MM >> c >> SS;
		if (!check(HH, MM, SS)) { throw std::domain_error("ERROR"); }
	}

	void print(std::ostream& o = std::cout) const {
		o << std::setfill('0') << std::setw(2) << HH << ':'
		  << std::setfill('0') << std::setw(2) << MM << ':'
		  << std::setfill('0') << std::setw(2) << SS;
	}
};

inline std::ostream & operator<<(std::ostream & salida, horas const& h) {
	h.print(salida);
	return salida;
}

inline std::istream & operator>>(std::istream & entrada, horas & h) {
	h.read(entrada);
	return entrada;
}


int main()
{
	int N;
	while(cin >> N && N != 0) {
		delete_queue<horas> q;
		for(int i = 0; i < N; i++) {
			horas val;
			cin >> val;
			q.push(val);
		}

		q.borrar();
		q.print();
	}

	return 0;
}