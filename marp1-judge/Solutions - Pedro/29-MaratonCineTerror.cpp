#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

struct Pelicula {
	int comienzo;
	int final;

	Pelicula(int comienzo, int final)
		: comienzo(comienzo), final(final)
	{}

	bool operator<(const Pelicula &rhs) const {
		return final < rhs.final;
	}
};

int max_peliculas(vector<Pelicula>& v)
{
	sort(v.begin(), v.end());

	int res = 0;
	int lastEnd = INT_MIN;

	for(const Pelicula& p : v) {

		if(p.comienzo > lastEnd) {
			res++;
			lastEnd = p.final;
		}
	}

	return res;
}

int main()
{
	int N;
	while(cin >> N && N != 0) {
		vector<Pelicula> v;

		while(N--) {
			int hh, mm, d;
			char tmp;
			cin >> hh >> tmp >> mm >> d;
			v.emplace_back(hh * 60 + mm, hh*60 + mm + d + 10 - 1);
		}

		cout << max_peliculas(v) << "\n";
	}

	return 0;
}