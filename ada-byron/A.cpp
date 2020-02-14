#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>

using namespace std;

int main()
{
	int xt, yt, xi, yi;
	while (cin >> xt >> yt >> xi >> yi && !( xt == 0 && yt == 0 && xi == 0 && yi == 0)) {
		
		int dx = xt - xi;
		int dy = yt - yi;

		if (dx == 0 || dy == 0 || abs(dx) == abs(dy)) {
			cout << "SI\n";
		} else {
			cout << "NO\n";
		}

	}

	return 0;
}