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
		if(ratio() == other.ratio()) {
			return nInstrumento < other.nInstrumento;
		}
		return ratio() < other.ratio();
	}

	float ratio() const {
		return musicos / partituras;
	}
};

int main()
{
	int P, N;

	while(cin >> P >> N) {
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
		cout << llrint(worst.ratio()) << "\n";
	}

}