
// NOMBRES Y APELLIDOS
// Mart�n G�mez Abej�n y Pedro Palacios Almendros

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include "bintree_eda.h"

struct Datos
{
    //Vamos a llamar rama a lo que en las transparencias se llama camino, para evitar colisiones
    int lCaminoMaximo; //Longitud del camino de pares m�s largo
    int lRamaMaxima; //Longitud de la rama de pares m�s larga
    Datos(int lCaminoMaximo, int lRamaMaxima) :lCaminoMaximo(lCaminoMaximo), lRamaMaxima(lRamaMaxima) { }
};

Datos recursiveCaminoPares(bintree<int> arbol)
{
    //Caso trivial
    if (arbol.empty()) { return { 0,0 }; }
    //Distinci�n de casos; ra�z par o impar
    if (arbol.root() % 2 == 1) //Impar
    {
        //No hay caminos que pasen por la ra�z, ni ramas;
        //por tanto los caminos que existen en los hijos son todos
        return { max(recursiveCaminoPares(arbol.left()).lCaminoMaximo,recursiveCaminoPares(arbol.right()).lCaminoMaximo),0 };
    }
    else //Par
    {
        auto iz = recursiveCaminoPares(arbol.left());
        auto der = recursiveCaminoPares(arbol.right());
        //Hay caminos que pasan por la ra�z, y las ramas de los hijos se prolongan hasta la ra�z
        return
            {
            //Caminos; m�ximo de los de los hijos y del nuevo camino formado por la ra�z y dos ramas
            max(
                max(iz.lCaminoMaximo, der.lCaminoMaximo),
                1 + iz.lRamaMaxima + der.lRamaMaxima
            ),
            //Ramas, cada rama se prolonga 1 unidad y nos interesa la m�s larga
            max(iz.lRamaMaxima,der.lRamaMaxima)+1
            };
    }
}

int caminoPares(bintree<int> arbol) {
    // completar (posiblemente definiendo tambi�n otras funciones)
    // Coste justificado del algoritmo:
    // El coste es lineal en el n�mero de nodos (O(n)), debido a que calculamos lo que se nos pide
    // haciendo una recursi�n por cada nodo, y el coste de cada recursi�n (sin contar las llamadas
    // a otras recursiones) es constante.

    //Para implementar este algoritmo podemos definir un tipo Datos que almacene ciertos datos que
    //permitan resolver el problema de forma recursiva
    //Se cumple que la longitud m�xima de un camino formado por nodos pares es el m�ximo de:
    // 1) Las longitudes de todos los caminos pares dentro de cada hijo
    // 2) Las longitudes de los caminos pares que pasan por la ra�z
    // Por lo que pasando recursivamente ambos par�metros (caminos, ramas) resolvemos lo que se nos pide
    return recursiveCaminoPares(arbol).lCaminoMaximo;
}

void resuelveCaso() {
    bintree<int> arbol = leerArbol(-1);
    cout << caminoPares(arbol) << '\n';
}


int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    cin >> numCasos;
    for (int i = 0; i < numCasos; ++i) {
        resuelveCaso();
    }

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
