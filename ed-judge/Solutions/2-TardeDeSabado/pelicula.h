#pragma once
#include <string>
#include <iostream>
#include "horas.h"

class pelicula
{
private:
	horas hora;
	std::string titulo;
public:
	bool operator<(const pelicula& other)
	{
		return hora < other.hora || (hora == other.hora && this->titulo < other.titulo);
	}
	pelicula() :hora(horas(0, 0, 0)), titulo("")
	{

	}
	~pelicula(){}
	std::ostream& imprimeA(std::ostream& os)
	{
		os << hora << titulo;
		return os;
	}
	std::istream& recibeDe(std::istream& is)
	{
		horas a;
		horas b;
		is >> a >> b;
		hora = a + b;
		std::getline(is, titulo);
		return is;
	}




};
inline std::ostream& operator<<(std::ostream& os, pelicula aImprimir)
{
	aImprimir.imprimeA(os);
	return os;
}

inline std::istream& operator>>(std::istream& is, pelicula& h)
{
	h.recibeDe(is);
	return is;
}