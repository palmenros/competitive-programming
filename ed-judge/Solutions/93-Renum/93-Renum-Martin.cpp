#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Tipo de dato Instrucci�n
struct Instruccion
{
	string t;
	int linea;
	Instruccion(string t, int linea):t(t),linea(linea){}
};

void resuelveCaso()
{
	//La funci�n est� en O(n), ya que todas las instrucciones son constantes y se repiten a lo sumo n veces
	//Por lo que con el criterio de la instrucci�n que m�s se repite, O(n)
	//Tendremos un diccionario en el que guardaremos, para cada l�nea del principio, su destino en la salida
	//Conviene hacerlo no ordenado; los datos entran ordenados y no nos interesa recorrerlo en orden
	//(hay otras formas) y as� adem�s evitamos estar en O(n log n).
	unordered_map<int, int> correspondencia;
	//Vector con las instrucciones
	vector<Instruccion> v;
	int linea;
	string in;
	int salto = 0;
	cin >> linea;
	//Coger entrada
	while (linea)
	{
		cin >> in;
		if (in != "RETURN")
		{
			cin >> salto;
		}
		v.push_back({ in,salto }); //Guardamos instrucci�n original; si es return el salto no es relevante
		correspondencia[linea] = 10 * (int)(v.size()); //Guardamos la correspondencia entre la l�nea antigua y la nueva
		cin >> linea;
	}
	//Sacamos a cout
	int lineaAct = 10; //L�nea actual
	auto it = v.begin(); //Recorremos el vector de instrucciones
	while (it != v.end())
	{
		cout << lineaAct << " " << (*it).t; //Sacar el principio de la instrucci�n
		if ((*it).t != "RETURN") //Si la instrucci�n tiene salto, calcularlo e imprimirlo
		{
			cout << " " << correspondencia[(*it).linea];
		}
		lineaAct += 10; //Aumentar n linea
		++it; //Avanzar
		cout << "\n";
	}
	cout << "---\n";


}

int main()
{
	int n;
	cin >> n;
	for(int i=0;i<n;i++)
	{
		resuelveCaso();
	}
}