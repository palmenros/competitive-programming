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

template <class T>
class arbolExt : public bintree<T>
{
	using Link = typename bintree<T>::Link;
public:
    arbolExt() : bintree<T>() {}
    arbolExt(arbolExt<T> const& l, T const& e, arbolExt<T> const& r) : bintree<T>(l, e, r) {}
    TipoDeArbol tipoDeArbol()
    {
        //Trivialmente lineal en el número de nodos, ya que hacemos un recorrido por niveles
        //No se puede mejorar porque si la respuesta es completo se visitan todos los nodos
        //En vez de hacer una recursión, vamos a hacer un recorrido por niveles, que es más original
        //y detecta antes árboles que no son nada muy desiguales que árboles que no son nada muy simétricos
        //Así la función es óptima para árboles aleatorios, y es más simétrica y no necesitamos recursión
        //Vamos a recorrer por niveles utilizando un nodo fantasma.
        //El árbol es semicompleto si y solo si cuando encontramos un nodo sin hijos no encontramos ninguno nunca más
        //El árbol es completo si y solo si es semicompleto y para todo nivel o encontramos hijos o no
        //Comenzamos el recorrido
        queue<Link> q;
        if (this->raiz != nullptr)
        {
            q.push(this->raiz);
        }
        //Fantasma y variables para recordar propiedades de los nodos previos
        bool sinHijosEncontrados = false; //Hemos no encontrado hijos previamente en este nivel?
        bool noHijosNivelesPrevios = false; //En el nivel previo había árboles sin hijos? Si es así tenemos que parar en este nivel para no ser nada
        q.push(nullptr);
        while (!q.empty())
        {
            Link act = q.front(); q.pop();
            //Distinción de casos: es fantasma o no?
            if (act == nullptr)
            {
                if (q.empty()) //Hemos terminado
                {
                    return (noHijosNivelesPrevios ? SEMICOMPLETO : COMPLETO);
                }
                else
                {
                    //Actualizamos booleanos
                    noHijosNivelesPrevios = sinHijosEncontrados;
                    sinHijosEncontrados = false;
                    q.push(nullptr);

                }
            }
            else
            {
                //Primero comprobamos que no tenga hijo en la derecha sin tenerlo en la izquierda
                if (act->right != nullptr && act->left == nullptr)
                {
                    return NADA;
                }
                //Si hemos encontrado nodos sin hijos previamente y este tiene hijos el árbol no es nada
                if ((noHijosNivelesPrevios || sinHijosEncontrados) && act->left != nullptr)
                {
                    return NADA;
                }
                //Actualizamos sinHijosEncontrados
                sinHijosEncontrados = (act->right == nullptr);
                //Pasamos los hijos a la cola
                if (act->left != nullptr) { q.push(act->left); }
                if (act->right != nullptr) { q.push(act->right); }
            }
        }

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