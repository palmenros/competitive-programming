
// Martín Gómez Abejón y Óscar Calvet Sisó

#include <iostream>
#include <fstream>
using namespace std;

#include "deque_eda.h"

class EngordarLista : public deque<int> {
    using Nodo = deque<int>::Nodo;
public:
    // imprime la lista enlazada
    //
    void print(std::ostream& o = std::cout) const {
        // tu código aquí
        //Trivialmente lineal en el número de nodos
        //booleano para regular espacios
        bool primeroHecho = false;
        //Nodo auxiliar para recorrer la deque
        Nodo* act = this->fantasma->sig;
        while (act != this->fantasma)
        {
            //Espacios
            if (!primeroHecho)
            {
                primeroHecho = true;
            }
            else
            {
                o << " ";
            }
            //Imprimir
            o << act->elem;
            //Avanzar
            act = act->sig;
        }
    }

    // introduce los elementos de other (una lista enlazada)
    // en la lista representada por this alternativamente al principio y al final
    void engordar(EngordarLista& other) {
        //Para empezar, esta operación tiene coste lineal en el número de nodos de la lista que se
        //queda vacía ya que utilizamos un bucle while y operaciones constantes en cada elemento de la lista
        //booleano que indica dónde estamos insertando; false al principio y true al final
        bool insertandoEn = false;
        //Cambiamos el número de elementos de cada lista para dejarlas en buen estado
        this->nelems += other.nelems;
        other.nelems = 0;
        //Cogemos la cadena de nodos de other y la desvinculamos, dejándola vacía
        other.fantasma->ant->sig = nullptr;
        //Nodo para recorrer other
        Nodo* act = other.fantasma->sig;
        //Dejamos other en buen estado
        other.fantasma->sig = other.fantasma->ant = other.fantasma;
        //Ahora insertamos los elementos en el lugar adecuado
        while (act != nullptr)
        {
            //Avanzamos en la segunda deque
            Nodo* aInsertar = act;
            act = act->sig;
            if (insertandoEn) //Meter al final
            {
                //Hay que modificar el fantasma, los nodos del que insertamos y el siguiente del último
                //Los enlaces tienen que quedar así

                //        --->           --->
                // previo      aInsertar      fantasma
                //        <---           <---

                Nodo* previo = this->fantasma->ant;
                previo->sig = this->fantasma->ant = aInsertar;
                aInsertar->ant = previo;
                aInsertar->sig = this->fantasma;
            }
            else //Meter al principio
            {
                //Análogo al anterior
                //          --->           --->
                // fantasma      aInsertar      posterior
                //          <---           <---
                Nodo* posterior = this->fantasma->sig;
                posterior->ant = this->fantasma->sig = aInsertar;
                aInsertar->sig = posterior;
                aInsertar->ant = this->fantasma;
            }
            //El enunciado especifica que hay que meter delante y detrás de manera alternada
            //Para regularlo, actualizamos este booleano a su estado siguiente
            insertandoEn = !insertandoEn;
        }
    }
};


inline std::ostream& operator<<(std::ostream& o, EngordarLista const& lista) {
    lista.print(o);
    return o;
}

EngordarLista leerLista() {
    EngordarLista lista;
    int n, val;
    std::cin >> n; // tamaño
    while (n--) {
        std::cin >> val;
        lista.push_back(val);
    }
    return lista;
}


void resuelveCaso() {
    auto lista1 = leerLista();
    auto lista2 = leerLista();
    lista1.engordar(lista2);
    std::cout << lista1 << '\n';
}


int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int casos;
    cin >> casos;
    while (casos--) {
        resuelveCaso();
    }

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
