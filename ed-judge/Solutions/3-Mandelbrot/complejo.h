#pragma once
class complejo
{
public:
	complejo(double a, double b);
	~complejo();
	complejo operator+(complejo const& other);
	complejo operator*(complejo const& other);
	complejo& operator=(complejo const& other);
	double modulo();
private:
	double a;
	double b;
	//El complejo será a + b i
};

