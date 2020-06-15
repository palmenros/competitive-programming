#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Operation {
	int line;
	string name;
	int param = -1;
};

void resolver()
{
	vector<Operation> v;
	unordered_map<int, int> m;
	m[-1] = -1;

	{
		Operation op;
		cin >> op.line;
		int line = 10;

		while(op.line != 0) {
			cin >> op.name;
			if(op.name != "RETURN") {
				cin >> op.param;
			} else {
				op.param = -1;
			}

			m[op.line] = line;

			op.line = line;
			v.push_back(op);

			line += 10;
			cin >> op.line;
		}
	}

	for(auto& op : v) {
		op.param = m[op.param];
	}


	for(auto& op : v) {
		cout << op.line << " " << op.name;
		if(op.param != -1) {
			cout << " " << op.param;
		}

		cout << endl;
	}

	cout << "---" << endl;
}


int main()
{
	int nCasos;
	cin >> nCasos;

	while(nCasos--) {
		resolver();
	}

	return 0;
}