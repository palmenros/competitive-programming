//Pedro Palacios Almendros

//Calcular el mayor valor posible mediante vuelta atras, podando y estimando para ahorrar tiempo

//      Espacio de soluciones explicito:
// ----------------------------------------------

// sol = [x0, .., xp-1]		x_i es la playa asignada a la i-esima persona

//		Espacio de soluciones implicito:
// -------------------------------------------

// Predicado auxiliar que nos dice si la i-ésima playa está limpia:
// playaLimpia(i) = (sum j : 0 <= j < p && sol[j] == i : recogePersona[j][i] ) >= basuraPlaya[i]

// ( #i : 0 <= i <= m : playaLimpia(i) ) >= l

// El arbol de exploracion tendrá p niveles, cada uno representando las distintas playas que puede limpiar una persona
// en cada nivel, el arbol se ramificará como mucho a m playas, que son las que puede limpiar la k-esima persona

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct tDatos { 
	
	// Datos de entrada
	int numPersonas, numPlayas, minLimpias;
	
	vector<int> basuraPlaya; // Basura a recoger en cada playa
	
	vector<vector<int>> recogePersona; // Basura que puede recoger cada persona en cada playa
									   // v[persona][playa]
};


// IMPLEMENTACION DEL ALGORITMO DE VUELTA ATRAS

// Explicaciones detalladas sobre la implementacion 
// Indicacion de los marcadores utilizados

//				PODAS DE OPTIMALIDAD
//----------------------------------------------

// 1. Calcular el maximo de basura total que pueden recoger las personas y comprobar si (p-1-k)*ese maximo + basura recogida hasta k <= maximo hasta ahora
// Si es asi, podemos podar y no es necesario continuar en esa rama

// 2. Calcular en un array el máximo de bsaura total que podrían recoger las k+1 personas, y comprobra si la basura recogida + ese maximo <= maximo hasta ahora

//Este segundo metodo es claramente mejor, ya que solamente tenemos en cuenta las personas a partir de la k-esima, y no todas

void playas_va(
	tDatos& datos,					 //Datos del problema
	vector<int>& sol,				 //[0...p)	sol[i] es la playa que limpia la persona i o -1 si no limpia ninguna
	vector<int>& basuraRestante,	 //[0...m)	basuraRestante[i] es cuanta basura queda por recoger en la playa i
	const vector<int>& maximaBasura, //[0...p)  maximaBasura[i] indica el maximo de basura que podran recoger las personas [i+1, ..., p) 
	int playasLimpias,				 //Cuantas playas han sido limpiadas por completo
	int basuraRecogida,				 //Basura eliminada hasta el momento
	int& mejorBasura,				 //Mejor valor encontrado hasta ahora de basura eliminada
	int& mejorLimpias,				 //Cantidad de playas limpias con la basura optima
	bool& exito,
	int k							 //Persona que estamos calculando la asignacion
) {

	//Definiciones para mayor claridad
	const int p = datos.numPersonas;
	const int m = datos.numPlayas;
	
	//Analizamos las distintas playas adjudicables a la k-esima persona, -1 significa que esa persona no limpia ninguna playa 
	for (int playa = -1; playa < m; playa++) {	
		sol[k] = playa;

		//Si la playa ya está limpia, podar esa rama, no es optimo 
		if (playa == -1 || basuraRestante[playa] > 0) {

			int basuraRecogidaEstaPlaya;
			bool limpia;

			if (playa != -1) {
				
				//Si la playa no es vacia, entonces calculamos la basura recogida en esta playa y actualizamos su basura restante y el numero de playas limpias

				basuraRecogidaEstaPlaya = min(basuraRestante[playa], datos.recogePersona[k][playa]);
				basuraRecogida += basuraRecogidaEstaPlaya;
				basuraRestante[playa] -= basuraRecogidaEstaPlaya;
				limpia = basuraRestante[playa] == 0;
				if (limpia) { playasLimpias++; }
			}
			
			if (k == p - 1) {
				
				//Si ya hemos adjudicado a todas las personas su solucion, comprobemos si es una solucion valida

				if (playasLimpias >= datos.minLimpias) {
					//Es una solucion valida
					exito = true;

					if (basuraRecogida > mejorBasura) {
						//Si es mejor solucion que lo que ya teniamos anteriormente, actualizar los mejores valores
						
						mejorBasura = basuraRecogida;
						mejorLimpias = playasLimpias;
					}
				
				}
			} else {

				//Si puede llegar a ser una mejor solucion, hacer vuelta atras, si no, podar

				//Poda: Si suponiendo que cada persona [k + 1, ..., p), que son p - 1 - k personas van a limpiar cada una de ellas una playa más,
				//entonces el maximo numero total de playas limpias sera las playas ya limpiadas hasta ahora (playasLimpias) + p - 1 - k, que debera ser mayor o igual que el minimo numero de playas limpias

				if ((basuraRecogida + maximaBasura[k] > mejorBasura) && (datos.minLimpias <= playasLimpias + (p - 1 - k))) {
					playas_va(datos, sol, basuraRestante, maximaBasura, playasLimpias, basuraRecogida, mejorBasura, mejorLimpias, exito, k + 1);
				}
			}

			if (playa != -1) {

				//Si la playa no es vacía, desmarcamos los marcadores realizados

				if (limpia) { playasLimpias--; }
				basuraRestante[playa] += basuraRecogidaEstaPlaya;
				basuraRecogida -= basuraRecogidaEstaPlaya;
			}

		}
	}
}

