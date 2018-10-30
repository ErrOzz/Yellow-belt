#include <iostream>
#include <iomanip>
#include <deque>

using namespace std;

void AddToString(deque<string>& str, const string& add, const string& old) {
  if (add.front() == '*' || add.front() == '/') {
    if (old.front() == '+' || old.front() == '-') {
      str.push_front("(");
      str.push_back(")");
    }
  }
  str.push_back(" ");
  str.push_back(add);
}

int main() {
  deque<string> str = {"x"};
  int n;
  cin >> str[0] >> n;
  cin.ignore(1);
  string old;
  while (n-- > 0) {
    string stat;
    getline(cin, stat, '\n');
    AddToString(str, stat, old);
    old = stat;
  }
  for (const auto& s : str) {
    cout << s;
  }
  return 0;
}
