#include <iostream>
#include <iomanip>
#include <deque>

using namespace std;

void AddToString(deque<string>& str, const string& stat) {
  str.push_front("(");
  str.push_back(") ");
  str.push_back(stat);
}

int main() {
  deque<string> str = {"x"};
	int n;
	cin >> str[0] >> n;
	cin.ignore(1);
	while (n-- > 0) {
	  string stat;
	  getline(cin, stat, '\n');
	  AddToString(str, stat);
	}
	for (const auto& s : str) {
	  cout << s;
	}
  return 0;
}