void resuelveCaso()
{
	// LECTURA DE LOS DATOS DE ENTRADA 
	tDatos d;
	cin >> d.numPersonas >> d.numPlayas >> d.minLimpias;
	
	for (int i = 0; i < d.numPlayas; ++i) {
		int aux;
        cin >> aux;
        d.basuraPlaya.push_back(aux);
	}

	for (int i = 0; i < d.numPersonas; ++i) {
		vector<int> aux(d.numPlayas);
		for (int &j : aux) cin >> j;
		d.recogePersona.push_back(aux);
	}

	//CALCULO Y ESCRITURA DEL RESULTADO

    // Inicializa para hacer la llamada
	int mejorBasura = -1; // Cantidad maxima de basura que se puede recoger
	int mejorLimpias; // Cantidad de playas completamente limpias
	bool exito = false; // Se hara cierto si es posible limpiar completamente al menos minLimpias playas

	vector<int> sol(d.numPersonas);
	vector<int> basuraRestante = d.basuraPlaya;

	int playasLimpias = 0;
	for (int b : basuraRestante) {
		if (b == 0) {
			playasLimpias++;
		}
	}

	vector<int> maximaBasura(d.numPersonas);
	if (d.numPersonas > 0) {
		maximaBasura[d.numPersonas - 1] = 0;
	}

	for (int i = d.numPersonas - 2; i >= 0; i--) {
		
		// (Maximo que puede obtener la persona i + 1) + maximaBasura[i+1]
		int maxPersona = 0;
		for (int b : d.recogePersona[i + 1]) {
			maxPersona = max(maxPersona, b);
		}

		maximaBasura[i] = maximaBasura[i + 1] + maxPersona;
	}	

	// Llama aqui a tu funcion
    // Inicializar playas limpias dependiendo del valor del enunciado

	playas_va(
		d,					//Datos del problema
		sol,				//[0...p)	sol[i] es la playa que limpia la persona i o -1 si no limpia ninguna
		basuraRestante,		//[0...m)	basuraRestante[i] es cuanta basura queda por recoger en la playa i
		maximaBasura,
		playasLimpias,		//Cuantas playas han sido limpiadas por completo
		0,					//Basura eliminada hasta el momento
		mejorBasura,		//Mejor valor encontrado hasta ahora de basura eliminada
		mejorLimpias,		//Cantidad de playas limpias con la basura optima
		exito,
		0					//Persona que estamos calculando la asignacion
	);

	if (exito)
	{
		cout << mejorBasura << " " << mejorLimpias << "\n";
    }
	else
	{
		cout << "IMPOSIBLE\n";
	}
}


int main() {
	// Para la entrada por fichero
	#ifndef DOMJUDGE
	ifstream in("sample3.in");
	auto cinbuf = cin.rdbuf(in.rdbuf());
	#endif

	int numCasos;
	cin >> numCasos;
	for (int i = 0; i < numCasos; ++i) resuelveCaso();

	#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
	system("pause");
	#endif
	
	return 0;
}
