//Martín Gómez Abejón y Pedro Palacios Almendros
#include <vector>
#include <iostream>
using namespace std;

//El problema se resuelve linealmente buscando el máximo de las longitudes
//de las zonas llanas. Para ello, simplemente hay que
//recorrer el vector de abajo a arriba contando la longitud de esas zonas

// N > 1
// fun tamanoLlanoMaximo(V[0...N) de ent) dev r : ent
int tamanoLlanoMaximo(vector<int>& v)
{
	int maximoGen = 0;
	int maximoLocal = 0;
	int i = 1;
	int alturaLocal = v[0];
	
	// Función de cota: N - i
	// llano(p, q) := forall i : p < i < q : V[i] = v[i - 1]
	// Invariante: maximoGen = (máx p, q : 0 <= p <= q <= i && llano(p, q) : q - p - 1 &&
	//			   alturaLocal = v[i - 1]											   &&
	//			   maximoLocal = (máx j : 0 <= j <= i && llano(j, i) : i - j - 1)	   &&
	//			   0 <= i <= N
	while (i<v.size())
	{
		if(alturaLocal == v[i])
		{
			maximoLocal++;
			if (maximoLocal > maximoGen){maximoGen = maximoLocal;}
		}
		else
		{
			maximoLocal = 0;
		}
		alturaLocal = v[i];
		i++;
	}
	return maximoGen;
}
// r = (máx p, q : 0 <= p <= q <= N && llano(p, q) : q - p - 1

int main()
{
	while (true)
	{
		vector<int> v;
		int aux;
		cin >> aux;
		while (aux != -1)
		{
			v.push_back(aux);
			cin >> aux;
		}
		if (!v.size()){return 0;}
		int resultado = tamanoLlanoMaximo(v);
		if (!resultado) {cout << "HOY NO COMEN" << endl;}
		else {cout << resultado << endl;}
	}
}