#include <iostream>
#include <exception>
#include <vector>
#include <unordered_set>

using namespace std;

class Sumidero {
	int V;
	int A;
	vector< vector<bool> > m;

private:
	bool esSumidero(int v) {
		//Todas la fila debe ser 0
		for(int i = 0; i < V; i++) {
			if(m[v][i]) {
				return false;
			}
		}

		//Toda la columna menos la diagonal debe ser 1
		for(int i = 0; i < V; i++) {
			if(i != v && !m[i][v]) {
				return false;
			}
		}

		return true;
	} 

public:

	Sumidero(istream& in)
	{
		if(!(in >> V)) {
			throw domain_error("Vacio");
		}

		in >> A;

		m = vector< vector<bool> > (V, vector<bool>(V, false));

		for(int i = 0; i < A; i++) {
			int v, w;
			cin >> v >> w;
			m[v][w] = true;
		}
	}
	
	int encontrarSumidero() {
		unordered_set<int> posibles;
		for(int i = 0; i < V; i++) {
			posibles.insert(i);
		}

		while(posibles.size() >= 2) {
			auto a = posibles.begin();
			auto b = next(a);

			if(m[*a][*b]) {
				posibles.erase(a);
			} else {
				posibles.erase(b);
			}
		}

		if(!posibles.empty()) {
			int v = *(posibles.begin());
			if(esSumidero(v)) {
				return v;
			} else {
				return -1;
			}
		}

		return -1;

	}

};

int main()
{
	while(true) {
		try {
			Sumidero s{cin};
			int i = s.encontrarSumidero();

			if(i == -1) {
				cout << "NO\n";
			} else {
				cout << "SI " << i << "\n";
			}

		} catch(exception& e) {
			break;
		}
	}

	return 0;
}
