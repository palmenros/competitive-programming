// Autores: Martín Gómez Abejón y Pedro Palacios Almendros

#include <iostream>
#include <vector>

using namespace std;

/*
	estrictamente_ordenado(v, N) := forall a, b : 0 <= a < b < N : v[a] < v[b]
	en_vector(v, N, elemento) := exists i : 0 <= i < N : v[i] = elemento

	{ N >= 0 && 0 <= a <= b <= N && 'a' <= cInicio && cInicio + N <= 'z' && estrictamente_ordenado(v, N) && v[N-1] <= cInicio + N && v[0] >= cInicio }
	fun preso_que_falta(V[0...N) de ent, a : ent, b : ent, cInicio : char)  dev c : char
	{ !en_vector(v, N, c) && cInicio <= c <= cInicio + N }
*/
char preso_que_falta(const vector<char>& v, int a, int b, char cInicio) {
	if (a == b)
	{
		return cInicio + a;
	}
	int c = (a + b) / 2;
	if (v[c] == cInicio + c)
	{
		return preso_que_falta(v, c + 1, b, cInicio);
	}
	else
	{
		return preso_que_falta(v, a, c, cInicio);
	}
}

int main()
{
	int N;
	cin >> N;
	while (N--) {
		char a, b;
		cin >> a >> b;
		vector<char> v;
		for (int i = 0; i < b - a; i++) {
			char tmp;
			cin >> tmp;
			v.push_back(tmp);
		}

		cout << preso_que_falta(v, 0, v.size(), a) << endl;

	}

	return 0;
}