// Pedro Palacios Almendros 

// Calculamos el maximo tamano teniendo en cuenta que sera el maximo entre lo
// que ya teniamos y la longitud del mayor subsegmento que acaba en n y cumple las condiciones del enunciado

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//					PRECONDICION Y ESPECIFICACIÓN
//----------------------------------------------------------

// { N >= 0 }
// fun resolver(v[0...N) de ent) : r ent

// Trabajamos con segmentos del tipo [a, b)

//						POSTCONDICION
//----------------------------------------------------------

// contiene_creciente_3(v, a, b): exists p : a <= p <= b - 3 : (v[p] < v[p+1]) && (v[p+1] < v[p+3])
// 
// {
//		r = max p, q : 0 <= p <= q <= N  && not contiene_creciente_3(v, p, q) : q - p
// }

//					COSTE ASINTÓTICO:
//----------------------------------------------------------

// Como estamos realizando unicamente un bucle desde 0 hasta N, 
// el coste asintotico es O(n), por el metodo de la instruccion critica, que es "i++"

int resolver(const vector<int> & v) {
	const int N = v.size();
	
	//Maximo absoluto
	int r = 0;
	
	//Maximo del subsegmento local que estamos teniendo en cuenta actualmente
	int maximoLocal = 0;

	int i = 0;

	//Función de cota: N - i
	//N - i >= 0 si i <= N
	//N - (i + 1) < N - i

	//Invariante:
	// i <= N	&&
	// r = max p, q : 0 <= p <= q <= i  && not contiene_creciente_3(v, p, q) : q - p	&&
	// maximoLocal = max p : 0 <= p <= i && not contiene_creciente_3(v, p, i) : i - p 

	while(i < N) {
	
		//Si en el segmento actual tenemos mas de 2 elementos y el nuevo elemento forma un subsegmento estrictamente creciente de tres elementos
		if (maximoLocal >= 2 && (v[i-2] < v[i-1]) && (v[i-1] < v[i])) {
			//El nuevo segmento actual consistira en los 2 ultimos elementos del segmento con el que estabamos trabajando
			maximoLocal = 2;
		}
		else {

			//El nuevo segmento local no contendra ningun subsegmento estrictamente creciente de tres elementos
			maximoLocal++;
			
			if (maximoLocal > r) {
				//En el caso de que el nuevo maximo local es mayor que el maximo general, actualizarlo
				r = maximoLocal;
			}
		}

		//Siguiente iteracion
		i++;
	}
    
	return r;
}

// Esta funcion resuelve un caso de prueba
void resuelveCaso() {
	int numElems = 0; 
	cin >> numElems;
	vector<int> v(numElems);
	for (int& i : v) cin >> i;
	int sol = resolver(v);
	cout << sol <<"\n";
}

int main() {
	// Para la entrada por fichero
	#ifndef DOMJUDGE
	ifstream in("sample1.in");
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
