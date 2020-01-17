// Pedro Palacios Almendros 

// Llamada recursiva a las 4 submatrices, devolviendo el valor de la diagonal 


#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Si v es una matriz cuadrada MxM, consideramos N=MxM el tamaño del problema
//La recurrencia es:
//
//	T(n) = | c1				si n == 1
//		   | 4*T(n/4) + c2  si n > 1
//
// Aplicando el teorema de la división, podemos ver que la solución es del orden O(N)=N,
// es decir, es lineal respecto al tamaño del problema


//f [0...n) es la fila de la posición superior izquierda donde comienza la matriz cuadrada
//c [0...n) es la columna de la posición superior izquierda donde comienza la matriz cuadrada
//n es la longitud de la matriz cuadrada
bool g_resolver(vector<vector<int>> const& v, int& d, int f, int c, int n) {
	
	//Una matriz 1x1 es equidiagonal
	if (n == 1) {
		//Ambas diagonales son iguales y son el unico valor
		d = v[f][c];
		return true;
	}

	//Dividamos el problema en 4 submatrices 
	int newN = n / 2;

	//vamos a ver si la funcion es equidiagonal
	bool result;

	//Almacenaremos las diagonales principales y secundarias necesarias
	int dp1, dp2 = 0, ds1 = 0, ds2 = 0;

	// Segun nuestro sistema de coordenadsa, las 4 submatrices quedan identificadas de la siguiente manera:

	// |    (f, c)	p1     |     (f, c + newL)	s1   |
	// |-------------------|-------------------------|
	// | (f + newL, c) s2  | (f + newL, c + newL) p2 |

	//Calculamos recursivamente los datos necesarios de las submatrices
	result = g_resolver(v, dp1, f, c, newN)   &&
		g_resolver(v, ds1, f, c + newN, newN) &&
		g_resolver(v, ds2, f + newN, c, newN) &&
		g_resolver(v, dp2, f + newN, c + newN, newN);

	//Calculamos la diagonal principal y la secundaria
	int dp = dp1 * dp2;
	int ds = ds1 * ds2;
	
	//Si la matriz no es equidiagonal, este valor se ignorara, asi que solamente tenemos que almacenar una diagonal
	d = dp;

	//La matriz es equidiagonal si son las cuatro submatrices y el producto de la diagonal principal es igual al producto de la diagonal secundaria
	return result && dp == ds;
}


//Esta funcion determina si v es equidiagonal
//y devuelve el producto de la diagonal principal
bool resolver(vector<vector<int>> const& v, int& d)
{
	//Llamamos a la funcion sumergida
	return g_resolver(v, d, 0, 0, v.size());
}


void resuelveCaso() {
	int dim = 0; 
	cin >> dim;
	vector<vector<int>> v(dim,vector<int>(dim));
	for (int i = 0; i < dim; i++)
	for (int j = 0; j < dim; j++)
	{
		cin >> v[i][j];
	}
	int d;
	if (resolver(v,d))
		cout << "SI " << d << "\n";
	else 
		cout << "NO\n";
}

int main() {
	// Para la entrada por fichero
	#ifndef DOMJUDGE
    ifstream in("sample2.in");
	auto cinbuf = cin.rdbuf(in.rdbuf());
	#endif

	int numCasos;
	cin >> numCasos;
	for (int i = 0; i < numCasos; ++i) 
		resuelveCaso();

	#ifndef DOMJUDGE 
	cin.rdbuf(cinbuf);
	system("PAUSE");
	#endif

	return 0;
}

