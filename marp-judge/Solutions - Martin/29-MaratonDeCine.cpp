#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//El algoritmo voraz considera las pel�culas ordenadas lexicogr�ficamente, y lleva dos iteradores en el vector
//itsig e itcandidato
//Siempre itsig est� m�s a la derecha de itcandidato.
//Se han elegido o descartado todas las pel�culas que van antes de itsig salvo itcandidato
//En cada paso, si itsig, que empieza despu�s de itcandidato est� contenida en �l, descartamos itcandidato, itcandidato
//pasa a ser itsig y avanzamos en itsig
//Si empieza antes de que itcandidato termine pero termina despu�s de it candidato, descartamos itsig, avanzando
//Si itsig empieza despu�s del fin de itcandidato, elegimos itcandidato
//Red . dif .
/**
* Supongamos que en el orden lexicogr�fico se cogen siempre las mismas hasta cierta pel�cula p.
* Si la �ptima la coge y la voraz no, vayamos al paso del algoritmo en que ha sido descartada.
* Si ha sido descartada porque se ha descartado frente a una contenida en ella, la �ptima puede ser modificada cogiendo
* la correspondiente pel�cula que est� contenida en p como se coge en la voraz.
* si ha sido descartada por la otra raz�n, podemos coger la pel�cula que s� coge la voraz, que ser� aquella frente a
* la que se descart� p o una contenida en ella.
* Si la �ptima no la coge y la voraz s�, es porque la �ptima est� cogiendo una que empieza despu�s y termina despu�s.
* La �ptima puede pasar a coger p, no habr� colisiones. Si las hubiera, ser�a por interferir con una pel�cula contenida
* en p, por lo que el voraz no habr�a elegido p, contradicci�n.
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
		if (itsig->second <= itcandidato->second) //Si itsig est� contenida
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
		else //Se puede ir a itcandidato y justo despu�s a itsig
		{
			//�ceptamos itcandidato
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