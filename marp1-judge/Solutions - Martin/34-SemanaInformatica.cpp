#include <iostream>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

enum class Estado
{
	Comienzo,
	Fin
};

struct DatosActividad
{
	int comienzo;
	int fin;
	Estado estado;
};

bool operator<(DatosActividad t1, DatosActividad t2)
{
	return (t1.estado==Estado::Comienzo?t1.comienzo:t1.fin) > (t2.estado == Estado::Comienzo ? t2.comienzo : t2.fin);
}

bool resuelveCaso()
{
	int n; cin >> n; if (!n) { return false; }
	priority_queue<DatosActividad> cola;
	for (int i = 0; i < n; i++)
	{
		int aux1, aux2; cin >> aux1 >> aux2;
		cola.push({ aux1,aux2,Estado::Comienzo });
	}
	int maxPersonasNecesarias = 0;
	int personasNecesariasAct = 0;
	int momentoActual = INT_MIN;
	while (!cola.empty())
	{
		DatosActividad act = cola.top(); cola.pop();
		if ((act.estado == Estado::Comienzo ? act.comienzo : act.fin)!=momentoActual)
		{
			momentoActual = (act.estado == Estado::Comienzo ? act.comienzo : act.fin);
			maxPersonasNecesarias = max(personasNecesariasAct, maxPersonasNecesarias);

		}
		if (act.estado == Estado::Comienzo)
		{
			personasNecesariasAct++;
			act.estado = Estado::Fin;
			cola.push(act);
		}
		else
		{
			personasNecesariasAct--;
		}
	}
	cout << maxPersonasNecesarias - 1 << "\n";


	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}