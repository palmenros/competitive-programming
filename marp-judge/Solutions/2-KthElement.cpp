//
// Created by pedro on 10/11/20.
//

#include <iostream>
#include <stack>
using namespace std;

template <class T, class Comparator = std::less<T>>
class Set {
protected:

	/*
	 Nodo que almacena internamente el elemento (de tipo T),
	 punteros al hijo izquierdo y derecho, que pueden ser
	 nullptr si el hijo es vacío, y la altura.
	 */
	struct TreeNode;
	using Link = TreeNode *;
	struct TreeNode {
		T elem;
		Link iz, dr;
		int altura;
		int tam_i;
		TreeNode(T const& e, Link i = nullptr, Link d = nullptr,
				 int alt = 1) : elem(e), iz(i), dr(d), altura(alt) {
			if(i == nullptr) {
				tam_i = 1;
			} else {
				tam_i = i->tam_i + 1;
			}
		}
	};

	// puntero a la raíz de la estructura jerárquica de nodos
	Link raiz;

	// número de elementos (cardinal del conjunto)
	int nelems;

	// objeto función que compara elementos (orden total estricto)
	Comparator menor;

public:

	// constructor (conjunto vacío)
	Set(Comparator c = Comparator()) : raiz(nullptr), nelems(0), menor(c) {}

	// constructor por copia
	Set(Set const& other) {
		copia(other);
	}

	// operador de asignación
	Set & operator=(Set const& that) {
		if (this != &that) {
			libera(raiz);
			copia(that);
		}
		return *this;
	}

	~Set() {
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

	bool contains(T const& e) const {
		return pertenece(e, raiz);
	}

	T const& kesimo(int k) const {
		return kesimo_recursivo(raiz, k);
	}

	T const& kesimo_recursivo(Link l, int k) const {
		if(l == nullptr) {
			throw std::domain_error("No existe");
		} else if (l->tam_i == k) {
			return l->elem;
		} else if (l->tam_i < k) {
			//El k esimo tiene que estar a la derecha
			return kesimo_recursivo(l->dr, k - l->tam_i);
		} else if (l->tam_i > k) {
			//El k esimo tiene que estar a la izquierda
			return kesimo_recursivo(l->iz, k);
		}
	}

protected:

	void copia(Set const& other) {
		raiz = copia(other.raiz);
		nelems = other.nelems;
		menor = other.menor;
	}

	static Link copia(Link a) {
		if (a == nullptr) return nullptr;
		else return new TreeNode(a->elem, copia(a->iz), copia(a->dr), a->altura);
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
		bool crece;
		if (a == nullptr) { // se inserta el nuevo elemento e
			a = new TreeNode(e);
			++nelems;
			crece = true;
		} else if (menor(e, a->elem)) {
			crece = inserta(e, a->iz);
			if (crece) {
				a->tam_i += 1;
				reequilibraDer(a);
			}
		} else if (menor(a->elem, e)) {
			crece = inserta(e, a->dr);
			if (crece) reequilibraIzq(a);
		} else // el elemento e ya está en el árbol
			crece = false;
		return crece;
	}

	int altura(Link a) {
		if (a == nullptr) return 0;
		else return a->altura;
	}

	void rotaDer(Link & r2) {
		Link r1 = r2->iz;

		r2->tam_i -= r1->tam_i;

		r2->iz = r1->dr;
		r1->dr = r2;
		r2->altura = std::max(altura(r2->iz), altura(r2->dr)) + 1;
		r1->altura = std::max(altura(r1->iz), altura(r1->dr)) + 1;
		r2 = r1;
	}

	void rotaIzq(Link & r1) {
		Link r2 = r1->dr;

		r2->tam_i += r1->tam_i;

		r1->dr = r2->iz;
		r2->iz = r1;
		r1->altura = std::max(altura(r1->iz), altura(r1->dr)) + 1;
		r2->altura = std::max(altura(r2->iz), altura(r2->dr)) + 1;
		r1 = r2;
	}

	void rotaIzqDer(Link & r3) {
		rotaIzq(r3->iz);
		rotaDer(r3);
	}

	void rotaDerIzq(Link & r1) {
		rotaDer(r1->dr);
		rotaIzq(r1);
	}

	void reequilibraIzq(Link & a) {
		if (altura(a->dr) - altura(a->iz) > 1) {
			if (altura(a->dr->iz) > altura(a->dr->dr))
				rotaDerIzq(a);
			else rotaIzq(a);
		}
		else a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
	}

	void reequilibraDer(Link & a) {
		if (altura(a->iz) - altura(a->dr) > 1) {
			if (altura(a->iz->dr) > altura(a->iz->iz))
				rotaIzqDer(a);
			else rotaDer(a);
		}
		else a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
	}

};

int main()
{
	int N;
	while(cin >> N && N != 0) {
		Set<int> s;

		while(N--) {
			int i;
			cin >> i;

			s.insert(i);
		}

		int M;
		cin >> M;

		while(M--) {
			int k;
			cin >> k;
			try {
				int res = s.kesimo(k);
				cout << res << endl;
			} catch(exception& e) {
				cout << "??" << endl;
			}
		}

		cout << "---" << endl;
	}


	return 0;
}