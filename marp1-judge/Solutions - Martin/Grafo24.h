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

using lli = long long int;

using Adys = std::vector<std::pair<int,lli>>;  // lista de adyacentes a un v�rtice

class Grafo24 {
private:
    int _V;  // n�mero de v�rtices
    int _A;  // n�mero de aristas
    std::vector<Adys> _ady;  // vector de listas de adyacentes
public:

    /**
     * Crea un grafo con V v�rtices.
     */
    Grafo24(int V) : _V(V), _A(0), _ady(_V) {}

    /**
     * Crea un grafo a partir de los datos en el flujo de entrada.
     */
    Grafo24(std::istream& flujo):_A(0) {
        flujo >> _V;
        if (!flujo) { return; }
        _ady.resize(_V);
        int E, v, w; lli d;
        flujo >> E;
        while (E--) {
            flujo >> v >> w >> d;
            v--;
            w--;
            ponArista(v, w, d);
        }
    }

    /**
     * Devuelve el n�mero de v�rtices del grafo.
     */
    int V() const { return _V; }

    /**
     * Devuelve el n�mero de aristas del grafo.
     */
    int A() const { return _A; }

    /**
     * A�ade la arista v-w al grafo.
     * @throws domain_error si alg�n v�rtice no existe
     */
    void ponArista(int v, int w, lli d) {
        if (v < 0 || v >= _V || w < 0 || w >= _V)
            throw std::domain_error("Vertice inexistente");
        ++_A;
        _ady[v].push_back({ w,d });
        _ady[w].push_back({ v,d });
    }

    /**
     * Devuelve la lista de adyacencia de v.
     * @throws domain_error si v no existe
     */
    Adys const& ady(int v) const {
        if (v < 0 || v >= _V)
            throw std::domain_error("Vertice inexistente");
        return _ady[v];
    }

    /**
     * Muestra el grafo en el stream de salida o (para depurar)
     */
    void print(std::ostream& o = std::cout) const {
        o << _V << " v�rtices, " << _A << " aristas\n";
        for (int v = 0; v < _V; ++v) {
            o << v << ": ";
            for (auto t : _ady[v]) {
                o << t.first << " ";
            }
            o << "\n";
        }
    }
};

/**
 * Para mostrar grafos por la salida est�ndar
 */
inline std::ostream& operator<<(std::ostream& o, Grafo24 const& g) {
    g.print(o);
    return o;
}

