#include <iostream>
#include <climits>

using namespace std;

using ll = long long;

int main()
{
	int N, L;
	while(cin >> N >> L)
	{
		int num = 0;
		ll last = LONG_LONG_MIN;

		while(N--) {
			ll val;
			cin >> val;

			if(val > last + L) {
				num++;
				last = val;
			}
		}

		cout << num << "\n";
	}

	return 0;
}