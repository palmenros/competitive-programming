
// NOMBRES Y APELLIDOS
// Martín Gómez Abejón y Pedro Palacios Almendros

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include "bintree_eda.h"

struct Datos
{
    //Vamos a llamar rama a lo que en las transparencias se llama camino, para evitar colisiones
    int lCaminoMaximo; //Longitud del camino de pares más largo
    int lRamaMaxima; //Longitud de la rama de pares más larga
    Datos(int lCaminoMaximo, int lRamaMaxima) :lCaminoMaximo(lCaminoMaximo), lRamaMaxima(lRamaMaxima) { }
};

Datos recursiveCaminoPares(bintree<int> arbol)
{
    //Caso trivial
    if (arbol.empty()) { return { 0,0 }; }
    //Distinción de casos; raíz par o impar
    if (arbol.root() % 2 == 1) //Impar
    {
        //No hay caminos que pasen por la raíz, ni ramas;
        //por tanto los caminos que existen en los hijos son todos
        return { max(recursiveCaminoPares(arbol.left()).lCaminoMaximo,recursiveCaminoPares(arbol.right()).lCaminoMaximo),0 };
    }
    else //Par
    {
        auto iz = recursiveCaminoPares(arbol.left());
        auto der = recursiveCaminoPares(arbol.right());
        //Hay caminos que pasan por la raíz, y las ramas de los hijos se prolongan hasta la raíz
        return
            {
            //Caminos; máximo de los de los hijos y del nuevo camino formado por la raíz y dos ramas
            max(
                max(iz.lCaminoMaximo, der.lCaminoMaximo),
                1 + iz.lRamaMaxima + der.lRamaMaxima
            ),
            //Ramas, cada rama se prolonga 1 unidad y nos interesa la más larga
            max(iz.lRamaMaxima,der.lRamaMaxima)+1
            };
    }
}

int caminoPares(bintree<int> arbol) {
    // completar (posiblemente definiendo también otras funciones)
    // Coste justificado del algoritmo:
    // El coste es lineal en el número de nodos (O(n)), debido a que calculamos lo que se nos pide
    // haciendo una recursión por cada nodo, y el coste de cada recursión (sin contar las llamadas
    // a otras recursiones) es constante.

    //Para implementar este algoritmo podemos definir un tipo Datos que almacene ciertos datos que
    //permitan resolver el problema de forma recursiva
    //Se cumple que la longitud máxima de un camino formado por nodos pares es el máximo de:
    // 1) Las longitudes de todos los caminos pares dentro de cada hijo
    // 2) Las longitudes de los caminos pares que pasan por la raíz
    // Por lo que pasando recursivamente ambos parámetros (caminos, ramas) resolvemos lo que se nos pide
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
