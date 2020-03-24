#include <iostream>
#include "bintree_eda.h"
#include <climits>
using namespace std;

template <class T>
struct Datos
{
	bool checkLB; //Indica si tenemos que comprobar que todo es mayor que LB
	bool checkUB; //Indica si tenemos que comprobar que todo es menor que RB
	T LB; //Cota inferior
	T UB; //Cota superior
	Datos(bool checkLB, bool checkUB, T LB, T UB) : checkLB(checkLB),checkUB(checkUB),LB(LB),UB(UB) {}
};
//Es de b�squeda el arbol dado, y est�n sus elementos estrictamente comprendidos entre las cotas?
//Lo vamos a hacer eficientemente, parando si no es de búsqueda en la superficie pero sin utilizar INT_MIN , INT_MAX
template <class T>
bool esDeBusqueda(bintree<T> arbol, Datos<T> datos)
{
	//Si es vac�o es de b�squeda
	if (arbol.empty())
	{
		return true;
	}
	//Si no, lo es sii tanto el izquierdo como el derecho lo son, sus elementos est�n comprendidos en los intervalos adecuados y la ra�z est� entre las cotas
	return 
	(
		(!datos.checkLB || arbol.root() > datos.LB) && //Si se dice que hay que comprobar cotas inf, ha de ser mayor la raíz
		(!datos.checkUB || arbol.root() < datos.UB) && //Si se dice que hay que comprobar cotas sup, ha de ser menor la raíz
		esDeBusqueda(arbol.left(), Datos<T>(datos.checkLB,true,datos.LB,arbol.root())) && //Comprobar árbol izq con cotas adecuadas
		esDeBusqueda(arbol.right(), Datos<T>(true,datos.checkUB,arbol.root(),datos.UB)) //Comprobar árbol der con cotas adecuadas
	);
}

void resuelveCaso()
{
	auto arbol = leerArbol(-1);
	//En la llamada de abajo, los 0 dan igual; pueden ser cualquier cosa. Las precondiciones son condicionales
	cout << (esDeBusqueda(arbol, Datos<int>(false,false,0,0)) ? "SI" : "NO") << "\n";
}

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		resuelveCaso();
	}
}