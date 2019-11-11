//Martín Gómez Abejón y Pedro Palacios Almendros
#include <vector>
#include <iostream>
using namespace std;

//El problema se resuelve linealmente buscando el máximo de las longitudes
//de las zonas co árboles altos. Para ello, simplemente hay que
//recorrer el vector de abajo a arriba encontrando la zona más larga

// N > 0
// fun intervaloMaximo(V[0...N) de ent, lMin : ent) dev inicioG : ent, finG : ent 
void intervaloMaximo(vector<int>& v, int lMin, int &inicioG, int &finG)
{	
	inicioG = -1; finG = -2;
	bool enIntervalo = false;
	int inicio = -1;
	int i = 0;

	// Función de cota: N - i
	// menor(p, q) := forall i : i <= p < q : V[i] > lMin
	// Invariante:  0 <= i <= N																   &&
	//				(finG - inicioG = (máx p, q : 0 <= p <= q <= N && menor(p, q) : q - p - 1) &&
	//				 menor(inicioG, finG + 1)) || (inicioG = -1 && finG = -2)				   &&
	//				enIntervalo = (i != 0 && v[i] - 1 > Lmin)								   &&
	//				enIntervalo -> (inicio = min p : 0 <= p <= i && menor(p, i + 1) : p)
	while (i < v.size())
	{
		if (enIntervalo)
		{
			if (!(v[i] > lMin))	{enIntervalo = false;}
		}
		else
		{
			if (v[i] > lMin)
			{
				enIntervalo = true;
				inicio = i;
			}
		}
		if (enIntervalo && i - inicio > finG - inicioG)
		{
			inicioG = inicio;
			finG = i;
		}
		i++;
	}
}
// finG - inicioG = (máx p, q : 0 <= p <= q <= N && menor(p, q) : q - p - 1) &&
// menor(inicioG, finG + 1)

int main()
{
	int casos;
	cin >> casos;
	for (int k = 0; k < casos; k++)
	{
		int n;
		int lMin;
		cin >> n;
		cin >> lMin;
		vector<int> v;
		v.reserve(n);
		for (int i = 0;i<n;i++)
		{
			int aux;
			cin >> aux;
			v.push_back(aux);
		}
		int inicio;
		int fin;
		intervaloMaximo(v,lMin, inicio,fin);
		cout << inicio << " " << fin << endl;
	}
}