#include <iostream>
#include <cstdint>
#include <limits>

using namespace std;

int main() {
	int n = 0, r = 0;
	cin >> n >> r;
	uint64_t vol = 0;
	int w = 0, h = 0, d = 0;
	for (int i = 0; i < n; ++i) {
		cin >> w >> h >> d;
		vol += static_cast<uint64_t>(w) * h * d;
	}
	cout << vol * r << endl;
	return 0;
}
