#include <iostream>
#include <cstdint>
#include <vector>
#include <set>

using namespace std;

int main() {
	int n = 0;
	cin >> n;
	vector<int> temps(n);
	int64_t sum = 0;
	for (auto& temp : temps) {
		cin >> temp;
		sum += temp;
	}
	int avg = static_cast<int>(sum / n);
	set<int> days;
	int i = 0;
	for (auto& temp : temps) {
		if (temp > avg) {
			days.insert(i);
		}
		++i;
	}
	cout << days.size() << endl;
	for (auto& day : days) {
		cout << day << " ";
	}
	return 0;

}
