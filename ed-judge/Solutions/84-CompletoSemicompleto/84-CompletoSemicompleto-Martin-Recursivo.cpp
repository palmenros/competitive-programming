#include <iostream>
#include "bintree_eda.h"
#include <queue>
using namespace std;

enum TipoDeArbol
{
	COMPLETO,
	SEMICOMPLETO,
	NADA
};

struct Datos
{
    TipoDeArbol tipo; //Tipo de árbol
    int altura; //Altura del árbol
    Datos(TipoDeArbol tipo, int altura) : tipo(tipo), altura(altura) {}

};

template <class T>
class arbolExt : public bintree<T>
{
	using Link = typename bintree<T>::Link;
public:
    arbolExt() : bintree<T>() {}
    arbolExt(arbolExt<T> const& l, T const& e, arbolExt<T> const& r) : bintree<T>(l, e, r) {}
    Datos tipoDeArbol(Link r) const
    {
        //Caso trivial
        if (r == nullptr)
        {
            return { COMPLETO,0 };
        }
        else
        {
            auto datosIzq = tipoDeArbol(r->left);
            auto datosDer = tipoDeArbol(r->right);
            if (datosIzq.tipo == COMPLETO && datosDer.tipo == COMPLETO && datosIzq.altura == datosDer.altura) //Si cumple las condiciones de completo
            {
                return { COMPLETO,datosIzq.altura + 1 };
            }
            else if ( //Condiciones de semicompleto si no es completo
                (datosIzq.tipo == COMPLETO && datosDer.tipo == SEMICOMPLETO && datosIzq.altura == datosDer.altura)
                ||
                (datosIzq.tipo != NADA && datosDer.tipo == COMPLETO && datosIzq.altura == datosDer.altura + 1)
                )
            {
                return { SEMICOMPLETO, datosIzq.altura + 1 };
            }
            else
            {
                return { NADA,0 }; //Altura no pertinente
            }
        }
    }
    TipoDeArbol tipoDeArbol() const
    {
        //Trivialmente lineal en el número de nodos, ya que hacemos un recorrido por niveles
        //No se puede mejorar porque si la respuesta es completo se visitan todos los nodos
        //La verdad es que lo del recorrido por niveles quedó un poco feo y puede ocupar algo de memoria
        //Así que ahora para redimirme lo voy a hacer recursivo
        //El envío anterior lo tiene con el recorrido por niveles
        //Esto es recursivo muy trivial
        return tipoDeArbol(this->raiz).tipo;
    }
};
template <class T>
arbolExt<T> leerArbol_ext(T vacio) {

    T raiz;
    std::cin >> raiz;
    if (raiz == vacio) { // es un árbol vacío
        return {};
    }
    else { // leer recursivamente los hijos
        auto iz = leerArbol_ext(vacio);
        auto dr = leerArbol_ext(vacio);
        return { iz, raiz, dr };
    }
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        arbolExt<char> arb = leerArbol_ext('.');
        switch (arb.tipoDeArbol())
        {
        case COMPLETO:
            cout << "COMPLETO\n";
            break;
        case SEMICOMPLETO:
            cout << "SEMICOMPLETO\n";
            break;
        case NADA:
            cout << "NADA\n";
            break;
        }
    }
}