#include <queue>
#include <iostream>
#include <cmath>

using namespace std;

using ll = unsigned long long int;

struct Instrumento {
	int nInstrumento;
	ll musicos;
	ll partituras;

	Instrumento(int nInstrumento, ll musicos, ll partituras)
		: nInstrumento(nInstrumento), musicos(musicos), partituras(partituras)
	{}

	bool operator<(const Instrumento &other) const
	{
		auto a = musicos * other.partituras;
		auto b = other.musicos * partituras;

		if(a == b) {
			return nInstrumento < other.nInstrumento;
		}
		return a < b;
	}

	long double ratio() const {
		return musicos / (long double)partituras;
	}
};

int main()
{
	int P, N;

	while(cin >> P >> N) {

		if(P == 0 && N == 0) {
			cout << 0 << "\n";
			continue;
		}

		//Todos los instrumentos deben tener al menos una partitura
		P -= N;

		priority_queue<Instrumento> pq;

		for(int i = 0; i < N; i++) {
			ll musicos;
			cin >> musicos;
			pq.push(Instrumento{i, musicos, 1});
		}

		while(P--) {
			auto top = pq.top();
			pq.pop();
			top.partituras++;
			pq.push(top);
		}

		auto worst = pq.top();
		cout << ceill(worst.ratio()) << "\n";
	}

}
