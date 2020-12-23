#include <climits>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;

/*
 * No usado:
 **/

/*struct Actividad {
	ll c;
	ll f;

	Actividad(ll c, ll f) :
		c(c), f(f)
	{}
};*/

struct Punto {
	ll t;
	bool esInicio;

	ll other;
	
	Punto(ll t, bool b, ll other) :
		t(t), esInicio(b), other(other)
	{}
};

ll min_numero_amigos(vector<Punto>& v) 
{
	sort(v.begin(), v.end(), [](const Punto& a, const Punto& b){
		if(a.t == b.t) {
			if(a.esInicio == b.esInicio) {
				return a.other < b.other;
			}
			return !a.esInicio;	
		}
		return a.t < b.t;
	});

	ll res = 0;

	for(const Punto& p : v) {
		if(p.esInicio) {
			//Inicio
			if(res > 0) {
				res--;
			}
		} else {
			//Final
			res++;
		}
	}

	if(res >= 1) {
		return res - 1;
	}

	return 0;
}

int main()
{
	int N;
	while(cin >> N && N != 0) {
	
		vector<Punto> v;

		while(N--) {
			ll c, f;
			cin >> c >> f;
			v.emplace_back(c, true, f);
			v.emplace_back(f, false, c);
		}
		
		cout << min_numero_amigos(v) << "\n";
	}


	return 0;
}
