#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
using namespace std;

int main()
{
	while (true)
	{
		//n log n en el n�mero de palabras (con repeticiones)
		//Ya que cada vuelta tiene coste log n ya que utilizamos map
		//Pero nos conviene para sacar los datos ordenados
		int n;
		cin >> n;
		cin.ignore(1);
		if (!n) { return 0; }
		//Almacenaremos cada palabra, con un vector con los enteros de las l�neas donde aparece
		//El vector hace de conjunto. Como los enteros entran ordenadamente, es más eficiente
		//que un conjunto. Hay que comprobar, eso sí, que no haya repeticiones
		map<string, vector<int>> referencias;
		for (int i = 1; i < n + 1; i++)
		{
			//Inicializar el sstream de la l�nea
			string cad;
			getline(cin, cad);
			stringstream ss(cad);
			string aux;
			//Procesar datos
			while (ss >> aux)
			{
				//Pasar a min�sculas
				transform(aux.begin(), aux.end(), aux.begin(),
					[](unsigned char c) { return tolower(c); });
				//Insertar
				if (aux.length() > 2)
				{
					auto& vec = referencias[aux];
					if (vec.empty() || vec[vec.size()-1]!=i)
					{
						vec.push_back(i);
					}
				}
			}
			

		}
		//Sacar datos
		for (auto dato : referencias)
		{
			cout << dato.first;
			for (int i : dato.second)
			{
				cout << " " << i;
			}
			cout << "\n";
		}
		cout << "---\n";
	}
}