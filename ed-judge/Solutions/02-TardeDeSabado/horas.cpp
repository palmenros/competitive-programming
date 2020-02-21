#include "horas.h"
#include <string>

horas::horas(int h, int m, int s):h(h),m(m),s(s)
{
}

void horas::imprime(std::ostream& os)
{
	os << (h >= 10 ? "" : "0") << h << (m >= 10 ? ":" : ":0") << m << (s >= 10 ? ":" : ":0") << s;
}

horas::horas():h(0),m(0),s(0)
{
}

horas::~horas()
{
}

void horas::obtenerHora(std::istream& is)
{
	char aux; //Para coger los separadores :
	is >> h;
	if (!is || h < 0 || h >= 24)
	{
		throw std::domain_error("ERROR");
	}
	is >> aux;
	is >> m;
	if (!is || m < 0 || m >= 60)
	{
		throw std::domain_error("ERROR");
	}
	is >> aux;
	is >> s;
	if (!is || s < 0 || s >= 60)
	{
		throw std::domain_error("ERROR");
	}
}

bool horas::operator<(horas const& other)
{
	return this->h<other.h || (this->h == other.h && (this->m < other.m || (this->m == other.m && (this->s < other.s))));
}

bool horas::operator==(horas const& other)
{
	return h == other.h && m == other.m && s == other.s;
}

horas horas::operator+(horas const& other)
{
	horas n = horas();
	n.h = h + other.h;
	n.m = m + other.m;
	n.s = s + other.s;
	if (n.s >= 60)
	{
		n.s -= 60; n.m++;
	}
	if (n.m >= 60)
	{
		n.m -= 60; n.h++;
	}
	if (n.h >= 24)
	{
		throw std::domain_error("ERROR");
	}
	return n;
}
