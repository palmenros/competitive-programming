//Autores: Martin Gomez y Pedro Palacios

#include <iostream>
#include <vector>

using namespace std;

typedef short int si;
typedef vector<si> vsi;
typedef vector<vector<si>> vvsi;


void maxima_satisfaccion_va(
	const vsi& edadesRecomendadas, 
	const vsi& edadesNinos, 
	const vvsi& satisfaccion,
	vsi& numJuguetesNinos,
	int& maxSatisfaccion,
	int& restantes,
	int k,
	int M,
	int current_sat,
	vsi& sol
) {

	const int N = edadesNinos.size();
	const int J = edadesRecomendadas.size();

	//-1 representa que no se asigna a nadie el juguete
	for (int nino = -1; nino < N; nino++) {
		sol[k] = nino;

		bool marcado = false;

		if (nino != -1) {
			//Marcar
			numJuguetesNinos[nino]++;

			if (numJuguetesNinos[nino] <= M)
			{
				//Restantes almacena la suma del numero de juguetes que le quedan a cada niño para tener M juguetes
				restantes--;
				marcado = true;
			}

			//Actualizamos valor
			current_sat += satisfaccion[nino][k];
		}
	

		/*
			-Edad juguete maxima
			-Restantes: Podar innecesarias que no son completables
		*/
		if (restantes <= J - k - 1 && (nino == -1 || edadesRecomendadas[k] <= edadesNinos[nino] )) {
			//Es completable
			if (k == J - 1) {
				//Es solución
				if (current_sat > maxSatisfaccion) {
					maxSatisfaccion = current_sat;
				}
			} else if(k < J - 1) {
				maxima_satisfaccion_va(edadesRecomendadas, edadesNinos, satisfaccion, numJuguetesNinos, maxSatisfaccion, restantes, k + 1, M, current_sat, sol);
			}
		}
		
		
		if (nino != -1) {
			//Desactualizamos valor solo si es un niño
			current_sat -= satisfaccion[nino][k];

			//Desmarcar
			numJuguetesNinos[nino]--;

			if (marcado) {
				restantes++;
			}
		}
		
	}

}

/*
	-1 representa que no se asigna el juguete

	Espacio de soluciones:
		sol:= (x0, ..., xJ-1) <- Vector de soluciones que indica el niño al que entregamos cada juguete

	Soluciones explicitas:

		forall i : 0 <= i < J : -1 <= sol[i] < N

		Es decir, a cada juguete se le asigna un niño valido

	Soluciones implicitas:

		(forall i : 0 <= i < J : edadRecomendada[i] <= edadesNinos[sol[i]])
		&&
		(forall i : 0 <= i < N : (#n : 0 <= n < K - 1 : sol[J] = i  >= M ))

		Es decir, cada juguete es adecuado para la edad de cada niño, y todos tienen los juguetes mínimos

*/
int maxima_satisfaccion(const vsi& edadesRecomendadas, const vsi& edadesNinos, const vvsi& satisfaccion, int M) {
	int N = edadesNinos.size();
	int J = edadesRecomendadas.size();
	
	int restantes = N * M;
	int maxSatisfaccion = 0;

	vsi sol(J);
	vsi numJuguetesNinos(N);
	for (int i = 0; i < N; i++) {
		numJuguetesNinos[i] = 0;
	}

	//Llamamos a la función de vuelta atrás
	maxima_satisfaccion_va(edadesRecomendadas, edadesNinos, satisfaccion, numJuguetesNinos, maxSatisfaccion, restantes, 0, M, 0, sol);
	
	return maxSatisfaccion;
}


int main()
{
	int J, N, M;
	while (cin >> J >> N >> M && !(J == 0 && N == 0 && M == 0)) {

		vector<si> edadesRecomendadas(J);
		for(int i = 0; i < J; i++) {
			cin >> edadesRecomendadas[i];
		}

		vector<si> edadesNinos(N);
		for (int i = 0; i < N; i++) {
			cin >> edadesNinos[i];
		}

		vector<vector<si>> satisfaccion(N);
		for (int i = 0; i < N; i++) {
			vector<si>& satisfaccionI = satisfaccion[i];
			satisfaccionI = vector<si>(J);

			for (int j = 0; j < J; j++) {
				cin >> satisfaccionI[j];
			}
		}

		cout << maxima_satisfaccion(edadesRecomendadas, edadesNinos, satisfaccion, M) << endl;

	}

}