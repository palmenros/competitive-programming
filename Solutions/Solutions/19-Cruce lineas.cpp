// Autores: Luis Ariza López y Pedro Palacios Almendros

#include <iostream>
#include <vector>

using namespace std;

/*
	Coste:
------------------------------------------------------------------

	Sea n := b - a

	T(n) = |  c1			n = 0
		   |  T(n/2) + c2	n != 0

	Por el teorema de la división, el coste es log(n).
	Como decrecemos estrictamente n hasta el caso trivial, el programa termina siempre.

	El programa utiliza recursión final, ya que la última llamada realizada es a la función recursiva.

	Precondición y postcondición:
------------------------------------------------------------------

	strict_crec(V, N) := forall i : 0 <= i < N - 1 : V[i] < V[i + 1]
	strict_dec(V, N) :=  forall i : 0 <= i < N - 1 : V[i] > V[i + 1]

	{
		N > 0 && strict_crec(crec, N) && strict_dec(dec, N) && 0 <= a <= b < N
	}
	fun cruce_lineas(crec [0...N) de ent, dec [0...N) de ent, a : ent, b : ent) dev res : bool, cruce : int
	{
		((exists p : 0 <= p < N && dec[p] == crec[p])  =>
			(res = True && cruce = min p : 0 <= p < N && dec[p] == crec[p]))		&&
		((exists p : 0 <= p < N && dec[p] < crec[p])   =>
			(res = False && cruce = min p : 0 <= p < N && dec[p] < crec[p] - 1))	&&
		(!(exists p : 0 <= p < N && dec[p] < crec[p])) =>
			(res = False && cruce = N - 1) 	
	}
*/

bool cruce_lineas(const vector<int>& crec, const vector<int>& dec, int a, int b, int& cruce)
{
	//Caso trivial, solamente tenemos 1 punto
	if (a == b) {

		if (crec[a] == dec[b])
		{
			//Si son iguales ambos vectores en ese punto, entonces el cruce es ese punto
			cruce = a;
			return true;
		}
		else if (crec[a] > dec[b])
		{
			//Si el creciente es mayor que el decreciente en ese punto, el cruce estará anteriormente,
			//como solo hay un punto, devolvemos a - 1
			cruce = a - 1;
			return false;
		} else {
			//Si el creciente es menor que el decreciente en ese punto, el cruce estará posteriormente
			//como solo hay un punto, devolvemos a
			cruce = a;
			return false;
		}	

	}

	//Utilizamos técnica divide y vencerás
	int mid = (a + b) / 2;

	if (crec[mid] == dec[mid]) {
		//Si son iguales ambos vectores en la mitad, entonces el cruce es la mitad
		cruce = mid;
		return true;
	} else if (crec[mid] > dec[mid]) {
		//Si el creciente es mayor que el decreciente en ese punto, el cruce estará en la parte izquierda
		//respecto de la mitad en el vector
		return cruce_lineas(crec, dec, a, mid, cruce);
	} else {
		//Si el creciente es menor que el decreciente en ese punto, el cruce estará en la parte derecha
		//respecto de la mitad en el vector
		return cruce_lineas(crec, dec, mid + 1, b, cruce);
	}

}

int main()
{
	int N;
	while (cin >> N && N != 0) {
		vector<int> a, b;
		int tmp;

		for (int i = 0; i < N; i++) {
			cin >> tmp;
			a.push_back(tmp);
		}

		for (int i = 0; i < N; i++) {
			cin >> tmp;
			b.push_back(tmp);
		}

		bool resultado; int cruce;
		resultado = cruce_lineas(a, b, 0, N - 1, cruce);

		if (resultado) {
			cout << "SI " << cruce << endl;
		} else {
			cout << "NO " << cruce << " " << cruce + 1 << endl;
		}

	}

	return 0;
}