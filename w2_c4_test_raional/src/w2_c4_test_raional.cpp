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
    }
    first = false;
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
    }
    first = false;
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
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
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

void Assert(bool b, const string& hint) {
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
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

class Rational {
public:
    Rational() {
        num = 0;
        den = 1;
    }

    Rational(int numerator, int denominator) {
        if (numerator == 0) {
			num = 0;
			den = 1;
		} else {
			if (denominator < 0) {
				numerator *= -1;
				denominator *= -1;
			}
			int nod = Nod(numerator, denominator);
			num = numerator / nod;
			den = denominator / nod;
		}
    }

    int Numerator() const {
        return num;
    }

    int Denominator() const {
        return den;
    }

private:
    int num;
    int den;
    int Nod(int a, int b) const {
		a = a < 0 ? -a : a;
		if (b == 0) {
			return a;
		} else {
			return Nod(b, a % b);
		}
	}
};

void DefConstrTest() {
	Rational r;
	AssertEqual(r.Numerator(), 0, "Numerator have to be zero.");
	AssertEqual(r.Denominator(), 1, "Denominator have to be one.");
}

void ReductionInConstrTest() {
	Rational r(1989, 2025);
	AssertEqual(r.Numerator(), 221, "Numerator have to be reduced.");
	AssertEqual(r.Denominator(), 225, "Denominator have to be reduced.");
}

void NegativeRationalTest() {
	Rational r(1979, -31);
	AssertEqual(r.Numerator(), -1979, "Numerator have to be negative.");
	AssertEqual(r.Denominator(), 31, "Denominator have to be positive.");
}

void PositiveRationalTest() {
	{
	Rational r(31, 12);
	AssertEqual(r.Numerator(), 31, "Numerator have to be positive.");
	AssertEqual(r.Denominator(), 12, "Denominator have to be positive.");
	}
	{
	Rational r(-31, -12);
	AssertEqual(r.Numerator(), 31, "Numerator have to be positive.");
	AssertEqual(r.Denominator(), 12, "Denominator have to be positive.");
	}
}

void ZeroRationalTest() {
	Rational r(0, 4194304);
	AssertEqual(r.Numerator(), 0, "Numerator have to be zero.");
	AssertEqual(r.Denominator(), 1, "Denominator have to be one.");
}

int main() {
  TestRunner runner;
  runner.RunTest(DefConstrTest, "Default constructor test");
  runner.RunTest(ReductionInConstrTest, "Reduction in default constructor test");
  runner.RunTest(NegativeRationalTest, "Negative rational test");
  runner.RunTest(PositiveRationalTest, "Positive rational test");
  runner.RunTest(ZeroRationalTest, "Zero raional test");
  return 0;
}
