#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <limits>

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

class Person {
public:
	void ChangeFirstName(int year, const string& first_name) {
		renamings[year].fn = first_name;
	}
	void ChangeLastName(int year, const string& last_name) {
		renamings[year].ln = last_name;
	}
	string GetFullName(int year) {
		string fname = "", lname = "";
		for (const pair<int, Renaming>& r : renamings) {
			if (r.first <= year) {
				fname = (r.second.fn.empty()) ? fname : r.second.fn;
				lname = (r.second.ln.empty()) ? lname : r.second.ln;
			} else { break; }
		}
		if (fname.empty() && lname.empty()) {
			return "Incognito";
		} else if (fname.empty()) {
			return lname + " with unknown first name";
		} else if (lname.empty()) {
			return fname + " with unknown last name";
		}
		return fname + " " + lname;
	}
private:
	struct Renaming {
		string fn = "";
		string ln = "";
	};
	map<int, Renaming> renamings;
};

void EmptyPersonTest() {
	Person p;
	AssertEqual(p.GetFullName(numeric_limits<int>::max()), "Incognito", "Empry person must return Incognito.");
}

void AddingFirstNameTest() {
	Person p;
	p.ChangeFirstName(2018, "Egor");
	AssertEqual(p.GetFullName(2018), "Egor with unknown last name", "After addig just first name.");
	AssertEqual(p.GetFullName(numeric_limits<int>::max()), "Egor with unknown last name", "Adding just one first name to the end of time.");
	AssertEqual(p.GetFullName(2017), "Incognito", "Incognito before addig just first name.");
}

void AddingLastNameTest() {
	Person p;
	p.ChangeLastName(2018, "Subbotin");
	AssertEqual(p.GetFullName(2018), "Subbotin with unknown first name", "After addig just last name.");
	AssertEqual(p.GetFullName(numeric_limits<int>::max()), "Subbotin with unknown first name", "After addig just last name to the end of time.");
	AssertEqual(p.GetFullName(2017), "Incognito", "Incognito before addig just last name.");
}

void ChangingNameTest() {
	Person p;
	p.ChangeFirstName(1979, "Egor");
	p.ChangeLastName(1979, "Subbotin");
	p.ChangeFirstName(2017, "Dart");
	p.ChangeLastName(2018, "Weider");
	AssertEqual(p.GetFullName(1978), "Incognito", "No other names changes befor initialization year.");
	AssertEqual(p.GetFullName(1979), "Egor Subbotin", "No other names changes after initialization year.");
	AssertEqual(p.GetFullName(2016), "Egor Subbotin", "Adding first and last name.");
	AssertEqual(p.GetFullName(2017), "Dart Subbotin", "Changing first name.");
	AssertEqual(p.GetFullName(2018), "Dart Weider", "Changing last name.");
	AssertEqual(p.GetFullName(numeric_limits<int>::max()), "Dart Weider", "No other names changes to the end of time.");
}

int main() {
  TestRunner runner;
  runner.RunTest(EmptyPersonTest, "Test for initialization empty person");
  runner.RunTest(AddingFirstNameTest, "Test for adding first name to empty person");
  runner.RunTest(AddingLastNameTest, "Test for adding last name to empty person");
  runner.RunTest(ChangingNameTest, "Test for changing names");
  return 0;
}
