#include <iostream>
#include <set>
#include <vector>

using namespace std;

using ll = long long;

struct Tarea {
	ll comienzo;
	mutable ll fin;

	bool operator<(const Tarea& other) const {
		return comienzo < other.comienzo;
	}
};

class Multitarea {
	ll T;
	set<Tarea> s;

public:
	
	Multitarea(ll T)
		: T(T)
	{}

	bool addTarea(ll comienzo, ll fin) {
		if(comienzo >= T) {
			return false;
		}	

		//[comienzo, fin)
		
		auto [it, succeeded] = s.insert(Tarea{comienzo, fin});
		
		if(!succeeded) {
			return true;
		}

		auto next = it;
		next++;

		//Comparar con anterior
		if(it != s.begin()) {
			auto prev = it; prev--;

			if(prev->fin > comienzo) {
				return true;
			}

			if(prev->fin == comienzo) {
				s.erase(it);
				prev->fin = fin;
				it = prev;
			}
		}

		//Comparar con siguiente
		if(next != s.end()) {
			
			if(fin > next->comienzo) {
				return true;
			}

			if(fin == next->comienzo) {
				it->fin = next->fin;
				s.erase(next);
			}
		}

		return false;
	}
};


int main()
{
	ll N, M, T;

	while(cin >> N >> M >> T) {
		Multitarea m{T};
		
		bool intersects = false;

		while(N-- && !intersects) {
			ll c, f;
			cin >> c >> f;

			intersects = m.addTarea(c, f);
		}

		while(M-- && !intersects) {
			ll c, f, t;
			cin >> c >> f >> t;

			while(c < T && !intersects) {
				intersects = m.addTarea(c, f);
				c += t;
				f += t;
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
