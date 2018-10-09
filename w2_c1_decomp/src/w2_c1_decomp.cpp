#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  string str_query;
  const map<string, QueryType> query = { {"NEW_BUS", QueryType::NewBus},
  	  	  	  	  	  	  	  	   {"BUSES_FOR_STOP", QueryType::BusesForStop},
  	  	  	  	  	  	  	  	   {"STOPS_FOR_BUS", QueryType::StopsForBus},
  	  	  	  	  	  	  	  	   {"ALL_BUSES", QueryType::AllBuses} };
  is >> str_query;
  q.type = query.at(str_query);
  switch (query.at(str_query)) {
  case QueryType::NewBus: {
	  int stops_count_ = 0;
	  is >> q.bus >> stops_count_;
	  q.stops.resize(stops_count_);
	  for (auto& stop : q.stops) {
		  is >> stop;
	  }
  }
	  break;
  case QueryType::BusesForStop:
	  is >> q.stop;
	  break;
  case QueryType::StopsForBus:
	  is >> q.bus;
	  break;
  case QueryType::AllBuses:
	  break;
  }
  return is;
}

struct BusesForStopResponse {
	bool no_stop_ = true;
	vector<string> buses_;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if (r.no_stop_) {
	  os << "No stop";
	  return os;
  }
  bool first_i = true;
  for(const auto& bus : r.buses_) {
	  if (!first_i) {
		  os << " ";
	  }
	  first_i = false;
	  os << bus;
  }
  return os;
}

struct StopsForBusResponse {
  bool no_bus_ = true;
  string bus_;
  vector<string> stops_;
  map<string, vector<string>> stop_to_buses_;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if (r.no_bus_) {
	os << "No bus";
	return os;
  }
  bool first_str = true;
  for (const auto& stop : r.stops_) {
	  if (!first_str) {
		  os << endl;
	  }
	  first_str = false;
	  os << "Stop ";
	  os << stop << ":";
	  if (r.stop_to_buses_.at(stop).size() == 1) {
		  os << " no interchange";
	  } else {
		  for (const auto& bus : r.stop_to_buses_.at(stop)) {
			if (bus != r.bus_) {
				os << " " << bus;
			}
		  }
	  }
  }
  return os;
}

struct AllBusesResponse {
	bool no_buses_ = true;
	map<string, vector<string>> all_buses_;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (r.no_buses_) {
	os << "No buses";
	return os;
  }
  bool first_str = true;
  for (const auto& bus_stops : r.all_buses_) {
	  if (!first_str) {
		  os << endl;
	  }
	  first_str = false;
	  os << "Bus ";
	  os << bus_stops.first << ":";
	  for (const auto& stop : bus_stops.second) {
		  os << " " << stop;
	  }
  }
  return os;
}

class BusManager {
private:
  map<string, vector<string>> buses_to_stops, stops_to_buses;

public:
  void AddBus(const string& bus, const vector<string>& stops) {
	  buses_to_stops[bus] = stops;
	  for (const string& stop : stops) {
	  stops_to_buses[stop].push_back(bus);
	  }
  }
  BusesForStopResponse GetBusesForStop(const string& stop) const {
	  BusesForStopResponse r;
	  if (stops_to_buses.count(stop) != 0) {
		  r.no_stop_ = false;
		  r.buses_ = stops_to_buses.at(stop);
	  }
	  return r;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
	  StopsForBusResponse r;
	  if (buses_to_stops.count(bus) != 0) {
		  r.no_bus_ = false;
		  r.bus_ = bus;
		  r.stops_ = buses_to_stops.at(bus);
		  r.stop_to_buses_ = stops_to_buses;
	  }
	  return r;
  }

  AllBusesResponse GetAllBuses() const {
	AllBusesResponse r;
	if (!buses_to_stops.empty()) {
		r.no_buses_ = false;
		r.all_buses_ = buses_to_stops;
	}
    return r;
  }
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
