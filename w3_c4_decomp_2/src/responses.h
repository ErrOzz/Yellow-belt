#pragma once

#include <vector>
#include <map>
#include <string>
#include <iostream>

using namespace std;

struct BusesForStopResponse {
	vector<string> buses_;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
  string bus_;
  vector<string> stops_;
  map<string, vector<string>> stop_to_buses_;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
	map<string, vector<string>> all_buses_;
};

ostream& operator << (ostream& os, const AllBusesResponse& r);
