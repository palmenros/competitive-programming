//
// Created by pedro on 28/3/20.
//

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <cctype>

using namespace std;

int main()
{
	unordered_map<string, string> p;
	unordered_map<string, int> d;

	unordered_set<string> blacklist;
	string deporteActual;

	string tk;
	while(getline(cin, tk)) {

		if(tk == "_FIN_") {
			//fin
			if(!deporteActual.empty() && d.count(deporteActual) == 0) {
				d[deporteActual] = 0;
			}

			//imprimir en pantalla

			vector<pair<string, int>> v;
			for(const auto& e : d) {
				v.push_back(e);
			}

			sort(v.begin(), v.end(), [](const pair<string, int>& a, const pair<string, int>& b)
			{
				if(a.second == b.second) {
					return a.first < b.first;
				}
				return a.second > b.second;
			});

			for(const auto& [k, v] : v) {
				cout << k << " " << v << endl;
			}

			cout << "---" << endl;

			p.clear();
			d.clear();
			blacklist.clear();
			deporteActual.clear();
		} else if (isupper(tk[0])) {
			if(!deporteActual.empty() && d.count(deporteActual) == 0) {
				d[deporteActual] = 0;
			}

			//deporte
			deporteActual = tk;
		} else {
			//persona
			if(blacklist.count(tk)) { continue; }

			auto it = p.find(tk);
			if(it == p.end()) {
				//Nueva persona
				p[tk] = deporteActual;
				d[deporteActual]++;
			} else {
				if(it->second != deporteActual) {
					d[it->second]--;
					blacklist.insert(tk);
				}
			}

		}


	}


}