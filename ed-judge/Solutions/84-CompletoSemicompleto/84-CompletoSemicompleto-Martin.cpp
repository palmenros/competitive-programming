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
        //Trivialmente lineal en el n�mero de nodos, ya que hacemos un recorrido por niveles
        //No se puede mejorar porque si la respuesta es completo se visitan todos los nodos
        //En vez de hacer una recursi�n, vamos a hacer un recorrido por niveles, que es m�s original
        //y detecta antes �rboles que no son nada muy desiguales que �rboles que no son nada muy sim�tricos
        //As� la funci�n es �ptima para �rboles aleatorios, y es m�s sim�trica y no necesitamos recursi�n
        //Vamos a recorrer por niveles utilizando un nodo fantasma.
        //El �rbol es semicompleto si y solo si cuando encontramos un nodo sin hijos no encontramos ninguno nunca m�s
        //El �rbol es completo si y solo si es semicompleto y para todo nivel o encontramos hijos o no
        //Comenzamos el recorrido
        queue<Link> q;
        if (this->raiz != nullptr)
        {
            q.push(this->raiz);
        }
        //Fantasma y variables para recordar propiedades de los nodos previos
        bool sinHijosEncontrados = false; //Hemos no encontrado hijos previamente en este nivel?
        bool noHijosNivelesPrevios = false; //En el nivel previo hab�a �rboles sin hijos? Si es as� tenemos que parar en este nivel para no ser nada
        q.push(nullptr);
        while (!q.empty())
        {
            Link act = q.front(); q.pop();
            //Distinci�n de casos: es fantasma o no?
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
                //Si hemos encontrado nodos sin hijos previamente y este tiene hijos el �rbol no es nada
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
    if (raiz == vacio) { // es un �rbol vac�o
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