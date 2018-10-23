#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int n = 0;
  cin >> n;
  vector<int> v(n);
  generate(v.begin(), v.end(), [&n](){ return --n + 1; });
  do {
    for (const auto& i : v) {
      cout << i << ' ';
    }
    cout << endl;
  } while (prev_permutation(v.begin(), v.end()));

  return 0;
}
