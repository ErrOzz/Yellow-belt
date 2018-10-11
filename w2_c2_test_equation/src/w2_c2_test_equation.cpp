#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    } else {
    first = false;
    }
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    } else {
    first = false;
    }
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    } else {
    first = false;
    }
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template <class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint = {}) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate." << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

int GetDistinctRealRootCount(double a, double b, double c) {
	if (a == 0) {
		if (b == 0) { return 0; }
		else { return 1; }
	} else {
		auto d = (b * b) - (4 * a * c);
		if (d < 0) { return 0; }
		else if (d == 0) { return 1; }
		else { return 2; }
	}
}

void OneCfZeroTest() {
	AssertEqual(GetDistinctRealRootCount(0, 10, 189765432), 1, "First cf zero.");
	AssertEqual(GetDistinctRealRootCount(0, 65536, -10), 1, "First cf zero.");
	AssertEqual(GetDistinctRealRootCount(1, 0, 1073741824), 0, "Second cf zero.");
	AssertEqual(GetDistinctRealRootCount(2000000000, 0, -100), 2, "Second cf zero.");
	AssertEqual(GetDistinctRealRootCount(-20, 100, 0), 2, "Free cf zero.");
	AssertEqual(GetDistinctRealRootCount(2100200100, -1, 0), 2, "Free cf zero.");
}

void TwoCfsZeroTest() {
	AssertEqual(GetDistinctRealRootCount(0, 0, 65536*1024), 0, "Firt and second cfs zero.");
	AssertEqual(GetDistinctRealRootCount(0, 159726483, 0), 1, "First and free cfs zero.");
	AssertEqual(GetDistinctRealRootCount(100, 0, 0), 1, "Second and free cfs zero.");
}

void NoOneCfZeroTest() {
	AssertEqual(GetDistinctRealRootCount(0.1, 2, 812), 0, "Discriminant < 0, b > 0.");
	AssertEqual(GetDistinctRealRootCount(0.1, -2, 812), 0, "Discriminant < 0, b < 0.");
	AssertEqual(GetDistinctRealRootCount(5, 16, 12.8), 1, "Discriminant = 0, b > 0.");
	AssertEqual(GetDistinctRealRootCount(5, -16, 12.8), 1, "Discriminant = 0, b < 0.");
	AssertEqual(GetDistinctRealRootCount(-25, 1, 3), 2, "Discriminant > 0, a < 0.");
	AssertEqual(GetDistinctRealRootCount(25, 1, -0.25), 2, "Discriminant > 0, c < 0.");
	AssertEqual(GetDistinctRealRootCount(25, 250, 25), 2, "Discriminant > 0, a, b, c > 0.");
}

int main() {
  TestRunner runner;
  runner.RunTest(OneCfZeroTest, "One coefficient is zero.");
  runner.RunTest(TwoCfsZeroTest, "Two coefficients is zero.");
  runner.RunTest(NoOneCfZeroTest, "Neither coefficient is zero.");
  return 0;
}

