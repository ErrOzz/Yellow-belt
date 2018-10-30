#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
  using eTp = typename RandomIt::value_type;
  return equal_range(range_begin, range_end, string(1, prefix), [](const eTp& lhs, const eTp& rhs) {
    return (lhs.front() < rhs.front());
  });
}

/*
template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix) {
  using eTp = typename RandomIt::value_type;
  size_t size = prefix.size();
  return equal_range(range_begin, range_end, prefix, [&size](const eTp& lhs, const eTp& rhs) {
    return (lhs.substr(0, size) < rhs.substr(0, size));
  });
}
*/
int main() {
  const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

  const auto m_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
  for (auto it = m_result.first; it != m_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;

  const auto p_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
  cout << (p_result.first - begin(sorted_strings)) << " " <<
      (p_result.second - begin(sorted_strings)) << endl;

  const auto z_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
  cout << (z_result.first - begin(sorted_strings)) << " " <<
      (z_result.second - begin(sorted_strings)) << endl;

  return 0;
}
