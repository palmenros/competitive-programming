// Autores: Martín Gómez Abejón y Pedro Palacios Almendros

#include <iostream>
#include <vector>

typedef long long int lli;
using namespace std;

// (N = v.size()) && N > 0
void delorean(const vector<lli>& v, lli& max, lli& fmax, lli& min, lli& fmin)
{
	max = v[0]; fmax = 1; min = v[0]; fmin = 1;
	int i = 1;
	const int N = v.size();

	// Invariante:
	//	  (max = máx j : 0 <= j < i : v[j]) && (min = min j : 0 <= j < i : v[j]) 
	// && (fmax = # j : 0 <= j < i : v[j] = max) && (fmin = # j : 0 <= j < i : v[j] = min)
	while (i < N) {
		const lli val = v[i];

		if(val > max) {
			max = val;
			fmax = 1;
		} else if(val == max) { 
			fmax++;
		}

		if(val < min) {
			min = val;
			fmin = 1;
		} else if(val == min) { 
			fmin++;
		}

		i++;
	}
}
//	  (max = máx i : 0 <= i < N : v[i]) && (min = min i : 0 <= i < N : v[i]) 
// && (fmax = # i : 0 <= i < N : v[i] = max) && (fmin = # i : 0 <= i < N : v[i] = min)

int main()
{
	int numCasos;
	cin >> numCasos;

	for (int i = 0; i < numCasos; i++) {
		lli tmp;
		vector<lli> v;
		
		while (cin >> tmp && tmp != 0) {
			v.push_back(tmp);
		}

		lli max, fmax, min, fmin;
		delorean(v, max, fmax, min, fmin);
		cout << min << " " << fmin << " " << max << " " << fmax  << endl;

	}

	return 0;
}