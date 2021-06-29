#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct Point {
	int x, y;

	Point(int x, int y) : x(x), y(y)
	{}

	bool operator==(const Point& other) const {
		return x == other.x && y == other.y;
	}	

	Point operator+(const Point& other) const {
		Point res{x + other.x, y + other.y};
		return res;
	}
};

//Hash
namespace std {

  template <>
  struct hash<Point>
  {
    std::size_t operator()(const Point& k) const
    {
      using std::size_t;
      using std::hash;
	
	  auto lhs = hash<int>()(k.x);
	  auto rhs = hash<int>()(k.y);
	  lhs ^= rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2);
	  return lhs;
    }
  };

}

struct Resultado {
	int num;
	int maxTam;

	Resultado(int n, int m)
		: num(n), maxTam(m)
	{}

	Resultado() {}
};

class ManchasNegras {

	const vector<vector<bool>>& g;
	vector<vector<bool>> marcas;
	unordered_set<Point>& s;
	int currentManchas{0};
	int maxManchas{0};
	int width, height;

	Point dirs[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

private:
	
	inline bool correct(const Point& pos) {
		return pos.x >= 0 && pos.y >= 0 && pos.x < width && pos.y < height;
	}

	void calcularRecursivo(Point p)
	{
		marcas[p.x][p.y] = true;
		currentManchas++;
		maxManchas = max(currentManchas, maxManchas);
		s.erase(p);
	
		for(const auto& d : dirs) {
			auto newPoint = p + d;
			
			if(correct(newPoint) && !marcas[newPoint.x][newPoint.y] && g[newPoint.x][newPoint.y] == false) {
				calcularRecursivo(newPoint);
			}
		}

	}

public:

	ManchasNegras(const vector<vector<bool>>& grid, unordered_set<Point>& s, int width, int height) :
		g(grid),
		s(s),
		width(width),
		height(height),
		marcas(vector<vector<bool>>( width, vector<bool>(height, false)))
	{}

	Resultado calcular() {
		Resultado res{0, 0};
		
		while(!s.empty()) {
			auto p = *(s.begin());
			currentManchas = 0;
			calcularRecursivo(p);
			res.num++;
		}

		res.maxTam = maxManchas;
		return res;
	}
};

int main()
{
	int width, height;

	while(cin >> height >> width) {
		
		//v[x][y]
		vector<vector<bool>> v(width, vector<bool>(height, false));
		unordered_set<Point> s;
	
		for(int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				char c;
				cin >> c;
				bool color = c == '-';

				v[x][y] = color;
				if(!color) {
					s.insert(Point{x, y});
				}
			}
		}

		ManchasNegras m{v, s, width, height};
		auto r = m.calcular();
		cout << r.num << " " << r.maxTam << "\n";
	}

	return 0;
}
