//
// Created by pedro on 15/6/20.
//

#include <algorithm>
#include <functional>
#include <stack>
#include <stdexcept>
#include <iostream>

using namespace std;

template <class T, class Comparator = std::less<T>>
class set {
	using set_t = set<T, Comparator>;

	/*
	 Nodo que almacena internamente el elemento (de tipo T),
	 y punteros al hijo izquierdo y derecho, que pueden ser
	 nullptr si el hijo es vacío.
	 */
	struct TreeNode;
	using Link = TreeNode *;
	struct TreeNode {
		T elem;
		Link iz, dr;
		TreeNode(T const& e, Link i = nullptr, Link d = nullptr) :
			elem(e), iz(i), dr(d) {}
	};

	// puntero a la raíz de la estructura jerárquica de nodos
	Link raiz;

	// número de elementos (cardinal del conjunto)
	int nelems;

	// objeto función que compara elementos (orden total estricto)
	Comparator menor;

public:

	// constructor (conjunto vacío)
	set(Comparator c = Comparator()) : raiz(nullptr), nelems(0), menor(c) {}

	// constructor por copia
	set(set_t const& other) {
		copia(other);
	}

	// operador de asignación
	set_t & operator=(set_t const& that) {
		if (this != &that) {
			libera(raiz);
			copia(that);
		}
		return *this;
	}

	~set() {
		libera(raiz);
	};

	bool insert(T const& e) {
		return inserta(e, raiz);
	}

	bool empty() const {
		return raiz == nullptr;
	}

	int size() const {
		return nelems;
	}

	int count(T const& e) const  {
		return pertenece(e, raiz) ? 1 : 0;
	}

	bool erase(T const& e) {
		return borra(e, raiz);
	}

protected:

	void copia(set_t const& other) {
		raiz = copia(other.raiz);
		nelems = other.nelems;
		menor = other.menor;
	}

	static Link copia(Link a) {
		if (a == nullptr) return nullptr;
		else return new TreeNode(a->elem, copia(a->iz), copia(a->dr));
	}

	static void libera(Link a) {
		if (a != nullptr){
			libera(a->iz);
			libera(a->dr);
			delete a;
		}
	}

	bool pertenece(T const& e, Link a) const {
		if (a == nullptr) {
			return false;
		}
		else if (menor(e, a->elem)) {
			return pertenece(e, a->iz);
		}
		else if (menor(a->elem, e)) {
			return pertenece(e, a->dr);
		}
		else { // e == a->elem
			return true;
		}
	}

	bool inserta(T const& e, Link & a) {
		if (a == nullptr) {
			a = new TreeNode(e);
			++nelems;
			return true;
		}
		else if (menor(e, a->elem)) {
			return inserta(e, a->iz);
		}
		else if (menor(a->elem, e)) {
			return inserta(e, a->dr);
		}
		else // el elemento e ya está en el árbol
			return false;
	}

	bool borra(T const& e, Link & a)  {
		if (a == nullptr)
			return false;
		else {
			if (menor(e, a->elem)) {
				return borra(e, a->iz);
			}
			else if (menor(a->elem, e)) {
				return borra(e, a->dr);
			}
			else { // e == a->elem
				if (a->iz == nullptr || a->dr == nullptr) {
					Link aux = a;
					a = (a->iz == nullptr) ? a->dr : a->iz;
					--nelems;
					delete aux;
				}
				else { // tiene dos hijos
					subirMenorHD(a);
					--nelems;
				}
				return true;
			}
		}
	}

	static void subirMenorHD(Link & a) {
		Link b = a->dr, padre = nullptr;
		while (b->iz != nullptr) {
			padre = b;
			b = b->iz;
		}
		if (padre != nullptr) {
			padre->iz = b->dr;
			b->dr = a->dr;
		}
		b->iz = a->iz;
		delete a;
		a = b;
	}

public:
	// iterador que recorre los elementos del conjunto de menor a mayor
	class const_iterator {
	public:
		T const& operator*() const {
			if (act == nullptr)
				throw std::out_of_range("No hay elemento a consultar");
			return act->elem;
		}

		T const* operator->() const {
			return &operator*();
		}

		const_iterator & operator++() {  // ++ prefijo
			next();
			return *this;
		}

		bool operator==(const_iterator const& that) const {
			return act == that.act;
		}

		bool operator!=(const_iterator const& that) const {
			return !(this->operator==(that));
		}

	protected:
		friend class set;
		Link act;
		std::stack<Link> ancestros;  // antecesores no visitados

		// construye el iterador al primero
		const_iterator(Link raiz) { act = first(raiz); }

		// construye el iterador al último
		const_iterator() : act(nullptr) {}

		Link first(Link ptr) {
			if (ptr == nullptr) {
				return nullptr;
			} else { // buscamos el nodo más a la izquierda
				while (ptr->iz != nullptr) {
					ancestros.push(ptr);
					ptr = ptr->iz;
				}
				return ptr;
			}
		}

		void next() {
			if (act == nullptr) {
				throw std::out_of_range("El iterador no puede avanzar");
			} else if (act->dr != nullptr) { // primero del hijo derecho
				act = first(act->dr);
			} else if (ancestros.empty()) { // hemos llegado al final
				act = nullptr;
			} else { // podemos retroceder
				act = ancestros.top();
				ancestros.pop();
			}
		}
	};

	const_iterator begin() const {
		return const_iterator(raiz);
	}

	const_iterator end() const {
		return const_iterator();
	}

private:

	int count_interval(const T& start, const T& end, Link el) {
		if(el == nullptr) {
			return 0;
		}

		int res = 0;

		if(!menor(el->elem, start) && ! menor(end, el->elem)) {
			res = 1;
		}

		if(menor(start, el->elem)) {
			res += count_interval(start, min(el->elem, end), el->iz);
		}

		if(menor(el->elem, end)) {
			res += count_interval(max(start, el->elem), end, el->dr);
		}

		return res;
	}

public:

	//[start, end]
	int count_interval(const T& start, const T& end) {
		return count_interval(start, end, raiz);
	}

};

int main() {

	int N, M;

	while(cin >> N >> M) {
		set<int> s;

		while(N--) {
			int tmp;
			cin >> tmp;
			s.insert(tmp);
		}

		while(M--) {
			int start, end;
			cin >> start >> end;

			cout << s.count_interval(start, end) << endl;
		}

		cout << "---" << endl;
	}

}