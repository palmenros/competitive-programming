#include <iostream>
#include <unordered_map>
#include <map>
#include <optional>
#include <utility>
#include <vector>

using namespace std;

typedef string Profesor;
typedef string Alumno;

struct InfoAlumno {
	int puntuacion;
	string profesor;

	InfoAlumno(int puntuacion, string profesor)
		: puntuacion(puntuacion), profesor(std::move(profesor))
	{}

};


class Autoescuela {
private:

	unordered_map<Alumno, InfoAlumno> ma;
	unordered_map<Profesor, map<Alumno, int> > mp;

public:

	void alta(const Alumno& a, const Profesor& p) {
		auto [itA, success] = ma.insert({a, InfoAlumno{0, p}});

		if(success) {
			//Nuevo alumno
			mp[p][a] = 0;
		} else {
			//Alumno ya creado

			auto& info = itA->second;
			Profesor profesorAntiguo = info.profesor;

			info.profesor = p;

			//Dar de baja del anterior profesor
			mp[profesorAntiguo].erase(a);

			//Darlo de alta en el nuevo profesor
			mp[p][a] = info.puntuacion;
		}
	}

	bool es_alumno(const Alumno& a, const Profesor& p) {
		auto itA = ma.find(a);

		if(itA != ma.end()) {
			return itA->second.profesor == p;
		}

		return false;
	}

	int puntuacion(const Alumno& a) {
		auto itA = ma.find(a);

		if(itA == ma.end()) {
			throw domain_error("El alumno " + a + " no esta matriculado");
		}

		return itA->second.puntuacion;
	}

	void actualizar(const Alumno& a, int n) {
		auto itA = ma.find(a);

		if(itA == ma.end()) {
			throw domain_error("El alumno " + a + " no esta matriculado");
		}

		itA->second.puntuacion += n;

		mp[itA->second.profesor][a] += n;
	}

	vector<Alumno> examen(const Profesor& p, int n) {
		vector<Alumno> v;

		auto itP = mp.find(p);

		if(itP != mp.end()) {
			for(const auto& [k, val] : itP->second) {
				if(val >= n) {
					v.push_back(k);
				}
			}
		}

		return v;
	}

	void aprobar(const Alumno& a) {
		auto itA = ma.find(a);

		if(itA == ma.end()) {
			throw domain_error("El alumno " + a + " no esta matriculado");
		}

		auto profesor = itA->second.profesor;
		ma.erase(itA);

		mp[profesor].erase(a);
	}

};

int main()
{
	string op;
	Autoescuela A;

	while(cin >> op) {

		try {

			if (op == "FIN") {
				A = {};

				cout << "---" << endl;
			}
			else if (op == "alta") {

				Alumno a;
				Profesor p;
				cin >> a >> p;

				A.alta(a, p);
			}
			else if (op == "es_alumno") {
				Alumno a;
				Profesor p;
				cin >> a >> p;

				bool res = A.es_alumno(a, p);

				if (res) {
					cout << a << " es alumno de " << p << endl;
				}
				else {
					cout << a << " no es alumno de " << p << endl;
				}
			}
			else if (op == "puntuacion") {
				Alumno a;
				cin >> a;

				int res = A.puntuacion(a);

				cout << "Puntuacion de " << a << ": " << res << endl;
			}
			else if (op == "actualizar") {
				Alumno a;
				int n;
				cin >> a >> n;

				A.actualizar(a, n);
			}
			else if (op == "examen") {
				Profesor p;
				int n;
				cin >> p >> n;

				auto v = A.examen(p, n);
				cout << "Alumnos de " << p << " a examen:" << endl;

				for (const auto &e : v) {
					cout << e << endl;
				}
			}
			else if (op == "aprobar") {
				Alumno a;
				cin >> a;

				A.aprobar(a);
			}
		} catch(exception& e) {
			cout << "ERROR" << endl;
		}
	}

	return 0;
}