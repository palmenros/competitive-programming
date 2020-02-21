#pragma once
#include <stdexcept>
#include <iostream>
#include <iomanip>
class fecha
{
public:
	fecha(int h, int m, int s);
	void imprime(std::ostream& os);
	fecha();
	~fecha();
	void obtenerFecha(std::istream& is);
	bool operator<(fecha const& other);
	fecha& operator=(fecha const& other);
	bool operator==(fecha const& other);
private:
	int fechaAnno;
	int fechaMes;
	int fechaDia;
};

inline std::ostream& operator<<(std::ostream& os, fecha aImprimir)
{
	aImprimir.imprime(os);
	return os;
}

inline std::istream& operator>>(std::istream& is, fecha& h)
{
	h.obtenerFecha(is);
	return is;
}
