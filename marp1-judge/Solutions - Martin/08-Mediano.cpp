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
	//Montículo con los floor((n-1)/2) primeros
	priority_queue<lli, vector<lli>, less<lli>> heapMin;
	//Montículo con los floor((n-1)/2) últimos
	priority_queue<lli, vector<lli>, greater<lli>> heapMax;
	//Cola con los elementos que no están en heapMin o en heapMax
	deque<lli> center;
	//Para la salida
	bool primeraVez = true;
public:
	//Hacemos la salida en la estructura de datos para no hacer el código muy complicado
	void insertar(T elem)
	{
		center.push_back(elem);
		//Desde el punto de vista de la nueva estructura, los montículos tienen cada uno floor(n)-1 elementos
		//Como acabamos de añadir uno, el orden se ha podido romper. Sin embargo, cada montículo contiene a floor(n)-2
		//de los floor(n) - 1 elementos extremos.
		//Pasamos un elemento de cada montículo a la cola, si es posible.
		if (!heapMax.empty())
		{
			center.push_front(heapMin.top());
			center.push_back(heapMax.top());
			heapMin.pop(); heapMax.pop();
		}
		//Ahora cada montículo tiene floor(n)-2 elementos, todos entre los floor(n)-1 extremos
		//Lo que hacemos ahora es ordenar el centro. Entonces, los floor(n)-1 elementos extremos se quedarán nece-
		//sariamente en el montículo y el extremo correspondiente.
		sort(center.begin(), center.end());
		//Ahora pasamos elementos a los montículos hasta que el centro sea pequeño. Como mínimo pasaremos una vez,
		//por lo que el invariante de la representación será recuperado.
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
		//Si la cola está vacía no hay elementos
		if (center.empty()) { cout << "ECSA"; return; }
		//Si no, retiramos el de la izquierda de la cola
		cout << center.front();
		center.pop_front();
		//Si la cola está vacía y hay elementos en los montículos, los añadimos
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
	//Lo implementaremos como hemos visto en los problemas, con dos montículos.
	//La parte central de la estructura, donde guardaremos la mediana y quizás algún otro elemento, será una cola doble.
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