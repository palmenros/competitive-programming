//Autores: Martín Gómez Abejón y Pedro Palacios Almendros
#include <iostream>
#include <vector>
using namespace std;
/*
El problema se resuelve utilizando divide y vencerás en el vector
Si cogemos un elemento en la mitad de un vector que cumpla
las condiciones del enunciado, será el mínimo o este estará a la derecha de él
si es menor que el valor en el índice de la izquierda,
y estará a la izquierda si el valor es mayor que el del índice de
la izquierda.

*/
//Coste logarítmico
int minimo(vector<int>& v, int a, int b)
{
	//Caso trivial
	if (a==b){return v[a];}
	int c = (a+b)/2+1;
	//El +1 hace que la función de cota de la recursión decrezca
	//Si no el algoritmo es incorrecto
	//Hacer recursión como se ha dicho arriba
	if (v[c] > v[a]){return minimo(v,a,c-1);}
	else{return minimo(v,c,b);}
}



int main()
{
	while (true){
	int n;
	cin >> n;
	if (!cin){return 0;}
	vector<int> v;
	v.reserve(n);
	for (int i=0;i<n;i++)
	{
		int aux;
		cin >> aux;
		v.push_back(aux);
	}
	cout << minimo(v,0,n-1) << endl;}
}