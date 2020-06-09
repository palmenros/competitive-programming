#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
	while (true)
	{
		//El coste es n log n porque el diccionario está ordenado
		//los costes del bucle son log n porque modificamos la entrada de un alumno
		//Conviene diccionario ordenado porque luego imprimimos en orden
		int n;
		cin >> n;
		//Para quitar un \n de cin para lo que hay despu�s
		cin.ignore(1);
		if (!n) { return 0; }
		//El mapa alumnos - notas
		map<string, int> m;
		for (int i = 0; i < n; i++)
		{
			string auxAlumno, auxCorreccion;
			//Cogemos de cin
			getline(cin, auxAlumno);
			getline(cin, auxCorreccion);
			//Registramos en el mapa los datos
			m[auxAlumno] += (auxCorreccion == "CORRECTO" ? 1 : -1);
		}
		//Sacamos los resultados por cin
		auto it = m.begin();
		while (it != m.end())
		{
			if ((*it).second != 0)
			{
				cout << (*it).first << ", " << (*it).second << "\n";
			}
			it++;
		}
		cout << "---\n";
	}
}