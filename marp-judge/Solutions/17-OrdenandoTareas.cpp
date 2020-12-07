#include <unordered_set>
#include <vector>
#include <iostream>

using namespace std;

class OrdenacionTareas {
	int V, A{0};
	vector< unordered_set<int> > graph;
	vector< unordered_set<int> > aristaHasta;
	unordered_set<int> verticesSinAristaIncidente;
public:
	
	OrdenacionTareas(int V) 
		: V(V),
		  graph(vector<unordered_set<int>>(V, unordered_set<int>{})),
		  aristaHasta(vector<unordered_set<int>>(V, unordered_set<int>{}))
	{
		for(int i = 0; i < V; i++)
			verticesSinAristaIncidente.insert(i);
	}

	void ponArista(int antes, int despues) {
		antes--;
		despues--;

		verticesSinAristaIncidente.erase(despues);
		graph[antes].insert(despues);
		aristaHasta[despues].insert(antes);
		A++;
	}

	void imprimeOrdenado() {
		vector<int> res;
		
		while(!verticesSinAristaIncidente.empty()) {
			int v = *verticesSinAristaIncidente.begin();
			verticesSinAristaIncidente.erase(v);

			res.push_back(v);

			for(auto other : graph[v]) {
				//Aristas adyacentes 
				aristaHasta[other].erase(v);
				A--;

				if(aristaHasta[other].empty()) {
					verticesSinAristaIncidente.insert(other);
				}
			}
		}
	
		if(A != 0) {
			cout << "Imposible\n";
			return;
		}

		//Imprimir resultado
		
		bool first = true;

		for(int e : res) {
			if(first)
				first = false;
			else
				cout << " ";

			cout << (e + 1);
		}

		cout << "\n";
	}
};

int main()
{
	int V;
	while(cin >> V) {
		OrdenacionTareas ordenacion{V};
		
		int A;
		cin >> A;
		
		while(A--) {
			int v, w;
			cin >> v >> w;
			
			ordenacion.ponArista(v, w);
		}

		ordenacion.imprimeOrdenado();

	}

	return 0;
}
