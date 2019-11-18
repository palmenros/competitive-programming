//Autores: Jesús Checa Sieres y Pedro Palacios Almendros

#include <iostream>
#include <cmath>

using namespace std;

//Especificación

/*
	Estructura de movil:

	tipo movil {
		pi				   : ent	//Peso izquierda, 0 si existe submovil_izquierdo
		pd				   : ent	//Peso derecha, 0 si existe submovil_derecho
		di				   : ent	//Distancia izquierda
		dd				   : ent	//Distancia derecha

		submovil_izquierdo : movil  //Submovil izquierdo, si existe
		submovil_derecho   : movil  //Submovil derecho, si existe
	}

*/

/*
	peso_izquierda(movil) := |	peso(m.submovil_izquierdo)		si m.pi == 0
							 |	m.pi							si m.pi != 0

	peso_derecha(movil) :=   |	peso(m.submovil_derecho)		si m.pi == 0
							 |	m.pd							si m.pd == 0

	peso(movil) := peso_izquierda(movil) + peso_derecha(movil)

	{ movilValido(m) && movilFinito(m) }	
	fun equilibrado(m : movil) dev b : booleano, sumaDePesos : ent 
	{ 
		sumaDePesos = peso(m)									&&
		b = (
			m.pi = 0 => equilibrado(m.submovil_izquierdo)		&&
			m.pd = 0 => equilibrado(m.submovil_derecho)			&&
			peso_izquierda(m) * di = peso_derecha(m) * dd
		)
	}
*/
bool equilibrado(int& sumaDePesos) {

	int pi, di, pd, dd;
	//Leemos los datos
	cin >> pi >> di >> pd >> dd;
	
	//Resultado a devolver, por defecto verdadero
	bool resultado = true;

	if (pi == 0) {
		//Existe submovil izquierdo

		int sumaIzquierda;	//Peso del submovil izquierdo

		// ¿Está equilibrado el submovil izquierda?
		// Es volatile para que el compilador no lo optimice
		// Es necesario llamarla siempre, para consumir la entrada
		volatile bool equilibrado_izquierda = equilibrado(sumaIzquierda);
		
		//Si el submovil no está equilibrado, resultado falso
		resultado = resultado && equilibrado_izquierda;

		//El peso izquierdo del submovil es el peso del submovil izquierdo
		pi = sumaIzquierda;
	}

	if (pd == 0) {
		//Existe submovil derecho

		int sumaDerecha;  //Peso del submovil derecho

		volatile bool equilibrado_derecha = equilibrado(sumaDerecha);

		// ¿Está equilibrado el submovil derecha?
		// Es volatile para que el compilador no lo optimice
		// Es necesario llamarla siempre, para consumir la entrada
		resultado = resultado && equilibrado_derecha;

		//El peso derecho del submovil es el peso del submovil derecho
		pd = sumaDerecha;
	}

	//El peso de este submovil es la suma de los izquierdos y derecho
	sumaDePesos = pi + pd;

	//Devolvera verdadero si los submoviles estan equilibrados y se cumple la ley de la palanca
	return resultado && pi * di == pd * dd;
}


int main()
{
	//Lectura de casos
	int numCasos;
	cin >> numCasos;

	while (numCasos--) {
		int tmp;

		//Llamada a función recursiva
		bool resultado = equilibrado(tmp);

		if (resultado) {
			cout << "SI" << endl;
		} else {
			cout << "NO" << endl;
		}

	}

	return 0;
}