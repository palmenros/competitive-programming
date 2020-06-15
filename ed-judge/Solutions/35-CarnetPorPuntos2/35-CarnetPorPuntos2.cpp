#include <iostream>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <array>

using namespace std;

typedef string dni_t;
typedef unsigned int puntos_t;

struct persona_t {

public:
	puntos_t puntos;
	list<dni_t>::iterator it;

	persona_t(puntos_t puntos)
		: puntos(puntos)
	{}

	persona_t(puntos_t puntos, list<dni_t>::iterator it)
		: puntos(puntos), it(it)
		{}
};

class carnet_puntos {
private:

	// m[dni] = numero de puntos del usuario con dni "dni"
	unordered_map<dni_t, persona_t> m;

	// arr[puntos] = lista de usuarios con "puntos" puntos
	array<list<dni_t>, 16> arr;

public:

	void nuevo(const dni_t& dni) {
		auto[it, succeeded] = m.insert({ dni, persona_t{15} });

		if(!succeeded) {
			throw domain_error("Conductor duplicado");
		}

		auto list_it = arr[15].insert(arr[15].end(), dni);

		auto& [key, val] = *it;

		val.it = list_it;
	}

	void quitar(const dni_t& dni, puntos_t puntos) {
		auto it = m.find(dni);

		if(it == m.end()) {
			throw domain_error("Conductor inexistente");
		}

		auto& [key, value] = *it;

		auto old = value.puntos;

		if(value.puntos < puntos) {
			value.puntos = 0;
		} else {
			value.puntos -= puntos;
		}

		if(old != value.puntos) {
			arr[old].erase(value.it);

			auto list_it = arr[value.puntos].insert(arr[value.puntos].end(), dni);
			value.it = list_it;
		}
	}

	void recuperar(const dni_t& dni, puntos_t puntos) {
		auto it = m.find(dni);

		if(it == m.end()) {
			throw domain_error("Conductor inexistente");
		}

		auto& [key, value] = *it;

		auto old = value.puntos;

		if(value.puntos + puntos > 15) {
			value.puntos = 15;
		} else {
			value.puntos += puntos;
		}

		if(old != value.puntos) {
			arr[old].erase(value.it);

			auto list_it = arr[value.puntos].insert(arr[value.puntos].end(), dni);
			value.it = list_it;
		}
	}

	puntos_t consultar(const dni_t& dni) {
		auto it = m.find(dni);

		if(it == m.end()) {
			throw domain_error("Conductor inexistente");
		}

		return it->second.puntos;
	}

	size_t cuantos_con_puntos(puntos_t puntos) {
		if(puntos < 0 || puntos > 15) {
			throw domain_error("Puntos no validos");
		}

		return arr[puntos].size();
	}

	list<dni_t> lista_por_puntos(puntos_t puntos) {
		if(puntos < 0 || puntos > 15) {
			throw domain_error("Puntos no validos");
		}

		return arr[puntos];
	}

};

int main()
{
	carnet_puntos db;
	string operation;
	while(cin >> operation) {

		if(operation == "FIN") {
			db = carnet_puntos{};
			cout << "---" << endl;
		}

		try {
			if (operation == "nuevo") {
				dni_t dni;
				cin >> dni;

				db.nuevo(dni);
			}
			else if (operation == "quitar") {
				dni_t dni;
				puntos_t puntos;
				cin >> dni >> puntos;

				db.quitar(dni, puntos);
			}
			else if (operation == "recuperar") {
				dni_t dni;
				puntos_t puntos;
				cin >> dni >> puntos;

				db.recuperar(dni, puntos);
			}
			else if (operation == "consultar") {
				dni_t dni;
				cin >> dni;

				auto val = db.consultar(dni);

				cout << "Puntos de " << dni << ": " << val << endl;
			}
			else if (operation == "cuantos_con_puntos") {
				puntos_t puntos;
				cin >> puntos;

				auto val = db.cuantos_con_puntos(puntos);

				cout << "Con " << puntos << " puntos hay " << val << endl;
			} else if (operation == "lista_por_puntos") {
				puntos_t puntos;
				cin >> puntos;

				auto val = db.lista_por_puntos(puntos);

				cout << "Tienen " << puntos << " puntos:";

				for(auto it = val.rbegin(); it != val.rend(); it++) {
					cout << " " << *it;
				}

				cout << endl;
			}

		} catch(exception& e) {
			cout << "ERROR: " << e.what() << endl;
		}

	}


	return 0;
}