#include "fecha.h"
#include <string>

fecha::fecha(int h, int m, int s):fechaAnno(h),fechaMes(m),fechaDia(s)
{
}

void fecha::imprime(std::ostream& os)
{
	os << std::setw(2) << std::setfill('0') << fechaDia << "/" << std::setw(2) << std::setfill('0') << fechaMes << "/" << std::setw(4) << std::setfill('0') << fechaAnno;
}

fecha::fecha():fechaAnno(0),fechaMes(0),fechaDia(0)
{
}

fecha::~fecha()
{
}

void fecha::obtenerFecha(std::istream& is)
{
	char aux; //Para coger los separadores :
	is >> fechaDia;
	is >> aux;
	is >> fechaMes;
	is >> aux;
	is >> fechaAnno;
}

bool fecha::operator<(fecha const& other)
{
	return this->fechaAnno<other.fechaAnno || (this->fechaAnno == other.fechaAnno && (this->fechaMes < other.fechaMes || (this->fechaMes == other.fechaMes && (this->fechaDia < other.fechaDia))));
}

fecha& fecha::operator=(fecha const& other)
{
	fechaAnno = other.fechaAnno; fechaMes = other.fechaMes; fechaDia = other.fechaDia;
	return *this;
}

bool fecha::operator==(fecha const& other)
{
	return fechaAnno == other.fechaAnno && fechaMes == other.fechaMes && fechaDia == other.fechaDia;
}


