#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

struct Casilla {
	int n;
	int movimientos;

	Casilla(int n, int movimientos)
		: n(n), movimientos(movimientos)
	{}
};

int minimo_movimientos(const vector<int>& movimientos, int K)
{
	int numCasillas = movimientos.size();
	vector<bool> marcados(numCasillas, false);

	queue<Casilla> q;

	marcados[0] = true;
	q.push({0, 0});

	while(!q.empty()){
		auto e = q.front();
		q.pop();

		if(e.n == numCasillas - 1) {
			return e.movimientos;
		}

		int v = e.n;

		for(int w = v + 1; (w <= v + K) && (w < numCasillas); w++) {
			//Añadimos por cada casilla una nueva arista

			if(!marcados[w]) {
				marcados[w] = true;
				q.push({movimientos[w] == -1 ? w : movimientos[w], e.movimientos + 1});
			}
		}

	}

}

int main()
{
	int N, K, S, E;
	while(cin >> N >> K >> S >> E && (N + K + S + E) != 0 ) {

		//Escalera o serpiente
		vector<int> movimientos(N * N, -1);

		while(S--) {
			int a, b;
			cin >> a >> b;
			a--; b--;

			movimientos[a] = b;
		}

		while(E--) {
			int a, b;
			cin >> a >> b;
			a--; b--;

			movimientos[a] = b;
		}

		cout << minimo_movimientos(movimientos, K) << "\n";
	}

	return 0;
}