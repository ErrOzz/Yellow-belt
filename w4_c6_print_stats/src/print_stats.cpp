#include "print_stats.h"

#include <iostream>

void PrintStats(vector<Person> persons) {
  cout << "Median age = " << ComputeMedianAge(begin(persons), end(persons)) << endl;
  auto m_it = partition(begin(persons), end(persons), [](const Person& p) { return p.gender == Gender::FEMALE; });
  cout << "Median age for females = " << ComputeMedianAge(begin(persons), m_it) << endl;
  cout << "Median age for males = " << ComputeMedianAge(m_it, end(persons)) << endl;
  auto fuemp_it = partition(begin(persons), m_it, [](const Person& p) { return p.is_employed; });
  cout << "Median age for employed females = " << ComputeMedianAge(begin(persons), fuemp_it) << endl;
  cout << "Median age for unemployed females = " << ComputeMedianAge(fuemp_it, m_it) << endl;
  auto muemp_it = partition(m_it, end(persons), [](const Person& p) { return p.is_employed; });
  cout << "Median age for employed males = " << ComputeMedianAge(m_it, muemp_it) << endl;
  cout << "Median age for unemployed males = " << ComputeMedianAge(muemp_it, end(persons)) << endl;
}
