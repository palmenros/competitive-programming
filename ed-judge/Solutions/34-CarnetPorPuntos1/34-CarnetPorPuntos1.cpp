#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef string dni_t;
typedef unsigned int puntos_t;

class carnet_puntos {
private:

	// m[dni] = numero de puntos del usuario con dni "dni"
	unordered_map<dni_t, puntos_t> m;

	// arr[puntos] = numero de usuarios con "puntos" puntos
	size_t arr [16];

public:

	carnet_puntos() {
		for(int i = 0; i < 16; i++) {
			arr[i] = 0;
		}
	}

	void nuevo(const dni_t& dni) {
		auto[it, succeeded] = m.insert({dni, 15});

		if(!succeeded) {
			throw domain_error("Conductor duplicado");
		}

		arr[15]++;
	}

	void quitar(const dni_t& dni, puntos_t puntos) {
		auto it = m.find(dni);

		if(it == m.end()) {
			throw domain_error("Conductor inexistente");
		}

		auto& [key, value] = *it;

		auto old = value;

		if(value < puntos) {
			value = 0;
		} else {
			value -= puntos;
		}

		if(old != value) {
			arr[old]--;
			arr[value]++;
		}
	}

	puntos_t consultar(const dni_t& dni) {
		auto it = m.find(dni);

		if(it == m.end()) {
			throw domain_error("Conductor inexistente");
		}

		return it->second;
	}

	size_t cuantos_con_puntos(puntos_t puntos) {
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
			}
		} catch(exception& e) {
			cout << "ERROR: " << e.what() << endl;
		}

	}


	return 0;
}