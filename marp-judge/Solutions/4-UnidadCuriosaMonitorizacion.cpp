#include <iostream>
#include <queue>

using namespace std;

using ll = unsigned long long;

struct Persona {
	unsigned int id;
	unsigned int period;
	ll time;

	Persona(int id, int period, int time)
		: id(id), period(period), time(time)
	{}

	Persona()
	{}

	bool operator<(const Persona& b) const {
		if(time == b.time) {
			return id > b.id;
		}
		return time > b.time;
	}
};

int main()
{
	int N;
	while(cin >> N && N != 0) {

		priority_queue<Persona> pq;

		while(N--) {
			Persona p;
			cin >> p.id >> p.time;
			p.period = p.time;

			pq.push(p);
		}

		int K;
		cin >> K;

		while(K--) {
			auto top = pq.top();
			pq.pop();
			cout << top.id << '\n';
			top.time = top.time + top.period;
			pq.push(top);
		}

		cout << "---\n";
	}

	return 0;
}