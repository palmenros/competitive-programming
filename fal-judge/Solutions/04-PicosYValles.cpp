//Autores: Martín Gómez y Pedro Palacios
//Especificación: N>=3, V[N] de enteros, devuelve peaks, valleys.
//Postcondición: peaks = num i : 1<=i < N-1: V[i]>V[i-1] y V[i]>V[i+1]
//valleys = num i : 1<=i < N-1: V[i]<V[i-1] y V[i]<V[i+1]

#include <iostream>
#include <vector>

using namespace std;


void solvePeaksAndValleys(const vector<int>& v, int& peaks, int& valleys);

int main()
{
	int c;
	cin >> c;
	for (int i = 0; i < c; i++)
	{
		vector<int> v;
		int l;
		cin >> l;
		v.reserve(l);
		for (int j = 0; j < l; j++)
		{
			int value;
			cin >> value;
			v.push_back(value);
		}
		
		int peaks;
		int valleys;

		if (v.size() < 3) { cout << "0 0" << endl; }
		else 
		{ 
			solvePeaksAndValleys(v, peaks, valleys); 
			cout << peaks << " " << valleys << endl;
		}
	}

}

void solvePeaksAndValleys(const vector<int>& v, int& peaks, int& valleys)
{
	peaks = 0;
	valleys = 0;

	//Complejidad lineal
	//Función de cota:n-i
	//Invariante: peaks = num j : 1<=j < i-1: V[j]>V[j-1] y V[j]>V[j+1]
	//valleys = num j : 1<=j < i-1: V[j]<V[j-1] y V[j]<V[j+1]
	//i >= 2 e i < N

	for (int i = 2; i < v.size(); i++)
	{
		if (v[i - 2] < v[i - 1] && v[i] < v[i - 1]) { peaks++; }
		if (v[i - 2] > v[i - 1] && v[i] > v[i - 1]) { valleys++; }
	}
}
