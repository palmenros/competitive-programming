//
// Created by pedro on 2/4/20.
//

#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

//Coste: lineal (porque unordered_map tiene acceso constante)
void resolver(int N)
{
	//Numero, apariciones
	unordered_map<int, int> m;
	vector<int> v;

	for(int i = 0; i < N; i++)
	{
		int e;
		cin >> e;
		m[e]++;

		if(m[e] == 1) {
			v.push_back(e);
		}
	}

	for(const auto& e : v) {
		cout << e << " " << m[e] << endl;
	}

	cout << "---" << endl;
}

int main()
{
	int n;
	while(cin >> n) {
		resolver(n);
	}

	return 0;
}