#include <iostream>
#include <queue>

using namespace std;

struct Element {
	int n;
	int level;
};

// BFS Search
int lowestSteps(int a, int b) 
{
	bool found[9999] {false};
	queue<Element> q;

	found[a] = true;
	q.push({a, 0});

	while(true) {
		auto top = q.front();
		q.pop();

		if(top.n == b) {
			return top.level;
		}

		auto tryNumber = [&](int n) {
			//Numbers are modulo 10000
			n = n % 10000;

			if(!found[n]) {
				found[n] = true;
				q.push({n, top.level + 1});
			}
		};

		tryNumber(top.n + 1);
		tryNumber(top.n * 2);
		tryNumber(top.n / 3);
	}

}


int main()
{
	int a, b;
	while(cin >> a >> b) {
		cout << lowestSteps(a, b) << "\n";
	}

	return 0;
}
