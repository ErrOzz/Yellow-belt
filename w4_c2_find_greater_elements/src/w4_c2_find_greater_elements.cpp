#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

//template <typename T>
//vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
//  auto border_it = find_if(begin(elements), end(elements), [&border](const T& element) { return element > border; });
//  vector<T> result;
//  for ( ; border_it != end(elements); ++border_it) {
//    result.push_back(*border_it);
//  }
//  return result;
//}

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
  auto it = begin(elements);
  while (it != end(elements) && *it <= border) {
    ++it;
  }
  return {it, end(elements)};
}

int main() {
  for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
    cout << x << " ";
  }
  cout << endl;

  string to_find = "Python";
  cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
  return 0;
}
