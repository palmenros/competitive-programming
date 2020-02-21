#include "complejo.h"
#include <cmath>
#include <iostream>
using namespace std;
complejo::complejo(double a, double b) : a(a), b(b)
{
}

complejo::~complejo()
{
}
complejo complejo::operator+(complejo const& other)
{
	//a += other.a;
	//b += other.b;
	return complejo(a+other.a,b+other.b);
}

complejo complejo::operator*(complejo const& other)
{
	//Como podrían ser el mismo, copiamos todas las variables para evitar sobreescrituras
	//de datos que se utilizarán después
	double a1 = a;
	double b1 = b;
	double a2 = other.a;
	double b2 = other.b;
	//a = a1 * a2 - b1 * b2;
	//b = b1 * a2 + b2 * a1;
	/*cout << a1 << endl;
	cout << b1 << endl;
	cout << a2 << endl;
	cout << b2 << endl;
	cout << (a1 * a2 - b1 * b2) << endl;
	cout << (b1 * a2 + b2 * a1) << endl;
	system("PAUSE");*/
	return complejo(a1 * a2 - b1 * b2, b1 * a2 + b2 * a1);
	
}

complejo& complejo::operator=(complejo const& other)
{
	a = other.a;
	b = other.b;
	return *this;
}

double complejo::modulo()
{
	return sqrt(a*a+b*b);
}
