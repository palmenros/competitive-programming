#include <string>
#include <iostream>

class persona
{
private:
	int edad = 0;
	std::string nombre = "";
public:
	int getEdad()
	{
		return edad;
	}
	std::string getNombre()
	{
		return nombre;
	}
	void recibeDe(std::istream& is)
	{
		is >> edad;
		char aux;
		is.get(aux);
		std::getline(is, nombre);

	}
	void imprimeA(std::ostream& os)
	{
		os << nombre << "\n";
	}

};
inline std::istream& operator>>(std::istream& is, persona& p)
{
	p.recibeDe(is);
	return is;
}
inline std::ostream& operator<<(std::ostream& os, persona& p)
{
	p.imprimeA(os);
	return os;
}