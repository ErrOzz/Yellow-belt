template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix) {
  using eTp = typename RandomIt::value_type;
  size_t size = prefix.size();
  return equal_range(range_begin, range_end, prefix, [&size](const eTp& lhs, const eTp& rhs) {
    return (lhs.substr(0, size) < rhs.substr(0, size));
  });
}
