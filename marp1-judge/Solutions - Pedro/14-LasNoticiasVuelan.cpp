#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include "Grafo.h"

using namespace std;

using Group = int;
using User = int;

class NoticiasVuelan {

	using ComponenteConexa = int;

private:
	const vector<vector<Group>>& userGroups;
	const vector<size_t>& groupSizes;
	const vector<unordered_set<User>>& groupUsers;
	const Grafo& graph;

	//Indica cuantos usuarios tiene cada componente conexa
	vector<unordered_set<User>> usuariosComponenteConexa;

	//Para cada grupo, ¿en que componente conexa esta?
	vector<ComponenteConexa> grupoComponenteConexa;	

	//Conjunto de grupos por visitar todavia
	unordered_set<Group> gruposNoVisitados;

	vector<bool> marcas;
	
	void calcularComponentesConexasRecursivo(Group g) {
		marcas[g] = true;

		for(auto v : groupUsers[g]) {
			usuariosComponenteConexa[usuariosComponenteConexa.size() - 1].insert(v);
		}

		gruposNoVisitados.erase(g);
		grupoComponenteConexa[g] = usuariosComponenteConexa.size() - 1;

		for(auto v : graph.ady(g)) {
			if(!marcas[v]) {
				calcularComponentesConexasRecursivo(v);
			}
		}
	}

public:
	NoticiasVuelan(
			const vector<vector<Group>>& userGroups, 
			const vector<size_t>& groupSizes, 
			const Grafo& graph,
			const vector<unordered_set<User>>& groupUsers
	) :
			userGroups(userGroups),
			groupSizes(groupSizes),
			graph(graph),
			grupoComponenteConexa( groupSizes.size(), -1),
			marcas(groupSizes.size(), false),
			groupUsers(groupUsers)
	{}

	void calcularComponentesConexas() {
		for(int i= 0; i < groupSizes.size(); i++) {
			gruposNoVisitados.insert(i);
		}

		while(!gruposNoVisitados.empty()) {
			auto first = *(gruposNoVisitados.begin());
			usuariosComponenteConexa.push_back({});
			calcularComponentesConexasRecursivo(first);
		}
	}

	void mostrarInfluencias() {
		bool first = true;
		for(auto& v : userGroups) {
			int num;
			if(v.empty()) {
				num = 1;
			} else {
				num = usuariosComponenteConexa[grupoComponenteConexa[v[0]]].size();
			}
			
			if(first) {
				first = false;
			} else {
				cout << ' ';
			}

			cout << num;
		}

		cout << '\n';
	}
};

int main() {
	int nUsers, nGroups;
	while(cin >> nUsers >> nGroups) {
		
		// userGroups[user] contains groups where user is in
		vector< vector<Group> > userGroups( nUsers , vector<Group>{});
		vector<size_t> groupSizes (nGroups, 0);
		vector<unordered_set<User>> groupUsers (nGroups, unordered_set<User>{});

		Grafo g{nGroups};

		for(int i = 0; i < nGroups; i++) {
			//Read each group
			int nUsersInGroup;
			cin >> nUsersInGroup;
			groupSizes[i] = nUsersInGroup;

			while(nUsersInGroup--) {
				User user;
				cin >> user;
				user--;

				//for each user in group
				
				groupUsers[i].insert(user);
				//add edge to every other group where this user is
				for(Group gr : userGroups[user]) {
					g.ponArista(gr, i);
				}

				userGroups[user].push_back(i);
			}
		}

		// G tiene grafo con grupos conectados
		// Tenemos que calcular las componentes conexas y asociar a cada usuario su componente conexa
		// Para cada componente conexa tenemos que calcular el numero de usuarios
		
		NoticiasVuelan noticias {userGroups, groupSizes, g, groupUsers};
		noticias.calcularComponentesConexas();
		noticias.mostrarInfluencias();
	}

}
