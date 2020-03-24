//
// Created by pedro on 17/3/20.
//

#include <iostream>
#include <algorithm>

using namespace std;

class HelloWorld {

};

HelloWorld hw;

int altura_arbol() {
	int nHijos;
	cin >> nHijos;

	if(nHijos == 0) {
		return 1;
	}

	int max_altura = 0;
	for(int i = 0; i < nHijos; i++) {
		int alturaHijo = altura_arbol();
		max_altura = max(max_altura, alturaHijo);
	}

	return max_altura + 1;
}

int main()
{
	int N;
	cin >> N;

	for(int i = 0; i < N; i++) {
		cout << altura_arbol() << endl;
	}

	return 0;
}