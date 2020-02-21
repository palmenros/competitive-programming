#include <iostream>
#include <deque>
#include <string>
#include <stack>
using namespace std;



void desapilar(stack<char>& s,deque<char>& d)
{
	while (!s.empty())
	{
		d.push_back(s.top());
		s.pop();
	}
}

void paso1(deque<char>& in)
{
	stack<char> s;
	deque<char> out;
	while (!in.empty())
	{
		char aux = in.front();
		in.pop_front();
		if (aux == 'a' || aux == 'e' || aux == 'i' || aux == 'o' || aux == 'u' || aux == 'A' || aux == 'E' || aux == 'I' || aux == 'O' || aux == 'U')
		{
			desapilar(s, out);
			out.push_back(aux);
		}
		else
		{
			s.push(aux);
		}
	}
	desapilar(s, out);
	in.swap(out);
}

void paso2(deque<char>& in)
{
	typedef enum
	{
		L,
		R
	}Lado;
	deque<char> out;
	Lado lado = (in.size()%2?L:R);
	
	while (!in.empty())
	{
		char aux;
		aux = in.back();
		in.pop_back();
		switch (lado)
		{
		case L:
			out.push_front(aux);
			
			lado = R;
			break;
		case R:
			out.push_back(aux);
			lado = L;
			break;
		}
	}
	in.swap(out);
	
}

int main()
{
	while (true)
	{
		string cad;
		getline(cin,cad);
		if (!cin) { return 0; }
		deque<char> in;
		for (char aux : cad)
		{
			in.push_back(aux);
		}
		paso2(in);
		paso1(in);
		while (!in.empty())
		{
			cout << in.front(); in.pop_front();
		}
		cout << "\n";

	}
}