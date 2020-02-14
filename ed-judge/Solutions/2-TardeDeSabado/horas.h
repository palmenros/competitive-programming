#pragma once
#include <stdexcept>
#include <iostream>
class horas
{
public:
	horas(int h, int m, int s);
	void imprime(std::ostream& os);
	horas();
	~horas();
	void obtenerHora(std::istream& is);
	bool operator<(horas const& other);
	bool operator==(horas const& other);
	horas operator+(horas const& other);
private:
	int h;
	int m;
	int s;
};

inline std::ostream& operator<<(std::ostream& os, horas aImprimir)
{
	aImprimir.imprime(os);
	return os;
}

inline std::istream& operator>>(std::istream& is, horas& h)
{
	h.obtenerHora(is);
	return is;
}
