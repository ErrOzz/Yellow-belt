#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//Мой вариант без использования algorithm

/*
vector<string> SplitIntoWords(const string& s) {
  auto begin_word = begin(s);
  auto end_word = begin_word;
  vector<string> result;
  while (end_word != end(s)) {
    ++end_word;
    if (*end_word == ' ' || end_word == end(s)) {
      result.push_back({begin_word, end_word});
      if (end_word != end(s)) {
        begin_word = ++end_word;
      }
    }
  }
  return result;
}
*/

//Референсный вариант

vector<string> SplitIntoWords(const string& str) {
  vector<string> result;
  auto str_begin = begin(str);
  const auto str_end = end(str);
  while (true) {
    auto it = find(str_begin, str_end, ' ');
    result.push_back(string(str_begin, it));
    if (it == str_end) {
      break;
    } else {
      str_begin = it + 1;
    }
  }
  return result;
}

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;

  return 0;
}
