
// ALBERTO VERDEJO

#ifndef HORAS_H
#define HORAS_H

#include <iostream>
#include <iomanip>
#include <stdexcept>  // invalid_argument

using namespace std;

class horas {
private:
   int HH; // las horas
   int MM; // los minutos
   int SS; // los segundos 
    
   bool check(int h, int m, int s) {
       return 0 <= h && h < 24 && 0 <= m && m < 60 && 0 <= s && s < 60;
   }

public:

    horas() : horas(0, 0, 0)
    {
    }

   // constructora
   horas(int h, int m, int s) : HH(h), MM(m), SS(s) {
       if (!check(h, m, s)) { throw std::domain_error("ERROR"); }
   }
   
   // observadoras
   int hora() const { return HH; }
   int minuto() const { return MM; }
   int segundo() const { return SS; }

   // operador de comparación
   bool operator<(horas const& h) const {
       return HH * 3600 + MM * 60 + SS < h.HH * 3600 + h.MM * 60 + h.SS;
   }

   void read(std::istream & input = std::cin) {
       char c;
       cin >> HH >> c >> MM >> c >> SS;
       if (!check(HH, MM, SS)) { throw std::domain_error("ERROR"); }
   }

   void print(std::ostream& o = std::cout) const {
      o << std::setfill('0') << std::setw(2) << HH << ':'
        << std::setfill('0') << std::setw(2) << MM << ':'
        << std::setfill('0') << std::setw(2) << SS;
   }
};

inline std::ostream & operator<<(std::ostream & salida, horas const& h) {
   h.print(salida);
   return salida;
}

inline std::istream & operator>>(std::istream & entrada, horas & h) {
   h.read(entrada);
   return entrada;
}

#endif
