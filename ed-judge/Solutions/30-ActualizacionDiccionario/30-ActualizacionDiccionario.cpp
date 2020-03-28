//
// Created by pedro on 27/3/20.
//

#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

map<string, int> read_map()
{
	map<string, int> m;
	string map_str;
	getline(cin, map_str);

	stringstream ss(map_str);
	string key;
	while(ss >> key) {
		int val;
		ss >> val;
		m[key] = val;
	}

	return m;
}

void print(const vector<string>& v, char symbol)
{
	if(v.size() == 0) {
		return;
	}

	cout << symbol;

	for(auto s : v) {
		cout << ' ' << s;
	}

	cout << endl;
}

int main()
{
	int N;
	cin >> N;
	cin.ignore(numeric_limits<int>::max(), '\n');
	while(N--) {

		map<string, int> viejo, nuevo;
		vector<string> creados, eliminados, cambiados;

		viejo = read_map();
		nuevo = read_map();

		//creados
		for(const auto& [k, v] : nuevo) {
			auto it = viejo.find(k);
			if(it == viejo.end()) {
				creados.push_back(k);
			}
		}

		for(const auto& [k, v] : viejo) {
			auto it = nuevo.find(k);
			if(it == nuevo.end()) {
				eliminados.push_back(k);
			} else if (it->second != v) {
				cambiados.push_back(k);
			}
		}

		if(creados.size() == 0 && eliminados.size() == 0 && cambiados.size() == 0) {
			cout << "Sin cambios" << endl;
		} else {
			print(creados, '+');
			print(eliminados, '-');
			print(cambiados, '*');
		}

		cout << "---" << endl;
	}


	return 0;
}