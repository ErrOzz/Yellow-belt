template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
  using eTp = typename RandomIt::value_type;
  return equal_range(range_begin, range_end, string(1, prefix), [](const eTp& lhs, const eTp& rhs) {
    return (lhs.front() < rhs.front());
  });
}
