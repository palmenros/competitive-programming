#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int N;

	while(cin >> N) {
		vector<int> aliens(N, 0);
		vector<int> defensas(N, 0);

		for(int i = 0; i < N; i++) {
			cin >> aliens[i];
		}

		for(int i = 0; i < N; i++) {
			cin >> defensas[i];
		}

		sort(aliens.begin(), aliens.end());
		sort(defensas.begin(), defensas.end());

		int index_aliens = 0, index_defensas = 0;
		int res = 0;

		while(index_aliens < N && index_defensas < N)
		{
			if(aliens[index_aliens] <= defensas[index_defensas]) {
				res++;
				index_defensas++;
				index_aliens++;
			} else {
				index_defensas++;
			}
		}

		cout << res << "\n";
	}


	return 0;
}