#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

template <typename T> T Sqr (const T& i);
template <typename First, typename Second> pair<First, Second> Sqr (const pair<First, Second>& p);
template <typename T> vector<T> Sqr (vector<T> v);
template <typename Key, typename Value> map<Key, Value> Sqr (map<Key, Value> m);

template <typename T> T Sqr (const T& i) {
	return i * i;
}

template <typename First, typename Second>
pair<First, Second> Sqr (const pair<First, Second>& p) {
	return make_pair(Sqr(p.first), Sqr(p.second));
}

template <typename T>
vector<T> Sqr (vector<T> v) {
	for (auto& i : v) {
		i = Sqr(i);
	}
	return v;
}

template <typename Key, typename Value>
map<Key, Value> Sqr (map<Key, Value> m) {
	for (auto& i : m) {
		i.second = Sqr(i.second);
	}
	return m;
}

int main() {
	// Пример вызова функции
	vector<int> v = {1, 2, 3};
	cout << "vector:";
	for (int x : Sqr(v)) {
	  cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
	  cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
	return 0;
}
