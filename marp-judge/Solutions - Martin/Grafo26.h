//
//  Grafo26.h
//
//  Implementaci�n de grafos dirigidos con cuyos inversos se puede trabajar eficientemente
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
#include <map>


using Adys = std::vector<std::pair<int, int>>;  // lista de adyacentes a un v�rtice

class Grafo26 {
private:
    int _V;  // n�mero de v�rtices
    int _A;  // n�mero de aristas
    std::vector<Adys> _ady;  // vector de listas de adyacentes
    std::vector<Adys> _adyDual;  // vector de listas de adyacentes duales
public:

    /**
     * Crea un grafo con V v�rtices.
     */
    Grafo26(int V) : _V(V), _A(0), _ady(_V), _adyDual(_V) {}

    /**
     * Crea un grafo a partir de los datos en el flujo de entrada.
     */
    Grafo26(std::istream& flujo) :_A(0) {
        flujo >> _V;
        if (!flujo) { return; }
        _ady.resize(_V);
        _adyDual.resize(_V);
        int E, v, w, esf;
        flujo >> E;
        while (E--) {
            flujo >> v >> w >> esf;
            v--; w--;
            ponArista(v, w, esf);
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
    void ponArista(int v, int w, int esf) {
        if (v < 0 || v >= _V || w < 0 || w >= _V)
            throw std::domain_error("Vertice inexistente");
        ++_A;
        _ady[v].push_back({w,esf});
        _adyDual[w].push_back({ v,esf });
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
     * Devuelve la lista de adyacencia dual de v.
     * @throws domain_error si v no existe
     */
    Adys const& adyDual(int v) const {
        if (v < 0 || v >= _V)
            throw std::domain_error("Vertice inexistente");
        return _adyDual[v];
    }
    /**
     * Muestra el grafo en el stream de salida o (para depurar)
     */
    void print(std::ostream& o = std::cout) const {
        o << _V << " v�rtices, " << _A << " aristas\n";
        for (int v = 0; v < _V; ++v) {
            o << v << ": ";
            for (auto& w : _ady[v]) {
                o << w.first << " " << w.second << " ";
            }
            o << "\n";
        }
    }
};

/**
 * Para mostrar grafos por la salida est�ndar
 */
inline std::ostream& operator<<(std::ostream& o, Grafo26 const& g) {
    g.print(o);
    return o;
}

