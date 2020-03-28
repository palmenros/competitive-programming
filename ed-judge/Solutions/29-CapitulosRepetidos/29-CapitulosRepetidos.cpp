//
// Created by pedro on 27/3/20.
//

#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	int nCasos;
	cin >> nCasos;
	while(nCasos--) {
		int n;
		cin >> n;

		vector<int> v;
		unordered_map<int, int> m;

		int maximo = 0;
		int num_actual = 0;

		for(int i = 0; i < n; i++) {
			int val;
			cin >> val;
			v.push_back(val);

			if(m.count(val) == 1) {
				maximo = max(maximo, num_actual);

				auto map_val = m[val];

				for(int j = i-num_actual; j <= map_val; j++) {
					m.erase(v[j]);
				}

				num_actual = i - map_val;
				m[val] = i;
			} else {
				num_actual++;
				m[val] = i;
			}
		}

		maximo = max(maximo, num_actual);
		cout << maximo << endl;
	}
}