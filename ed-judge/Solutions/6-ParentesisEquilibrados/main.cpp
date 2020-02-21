#include <stack>
#include <iostream>
#include <string>
using namespace std;

int main()
{
	while (true)
	{
		string aux;
		getline(cin, aux);
		if (!cin) { return 0; }
		stack<char> pila;
		//Se trata de hacer una pila con los caracteres que nos importan : (,{,[
		bool isGood = true;
		for (char i : aux)
		{
			if (isGood) //Una vez que isGood sea false, no se procesará nada más.
			{
				if (i == '{' || i == '[' || i == '(') //Si recibimos una apertura la añadimos a la pila
				{
					pila.push(i);
				}
				else if (i == '}' || i == ']' || i == ')') //Si recibimos un cierre hemos de poderlo compensar con la pila
				{
					char complemento;
					switch (i) //Obtenemos la apertura correspondiente
					{
					case '}':
						complemento = '{';
						break;
					case ']':
						complemento = '[';
						break;
					case ')':
						complemento = '(';
						break;
					}
					if (pila.empty()) //Si la pila está vacía
					{
						isGood = false;
					}
					else if (pila.top() != complemento) //Si la apertura no coincide con el cierre
					{
						isGood = false;
					}
					else //Todo correcto. Quitamos el elemento de arriba de la pila.
					{
						pila.pop();
					}
				}
			}
		}
		cout << (isGood && pila.empty()?"SI":"NO") << "\n";
	}
}