#include <iostream>
#include <climits>
#include <algorithm>
#include <cmath>
#include <map>
#include <fstream>

using namespace std;

struct bici {
	int pos;
	int v;
};

int tiempo(const bici& a, const bici& b)
{
	if (a.v - b.v == 0) {
		return INT_MAX;
	}

	long double time = (a.pos - b.pos) / (long double)(b.v - a.v);
	
	if (time < 0) {
		return INT_MAX;
	} else {
		return (int)time;
	}

}

int main() {

	//ifstream file("H.txt");
	istream& in = cin;

	int n;
	while (in >> n && n != 0) {

		map<int, int> m;

		int minimo = INT_MAX;

		int patata = n;
		for (int i = 0; i < patata; i++)
		{
			int pos, v;
			in >> pos >> v;

			if (m.count(pos) != 0) {
				//Se han chocado ya
				minimo = 0;
				n--;
			}

			m[pos] = v;
		}

		if (n == 2) {

			auto a = *m.begin();
			auto itb = m.begin();
			itb++;
			auto b = *(itb);

			minimo = tiempo({ a.first, a.second }, { b.first, b.second });

		}
		else if (n > 2) {
			auto s = m.begin();
			s++;

			auto e = m.end();
			e--;

			for (auto it = s; it != e; it++) {
				bici a = { it->first, it->second };

				auto it2 = it;
				if (a.v > 0) {
					it2++;
				}
				else if (a.v < 0) {
					it2--;
				}

				bici b = { it2->first, it2->second };

				minimo = min(minimo, tiempo(a, b));
			}
			
			//Tener en cuenta primero y ultimo

			bici first = { m.begin()->first, m.begin()->second };
			if (first.v > 0) {
				auto second = m.begin();
				second++;
				minimo = min(minimo, tiempo(first, bici{ second->first, second->second }));
			}

			auto lastIt = m.end();
			lastIt--;

			bici last = { lastIt->first, lastIt->second };
			if (last.v < 0) {
				auto secondLast = lastIt;
				secondLast--;
				minimo = min(minimo, tiempo(last, bici{ secondLast->first, secondLast->second }));
			}

		}

		if (minimo == INT_MAX) {
			cout << "SIN COLISION" << endl;
		} else {
			cout << minimo << endl;
		}
	}
	return 0;
}