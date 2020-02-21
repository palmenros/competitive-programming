#include <iostream>
#include <deque>
using namespace std;

void reordenar(deque<int>& in)
{
	//Hay muchas formas de hacer esto
	//Yo he elegido esta porque creo que es la más eficiente y la memoria que utiliza es constante
	//La idea es hacer otra deque, ir sacando de la dada y meter por los extremos en la otra
	//Y por último hacer swap
	//También se podría hacer con una cola que guardara los negativos.
	//Sin embargo de mi forma solo hay que mover cada dato una vez
	deque<int> out;
	while (!in.empty())
	{
		int aux = in.front();
		in.pop_front();
		if (aux < 0) { out.push_front(aux); }
		else { out.push_back(aux); }
	}
	in.swap(out);


}

int main()
{
	while (true)
	{
		int n;
		cin >> n;
		if (!n) { return 0; }
		deque<int> in;
		for (int i = 0; i < n; i++)
		{
			int aux;
			cin >> aux;
			in.push_back(aux);
		}
		reordenar(in);
		bool firstElem = true;
		while (!in.empty())
		{
			cout << (firstElem ? "" : " ") << in.front(); in.pop_front();
			firstElem = false;
		}
		cout << "\n";

	}
}