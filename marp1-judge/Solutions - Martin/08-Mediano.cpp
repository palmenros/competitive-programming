#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <climits>
#include <deque>
#include <algorithm>
using namespace std;

using lli = long long int;

template <class T>
class medianManagement
{
private:
	//Mont�culo con los floor((n-1)/2) primeros
	priority_queue<lli, vector<lli>, less<lli>> heapMin;
	//Mont�culo con los floor((n-1)/2) �ltimos
	priority_queue<lli, vector<lli>, greater<lli>> heapMax;
	//Cola con los elementos que no est�n en heapMin o en heapMax
	deque<lli> center;
	//Para la salida
	bool primeraVez = true;
public:
	//Hacemos la salida en la estructura de datos para no hacer el c�digo muy complicado
	void insertar(T elem)
	{
		center.push_back(elem);
		//Desde el punto de vista de la nueva estructura, los mont�culos tienen cada uno floor(n)-1 elementos
		//Como acabamos de a�adir uno, el orden se ha podido romper. Sin embargo, cada mont�culo contiene a floor(n)-2
		//de los floor(n) - 1 elementos extremos.
		//Pasamos un elemento de cada mont�culo a la cola, si es posible.
		if (!heapMax.empty())
		{
			center.push_front(heapMin.top());
			center.push_back(heapMax.top());
			heapMin.pop(); heapMax.pop();
		}
		//Ahora cada mont�culo tiene floor(n)-2 elementos, todos entre los floor(n)-1 extremos
		//Lo que hacemos ahora es ordenar el centro. Entonces, los floor(n)-1 elementos extremos se quedar�n nece-
		//sariamente en el mont�culo y el extremo correspondiente.
		sort(center.begin(), center.end());
		//Ahora pasamos elementos a los mont�culos hasta que el centro sea peque�o. Como m�nimo pasaremos una vez,
		//por lo que el invariante de la representaci�n ser� recuperado.
		while (center.size() > 2)
		{
			heapMin.push(center.front());
			heapMax.push(center.back());
			center.pop_back(); center.pop_front();
		}
		
	}
	void retirar()
	{
		//Salida
		if (primeraVez)
		{
			primeraVez = false;
		}
		else
		{
			cout << " ";
		}
		//Si la cola est� vac�a no hay elementos
		if (center.empty()) { cout << "ECSA"; return; }
		//Si no, retiramos el de la izquierda de la cola
		cout << center.front();
		center.pop_front();
		//Si la cola est� vac�a y hay elementos en los mont�culos, los a�adimos
		if (!heapMax.empty() && center.empty())
		{
			center.push_front(heapMin.top());
			center.push_back(heapMax.top());
			heapMin.pop(); heapMax.pop();
		}
	}
};


bool resuelveCaso()
{
	//Lo implementaremos como hemos visto en los problemas, con dos mont�culos.
	//La parte central de la estructura, donde guardaremos la mediana y quiz�s alg�n otro elemento, ser� una cola doble.
	//Coste en O(n log n)

	lli n;
	cin >> n;
	if (!cin) { return false; }
	//Tomar datos
	medianManagement<lli> system;
	
	while (n--)
	{
		lli aux;
		cin >> aux;
		if (aux)
		{
			system.insertar(aux);
		}
		else
		{
			system.retirar();
		}
	}
	cout << "\n";
	return true;
}

int main()
{
	while (resuelveCaso());
	return 0;
}