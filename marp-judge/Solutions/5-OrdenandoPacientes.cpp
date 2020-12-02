#include <queue>
#include <string>
#include <iostream>
#include <climits>

using namespace std;

struct Paciente {
	string nombre;
	unsigned int gravedad;
	unsigned int tiempo;

	Paciente(const string &nombre, unsigned int gravedad, unsigned int tiempo)
		: nombre(nombre), gravedad(gravedad), tiempo(tiempo)
	{}
};

int main()
{
	int N;
	while (cin >> N && N != 0) {

		auto cmp = [](const Paciente& a, const Paciente& b) {
			if(a.gravedad == b.gravedad) {
				return a.tiempo > b.tiempo;
			}
			return a.gravedad < b.gravedad;
		};

		priority_queue<Paciente, vector<Paciente>, decltype(cmp)> pq{cmp};

		unsigned int counter = 0;

		while(N--) {
			char c;
			string str;
			unsigned int gravedad;
			cin >> c;

			if(c == 'I') {

				cin >> str >> gravedad;

				pq.push(Paciente{str, gravedad, counter});
				counter++;
			} else if (c == 'A') {
				cout << pq.top().nombre << endl;
				pq.pop();
			}
		}

		cout << "---" << endl;
	}

	return 0;
}