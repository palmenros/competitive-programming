//
// Created by pedro on 27/3/20.
//

#include <iostream>
#include <map>
#include <string>
#include <limits>

using namespace std;

int getDiff()
{
	string tmp;
	cin >> tmp;
	if(tmp == "INCORRECTO") {
		return -1;
	} else {
		return 1;
	}
}

int main()
{
	int N;
	while(cin >> N && N != 0) {
		map<string, int> m;
		string name;

		for(int i = 0; i < N; i++) {
			cin.ignore(numeric_limits<int>::max(), '\n');
			getline(cin, name);
			m[name] += getDiff();
		}

		for(auto p : m) {
			if(p.second != 0) {
				cout << p.first << ", " << p.second << endl;
			}
		}

		cout << "---" << endl;

	}

	return 0;
}