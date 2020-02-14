
// ALBERTO VERDEJO

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <fstream>
#include <stdexcept>

using namespace std;

#include "horas.h"

bool resuelveCaso() {
    
    std::set<horas> s;

    //Leer memoria
    int N, M;
    cin >> N >> M;

    if (N == 0 && M == 0) {
        return false;
    }

    for (int i = 0; i < N; i++) {
        horas h;
        cin >> h;
        s.insert(h);
    }


    for (int i = 0; i < M; i++) {
        try {
            horas x;
            cin >> x;
            auto val = std::lower_bound(s.begin(), s.end(), x);
            if (val == s.end()) {
                //Not found
                cout << "NO" << endl;
            } else {
                cout << *val << endl;
            }
        }
        catch (const std::exception & e) {
            cout << e.what() << endl;
        }
    }

    cout << "---" << endl   ;

   return true;
}

int main() {
   // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

   while (resuelveCaso());

   // restablecimiento de cin
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("pause");
#endif
   return 0;
}
