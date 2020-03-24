#include <iostream>
#include <queue>
#include <vector>
#include "bintree_eda.h"
using namespace std;
struct Datos
{
    bool existe; //Existe el elemento
    int valor; //Valor del elemento
    int diepte; //Profundidad del elemento
    Datos(bool existe, int valor, int diepte):existe(existe),valor(valor),diepte(diepte){}
};

template <class T>
class arbol_ext : public bintree<T>
{
    using Link = typename bintree<T>::Link;
public:
    arbol_ext() :bintree<T>() {}
    arbol_ext(arbol_ext<T> const& l, T const& e, arbol_ext<T> const& r) : bintree<T>(l, e, r) {}
 
    Datos accesibleBuscado(vector<bool>& vectorCriba)
    {
        //Cuidado con la definici�n de accesible: �l mismo tampoco puede ser primo
        //Lineal en el n�mero de nodos porque las operaciones que se hacen son constantes por cada nodo
        //Realmente es lineal en la posici�n (en el recorrido por nivel) del nodo soluci�n
        //En el peor caso, hay que recorrer todo el �rbol y ver que no hay soluci�n, as� que lineal en # nodos
        //Para hacer esta funci�n �ptimamente observamos que el nodo que nos interesa es el primero accesible en el
        //recorrido por nivel, adem�s este recorrido es �ptimo ya que podemos retirar nodos cuyos hijos no nos interesan
        //Empezamos el recorrido por nivel; lo vamos a hacer con pair<Link, int> para recordar la profundidad
        //El recorrido por nivel no se inicializa si el �rbol es vac�o; esto para asegurar que la cola tiene nodos reales
        if (this->raiz == nullptr)
        {
            return { false,0,0 };
        }
        queue<pair<Link, int>> colaRNivel;
        colaRNivel.push({ this->raiz,1 });
        while (!colaRNivel.empty())
        {
            //Si encontramos uno accesible lo devolvemos; si no a�adimos a sus hijos (o no)
            auto act = colaRNivel.front();
            colaRNivel.pop();
            //Si no es primo nos interesa; si lo es no
            if (!vectorCriba[act.first->elem])
            {
                if (act.first->elem % 7 == 0) //Si es accesible
                {
                    return { true,act.first->elem,act.second };
                }
                //A�adimos sus hijos a la cola
                if (act.first->left != nullptr)
                {
                    colaRNivel.push({ act.first->left, act.second + 1 });
                }
                if (act.first->right != nullptr)
                {
                    colaRNivel.push({ act.first->right, act.second + 1 });
                }
            }
        }
        //No hemos encontrado ninguno
        return { false,0,0 };
    }
};
template <class T>
arbol_ext<T> leerArbol_ext(T vacio) {

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

void resuelveCaso(vector<bool>& vectorCriba)
{
    auto arbol = leerArbol_ext(-1);
    auto datos = arbol.accesibleBuscado(vectorCriba);
    if (datos.existe)
    {
        cout << datos.valor << " " << datos.diepte;
    }
    else
    {
        cout << "NO HAY";
    }
    cout << endl;

}

int main()
{
    vector<bool> vectorCriba(5001, true);
    //Vamos a hacer la criba de Erat�stenes, necesitamos hacerla hasta el 67
    for (int i = 2; i < 68; i++)
    {
        //Tenemos que retirar los m�ltiplos de i salvo i, solo si i es primo
        //Por hip�tesis de inducci�n i es primo sii est� marcado con true en el vector en este momento
        if (vectorCriba[i]) //Si i es primo
        {
            //Retiramos los m�ltiplos
            int j = 2 * i;
            while (j <= 5000)
            {
                vectorCriba[j] = false;
                j += i;
            }
        }
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        resuelveCaso(vectorCriba);
    }
    return 0;
}