#include <iostream>
#include <set>
#include <vector>
#include <queue>

using namespace std;

using ll = long long;

struct Tarea {
	ll comienzo;
	ll fin;
	ll periodo;

	Tarea(ll comienzo, ll fin, ll periodo = -1)
		: comienzo(comienzo), fin(fin), periodo(periodo)
	{}

	bool operator<(const Tarea& other) const {
		return comienzo > other.comienzo;
	}
};


int main()
{
	ll N, M, T;

	while(cin >> N >> M >> T) {

		priority_queue<Tarea> pq;

		while(N--) {
			ll c, f;
			cin >> c >> f;

			if(c < T) {
				pq.push({c, f});
			}
		}

		while(M--) {
			ll c, f, t;
			cin >> c >> f >> t;

			if(c < T) {
				pq.push({c, f, t});
			}		}

		bool intersects = false;
		ll previousEndTime = 0;

		while (!intersects && !pq.empty()) {

			//Get first and find if intersects
			auto top = pq.top();
			pq.pop();

			if(previousEndTime > top.comienzo) {
				intersects = true;
			}

			previousEndTime = top.fin;

			//If periodic, add another time to priority queue
			if(top.periodo != -1 && top.comienzo + top.periodo < T ) {
				pq.push({top.comienzo + top.periodo, top.fin + top.periodo, top.periodo});
			}

		}

		if(intersects) {
			cout << "SI\n";
		} else {
			cout << "NO\n";
		}

	}

	return 0;
}
