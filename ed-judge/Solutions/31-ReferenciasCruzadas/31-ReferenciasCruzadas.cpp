//
// Created by pedro on 28/3/20.
//

#include <limits>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

string to_lower(const string& str) {
	string res {str};

	for(char& c : res) {
		if(c >= 'A' && c <= 'Z' ) {
			c += 'a' - 'A';
		}
	}

	return res;
}

int main()
{
	int N;
	while(cin >> N && N != 0)
	{
		cin.ignore(numeric_limits<int>::max(), '\n');

		map<string, set<int>> m;

		for(int i = 1; i <= N; i++)
		{
			string line;
			getline(cin, line);

			stringstream ss{line};

			string tk;
			while(ss >> tk) {
				tk = to_lower(tk);

				if(tk.size() <= 2) {continue;}
				m[tk].insert(i);
			}
		}

		for(const auto& [k, v] : m) {
			cout << k;
			for(auto e : v) {
				cout << ' ' << e;
			}
			cout << endl;
		}

		cout << "---" << endl;
	}

}