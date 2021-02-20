//
//  Grafo.h
//
//  Implementaci�n de grafos no dirigidos
//
//  Facultad de Inform�tica
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//


#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <unordered_set>

using Adys = std::unordered_set<int>;  // lista de adyacentes a un v�rtice

class Grafo17 {
private:
    int _V;  // n�mero de v�rtices + 1
    int _A;  // n�mero de aristas
    std::vector<Adys> _ady;  // vector de listas de adyacentes
public:

    /**
     * Crea un grafo con V v�rtices.
     */
    Grafo17(int V) : _V(V + 1), _A(0), _ady(_V) { ; }

    /**
     * Crea un grafo a partir de los datos en el flujo de entrada.
     */
    Grafo17(std::istream& flujo) :_A(0) {
        flujo >> _V; _V++;
        if (!flujo) { return; }
        _ady.resize(_V);
        int E, v, w;
        flujo >> E;
        while (E--) {
            flujo >> v >> w;
            ponArista(v, w);
        }
    }

    /**
     * Devuelve el n�mero de v�rtices del grafo.
     */
    int V() const { return _V - 1; }

    /**
     * Devuelve el n�mero de aristas del grafo.
     */
    int A() const { return _A; }

    /*
    * Devuelve si hay una arista de v a w.
    */
    bool hayArista(int v, int w)
    {
        return _ady[v].find(w) != _ady[v].end();
    }

    /**
     * A�ade la arista v-w al grafo.
     * @throws domain_error si alg�n v�rtice no existe
     */
    void ponArista(int v, int w) {
        if (v <= 0 || v > _V || w <= 0 || w > _V)
            throw std::domain_error("Vertice inexistente");
        ++_A;
        _ady[v].insert(w);
    }

    /**
     * Devuelve la lista de adyacencia de v.
     * @throws domain_error si v no existe
     */
    Adys const& ady(int v) const {
        if (v <= 0 || v > _V)
            throw std::domain_error("Vertice inexistente");
        return _ady[v];
    }

    /**
     * Muestra el grafo en el stream de salida o (para depurar)
     */
    void print(std::ostream& o = std::cout) const {
        o << _V - 1 << " v�rtices, " << _A << " aristas\n";
        for (int v = 1; v <= _V; ++v) {
            o << v << ": ";
            for (int w : _ady[v]) {
                o << w << " ";
            }
            o << "\n";
        }
    }
};

/**
 * Para mostrar grafos por la salida est�ndar
 */
inline std::ostream& operator<<(std::ostream& o, Grafo17 const& g) {
    g.print(o);
    return o;
}

