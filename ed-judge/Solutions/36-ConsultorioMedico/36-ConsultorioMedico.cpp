#include <iostream>
#include <unordered_map>
#include <set>
#include <map>
#include <vector>
#include <iomanip>

using namespace std;

typedef unsigned int dia_t;
typedef string medico_t;
typedef string paciente_t;

class fecha_t {

private:

	size_t toMinutes() const {
		return day * 24 * 60 + hour * 60 + minute;
	}

public:

	dia_t day, hour, minute;

	bool operator<(const fecha_t& other) const {
		return toMinutes() < other.toMinutes();
	}

	fecha_t(int day, int hour, int minute) :
		day(day), hour(hour), minute(minute)
	{}

	fecha_t() 
	{}

};

istream& operator>>(istream& is, fecha_t& fecha) {
	cin >> fecha.day >> fecha.hour;

	char aux;
	cin >> aux;

	cin >> fecha.minute;
	return is;
}

ostream& operator<<(ostream& os, fecha_t fecha) {
	return os <<  std::setw(2) << std::setfill('0') << fecha.hour << ":" <<  std::setw(2) << std::setfill('0') << fecha.minute;
}


struct consulta_t {
	fecha_t fecha;
	paciente_t paciente;

	consulta_t(const paciente_t& paciente, fecha_t fecha)
		: fecha(fecha), paciente(paciente)
	{}

	
};

class consultorio_t {
private:

	unordered_map<medico_t, map<fecha_t, paciente_t> > m;
	unordered_map<medico_t, unordered_map<dia_t, map<fecha_t, paciente_t>>> calendario;

public:

	void nuevo_medico(const medico_t& medico) {
		m.insert({medico, {}});
		calendario.insert({medico, {}});
	}

	void pide_consulta(const paciente_t& paciente, const medico_t& medico, fecha_t fecha) {
		auto itM = m.find(medico);

		if(itM == m.end()) {
			throw domain_error("Medico no existente");
		}

		auto& consultas = itM->second;
		auto [itC, succeeded] = consultas.insert({fecha, paciente});

		if(!succeeded) {
			throw domain_error("Fecha ocupada");
		}

		calendario[medico][fecha.day][fecha] = paciente;
	}

	paciente_t siguiente_paciente(const medico_t& medico) {
		auto itM = m.find(medico);

		if(itM == m.end()) {
			throw domain_error("Medico no existente");
		}

		auto& consultas = itM->second;
		auto itP = consultas.begin();
		
		if(itP == consultas.end()) {
			throw domain_error("No hay pacientes");
		}

		return itP->second;
	}

	void atiende_consulta(const medico_t& medico) {
		auto itM = m.find(medico);

		if(itM == m.end()) {
			throw domain_error("Medico no existente");
		}

		auto& consultas = itM->second;
		auto itP = consultas.begin();
		
		if(itP == consultas.end()) {
			throw domain_error("No hay pacientes");
		}	

		auto& fecha = itP->first;
		consultas.erase(itP);

		calendario[medico][fecha.day].erase(fecha);

		if(calendario[medico][fecha.day].empty()) {
			calendario[medico].erase(fecha.day);
		}

	}

	vector<consulta_t> lista_pacientes(const medico_t& medico, int dia) {
		auto itM = calendario.find(medico);

		if(itM == calendario.end()) {
			throw domain_error("Medico no existente");
		}

		vector<consulta_t> v;

		auto& map = itM->second;

		auto itDia = map.find(dia);

		if(itDia != map.end()) {
			for(const auto& [fecha, paciente] : itDia->second) {
				v.push_back({ paciente, fecha });
			}
		}
		
		return v;
	}


};

int main()
{
	int nOperaciones;
	while(cin >> nOperaciones) {

		consultorio_t c;

		while(nOperaciones--) {
			
			string operation;
			cin >> operation;


			try {

				if(operation == "nuevoMedico") {
					medico_t medico;
					cin >> medico;

					c.nuevo_medico(medico);
				} else if (operation == "pideConsulta") {

					paciente_t paciente;
					medico_t medico;
					fecha_t fecha;

					cin >> paciente >> medico >> fecha;

					c.pide_consulta(paciente, medico, fecha);					

				} else if (operation == "siguientePaciente") {
					
					medico_t medico;
					cin >> medico;

					auto paciente = c.siguiente_paciente(medico);

					cout << "Siguiente paciente doctor " << medico << endl << paciente << endl;

				} else if (operation == "atiendeConsulta") {

					medico_t medico;
					cin >> medico;

					c.atiende_consulta(medico);

				} else if (operation == "listaPacientes") {
					
					medico_t medico;
					int dia;

					cin >> medico >> dia;

					auto lista = c.lista_pacientes(medico, dia);

					cout << "Doctor " << medico << " dia " << dia << endl;
					for(auto el : lista) {
						cout << el.paciente << " " << el.fecha << endl;
					}
				}

			} catch(exception& e) {
				cout << e.what() << endl;
			}

		}

		cout << "---" << endl;
	}


	return 0;
}


