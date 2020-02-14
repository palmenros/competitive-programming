//Autores: Martín Gómez Abejón y Pedro Palacios Almendros

#include <iostream>
#include <vector>

using namespace std;

// {n > 0}
bool pueden_ser_dalton(const vector<int>& v)
{
	const int n = v.size();

	bool result = true;
	int i = 0;

	if (v[0] > v[1])
	{
		//Invariante: (i < n - 1) && ( forall j : 0 <= j < i - 1 : v[j] > v[j+1]) )
		//Función de cota: n - i
		while (result && i < n - 1)
		{
			result = v[i] > v[i + 1];
			i++;
		}
	}
	else if (v[0] < v[1]) {
		// Invariante: (i < n - 1) && ( forall j : 0 <= j < i - 1 : v[j] < v[j+1] )
		// Función de cota: n - i
		while (result && i < n - 1)
		{
			result = v[i] < v[i + 1];
			i++;
		}
	}
	else
	{
		result = false;
	}

	return result;
}
// { ret = (forall i : 0 <= i < n - 1 : v[i] < v[i+1]) or (forall i : 0 <= i < n - 1 : v[i] > v[i+1])}

int main() {

	int n;
	while (cin >> n && n > 0) {
		vector<int> v;
		int tmp;
		v.reserve(n);

		for (int i = 0; i < n; i++) { cin >> tmp; v.push_back(tmp); }

		if (pueden_ser_dalton(v)) {
			cout << "DALTON" << endl;
		}
		else {
			cout << "DESCONOCIDOS" << endl;
		}

	}
}