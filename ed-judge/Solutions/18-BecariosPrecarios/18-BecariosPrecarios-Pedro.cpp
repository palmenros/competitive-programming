//
// Created by pedro on 17/3/20.
//

#include <iostream>
using namespace std;

int becarios_preciaros(int numJefes)
{
	int numHijos;
	cin >> numHijos;

	if(numHijos == 0) {
		return numJefes <= 0 ? 1 : 0;
	}

	int suma = 0;
	for(int i = 0; i < numHijos; i++) {
		suma += becarios_preciaros(numJefes - 1);
	}

	return suma;
}

int main()
{
	int numJefes;
	while(cin >> numJefes) {
		cout << becarios_preciaros(numJefes) << endl;
	}

	return 0;
}