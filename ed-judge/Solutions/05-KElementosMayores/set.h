#pragma once

#include <stdexcept>  // std::domain_error
#include <utility>    // std::move
#include <algorithm>


template <class T>
class set {
public:
	set(int tam = TAM_INICIAL); // constructor
	set(set<T> const& other); // constructor por copia
	set<T>& operator=(set<T> const& other); // operador de asignaci�n
	~set(); // destructor
	void insert(T e);
	bool contains(T e) const;
	void erase(T e);
	bool empty() const;
	int size() const;
	T minimo() const;
	void delMinimo();
private:
	const static int TAM_INICIAL = 8;
	int contador;
	int capacidad;
	T* datos;
	void amplia();
	void libera();
	void copia(set<T> const& other);
};

template <class T>
set<T>::set(int tam) : contador(0), capacidad(tam), datos(new T[capacidad]) {}

template <class T>
set<T>::~set() {
	libera();
}

template <class T>
void set<T>::libera() {
	delete[] datos;
}

/** Constructor por copia */
template <class T>
set<T>::set(set<T> const& other) {
	copia(other);
}

/** Operador de asignaci�n */
template <class T>
set<T>& set<T>::operator=(set<T> const& other) {
	if (this != &other) {
		libera();
		copia(other);
	}
	return *this;
}

template <class T>
void set<T>::copia(set<T> const& other) {
	capacidad = other.capacidad;
	contador = other.contador;
	datos = new T[capacidad];
	for (int i = 0; i < contador; ++i)
		datos[i] = other.datos[i];
}

template <class T>
void set<T>::insert(T e) {
	if (!contains(e)) {
		if (contador == capacidad)
			amplia();
		datos[contador] = e;
		++contador;
	}
	std::sort(datos, datos + contador);
}

template <class T>
bool set<T>::contains(T e) const {
	int i = 0;
	while (i < contador && datos[i] != e)
		++i;
	return i < contador;
}

template <class T>
void set<T>::amplia() {
	T* nuevos = new T[2 * capacidad];
	for (int i = 0; i < capacidad; ++i)
		nuevos[i] = std::move(datos[i]);
	delete[] datos;
	datos = nuevos;
	capacidad *= 2;
}

template <class T>
void set<T>::erase(T e) {
	int i = 0;
	while (i < contador && datos[i] != e)
		++i;
	if (i < contador) {
		datos[i] = datos[contador - 1];
		--contador;
	}
	else
		throw std::domain_error("El elemento no esta");
}


template <class T>
bool set<T>::empty() const {
	return contador == 0;
}

template <class T>
int set<T>::size() const {
	return contador;
}

template<class T>
inline T set<T>::minimo() const
{
	if (contador == 0)
	{
		throw std::domain_error("EMPTY SET");
	}
	return datos[0];
}

template<class T>
inline void set<T>::delMinimo()
{
	if (contador == 0)
	{
		throw std::domain_error("EMPTY SET");
	}
	for (int i = 0; i < contador - 1; i++)
	{
		datos[i] = datos[i + 1];
	}
	contador--;
}
