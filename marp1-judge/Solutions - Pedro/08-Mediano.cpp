#include <iostream>
#include <queue>
#include <exception>
#include <limits>

using namespace std;

using ll = long long int;

class MedianHeap {
private:
	priority_queue<ll, vector<ll>, less<>> less_than_median; //Max heap
	priority_queue<ll, vector<ll>, greater<>> greater_than_median; //Min heap
public:

	ll median() {

		if(less_than_median.empty() && greater_than_median.empty()) {
			return numeric_limits<ll>::min();
		}

		if(less_than_median.size() >= greater_than_median.size()) {
			return less_than_median.top();
		} else {
			return greater_than_median.top();
		}
	}

	void pop_median() {
		if(less_than_median.size() >= greater_than_median.size()) {
			less_than_median.pop();
		} else {
			greater_than_median.pop();
		}
	}

	void balance() {
		if(less_than_median.size() >= 2 + greater_than_median.size()) {
			auto val = less_than_median.top();
			less_than_median.pop();
			greater_than_median.push(val);
		} else if(greater_than_median.size() >= 2 + less_than_median.size()) {
			auto val = greater_than_median.top();
			greater_than_median.pop();
			less_than_median.push(val);
		}
	}

	void push(ll e) {
		if(e > median()) {
			greater_than_median.push(e);
		} else {
			less_than_median.push(e);
		}
		balance();
	}

	ll get_median() {
		if(less_than_median.empty() && greater_than_median.empty()) {
			throw domain_error("El carnicero se aburre");
		}
		return median();
	}
};

int main() {

	int N;
	while(cin >> N) {

		MedianHeap h;

		bool first = true;

		while(N--) {
			int tmp;
			cin >> tmp;

			if(tmp == 0) {

				if(first) {
					first = false;
				} else {
					cout << ' ';
				}

				try {
					ll median = h.get_median();
					cout << median;
					h.pop_median();
				} catch (exception& e) {
					cout << "ECSA";
				}
			} else {
				h.push(tmp);
			}
		}

		cout << "\n";
	}

	return 0;
}