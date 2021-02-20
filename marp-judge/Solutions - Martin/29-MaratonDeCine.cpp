#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//El algoritmo voraz considera las películas ordenadas lexicográficamente, y lleva dos iteradores en el vector
//itsig e itcandidato
//Siempre itsig está más a la derecha de itcandidato.
//Se han elegido o descartado todas las películas que van antes de itsig salvo itcandidato
//En cada paso, si itsig, que empieza después de itcandidato está contenida en él, descartamos itcandidato, itcandidato
//pasa a ser itsig y avanzamos en itsig
//Si empieza antes de que itcandidato termine pero termina después de it candidato, descartamos itsig, avanzando
//Si itsig empieza después del fin de itcandidato, elegimos itcandidato
//Red . dif .
/**
* Supongamos que en el orden lexicográfico se cogen siempre las mismas hasta cierta película p.
* Si la óptima la coge y la voraz no, vayamos al paso del algoritmo en que ha sido descartada.
* Si ha sido descartada porque se ha descartado frente a una contenida en ella, la óptima puede ser modificada cogiendo
* la correspondiente película que esté contenida en p como se coge en la voraz.
* si ha sido descartada por la otra razón, podemos coger la película que sí coge la voraz, que será aquella frente a
* la que se descartó p o una contenida en ella.
* Si la óptima no la coge y la voraz sí, es porque la óptima está cogiendo una que empieza después y termina después.
* La óptima puede pasar a coger p, no habrá colisiones. Si las hubiera, sería por interferir con una película contenida
* en p, por lo que el voraz no habría elegido p, contradicción.
* 
* 
* 
* 
*/
bool resuelveCaso()
{
	int n; cin >> n; if (!n) { return false; }
	vector<pair<int, int>> v;
	for (int i = 0; i < n; i++)
	{
		int h;
		int m;
		char aux;
		int dur;
		cin >> h >> aux >> m >> dur;
		v.push_back({ 60 * h + m,60 * h + m + dur + 10 });
	}
	sort(v.begin(), v.end());
	int nTotal = 0;
	//Inicializar iteradores
	auto itsig = v.begin(); ++itsig;
	auto itcandidato = v.begin();
	while (itsig != v.end())
	{
		if (itsig->second <= itcandidato->second) //Si itsig está contenida
		{
			//Descartar itcandidato
			itcandidato = itsig;
			itsig++;
		}
		else if (itsig->first < itcandidato->second)
		{
			//Descartar itsig
			itsig++;
		}
		else //Se puede ir a itcandidato y justo después a itsig
		{
			//Áceptamos itcandidato
			nTotal++;
			itcandidato = itsig;
			itsig++;
		}
	}
	nTotal++;
	cout << nTotal << "\n";





	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}