#include <iostream>
#include <queue>

using namespace std;

using ll = long long;

int main()
{
	int N;

	while(cin >> N && N != 0) {

		priority_queue<ll, std::vector<ll>, std::greater<>> pq;

		while(N--) {
			ll a;
			cin >> a;
			pq.push(a);
		}

		ll totalCost = 0;

		while(pq.size() >= 2) {
			auto a = pq.top();
			pq.pop();
			auto b = pq.top();
			pq.pop();

			totalCost += a + b;
			pq.push(a +b);
		}

		cout << totalCost << endl;
	}

	return 0;
}