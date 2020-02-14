#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>

using namespace std;


struct Monomial {
	int coeff;
	int exp;

	Monomial(int coeff, int exp) : coeff(coeff), exp(exp) {
	}
};

class Polinomial {
private:
	vector<Monomial> v;

public:

	void add(const Monomial& p) {
		//Binary search

		auto pos = lower_bound(v.begin(), v.end(), p, [](const Monomial& a, const Monomial& b) {
			return a.exp < b.exp;
			});

		if (pos == v.end()) {
			//End of vector
			v.push_back(p);
		} else if (pos->exp == p.exp) {
			//Already exists
			pos->coeff += p.coeff;
		} else {
			v.insert(pos, p);
		}

	}

	long long int evaluate(long long int a) const {
		long long int res = 0;

		for (Monomial m : v) {
			res += m.coeff * pow(a, m.exp);
		}

		return res;
	}

};

int main() {

	int coeff, exp;
	while (cin >> coeff >> exp) {
		Polinomial p;
		do {
			p.add(Monomial{ coeff, exp });
		} while (cin >> coeff >> exp && !(coeff == 0 && exp == 0));

		int N;
		cin >> N;

		for (int i = 0; i < N; i++) {
			int val;
			cin >> val;
			cout << p.evaluate(val);

			if (i == N - 1) {
				cout << endl;
			}
			else {
				cout << " ";
			}
		}

	}

	return 0;
}