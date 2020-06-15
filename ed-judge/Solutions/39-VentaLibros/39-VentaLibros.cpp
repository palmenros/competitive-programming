#include <unordered_map>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

typedef string Libro;

struct Venta {
	Libro libro;
	int ventas;
	int numeroVenta;

	Venta(const Libro &libro, int ventas, int numeroVenta)
		: libro(libro), ventas(ventas), numeroVenta(numeroVenta)
	{}

	bool operator<(const Venta& other) const {
		if(ventas == other.ventas) {
			return numeroVenta > other.numeroVenta;
		}

		return ventas > other.ventas;
	}
};

struct InfoLibro {
	int ejemplares;
	set<Venta>::iterator it;

	InfoLibro(int ejemplares, const set<Venta>::iterator &it)
		: ejemplares(ejemplares), it(it)
	{}

	InfoLibro()
	{}
};

class Tienda {
private:

	unordered_map<Libro, InfoLibro> db;
	set<Venta> vendidos;

	int numeroVenta = 0;

public:

	void nuevoLibro(int n, const Libro& libro) {
		auto [it, succeeded] = db.insert({libro, { n, vendidos.end() }});

		if(!succeeded) {
			db[libro].ejemplares += n;
		}
	}

	void comprar(const Libro& libro) {
		auto it = db.find(libro);

		if(it == db.end()) {
			throw invalid_argument("Libro no existente");
		}

		auto& info = it->second;
		if(info.ejemplares == 0) {
			throw out_of_range("No hay ejemplares");
		}

		info.ejemplares--;

		if(info.it == vendidos.end()) {
			//No se habia vendido antes
			auto[itS, succeed] = vendidos.insert(Venta{ libro, 1, numeroVenta++ });
			info.it = itS;
		} else {
			int ventas = info.it->ventas + 1;
			vendidos.erase(info.it);
			auto[itS, succeed] = vendidos.insert(Venta{ libro, ventas, numeroVenta++ });
			info.it = itS;
		}
	}

	bool estaLibro(const Libro& libro) {
		return db.count(libro) > 0;
	}

	void elimLibro(const Libro& libro) {
		auto it = db.find(libro);

		if(it == db.end()) {
			return;
		}

		auto info = it->second;
		if(info.it != vendidos.end()) {
			vendidos.erase(info.it);
		}

		db.erase(it);
	}

	int numEjemplares(const Libro& libro) {
		auto it = db.find(libro);

		if(it == db.end()) {
			throw invalid_argument("Libro no existente");
		}

		return it->second.ejemplares;
	}

	vector<Libro> top10() {
		int n = min((size_t) 10, vendidos.size());

		auto it = vendidos.begin();

		vector<Libro> v;

		for(int i = 0; i < n; i++, ++it) {
			v.push_back(it->libro);
		}

		return v;
	}

};

void leerLibro(Libro& libro) {
	getline(cin, libro);
	libro.erase(libro.begin());
}

int main()
{
	int nOperations;
	while(cin >> nOperations) {
		Tienda T;

		while (nOperations--) {

			string operation;
			cin >> operation;

			try {
				if (operation == "nuevoLibro") {
					int n;
					Libro libro;
					cin >> n;

					leerLibro(libro);

					T.nuevoLibro(n, libro);
				}
				else if (operation == "comprar") {
					Libro libro;
					leerLibro(libro);

					T.comprar(libro);
				}
				else if (operation == "estaLibro") {
					Libro libro;
					leerLibro(libro);

					bool res = T.estaLibro(libro);

					if (res) {
						cout << "El libro " << libro << " esta en el sistema" << endl;
					}
					else {
						cout << "No existe el libro " << libro << " en el sistema" << endl;
					}

				}
				else if (operation == "elimLibro") {
					Libro libro;
					leerLibro(libro);

					T.elimLibro(libro);
				}
				else if (operation == "numEjemplares") {
					Libro libro;
					leerLibro(libro);

					try {
						int res = T.numEjemplares(libro);
						cout << "Existen " << res << " ejemplares del libro " << libro << endl;
					}
					catch (exception &e) {
						cout << "No existe el libro " << libro << " en el sistema" << endl;
					}

				}
				else if (operation == "top10") {
					auto v = T.top10();
					cout << "TOP10" << endl;

					for (const auto &el : v) {
						cout << "    " << el << endl;
					}
				}
			}
			catch (exception &e) {
				cout << e.what() << endl;
			}
		}

		cout << "---" << endl;
	}

	return 0;
}