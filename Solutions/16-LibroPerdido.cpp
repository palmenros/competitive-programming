//Autores: Martín Gómez Abejón y Pedro Palacios Almendros
#include <iostream>
#include <vector>
using namespace std;
/*
El problema se resuelve utilizando divide y vencerás en el vector
Si cogemos un índice par i a la derecha del índice del libro faltante,
coinciden los valores v[i] e v[i-1]. Si está a la izquierda,
coinciden v[i] e v[i+1]. Así podemos optimizarlo

*/
//Coste logarítmico

//Trabajamos con la mitad de la longitud del vector; es el número de índices que hay
int faltante(vector<int>& v, int a, int b)
{
	//Casos triviales
	if (a == b){return 2*a;}
	if (a + 1 == b){return (v[2*a]!=v[2*a+1]?2*a:2*b);}
	//Recursión
	int c = (a+b)/2;
	if (v[2*c+1]==v[2*c]){return faltante(v,c+1,b);}
	else if (v[2*c-1]==v[2*c]){return faltante(v,a,c-1);}
	else{return 2*c;}
}



int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int k;
		cin >> k;
		vector<int> v;
		v.reserve(k);
		for (int j = 0;j<k;j++)
		{
			int aux;
			cin >> aux;
			v.push_back(aux);
		}
		
		cout << faltante(v,0,(k-1)/2) << endl;
	}
}