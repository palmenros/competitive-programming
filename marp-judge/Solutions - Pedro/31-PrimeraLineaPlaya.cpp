#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

struct Edificio {
	ll start;
	ll end;

	Edificio(ll s, ll e) :
		start(s), end(e)
	{}
};


ll num_tuneles(vector<Edificio>& v)
{
	sort(v.begin(), v.end(), [](const Edificio& a, const Edificio& b){
		return a.end < b.end;
	});

	ll res = 0;
	ll i = 0;
	size_t n = v.size();

	while (i < n) 
    {
		int current_end = v[i].end;
        res++;
        
		int j = i + 1;

        if (j >= n) {
            break;
		}

        int new_start = v[j].start;

		while (current_end >= new_start) {
            j++;

            if (j >= n) {
              break;
			}

			new_start = v[j].start;
        }

        i = j;
    }

	return res;
}

int main()
{
	int N;
	
	while(cin >> N && N != 0) {
		vector<Edificio> v;
	
		while(N--) {
			ll s, e;
			cin >> s >> e;
			e--;
			v.emplace_back(s, e);
		}

		cout << num_tuneles(v) << "\n";
	}

	return 0;
}
